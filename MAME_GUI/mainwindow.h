#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_Launcher_Button_clicked();

    void on_Chose_file1_clicked();

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

    void on_Chose_file_PC88_Cassete_clicked();

    void on_Chose_file_PC98_HDD_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
