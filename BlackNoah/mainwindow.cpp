#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "launchmethods.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QShortcut>
#include <QTreeView>

static const std::string SHADER_NONE         = " -bgfx_screen_chains none";
static const std::string SHADER_CRT_GEOM     = " -bgfx_screen_chains crt-geom";
static const std::string SHADER_CRT_GEOM_DLX = " -bgfx_screen_chains crt-geom-deluxe";
static const std::string SHADER_LCD_GRID     = " -bgfx_screen_chains lcd-grid";

static LaunchMethods LM;

// ── helpers ──────────────────────────────────────────────────────────────────

static bool requireFile(QWidget *parent, const std::string &path, const QString &system)
{
    if (!path.empty()) return true;
    QMessageBox::warning(parent, "No File Selected",
        QString("Please select a %1 file before launching.").arg(system));
    return false;
}

static bool requireAnyFile(QWidget *parent, std::initializer_list<const std::string *> paths,
                            const QString &system)
{
    for (const std::string *p : paths)
        if (!p->empty()) return true;
    QMessageBox::warning(parent, "No File Selected",
        QString("Please select at least one %1 file before launching.").arg(system));
    return false;
}

static void restoreShader3(QRadioButton *none, QRadioButton *crt, QRadioButton *dlx,
                           const std::string &val)
{
    if      (val == SHADER_CRT_GEOM)     crt->setChecked(true);
    else if (val == SHADER_CRT_GEOM_DLX) dlx->setChecked(true);
    else                                  none->setChecked(true);
}

// ── constructor / destructor ──────────────────────────────────────────────────

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Black Noah");

    LoadSettings();

    // Restore toggle states
    if (state.vertical_stretch == " -unevenstretch")
        ui->toggle_unevenstretch->setChecked(true);
    else {
        state.vertical_stretch = " -nounevenstretch";
        ui->toggle_unevenstretch->setChecked(false);
    }
    if (state.glsl_shader == " -gl_glsl")
        ui->toggle_shader->setChecked(true);
    else {
        state.glsl_shader = " -nogl_glsl ";
        ui->toggle_shader->setChecked(false);
    }

    restoreUI();

    // File browser — single model shared across all tabs
    FileExplorer = new QFileSystemModel(this);
    QModelIndex rootIndex = FileExplorer->setRootPath(QString::fromStdString(state.ROM_Dir));
    QTreeView *views[] = {ui->treeViewMisc, ui->treeViewNEC, ui->treeViewNintendo,
                          ui->treeViewSega, ui->treeViewSony, ui->treeViewMicrosoft};
    for (QTreeView *view : views) {
        view->setModel(FileExplorer);
        view->header()->resizeSection(0, 600);
        view->setRootIndex(rootIndex);
    }

    // Status bar
    statusLabel = new QLabel(this);
    statusBar()->addPermanentWidget(statusLabel);
    updateStatusBar();

    // Ctrl+L launches whatever system is currently visible
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+L"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::launchCurrentSystem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ── settings ──────────────────────────────────────────────────────────────────

void MainWindow::SaveSettings()
{
    QSettings settings("blacknoah.ini", QSettings::IniFormat);
    settings.beginGroup("Settings");
    settings.setValue("ROM_Dir",          QString::fromStdString(state.ROM_Dir));
    settings.setValue("Shader",           QString::fromStdString(state.glsl_shader));
    settings.setValue("Vertical_Stretch", QString::fromStdString(state.vertical_stretch));
    // Per-system shader picks
    settings.setValue("X68K_shader",      QString::fromStdString(state.X68K_shader));
    settings.setValue("PC88_shader",      QString::fromStdString(state.PC88_shader));
    settings.setValue("PC98_shader",      QString::fromStdString(state.PC98_shader));
    settings.setValue("PCe_shader",       QString::fromStdString(state.PCe_shader));
    settings.setValue("PCFX_shader",      QString::fromStdString(state.PCFX_shader));
    settings.setValue("FMTmarty_shader",  QString::fromStdString(state.FMTmarty_shader));
    settings.setValue("GBC_shader",       QString::fromStdString(state.GBC_shader));
    settings.setValue("NGPC_shader",      QString::fromStdString(state.NGPC_shader));
    settings.setValue("NGCD_shader",      QString::fromStdString(state.NGCD_shader));
    // Region picks
    settings.setValue("region_PSX",       QString::fromStdString(state.region_PSX));
    settings.setValue("region_MegaDrive", QString::fromStdString(state.region_MegaDrive));
    settings.setValue("region_MegaCD",    QString::fromStdString(state.region_MegaCD));
    settings.setValue("region_Saturn",    QString::fromStdString(state.region_Saturn));
    settings.setValue("region_Dreamcast", QString::fromStdString(state.region_Dreamcast));
    settings.endGroup();
}

void MainWindow::LoadSettings()
{
    QSettings settings("blacknoah.ini", QSettings::IniFormat);
    settings.beginGroup("Settings");
    state.ROM_Dir          = settings.value("ROM_Dir").toString().toStdString();
    state.glsl_shader      = settings.value("Shader").toString().toStdString();
    state.vertical_stretch = settings.value("Vertical_Stretch").toString().toStdString();
    // Per-system shader picks
    state.X68K_shader      = settings.value("X68K_shader").toString().toStdString();
    state.PC88_shader      = settings.value("PC88_shader").toString().toStdString();
    state.PC98_shader      = settings.value("PC98_shader").toString().toStdString();
    state.PCe_shader       = settings.value("PCe_shader").toString().toStdString();
    state.PCFX_shader      = settings.value("PCFX_shader").toString().toStdString();
    state.FMTmarty_shader  = settings.value("FMTmarty_shader").toString().toStdString();
    state.GBC_shader       = settings.value("GBC_shader").toString().toStdString();
    state.NGPC_shader      = settings.value("NGPC_shader").toString().toStdString();
    state.NGCD_shader      = settings.value("NGCD_shader").toString().toStdString();
    // Region picks
    state.region_PSX       = settings.value("region_PSX").toString().toStdString();
    state.region_MegaDrive = settings.value("region_MegaDrive").toString().toStdString();
    state.region_MegaCD    = settings.value("region_MegaCD").toString().toStdString();
    state.region_Saturn    = settings.value("region_Saturn").toString().toStdString();
    state.region_Dreamcast = settings.value("region_Dreamcast").toString().toStdString();
    settings.endGroup();
}

void MainWindow::restoreUI()
{
    // Shader radio buttons
    restoreShader3(ui->x68k_shader_none, ui->x68k_shader_CRT_geom, ui->x68k_shader_CRT_geom_deluxe, state.X68K_shader);
    restoreShader3(ui->pc88_shader_none, ui->pc88_shader_crt_geom, ui->pc88_shader_crt_geom_deluxe, state.PC88_shader);
    restoreShader3(ui->pc98_shader_none, ui->pc98_shader_crt_geom, ui->pc98_shader_crt_geom_deluxe, state.PC98_shader);
    restoreShader3(ui->pcengine_shader_none, ui->pcengine_shader_crt_geom, ui->pcengine_shader_crt_geom_deluxe, state.PCe_shader);
    restoreShader3(ui->pcfx_shader_none, ui->pcfx_shader_crt_geom, ui->pcfx_shader_crt_geom_deluxe, state.PCFX_shader);
    restoreShader3(ui->FMTownes_Marty_shader_none, ui->FMTownes_Marty_shader_crt_geom, ui->FMTownes_Marty_shader_crt_geom_deluxe, state.FMTmarty_shader);
    restoreShader3(ui->neogeocd_shader_none, ui->neogeocd_shader_crt_geom, ui->neogeocd_shader_crt_geom_deluxe, state.NGCD_shader);

    if (state.GBC_shader == SHADER_LCD_GRID) ui->gbc_shader_lcd_grid->setChecked(true);
    else                                      ui->gbc_shader_none->setChecked(true);

    if (state.NGPC_shader == SHADER_CRT_GEOM) ui->neogeopocketcolor_shader_lcd_grid->setChecked(true);
    else                                       ui->neogeopocketcolor_shader_none_2->setChecked(true);

    // Region radio buttons — default to USA if empty or unknown
    if      (state.region_PSX == "pse") ui->radioButton_PAL_EU->setChecked(true);
    else if (state.region_PSX == "psj") ui->radioButton_NTSC_Japan->setChecked(true);
    else                                 ui->radioButton_NTSC_USA->setChecked(true);

    if (state.region_MegaDrive == "megadrij") ui->radioButton_NTSC_Japan_MegaDrive->setChecked(true);
    else                                       ui->radioButton_NTSC_USA_MegaDrive->setChecked(true);

    if (state.region_MegaCD == "megacd2j") ui->radioButton_NTSC_Japan_MegaCD->setChecked(true);
    else                                    ui->radioButton_NTSC_USA_MegaCD->setChecked(true);

    if      (state.region_Saturn == "saturneu") ui->radioButton_PAL_EU_Saturn->setChecked(true);
    else if (state.region_Saturn == "saturnjp") ui->radioButton_NTSC_Japan_Saturn->setChecked(true);
    else                                         ui->radioButton_NTSC_USA_Saturn->setChecked(true);

    if      (state.region_Dreamcast == "dceu") ui->radioButton_PAL_EU_Dreamcast->setChecked(true);
    else if (state.region_Dreamcast == "dcjp") ui->radioButton_NTSC_Japan_Dreamcast->setChecked(true);
    else                                        ui->radioButton_NTSC_USA_Dreamcast->setChecked(true);
}

// ── status bar ────────────────────────────────────────────────────────────────

void MainWindow::updateStatusBar()
{
    QString romDir = state.ROM_Dir.empty()
        ? "not set"
        : QString::fromStdString(state.ROM_Dir);

    QString mameVer = "not detected";
    QProcess proc;
    proc.start("mame", {"-version"});
    if (proc.waitForFinished(500)) {
        QStringList parts = QString(proc.readAllStandardOutput()).simplified().split(' ');
        if (parts.size() >= 2) mameVer = parts[1];
    }

    statusLabel->setText(QString("  ROM Dir: %1   |   MAME: %2  ").arg(romDir, mameVer));
}

// ── Ctrl+L: launch active system ─────────────────────────────────────────────

void MainWindow::launchCurrentSystem()
{
    switch (ui->tabWidget_2->currentIndex()) {
        case 0: // Misc
            switch (ui->tabWidget->currentIndex()) {
                case 0: on_pushButton_launch_MAME_clicked();  break;
                case 1: on_Launcher_Button_X68k_clicked();    break;
                case 2: on_Launcher_Button_FMMarty_clicked(); break;
                case 3: on_Launcher_Button_NGPcolor_clicked(); break;
                case 4: on_Launcher_Button_NeoGeoCDz_clicked(); break;
            }
            break;
        case 1: // NEC
            switch (ui->tabWidget_6->currentIndex()) {
                case 0: on_Launcher_Button_PC88_clicked();       break;
                case 1: on_Launcher_Button_PC98_clicked();       break;
                case 2: on_Launcher_Button_PC_Engine_clicked();  break;
                case 3: on_Launcher_Button_PC_FX_clicked();      break;
            }
            break;
        case 2: // Nintendo
            switch (ui->tabWidget_5->currentIndex()) {
                case 0: on_Launcher_Button_NES_clicked();          break;
                case 1: on_Launcher_Button_FamicomDisk_clicked();  break;
                case 2: on_Launcher_Button_SNES_clicked();         break;
                case 3: on_Launcher_Button_N64_clicked();          break;
                case 4: on_Launcher_Button_GBC_clicked();          break;
                case 5: on_Launcher_Button_GBAdvanced_clicked();   break;
            }
            break;
        case 3: // Microsoft
            on_Launcher_Button_MSX_clicked();
            break;
        case 4: // Sega
            switch (ui->tabWidget_4->currentIndex()) {
                case 0: on_Launcher_Button_MasterSystem_clicked(); break;
                case 1: on_Launcher_Button_Megadrive_clicked();    break;
                case 2: on_Launcher_Button_SEGA_CD_clicked();      break;
                case 3: on_Launcher_Button_Saturn_clicked();       break;
                case 4: on_Launcher_Button_Dreamcast_clicked();    break;
            }
            break;
        case 5: // Sony
            on_Launcher_Button_PSX_clicked();
            break;
    }
}

void MainWindow::reportLaunchError()
{
    QMessageBox::critical(this, "Launch Failed",
        "Failed to start MAME. Make sure it is installed and available in PATH.");
}

// ── toggle handlers ───────────────────────────────────────────────────────────

void MainWindow::on_toggle_unevenstretch_changed()
{
    state.vertical_stretch = ui->toggle_unevenstretch->isChecked() ? " -unevenstretch" : " -nounevenstretch";
    SaveSettings();
}

void MainWindow::on_toggle_shader_changed()
{
    state.glsl_shader = ui->toggle_shader->isChecked() ? " -gl_glsl" : " -nogl_glsl ";
    SaveSettings();
}

// ── file selection helper ─────────────────────────────────────────────────────

void MainWindow::setRomFile(std::string &target, const std::string &source, const QString &label)
{
    target = source;
    if (!source.empty())
        statusBar()->showMessage(
            label + ": " + QFileInfo(QString::fromStdString(source)).fileName(), 3000);
}

// ── Set buttons — copy highlighted tree view file into each system slot ───────

void MainWindow::on_Chose_file_PSX_clicked()               { setRomFile(state.ROM_path_PSX,               state.Selected_File_Sony,      "PlayStation"); }
void MainWindow::on_Chose_file_X68k_floppy1_clicked()      { setRomFile(state.ROM_path_X68k_floppy1,      state.Selected_File_Misc,      "X68k Floppy 1"); }
void MainWindow::on_Chose_file_X68k_floppy2_clicked()      { setRomFile(state.ROM_path_X68k_floppy2,      state.Selected_File_Misc,      "X68k Floppy 2"); }
void MainWindow::on_Chose_file_X68k_floppy3_clicked()      { setRomFile(state.ROM_path_X68k_floppy3,      state.Selected_File_Misc,      "X68k Floppy 3"); }
void MainWindow::on_Chose_file_X68k_floppy4_clicked()      { setRomFile(state.ROM_path_X68k_floppy4,      state.Selected_File_Misc,      "X68k Floppy 4"); }
void MainWindow::on_Chose_file_FMTownsMarty_floppy_clicked(){ setRomFile(state.ROM_path_FMMarty_floppy,   state.Selected_File_Misc,      "FM Marty Floppy"); }
void MainWindow::on_Chose_file_FMTownsMarty_CDROM_clicked() { setRomFile(state.ROM_path_FMMarty_CDROM,    state.Selected_File_Misc,      "FM Marty CD-ROM"); }
void MainWindow::on_Chose_file_NGPC_clicked()              { setRomFile(state.ROM_path_NGPC,              state.Selected_File_Misc,      "Neo Geo Pocket Color"); }
void MainWindow::on_Chose_file_NeoGeoCDz_clicked()         { setRomFile(state.ROM_path_Neo_Geo_CDz,       state.Selected_File_Misc,      "Neo Geo CD"); }
void MainWindow::on_Chose_file_PC_Engine_HuCard_clicked()  { setRomFile(state.ROM_path_PC_Engine_HuCards, state.Selected_File_NEC,       "PC Engine HuCard"); }
void MainWindow::on_Chose_file_PC_Engine_CDROM_clicked()   { setRomFile(state.ROM_path_PC_Engine_CDROM,   state.Selected_File_NEC,       "PC Engine CD-ROM"); }
void MainWindow::on_Chose_file_PC_FX_CDROM_clicked()       { setRomFile(state.ROM_path_PC_FX_CDROM,       state.Selected_File_NEC,       "PC-FX CD-ROM"); }
void MainWindow::on_Chose_file_PC88_floppy1_clicked()      { setRomFile(state.ROM_path_PC88_floppy1,      state.Selected_File_NEC,       "PC-88 Floppy 1"); }
void MainWindow::on_Chose_file_PC88_floppy2_clicked()      { setRomFile(state.ROM_path_PC88_floppy2,      state.Selected_File_NEC,       "PC-88 Floppy 2"); }
void MainWindow::on_Chose_file_PC88_Cassette_clicked()     { setRomFile(state.ROM_path_PC88_Cassette,     state.Selected_File_NEC,       "PC-88 Cassette"); }
void MainWindow::on_Chose_file_PC98_floppy1_clicked()      { setRomFile(state.ROM_path_PC98_floppy1,      state.Selected_File_NEC,       "PC-98 Floppy 1"); }
void MainWindow::on_Chose_file_PC98_floppy2_clicked()      { setRomFile(state.ROM_path_PC98_floppy2,      state.Selected_File_NEC,       "PC-98 Floppy 2"); }
void MainWindow::on_Chose_file_PC98_CDROM_clicked()        { setRomFile(state.ROM_path_PC98_CDROM,        state.Selected_File_NEC,       "PC-98 CD-ROM"); }
void MainWindow::on_Chose_file_PC98_HDD_clicked()          { setRomFile(state.ROM_path_PC98_HDD,          state.Selected_File_NEC,       "PC-98 HDD"); }
void MainWindow::on_Chose_file_NES_clicked()               { setRomFile(state.ROM_path_NES,               state.Selected_File_Nintendo,  "NES"); }
void MainWindow::on_Chose_file_FamicomDisk_clicked()       { setRomFile(state.ROM_path_FDS,               state.Selected_File_Nintendo,  "Famicom Disk"); }
void MainWindow::on_Chose_file_SNES_clicked()              { setRomFile(state.ROM_path_SNES,              state.Selected_File_Nintendo,  "SNES"); }
void MainWindow::on_Chose_file_GBC_clicked()               { setRomFile(state.ROM_path_GBC,               state.Selected_File_Nintendo,  "Game Boy Color"); }
void MainWindow::on_Chose_file_GBAdvanced_clicked()        { setRomFile(state.ROM_path_GBA,               state.Selected_File_Nintendo,  "Game Boy Advance"); }
void MainWindow::on_Chose_file_N64_clicked()               { setRomFile(state.ROM_path_N64,               state.Selected_File_Nintendo,  "N64"); }
void MainWindow::on_Chose_file_MasterSystem_clicked()      { setRomFile(state.ROM_path_MasterSystem,      state.Selected_File_Sega,      "Master System"); }
void MainWindow::on_Chose_file_MegaDrive_clicked()         { setRomFile(state.ROM_path_Genesis,           state.Selected_File_Sega,      "Genesis/Mega Drive"); }
void MainWindow::on_Chose_file_SEGA_CD_clicked()           { setRomFile(state.ROM_path_SEGA_CD,           state.Selected_File_Sega,      "Sega CD"); }
void MainWindow::on_Chose_file_Saturn_clicked()            { setRomFile(state.ROM_path_Saturn,            state.Selected_File_Sega,      "Saturn"); }
void MainWindow::on_Chose_file_Dreamcast_clicked()         { setRomFile(state.ROM_path_Dreamcast,         state.Selected_File_Sega,      "Dreamcast"); }
void MainWindow::on_Chose_file_MSX_Cassette_clicked()      { setRomFile(state.ROM_path_MSX_Cass,          state.Selected_File_Microsoft, "MSX Cassette"); }
void MainWindow::on_Chose_file_MSX_Cart1_clicked()         { setRomFile(state.ROM_path_MSX_Cart1,         state.Selected_File_Microsoft, "MSX Cart 1"); }
void MainWindow::on_Chose_file_MSX_Cart2_clicked()         { setRomFile(state.ROM_path_MSX_Cart2,         state.Selected_File_Microsoft, "MSX Cart 2"); }
void MainWindow::on_Chose_file_MSX_Floppy_clicked()        { setRomFile(state.ROM_path_MSX_Floppy,        state.Selected_File_Microsoft, "MSX Floppy"); }

// ── launchers ─────────────────────────────────────────────────────────────────

void MainWindow::on_pushButton_launch_MAME_clicked()
{
    QProcess::startDetached("mame",
        QString::fromStdString(state.vertical_stretch + " " + state.glsl_shader)
            .simplified().split(' ', Qt::SkipEmptyParts));
}

void MainWindow::on_Launcher_Button_PSX_clicked()
{
    if (ui->radioButton_NTSC_USA->isChecked())   state.region_PSX = "psu";
    if (ui->radioButton_PAL_EU->isChecked())     state.region_PSX = "pse";
    if (ui->radioButton_NTSC_Japan->isChecked()) state.region_PSX = "psj";
    if (!requireFile(this, state.ROM_path_PSX, "PlayStation disc")) return;
    SaveSettings();
    if (!LM.Playstation(state.ROM_path_PSX, state.vertical_stretch, state.glsl_shader, state.region_PSX))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_X68k_clicked()
{
    if (ui->x68k_shader_none->isChecked())            state.X68K_shader = SHADER_NONE;
    if (ui->x68k_shader_CRT_geom->isChecked())        state.X68K_shader = SHADER_CRT_GEOM;
    if (ui->x68k_shader_CRT_geom_deluxe->isChecked()) state.X68K_shader = SHADER_CRT_GEOM_DLX;
    if (!requireAnyFile(this, {&state.ROM_path_X68k_floppy1, &state.ROM_path_X68k_floppy2,
                                &state.ROM_path_X68k_floppy3, &state.ROM_path_X68k_floppy4}, "X68k floppy")) return;
    SaveSettings();
    if (!LM.X68k(state.ROM_path_X68k_floppy1, state.ROM_path_X68k_floppy2,
                 state.ROM_path_X68k_floppy3, state.ROM_path_X68k_floppy4,
                 state.vertical_stretch, state.X68K_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_PC88_clicked()
{
    if (ui->pc88_shader_none->isChecked())            state.PC88_shader = SHADER_NONE;
    if (ui->pc88_shader_crt_geom->isChecked())        state.PC88_shader = SHADER_CRT_GEOM;
    if (ui->pc88_shader_crt_geom_deluxe->isChecked()) state.PC88_shader = SHADER_CRT_GEOM_DLX;
    if (!requireAnyFile(this, {&state.ROM_path_PC88_floppy1, &state.ROM_path_PC88_floppy2,
                                &state.ROM_path_PC88_Cassette}, "PC-88 media")) return;
    SaveSettings();
    if (!LM.PC88(state.ROM_path_PC88_floppy1, state.ROM_path_PC88_floppy2,
                 state.ROM_path_PC88_Cassette, state.vertical_stretch, state.PC88_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_PC98_clicked()
{
    if (ui->pc98_shader_none->isChecked())            state.PC98_shader = SHADER_NONE;
    if (ui->pc98_shader_crt_geom->isChecked())        state.PC98_shader = SHADER_CRT_GEOM;
    if (ui->pc98_shader_crt_geom_deluxe->isChecked()) state.PC98_shader = SHADER_CRT_GEOM_DLX;
    if (!requireAnyFile(this, {&state.ROM_path_PC98_floppy1, &state.ROM_path_PC98_floppy2,
                                &state.ROM_path_PC98_CDROM,   &state.ROM_path_PC98_HDD}, "PC-98 media")) return;
    SaveSettings();
    if (!LM.PC98(state.ROM_path_PC98_HDD, state.ROM_path_PC98_CDROM,
                 state.ROM_path_PC98_floppy1, state.ROM_path_PC98_floppy2,
                 state.vertical_stretch, state.PC98_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_FMMarty_clicked()
{
    if (ui->FMTownes_Marty_shader_none->isChecked())            state.FMTmarty_shader = SHADER_NONE;
    if (ui->FMTownes_Marty_shader_crt_geom->isChecked())        state.FMTmarty_shader = SHADER_CRT_GEOM;
    if (ui->FMTownes_Marty_shader_crt_geom_deluxe->isChecked()) state.FMTmarty_shader = SHADER_CRT_GEOM_DLX;
    if (!requireAnyFile(this, {&state.ROM_path_FMMarty_CDROM, &state.ROM_path_FMMarty_floppy}, "FM Marty media")) return;
    SaveSettings();
    if (!LM.FMMarty(state.ROM_path_FMMarty_CDROM, state.ROM_path_FMMarty_floppy,
                    state.vertical_stretch, state.FMTmarty_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_PC_Engine_clicked()
{
    if (ui->pcengine_shader_none->isChecked())            state.PCe_shader = SHADER_NONE;
    if (ui->pcengine_shader_crt_geom->isChecked())        state.PCe_shader = SHADER_CRT_GEOM;
    if (ui->pcengine_shader_crt_geom_deluxe->isChecked()) state.PCe_shader = SHADER_CRT_GEOM_DLX;
    if (!requireAnyFile(this, {&state.ROM_path_PC_Engine_HuCards, &state.ROM_path_PC_Engine_CDROM}, "PC Engine media")) return;
    SaveSettings();
    if (!LM.PC_Engine(state.ROM_path_PC_Engine_HuCards, state.ROM_path_PC_Engine_CDROM,
                      state.vertical_stretch, state.PCe_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_PC_FX_clicked()
{
    if (ui->pcfx_shader_none->isChecked())            state.PCFX_shader = SHADER_NONE;
    if (ui->pcfx_shader_crt_geom->isChecked())        state.PCFX_shader = SHADER_CRT_GEOM;
    if (ui->pcfx_shader_crt_geom_deluxe->isChecked()) state.PCFX_shader = SHADER_CRT_GEOM_DLX;
    if (!requireFile(this, state.ROM_path_PC_FX_CDROM, "PC-FX disc")) return;
    SaveSettings();
    if (!LM.PC_FX(state.ROM_path_PC_FX_CDROM, state.vertical_stretch, state.PCFX_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_MasterSystem_clicked()
{
    if (!requireFile(this, state.ROM_path_MasterSystem, "Master System ROM")) return;
    SaveSettings();
    if (!LM.MasterSystem(state.ROM_path_MasterSystem, state.vertical_stretch, state.glsl_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_Megadrive_clicked()
{
    if (ui->radioButton_NTSC_USA_MegaDrive->isChecked())   state.region_MegaDrive = "genesis";
    if (ui->radioButton_NTSC_Japan_MegaDrive->isChecked()) state.region_MegaDrive = "megadrij";
    if (!requireFile(this, state.ROM_path_Genesis, "Mega Drive ROM")) return;
    SaveSettings();
    if (!LM.MegaDrive(state.ROM_path_Genesis, state.region_MegaDrive, state.vertical_stretch, state.glsl_shader))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_SEGA_CD_clicked()
{
    if (ui->radioButton_NTSC_USA_MegaCD->isChecked())   state.region_MegaCD = "segacd";
    if (ui->radioButton_NTSC_Japan_MegaCD->isChecked()) state.region_MegaCD = "megacd2j";
    if (!requireFile(this, state.ROM_path_SEGA_CD, "Sega CD disc")) return;
    SaveSettings();
    if (!LM.SEGA_MD_CD(state.ROM_path_SEGA_CD, state.vertical_stretch, state.glsl_shader, state.region_MegaCD))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_Saturn_clicked()
{
    if (ui->radioButton_NTSC_USA_Saturn->isChecked())   state.region_Saturn = "saturn";
    if (ui->radioButton_PAL_EU_Saturn->isChecked())     state.region_Saturn = "saturneu";
    if (ui->radioButton_NTSC_Japan_Saturn->isChecked()) state.region_Saturn = "saturnjp";
    if (!requireFile(this, state.ROM_path_Saturn, "Saturn disc")) return;
    SaveSettings();
    if (!LM.SEGA_Saturn(state.ROM_path_Saturn, state.vertical_stretch, state.glsl_shader, state.region_Saturn))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_Dreamcast_clicked()
{
    if (ui->radioButton_NTSC_USA_Dreamcast->isChecked())   state.region_Dreamcast = "dc";
    if (ui->radioButton_PAL_EU_Dreamcast->isChecked())     state.region_Dreamcast = "dceu";
    if (ui->radioButton_NTSC_Japan_Dreamcast->isChecked()) state.region_Dreamcast = "dcjp";
    if (!requireFile(this, state.ROM_path_Dreamcast, "Dreamcast disc")) return;
    SaveSettings();
    if (!LM.SEGA_Dreamcast(state.ROM_path_Dreamcast, state.vertical_stretch, state.glsl_shader, state.region_Dreamcast))
        reportLaunchError();
}

void MainWindow::on_Launcher_Button_NES_clicked()
{
    if (!requireFile(this, state.ROM_path_NES, "NES ROM")) return;
    SaveSettings();
    if (!LM.Nintendo_NES(state.ROM_path_NES, state.vertical_stretch, state.glsl_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_FamicomDisk_clicked()
{
    if (!requireFile(this, state.ROM_path_FDS, "Famicom Disk image")) return;
    SaveSettings();
    if (!LM.Nintendo_FDS(state.ROM_path_FDS, state.vertical_stretch, state.glsl_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_SNES_clicked()
{
    if (!requireFile(this, state.ROM_path_SNES, "SNES ROM")) return;
    SaveSettings();
    if (!LM.Nintendo_SNES(state.ROM_path_SNES, state.vertical_stretch, state.glsl_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_N64_clicked()
{
    if (!requireFile(this, state.ROM_path_N64, "N64 ROM")) return;
    SaveSettings();
    if (!LM.Nintendo_64(state.ROM_path_N64, state.vertical_stretch, state.glsl_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_GBC_clicked()
{
    if (ui->gbc_shader_none->isChecked())     state.GBC_shader = SHADER_NONE;
    if (ui->gbc_shader_lcd_grid->isChecked()) state.GBC_shader = SHADER_LCD_GRID;
    if (!requireFile(this, state.ROM_path_GBC, "Game Boy Color ROM")) return;
    SaveSettings();
    if (!LM.Nintendo_GBC(state.ROM_path_GBC, state.vertical_stretch, state.GBC_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_GBAdvanced_clicked()
{
    if (!requireFile(this, state.ROM_path_GBA, "Game Boy Advance ROM")) return;
    SaveSettings();
    if (!LM.Nintendo_GBA(state.ROM_path_GBA, state.vertical_stretch, state.glsl_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_NGPcolor_clicked()
{
    if (ui->neogeopocketcolor_shader_none_2->isChecked())   state.NGPC_shader = SHADER_NONE;
    if (ui->neogeopocketcolor_shader_lcd_grid->isChecked()) state.NGPC_shader = SHADER_CRT_GEOM;
    if (!requireFile(this, state.ROM_path_NGPC, "Neo Geo Pocket Color ROM")) return;
    SaveSettings();
    if (!LM.SNK_NGPC(state.ROM_path_NGPC, state.vertical_stretch, state.NGPC_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_NeoGeoCDz_clicked()
{
    if (ui->neogeocd_shader_none->isChecked())            state.NGCD_shader = SHADER_NONE;
    if (ui->neogeocd_shader_crt_geom->isChecked())        state.NGCD_shader = SHADER_CRT_GEOM;
    if (ui->neogeocd_shader_crt_geom_deluxe->isChecked()) state.NGCD_shader = SHADER_CRT_GEOM_DLX;
    if (!requireFile(this, state.ROM_path_Neo_Geo_CDz, "Neo Geo CD disc")) return;
    SaveSettings();
    if (!LM.SNK_Neo_geo_CDz(state.ROM_path_Neo_Geo_CDz, state.vertical_stretch, state.NGCD_shader)) reportLaunchError();
}

void MainWindow::on_Launcher_Button_MSX_clicked()
{
    if (!requireAnyFile(this, {&state.ROM_path_MSX_Cass, &state.ROM_path_MSX_Cart1,
                                &state.ROM_path_MSX_Cart2, &state.ROM_path_MSX_Floppy}, "MSX media")) return;
    SaveSettings();
    if (!LM.MSX(state.ROM_path_MSX_Cass, state.ROM_path_MSX_Cart1, state.ROM_path_MSX_Cart2,
                state.ROM_path_MSX_Floppy, state.vertical_stretch, state.glsl_shader))
        reportLaunchError();
}

// ── menu bar ──────────────────────────────────────────────────────────────────

void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::information(this, "About", "Developed by Rugaliz 2019-2025");
}

void MainWindow::on_actionExit_triggered()
{
    SaveSettings();
    close();
}

void MainWindow::on_actionRomPath_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Files Directory"), "",
                                                    QFileDialog::ShowDirsOnly);
    if (dir.isEmpty()) return;
    state.ROM_Dir = dir.toStdString();
    SaveSettings();
    updateStatusBar();
    QModelIndex rootIndex = FileExplorer->setRootPath(dir);
    QTreeView *views[] = {ui->treeViewMisc, ui->treeViewNEC, ui->treeViewNintendo,
                          ui->treeViewSega, ui->treeViewSony, ui->treeViewMicrosoft};
    for (QTreeView *view : views)
        view->setRootIndex(rootIndex);
}

// ── file browser — store selection and show in status bar ────────────────────

void MainWindow::on_treeViewMisc_clicked(const QModelIndex &index)
{
    state.Selected_File_Misc = FileExplorer->fileInfo(index).absoluteFilePath().toStdString();
    statusBar()->showMessage(QString::fromStdString(state.Selected_File_Misc), 2000);
}

void MainWindow::on_treeViewNEC_clicked(const QModelIndex &index)
{
    state.Selected_File_NEC = FileExplorer->fileInfo(index).absoluteFilePath().toStdString();
    statusBar()->showMessage(QString::fromStdString(state.Selected_File_NEC), 2000);
}

void MainWindow::on_treeViewNintendo_clicked(const QModelIndex &index)
{
    state.Selected_File_Nintendo = FileExplorer->fileInfo(index).absoluteFilePath().toStdString();
    statusBar()->showMessage(QString::fromStdString(state.Selected_File_Nintendo), 2000);
}

void MainWindow::on_treeViewSega_clicked(const QModelIndex &index)
{
    state.Selected_File_Sega = FileExplorer->fileInfo(index).absoluteFilePath().toStdString();
    statusBar()->showMessage(QString::fromStdString(state.Selected_File_Sega), 2000);
}

void MainWindow::on_treeViewSony_clicked(const QModelIndex &index)
{
    state.Selected_File_Sony = FileExplorer->fileInfo(index).absoluteFilePath().toStdString();
    statusBar()->showMessage(QString::fromStdString(state.Selected_File_Sony), 2000);
}

void MainWindow::on_treeViewMicrosoft_clicked(const QModelIndex &index)
{
    state.Selected_File_Microsoft = FileExplorer->fileInfo(index).absoluteFilePath().toStdString();
    statusBar()->showMessage(QString::fromStdString(state.Selected_File_Microsoft), 2000);
}
