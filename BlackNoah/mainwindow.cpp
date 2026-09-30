#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractButton>
#include <QCloseEvent>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QRadioButton>
#include <QShortcut>
#include <QSignalBlocker>
#include <QStandardPaths>
#include <QTreeView>

namespace {

const QString kStretchOn  = " -unevenstretch";
const QString kStretchOff = " -nounevenstretch";
const QString kGlslOn     = " -gl_glsl";
const QString kGlslOff    = " -nogl_glsl";

// Settings live in the per-user config folder. A blacknoah.ini left next to the old
// working directory / executable is migrated on first run.
QString settingsFilePath()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(dir);
    const QString path = dir + "/blacknoah.ini";
    if (!QFile::exists(path)) {
        const QStringList legacy{QDir::current().filePath("blacknoah.ini"),
                                 QCoreApplication::applicationDirPath() + "/blacknoah.ini"};
        for (const QString &old : legacy) {
            if (QFile::exists(old) && QFile::copy(old, path))
                break;
        }
    }
    return path;
}

QString fileLabel(const QString &path)
{
    return QFileInfo(path).fileName();
}

int indexOfValue(const QList<RadioChoice> &choices, const QString &value)
{
    for (int i = 0; i < choices.size(); ++i) {
        if (choices[i].value == value)
            return i;
    }
    return -1;
}

} // namespace

template <typename T>
T *MainWindow::child(const QString &name)
{
    T *widget = findChild<T *>(name);
    if (!widget)
        qWarning("BlackNoah: widget '%s' not found in mainwindow.ui", qPrintable(name));
    return widget;
}

// ── construction ─────────────────────────────────────────────────────────────

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(std::make_unique<Ui::MainWindow>()),
    m_settings(settingsFilePath(), QSettings::IniFormat),
    m_specs(allSystems())
{
    ui->setupUi(this);
    setWindowTitle("Black Noah");

    setupSystems();
    loadSettings();

    {
        const QSignalBlocker stretchBlocker(ui->toggle_unevenstretch);
        const QSignalBlocker shaderBlocker(ui->toggle_shader);
        ui->toggle_unevenstretch->setChecked(m_stretch == kStretchOn);
        ui->toggle_shader->setChecked(m_glslShader == kGlslOn);
    }
    for (int i = 0; i < static_cast<int>(m_specs.size()); ++i)
        applyStateToUi(i);

    setupFileBrowser();
    setupMenus();
    setupStatusBar();
    restoreWindowState();

    // Ctrl+Return launches whatever system is currently visible (Ctrl+L is "Set ROM path")
    auto *shortcut = new QShortcut(QKeySequence("Ctrl+Return"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::launchCurrent);

    connect(&m_launcher, &MameLauncher::launchFailed, this, [this](const QString &message) {
        QMessageBox::critical(this, tr("Launch Failed"), message);
    });
    connect(&m_launcher, &MameLauncher::versionDetected, this, [this](const QString &version) {
        m_mameVersion = version;
        updateStatusBar();
    });
    m_launcher.queryVersion();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::setupSystems()
{
    m_states.resize(m_specs.size());
    m_widgets.resize(m_specs.size());

    for (int i = 0; i < m_specs.size(); ++i) {
        const SystemSpec &spec = m_specs[i];
        SystemState &state = m_states[i];
        SystemWidgets &widgets = m_widgets[i];

        state.paths = QStringList();
        for (int s = 0; s < spec.media.size(); ++s)
            state.paths.append(QString());
        if (!spec.shaders.isEmpty())
            state.shader = spec.shaders.first().value;
        if (!spec.regions.isEmpty())
            state.region = spec.regions.first().value;

        for (int s = 0; s < spec.media.size(); ++s) {
            auto *button = child<QAbstractButton>(spec.media[s].chooseButton);
            widgets.chooseButtons.push_back(button);
            if (!button)
                continue;
            connect(button, &QAbstractButton::clicked, this, [this, i, s] {
                const QString &selected = m_selectedFile[m_specs[i].topTab];
                if (selected.isEmpty())
                    statusBar()->showMessage(tr("Select a file in the file browser first."), 3000);
                else
                    setMedia(i, s, selected);
            });
        }
        for (const RadioChoice &choice : spec.shaders)
            widgets.shaderRadios.push_back(child<QRadioButton>(choice.radio));
        for (const RadioChoice &choice : spec.regions)
            widgets.regionRadios.push_back(child<QRadioButton>(choice.radio));

        if (auto *launch = child<QAbstractButton>(spec.launchButton))
            connect(launch, &QAbstractButton::clicked, this, [this, i] { launchSystem(i); });
    }
}

void MainWindow::setupFileBrowser()
{
    // A single model is shared by every vendor tab.
    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setNameFilterDisables(false);
    const QModelIndex rootIndex = m_fileModel->setRootPath(m_romDir);

    for (int top = 0; top < kVendorTabs; ++top) {
        QTreeView *view = treeView(top);
        view->setModel(m_fileModel);
        view->header()->resizeSection(0, 600);
        view->setRootIndex(rootIndex);
        view->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(view, &QTreeView::clicked, this, [this, top](const QModelIndex &index) {
            if (selectFile(top, index))
                statusBar()->showMessage(m_selectedFile[top], 2000);
        });
        connect(view, &QTreeView::doubleClicked, this, [this, top](const QModelIndex &index) {
            if (!selectFile(top, index))
                return;     // folders keep their default expand/collapse behaviour
            const int system = systemForTab(top);
            if (system < 0) {
                statusBar()->showMessage(tr("Open a system tab to launch this file."), 3000);
                return;
            }
            setMedia(system, 0, m_selectedFile[top]);
            launchSystem(system);
        });
        connect(view, &QWidget::customContextMenuRequested, this, [this, top](const QPoint &pos) {
            showBrowserMenu(top, pos);
        });
    }
}

void MainWindow::setupMenus()
{
    auto *chooseMame = new QAction(tr("Set MAME executable..."), this);
    connect(chooseMame, &QAction::triggered, this, &MainWindow::chooseMameExecutable);
    ui->menuFile->insertAction(ui->actionExit, chooseMame);

    m_recentMenu = new QMenu(tr("Recent"), this);
    menuBar()->insertMenu(ui->menuHelp->menuAction(), m_recentMenu);
    rebuildRecentMenu();
}

void MainWindow::setupStatusBar()
{
    m_filterEdit = new QLineEdit(this);
    m_filterEdit->setPlaceholderText(tr("Filter files..."));
    m_filterEdit->setClearButtonEnabled(true);
    m_filterEdit->setFixedWidth(200);
    connect(m_filterEdit, &QLineEdit::textChanged, this, &MainWindow::applyNameFilter);
    statusBar()->addPermanentWidget(m_filterEdit);

    m_statusLabel = new QLabel(this);
    statusBar()->addPermanentWidget(m_statusLabel);
    updateStatusBar();
}

void MainWindow::restoreWindowState()
{
    m_settings.beginGroup("Window");
    restoreGeometry(m_settings.value("geometry").toByteArray());
    const int top = m_settings.value("topTab", 0).toInt();
    if (top >= 0 && top < kVendorTabs)
        ui->tabWidget_2->setCurrentIndex(top);
    for (int i = 0; i < kVendorTabs; ++i) {
        QTabWidget *tabs = systemTabs(i);
        const int sub = m_settings.value(QString("subTab%1").arg(i), 0).toInt();
        if (sub >= 0 && sub < tabs->count())
            tabs->setCurrentIndex(sub);
    }
    m_settings.endGroup();
}

// ── settings ─────────────────────────────────────────────────────────────────

void MainWindow::loadSettings()
{
    m_settings.beginGroup("Settings");
    m_romDir = m_settings.value("ROM_Dir").toString();
    m_stretch = m_settings.value("Vertical_Stretch").toString().trimmed() == kStretchOn.trimmed()
                    ? kStretchOn : kStretchOff;
    m_glslShader = m_settings.value("Shader").toString().trimmed() == kGlslOn.trimmed()
                       ? kGlslOn : kGlslOff;

    for (int i = 0; i < m_specs.size(); ++i) {
        const SystemSpec &spec = m_specs[i];
        SystemState &state = m_states[i];

        if (!spec.shaders.isEmpty()) {
            QString shader = m_settings.value(spec.shaderKey).toString();
            // Older versions stored crt-geom for the NGPC "LCD grid" option.
            if (spec.id == "NGPC" && shader == kShaderCrtGeom)
                shader = kShaderLcdGrid;
            if (indexOfValue(spec.shaders, shader) >= 0)
                state.shader = shader;
        }
        if (!spec.regions.isEmpty()) {
            const QString region = m_settings.value(spec.regionKey).toString();
            if (indexOfValue(spec.regions, region) >= 0)
                state.region = region;
        }
    }
    m_settings.endGroup();

    m_launcher.setConfiguredPath(m_settings.value("MAME_path").toString());

    m_settings.beginGroup("Paths");
    for (int i = 0; i < m_specs.size(); ++i) {
        for (int s = 0; s < m_specs[i].media.size(); ++s) {
            const QString path = m_settings.value(m_specs[i].id + "/" + m_specs[i].media[s].id).toString();
            if (!path.isEmpty() && QFileInfo::exists(path))
                m_states[i].paths[s] = path;
        }
    }
    m_settings.endGroup();

    m_settings.beginGroup("MachineOverrides");
    for (const QString &key : m_settings.childKeys())
        m_machineOverrides.insert(key, m_settings.value(key).toString());
    m_settings.endGroup();

    const int count = m_settings.beginReadArray("Recent");
    for (int i = 0; i < count && i < kMaxRecent; ++i) {
        m_settings.setArrayIndex(i);
        RecentEntry entry;
        entry.title = m_settings.value("title").toString();
        entry.logName = m_settings.value("log").toString();
        const QJsonArray args =
            QJsonDocument::fromJson(m_settings.value("args").toString().toUtf8()).array();
        for (const QJsonValue &arg : args)
            entry.args << arg.toString();
        if (!entry.title.isEmpty() && !entry.args.isEmpty())
            m_recent.append(entry);
    }
    m_settings.endArray();
}

void MainWindow::saveSettings()
{
    m_settings.beginGroup("Settings");
    m_settings.setValue("ROM_Dir", m_romDir);
    m_settings.setValue("Shader", m_glslShader);
    m_settings.setValue("Vertical_Stretch", m_stretch);
    for (int i = 0; i < m_specs.size(); ++i) {
        const SystemSpec &spec = m_specs[i];
        if (!spec.shaders.isEmpty())
            m_settings.setValue(spec.shaderKey, m_states[i].shader);
        if (!spec.regions.isEmpty())
            m_settings.setValue(spec.regionKey, m_states[i].region);
    }
    m_settings.endGroup();

    m_settings.setValue("MAME_path", m_launcher.configuredPath());

    m_settings.beginGroup("Paths");
    for (int i = 0; i < m_specs.size(); ++i) {
        for (int s = 0; s < m_specs[i].media.size(); ++s)
            m_settings.setValue(m_specs[i].id + "/" + m_specs[i].media[s].id, m_states[i].paths[s]);
    }
    m_settings.endGroup();

    m_settings.beginWriteArray("Recent", m_recent.size());
    for (int i = 0; i < m_recent.size(); ++i) {
        m_settings.setArrayIndex(i);
        m_settings.setValue("title", m_recent[i].title);
        m_settings.setValue("log", m_recent[i].logName);
        m_settings.setValue("args", QString::fromUtf8(
            QJsonDocument(QJsonArray::fromStringList(m_recent[i].args)).toJson(QJsonDocument::Compact)));
    }
    m_settings.endArray();

    m_settings.beginGroup("Window");
    m_settings.setValue("geometry", saveGeometry());
    m_settings.setValue("topTab", ui->tabWidget_2->currentIndex());
    for (int i = 0; i < kVendorTabs; ++i)
        m_settings.setValue(QString("subTab%1").arg(i), systemTabs(i)->currentIndex());
    m_settings.endGroup();

    m_settings.sync();
}

// ── per-system state <-> widgets ─────────────────────────────────────────────

void MainWindow::readUiState(int system)
{
    const SystemSpec &spec = m_specs[system];
    SystemState &state = m_states[system];
    const SystemWidgets &widgets = m_widgets[system];

    for (int i = 0; i < spec.shaders.size(); ++i) {
        if (widgets.shaderRadios[i] && widgets.shaderRadios[i]->isChecked())
            state.shader = spec.shaders[i].value;
    }
    for (int i = 0; i < spec.regions.size(); ++i) {
        if (widgets.regionRadios[i] && widgets.regionRadios[i]->isChecked())
            state.region = spec.regions[i].value;
    }
}

void MainWindow::applyStateToUi(int system)
{
    const SystemSpec &spec = m_specs[system];
    const SystemState &state = m_states[system];
    const SystemWidgets &widgets = m_widgets[system];

    const int shader = indexOfValue(spec.shaders, state.shader);
    if (shader >= 0 && widgets.shaderRadios[shader])
        widgets.shaderRadios[shader]->setChecked(true);

    const int region = indexOfValue(spec.regions, state.region);
    if (region >= 0 && widgets.regionRadios[region])
        widgets.regionRadios[region]->setChecked(true);

    for (int s = 0; s < spec.media.size(); ++s) {
        if (widgets.chooseButtons[s] && !state.paths[s].isEmpty())
            widgets.chooseButtons[s]->setToolTip(state.paths[s]);
    }
}

void MainWindow::setMedia(int system, int slot, const QString &path)
{
    m_states[system].paths[slot] = path;
    if (QAbstractButton *button = m_widgets[system].chooseButtons[slot])
        button->setToolTip(path);
    statusBar()->showMessage(m_specs[system].media[slot].label + ": " + fileLabel(path), 3000);
}

QStringList MainWindow::videoArgs(const SystemSpec &spec, const SystemState &state) const
{
    // Systems with their own shader choice ignore the global shader toggle.
    const QString &shader = spec.shaders.isEmpty() ? m_glslShader : state.shader;
    return splitOptions(m_stretch + " " + shader);
}

LaunchRequest MainWindow::makeRequest(int system) const
{
    const SystemSpec &spec = m_specs[system];
    const SystemState &state = m_states[system];

    const QString machine = spec.regions.isEmpty() ? spec.machine : state.region;

    LaunchRequest request;
    request.machine = m_machineOverrides.value(machine, machine);
    request.fixedArgs = spec.fixedArgs;
    if (spec.extraArgs)
        request.fixedArgs += spec.extraArgs();
    for (int s = 0; s < spec.media.size(); ++s)
        request.media.append({spec.media[s].option, state.paths[s]});
    request.videoArgs = videoArgs(spec, state);
    return request;
}

// ── launching ────────────────────────────────────────────────────────────────

void MainWindow::launchSystem(int system)
{
    const SystemSpec &spec = m_specs[system];
    readUiState(system);
    const SystemState &state = m_states[system];

    QString firstFile;
    for (const QString &path : state.paths) {
        if (path.isEmpty())
            continue;
        if (!QFileInfo::exists(path)) {
            QMessageBox::warning(this, tr("File Not Found"),
                                 tr("This file no longer exists:\n%1").arg(path));
            return;
        }
        if (firstFile.isEmpty())
            firstFile = path;
    }
    if (firstFile.isEmpty()) {
        QMessageBox::warning(this, tr("No File Selected"),
            spec.media.size() == 1
                ? tr("Please select a %1 file before launching.").arg(spec.media.first().label)
                : tr("Please select at least one %1 file before launching.").arg(spec.name));
        return;
    }

    saveSettings();
    const LaunchRequest request = makeRequest(system);
    startMame(buildArguments(request), spec.name + ": " + fileLabel(firstFile), request.machine);
}

void MainWindow::launchCurrent()
{
    const int top = ui->tabWidget_2->currentIndex();
    const int system = systemForTab(top);
    if (system >= 0)
        launchSystem(system);
    else if (top == 0 && ui->tabWidget->currentIndex() == 0)
        on_pushButton_launch_MAME_clicked();
}

bool MainWindow::chooseMameExecutable()
{
    const QString path = QFileDialog::getOpenFileName(this, tr("Choose MAME executable"),
                                                      m_launcher.configuredPath());
    if (path.isEmpty())
        return false;
    m_launcher.setConfiguredPath(path);
    saveSettings();
    m_launcher.queryVersion();
    return true;
}

bool MainWindow::ensureMameAvailable()
{
    if (!m_launcher.resolvedExecutable().isEmpty())
        return true;
    const auto answer = QMessageBox::question(this, tr("MAME Not Found"),
        tr("MAME could not be found in PATH or next to BlackNoah. Do you want to locate it now?"));
    return answer == QMessageBox::Yes && chooseMameExecutable()
           && !m_launcher.resolvedExecutable().isEmpty();
}

void MainWindow::startMame(const QStringList &args, const QString &title, const QString &logName)
{
    if (!ensureMameAvailable())
        return;
    m_launcher.launch(args, logName);
    addRecent({title, logName, args});
}

void MainWindow::addRecent(const RecentEntry &entry)
{
    for (int i = m_recent.size() - 1; i >= 0; --i) {
        if (m_recent[i].args == entry.args)
            m_recent.removeAt(i);
    }
    m_recent.prepend(entry);
    while (m_recent.size() > kMaxRecent)
        m_recent.removeLast();
    rebuildRecentMenu();
}

void MainWindow::rebuildRecentMenu()
{
    m_recentMenu->clear();
    if (m_recent.isEmpty()) {
        m_recentMenu->addAction(tr("(empty)"))->setEnabled(false);
        return;
    }
    for (const RecentEntry &entry : std::as_const(m_recent)) {
        m_recentMenu->addAction(entry.title, this, [this, entry] {
            startMame(entry.args, entry.title, entry.logName);
        });
    }
    m_recentMenu->addSeparator();
    m_recentMenu->addAction(tr("Clear recent"), this, [this] {
        m_recent.clear();
        rebuildRecentMenu();
    });
}

void MainWindow::on_pushButton_launch_MAME_clicked()
{
    startMame(splitOptions(m_stretch + " " + m_glslShader), "MAME", "mame");
}

// ── toggles ──────────────────────────────────────────────────────────────────

void MainWindow::on_toggle_unevenstretch_toggled(bool checked)
{
    m_stretch = checked ? kStretchOn : kStretchOff;
    saveSettings();
}

void MainWindow::on_toggle_shader_toggled(bool checked)
{
    m_glslShader = checked ? kGlslOn : kGlslOff;
    saveSettings();
}

// ── menu bar ─────────────────────────────────────────────────────────────────

void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::information(this, tr("About"), tr("Developed by Rugaliz 2019-2025"));
}

void MainWindow::on_actionExit_triggered()
{
    close();    // closeEvent saves the settings
}

void MainWindow::on_actionRomPath_triggered()
{
    const QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Files Directory"), m_romDir,
                                                          QFileDialog::ShowDirsOnly);
    if (dir.isEmpty())
        return;
    m_romDir = dir;
    saveSettings();
    updateStatusBar();
    const QModelIndex rootIndex = m_fileModel->setRootPath(dir);
    for (int top = 0; top < kVendorTabs; ++top)
        treeView(top)->setRootIndex(rootIndex);
}

// ── file browser ─────────────────────────────────────────────────────────────

QTreeView *MainWindow::treeView(int vendorTab) const
{
    // Vendor tab order: Misc, NEC, Nintendo, Microsoft, Sega, Sony.
    const std::array<QTreeView *, kVendorTabs> views{ui->treeViewMisc, ui->treeViewNEC, ui->treeViewNintendo,
                                                     ui->treeViewMicrosoft, ui->treeViewSega, ui->treeViewSony};
    return views[vendorTab];
}

QTabWidget *MainWindow::systemTabs(int vendorTab) const
{
    const std::array<QTabWidget *, kVendorTabs> tabs{ui->tabWidget, ui->tabWidget_6, ui->tabWidget_5,
                                                     ui->tabWidget_8, ui->tabWidget_4, ui->tabWidget_3};
    return tabs[vendorTab];
}

// Directories are ignored so a stray click on a folder can't become a ROM path.
bool MainWindow::selectFile(int vendorTab, const QModelIndex &index)
{
    const QFileInfo info = m_fileModel->fileInfo(index);
    if (!info.isFile())
        return false;
    m_selectedFile[vendorTab] = info.absoluteFilePath();
    return true;
}

// Index of the system shown in the given vendor tab, or -1 (e.g. the plain MAME tab).
int MainWindow::systemForTab(int vendorTab) const
{
    const int sub = systemTabs(vendorTab)->currentIndex();
    for (int i = 0; i < m_specs.size(); ++i) {
        if (m_specs[i].topTab == vendorTab && m_specs[i].subTab == sub)
            return i;
    }
    return -1;
}

void MainWindow::showBrowserMenu(int vendorTab, const QPoint &pos)
{
    QTreeView *view = treeView(vendorTab);
    if (!selectFile(vendorTab, view->indexAt(pos)))
        return;
    const int system = systemForTab(vendorTab);
    if (system < 0)
        return;

    const SystemSpec &spec = m_specs[system];
    const QString file = m_selectedFile[vendorTab];

    QMenu menu(this);
    for (int s = 0; s < spec.media.size(); ++s)
        menu.addAction(tr("Set as %1").arg(spec.media[s].label), this, [this, system, s, file] {
            setMedia(system, s, file);
        });
    menu.addSeparator();
    menu.addAction(tr("Launch with %1").arg(spec.name), this, [this, system, file] {
        setMedia(system, 0, file);
        launchSystem(system);
    });
    menu.exec(view->viewport()->mapToGlobal(pos));
}

void MainWindow::applyNameFilter(const QString &text)
{
    m_fileModel->setNameFilters(text.isEmpty() ? QStringList() : QStringList{"*" + text + "*"});
}

// ── status bar ───────────────────────────────────────────────────────────────

void MainWindow::updateStatusBar()
{
    const QString romDir = m_romDir.isEmpty() ? tr("not set") : m_romDir;
    const QString mame = m_mameVersion.isEmpty() ? tr("not detected") : m_mameVersion;
    m_statusLabel->setText(tr("  ROM Dir: %1   |   MAME: %2  ").arg(romDir, mame));
}
