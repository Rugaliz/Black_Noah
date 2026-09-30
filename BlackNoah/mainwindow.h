#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mamelauncher.h"
#include "systems.h"
#include <QHash>
#include <QMainWindow>
#include <QSettings>
#include <array>
#include <memory>
#include <vector>

class QAbstractButton;
class QFileSystemModel;
class QLabel;
class QLineEdit;
class QMenu;
class QModelIndex;
class QRadioButton;
class QTabWidget;
class QTreeView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_launch_MAME_clicked();
    void on_actionAbout_2_triggered();
    void on_actionExit_triggered();
    void on_actionRomPath_triggered();
    void on_toggle_unevenstretch_toggled(bool checked);
    void on_toggle_shader_toggled(bool checked);

private:
    static constexpr int kVendorTabs = 6;
    static constexpr int kMaxRecent = 10;

    // User choices for one system; indexed like allSystems().
    struct SystemState {
        QStringList paths;   // one per media slot
        QString shader;
        QString region;      // MAME machine for the selected region
    };

    // Widgets of one system, looked up once by name from the .ui file.
    struct SystemWidgets {
        std::vector<QAbstractButton *> chooseButtons;
        std::vector<QRadioButton *> shaderRadios;
        std::vector<QRadioButton *> regionRadios;
    };

    struct RecentEntry {
        QString title;
        QString logName;
        QStringList args;
    };

    // setup
    void setupFileBrowser();
    void setupSystems();
    void setupMenus();
    void setupStatusBar();
    void restoreWindowState();

    // settings
    void loadSettings();
    void saveSettings();

    // per-system state <-> widgets
    void readUiState(int system);
    void applyStateToUi(int system);
    void setMedia(int system, int slot, const QString &path);
    LaunchRequest makeRequest(int system) const;
    QStringList videoArgs(const SystemSpec &spec, const SystemState &state) const;

    // launching
    void launchSystem(int system);
    void launchCurrent();
    bool ensureMameAvailable();
    bool chooseMameExecutable();
    void startMame(const QStringList &args, const QString &title, const QString &logName);
    void addRecent(const RecentEntry &entry);
    void rebuildRecentMenu();

    // file browser
    QTreeView *treeView(int vendorTab) const;
    QTabWidget *systemTabs(int vendorTab) const;
    bool selectFile(int vendorTab, const QModelIndex &index);
    int systemForTab(int vendorTab) const;
    void showBrowserMenu(int vendorTab, const QPoint &pos);
    void applyNameFilter(const QString &text);

    // status bar
    void updateStatusBar();

    template <typename T>
    T *child(const QString &name);

    std::unique_ptr<Ui::MainWindow> ui;
    QSettings m_settings;
    MameLauncher m_launcher;
    QFileSystemModel *m_fileModel = nullptr;
    QLabel *m_statusLabel = nullptr;
    QLineEdit *m_filterEdit = nullptr;
    QMenu *m_recentMenu = nullptr;

    const QList<SystemSpec> &m_specs;
    std::vector<SystemState> m_states;
    std::vector<SystemWidgets> m_widgets;
    std::array<QString, kVendorTabs> m_selectedFile;
    QHash<QString, QString> m_machineOverrides;
    QList<RecentEntry> m_recent;

    QString m_romDir;
    QString m_stretch = " -nounevenstretch";
    QString m_glslShader = " -nogl_glsl";
    QString m_mameVersion;
};

#endif // MAINWINDOW_H
