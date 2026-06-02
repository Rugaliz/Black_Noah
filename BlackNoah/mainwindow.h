#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QLabel>
#include <QtCore>
#include <QSettings>
#include <string>

namespace Ui {
class MainWindow;
}

struct AppState {
    std::string ROM_Dir;
    std::string vertical_stretch;
    std::string glsl_shader;

    std::string Selected_File_Misc, Selected_File_NEC, Selected_File_Nintendo;
    std::string Selected_File_Sega, Selected_File_Sony, Selected_File_Microsoft;

    std::string ROM_path_PSX, ROM_path_Saturn, ROM_path_SNES, ROM_path_NES;
    std::string ROM_path_FDS, ROM_path_N64, ROM_path_GBC, ROM_path_GBA;
    std::string ROM_path_MasterSystem, ROM_path_SEGA_CD, ROM_path_Dreamcast;
    std::string ROM_path_PC_Engine_HuCards, ROM_path_PC_Engine_CDROM, ROM_path_PC_FX_CDROM;
    std::string ROM_path_Genesis;
    std::string ROM_path_X68k_floppy1, ROM_path_X68k_floppy2;
    std::string ROM_path_X68k_floppy3, ROM_path_X68k_floppy4;
    std::string ROM_path_PC88_floppy1, ROM_path_PC88_floppy2, ROM_path_PC88_Cassette;
    std::string ROM_path_PC98_floppy1, ROM_path_PC98_floppy2, ROM_path_PC98_CDROM, ROM_path_PC98_HDD;
    std::string ROM_path_FMMarty_floppy, ROM_path_FMMarty_CDROM;
    std::string ROM_path_NGPC, ROM_path_Neo_Geo_CDz;
    std::string ROM_path_MSX_Cass, ROM_path_MSX_Cart1, ROM_path_MSX_Cart2, ROM_path_MSX_Floppy;

    std::string region_PSX, region_MegaCD, region_Saturn, region_Dreamcast, region_MegaDrive;

    std::string X68K_shader, GBC_shader, NGPC_shader, NGCD_shader;
    std::string PC88_shader, PC98_shader, PCe_shader, PCFX_shader, FMTmarty_shader;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Launcher_Button_PSX_clicked();
    void on_Chose_file_PSX_clicked();
    void on_pushButton_launch_MAME_clicked();
    void on_Launcher_Button_Saturn_clicked();
    void on_Chose_file_Saturn_clicked();
    void on_Chose_file_SNES_clicked();
    void on_Launcher_Button_SNES_clicked();
    void on_Chose_file_NES_clicked();
    void on_Launcher_Button_NES_clicked();
    void on_Chose_file_PC98_floppy1_clicked();
    void on_Chose_file_PC98_floppy2_clicked();
    void on_Chose_file_PC98_CDROM_clicked();
    void on_Launcher_Button_PC98_clicked();
    void on_actionAbout_2_triggered();
    void on_actionExit_triggered();
    void on_actionRomPath_triggered();
    void on_Chose_file_MegaDrive_clicked();
    void on_Launcher_Button_Megadrive_clicked();
    void on_Chose_file_N64_clicked();
    void on_Launcher_Button_N64_clicked();
    void on_Chose_file_PC88_floppy1_clicked();
    void on_Chose_file_PC88_floppy2_clicked();
    void on_Launcher_Button_PC88_clicked();
    void on_Chose_file_MasterSystem_clicked();
    void on_Launcher_Button_MasterSystem_clicked();
    void on_Chose_file_PC_Engine_HuCard_clicked();
    void on_Chose_file_PC_Engine_CDROM_clicked();
    void on_Launcher_Button_PC_Engine_clicked();
    void on_Chose_file_SEGA_CD_clicked();
    void on_Launcher_Button_SEGA_CD_clicked();
    void on_Chose_file_Dreamcast_clicked();
    void on_Launcher_Button_Dreamcast_clicked();
    void on_Chose_file_GBC_clicked();
    void on_Launcher_Button_GBC_clicked();
    void on_Chose_file_GBAdvanced_clicked();
    void on_Launcher_Button_GBAdvanced_clicked();
    void on_toggle_unevenstretch_changed();
    void on_toggle_shader_changed();
    void on_Chose_file_X68k_floppy1_clicked();
    void on_Chose_file_X68k_floppy2_clicked();
    void on_Chose_file_X68k_floppy3_clicked();
    void on_Chose_file_X68k_floppy4_clicked();
    void on_Launcher_Button_X68k_clicked();
    void on_Chose_file_PC88_Cassette_clicked();
    void on_Chose_file_PC98_HDD_clicked();
    void on_Chose_file_NGPC_clicked();
    void on_Launcher_Button_NGPcolor_clicked();
    void on_Chose_file_NeoGeoCDz_clicked();
    void on_Launcher_Button_NeoGeoCDz_clicked();
    void on_Chose_file_FMTownsMarty_floppy_clicked();
    void on_Chose_file_FMTownsMarty_CDROM_clicked();
    void on_Launcher_Button_FMMarty_clicked();
    void on_Chose_file_PC_FX_CDROM_clicked();
    void on_Launcher_Button_PC_FX_clicked();
    void on_Chose_file_FamicomDisk_clicked();
    void on_Launcher_Button_FamicomDisk_clicked();
    void on_Chose_file_MSX_Cassette_clicked();
    void on_Chose_file_MSX_Cart1_clicked();
    void on_Chose_file_MSX_Cart2_clicked();
    void on_Chose_file_MSX_Floppy_clicked();
    void on_Launcher_Button_MSX_clicked();
    void on_treeViewMisc_clicked(const QModelIndex &index);
    void on_treeViewNEC_clicked(const QModelIndex &index);
    void on_treeViewNintendo_clicked(const QModelIndex &index);
    void on_treeViewSega_clicked(const QModelIndex &index);
    void on_treeViewSony_clicked(const QModelIndex &index);
    void on_treeViewMicrosoft_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *FileExplorer;
    QLabel *statusLabel;
    AppState state;

    void SaveSettings();
    void LoadSettings();
    void restoreUI();
    void updateStatusBar();
    void setRomFile(std::string &target, const std::string &source, const QString &label);
    void launchCurrentSystem();
    void reportLaunchError();
};

#endif // MAINWINDOW_H
