#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "os_check.h"~
#include "launchmethods.h"
#include <string>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>

static std::string cmd="";
static std::string filename="";
static std::string ROM_path="";
static std::string ROM_path_Saturn="";
static std::string ROM_path_SNES = "";
static std::string ROM_path_NES = "";
static std::string ROM_path_N64 = "";
static std::string ROM_path_GBC = "";
static std::string ROM_path_GBA = "";
static std::string ROM_path_MasterSystem = "";
static std::string ROM_path_SEGA_CD = "";
static std::string ROM_path_Dreamcast = "";
static std::string ROM_path_PC_Engine_HuCards ="";
static std::string ROM_path_PC_Engine_CDROM ="";
static std::string ROM_path_Genesis = "";
static std::string ROM_path_X68k_floppy1 = "";
static std::string ROM_path_X68k_floppy2 = "";
static std::string ROM_path_X68k_floppy3 = "";
static std::string ROM_path_X68k_floppy4 = "";
static std::string ROM_path_PC88_floppy1 = "";
static std::string ROM_path_PC88_floppy2 = "";
static std::string ROM_path_PC88_Cassete = "";
static std::string ROM_path_PC98_floppy1 = "";
static std::string ROM_path_PC98_floppy2 = "";
static std::string ROM_path_PC98_CDROM = "";
static std::string ROM_path_PC98_HDD = "";
static std::string Shader="";
static std::string region = "";
static std::string region_MegaCD = "";
static std::string filter = "";
static std::string region_Saturn ="";
static std::string region_Dreamcast ="";
static std::string vertical_strech ="";
static std::string glsl_shader ="";
static std::string Last_Directory = "/home" ;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    Default_Settings();
    ui->setupUi(this);
    ui->toggle_unevenstretch->setChecked(false);
    ui->radioButton_NTSC_USA->setChecked(true);             // set radiobutton of region set by default to ntsc
    ui->radioButton_NTSC_USA_Saturn->setChecked(true);      // set radiobutton of region set by default to ntsc
    ui->radioButton_NTSC_USA_MegaCD->setChecked(true);      // set radiobutton of region set by default to ntsc
    ui->radioButton_NTSC_USA_Dreamcast->setChecked(true);   // set radiobutton of region set by default to ntsc
    this->setWindowTitle("Black Noah");                     // change window title

    // begin checking for toggled buttons
    if (ui->toggle_unevenstretch->isChecked()) {
         vertical_strech = " -unevenstretch";

    }
    else {
         vertical_strech = " -nounevenstretch";
    }
    if (ui->toggle_shader->isChecked()) {
         glsl_shader = " -gl_glsl";

    }
    else {
         glsl_shader = " -nogl_glsl ";
    }
    // end checking for toggeled buttons

}

// Place method and class imports after Qwidget constructor to avoid compiler errors
static LaunchMethods LM;           // Import methods to launch various systems
static OS_Check os_Check;          // Import classes from OS_Check
//static Default_Settings defSet;    //Import classes


MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_toggle_unevenstretch_changed()
{
    if (ui->toggle_unevenstretch->isChecked()) {
         vertical_strech = " -unevenstretch";

    }
    else {
         vertical_strech = " -nounevenstretch";
    }
}

void MainWindow::on_toggle_shader_changed()
{
    if (ui->toggle_shader->isChecked()) {
         glsl_shader = " -gl_glsl";

    }
    else {
         glsl_shader = " -nogl_glsl ";
    }
}

// File Chose section
void MainWindow::on_Chose_file1_clicked()
//chosing files and saving file path (Playstation)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );

    ROM_path = filename.toUtf8().constData();
    Last_Directory = ROM_path;
    //QMessageBox::information(this,tr("File Name"),filename);
}

void MainWindow::on_Chose_file_X68k_floppy1_clicked()
//chosing files and saving file path (X68k)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_X68k_floppy1 = filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_X68k_floppy2_clicked()
//chosing files and saving file path (X68k)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_X68k_floppy2 = filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_X68k_floppy3_clicked()
//chosing files and saving file path (X68k)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_X68k_floppy3 = filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_X68k_floppy4_clicked()
//chosing files and saving file path (X68k)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_X68k_floppy4 = filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_Saturn_clicked()
//chosing files and saving file path (Saturn)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_saturn = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_Saturn = filename_saturn.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename_saturn);
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_Dreamcast_clicked()
//chosing files and saving file path (Dreamcast)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_Dreamcast = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_Dreamcast = filename_Dreamcast.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC_Engine_HuCard_clicked()
//chosing files and saving file path (PC Engine HuCards)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zipped archive (*.zip);;HuCard files (*.pce);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC_Engine_HuCards = filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC_Engine_CDROM_clicked()
//chosing files and saving file path (PC Engine CDROMs)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Compressed hunks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC_Engine_CDROM = filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_SNES_clicked()
//chosing files and saving file path (SNES)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_SNES = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.smc);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_SNES = filename_SNES.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_NES_clicked()
//chosing files and saving file path (NES)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_NES = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.smc);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_NES = filename_NES.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_GBC_clicked()
//chosing files and saving file path (GBC)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_GBC = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.gbc);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_GBC = filename_GBC.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_GBAdvanced_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_GBA = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.gba);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_GBA = filename_GBA.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC88_floppy1_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC88_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC88_floppy1 = filename_PC88_floppy1.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC88_floppy2_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC88_floppy2 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC88_floppy2 = filename_PC88_floppy2.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC88_Cassete_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC88_cassete = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Cassete image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC88_Cassete = filename_PC88_cassete.toUtf8().constData();
    Last_Directory = ROM_path;
}


void MainWindow::on_Chose_file_PC98_floppy1_clicked()
//chosing files and saving file path (PC-98)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC98_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.fdi *.FDI *.hdm *.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_floppy1 = filename_PC98_floppy1.toUtf8().constData();
    Last_Directory = ROM_path;

}

void MainWindow::on_Chose_file_PC98_floppy2_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC98_floppy2 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Floppy disk image (*.fdi *.FDI *.hdm *.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_floppy2 = filename_PC98_floppy2.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC98_CDROM_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC98_CDROM = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Compressed hunk of data (*.chd);;Disk image (*.iso);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_CDROM = filename_PC98_CDROM.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_PC98_HDD_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_PC98_HDD = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Hard Disk Image (*.hdi);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_HDD = filename_PC98_HDD.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_MasterSystem_clicked()
//chosing files and saving file path (Master System)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_MasterSystem = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.sms);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_MasterSystem = filename_MasterSystem.toUtf8().constData();
    Last_Directory = ROM_path;
}


void MainWindow::on_Chose_file_MegaDrive_clicked()
//chosing files and saving file path (Genesis/Megadrive)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_Genesis = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.md);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_Genesis = filename_Genesis.toUtf8().constData();
    Last_Directory = ROM_path;

}

void MainWindow::on_Chose_file_SEGA_CD_clicked()
//chosing files and saving file path (sega cd)
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_SEGA_CD = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Compressed Hunk of Data(*.chd);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_SEGA_CD = filename_SEGA_CD.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_Chose_file_N64_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_N64 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                QLast_Directory,
                "Zip files (*.zip);;Cartridge files (*.z64);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_N64 = filename_N64.toUtf8().constData();
    Last_Directory = ROM_path;
}

void MainWindow::on_pushButton_launch_MAME_clicked()  // Launcher for MAME
{

    std::string option = vertical_strech + glsl_shader;
    std::string command = "mame" + option;
    const char *mame_Command = command.c_str();
    system(mame_Command);
}

void MainWindow::on_Launcher_Button_X68k_clicked()
{
    LM.X68k(ROM_path_X68k_floppy1, ROM_path_X68k_floppy2, ROM_path_X68k_floppy3, ROM_path_X68k_floppy4, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_clicked()
{
    if (ui->radioButton_NTSC_USA->isChecked()) {
        region = "psu";
    }
    if (ui->radioButton_PAL_EU->isChecked()) {
        region = "pse";
    }
    if (ui->radioButton_NTSC_Japan->isChecked()) {
        region = "psj";
    }
    LM.Playstation(ROM_path, vertical_strech, glsl_shader, region);    // Playstation launcher method from class launchmethods
}

void MainWindow::on_Launcher_Button_PC88_clicked()
{
    LM.PC88(ROM_path_PC88_floppy1, ROM_path_PC88_floppy2, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_PC98_clicked() // PC98 launcher (NES_2 is a mistake)
{
    LM.PC98(ROM_path_PC98_HDD, ROM_path_PC98_CDROM, ROM_path_PC98_floppy1, ROM_path_PC98_floppy2, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_PC_Engine_clicked()
{
    LM.PC_Engine(ROM_path_PC_Engine_HuCards, ROM_path_PC_Engine_CDROM, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_MasterSystem_clicked()
{
    LM.MasterSystem(ROM_path_MasterSystem, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_Megadrive_clicked()
{
    LM.MegaDrive(ROM_path_Genesis, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_SEGA_CD_clicked()
{
    if (ui->radioButton_NTSC_USA_MegaCD->isChecked()) {
         region_MegaCD = "segacd";
    }

    if (ui->radioButton_NTSC_Japan_MegaCD->isChecked()) {
         region_MegaCD = "megacd2j";
    }
    LM.SEGA_MD_CD(ROM_path_SEGA_CD, vertical_strech, glsl_shader, region_MegaCD);
}


void MainWindow::on_Launcher_Button_Saturn_clicked()
{
    if (ui->radioButton_NTSC_USA_Saturn->isChecked()) {
         region_Saturn = "saturn";
    }

    if (ui->radioButton_PAL_EU_Saturn->isChecked()) {
         region_Saturn = "saturneu";
    }

    if (ui->radioButton_NTSC_Japan_Saturn->isChecked()) {
         region_Saturn = "saturnjp";
    }
    LM.SEGA_Saturn(ROM_path_Saturn, vertical_strech, glsl_shader, region_Saturn);
}

void MainWindow::on_Launcher_Button_Dreamcast_clicked()
{
    if (ui->radioButton_NTSC_USA_Dreamcast->isChecked()) {
         region_Dreamcast = "dc";
    }

    if (ui->radioButton_PAL_EU_Dreamcast->isChecked()) {
         region_Dreamcast = "dceu";
    }

    if (ui->radioButton_NTSC_Japan_Dreamcast->isChecked()) {
         region_Dreamcast = "dcjp";
    }
    LM.SEGA_Dreamcast(ROM_path_Dreamcast, vertical_strech, glsl_shader, region_Dreamcast);
}

void MainWindow::on_Launcher_Button_NES_clicked()
{
    LM.Nintendo_NES(ROM_path_NES, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_SNES_clicked()
{
    LM.Nintendo_SNES(ROM_path_SNES, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_N64_clicked()
{
    LM.Nintendo_64(ROM_path_N64, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_GBC_clicked()
{
    LM.Nintendo_GBC(ROM_path_GBC, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_GBAdvanced_clicked()
{
    LM.Nintendo_GBA(ROM_path_GBA, vertical_strech, glsl_shader);
}


// Menu Bar section
void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::information(this,"About","Developed by Rugaliz 2019-2020");
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

