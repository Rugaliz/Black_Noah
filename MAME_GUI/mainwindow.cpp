#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>

static std::string PS_memcard1 ="";
static std::string PS_memcard2 ="";
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
static std::string ROM_path_PC88_floppy1 = "";
static std::string ROM_path_PC88_floppy2 = "";
static std::string ROM_path_PC98_floppy1 = "";
static std::string ROM_path_PC98_floppy2 = "";
static std::string ROM_path_PC98_CDROM = "";
static std::string CRT_Shader="";
static std::string region = "";
static std::string region_MegaCD = "";
static std::string filter = "";
static std::string region_Saturn ="";
static std::string region_Dreamcast ="";
static std::string vertical_strech ="";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toggle_unevenstretch->setChecked(false);
    ui->radioButton_NTSC_USA->setChecked(true);             // set radiobutton of region set by default to ntsc
    ui->radioButton_NTSC_USA_Saturn->setChecked(true);      // set radiobutton of region set by default to ntsc
    ui->radioButton_NTSC_USA_MegaCD->setChecked(true);      // set radiobutton of region set by default to ntsc
    ui->radioButton_NTSC_USA_Dreamcast->setChecked(true);   // set radiobutton of region set by default to ntsc
    this->setWindowTitle("Black Noah");                     // change window title


}


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

// File Chose section
// //////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_Chose_file1_clicked()
//chosing files and saving file path (Playstation)
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path = filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
}



void MainWindow::on_Chose_file_Saturn_clicked()
//chosing files and saving file path (Saturn)
{
    QString filename_saturn = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_Saturn = filename_saturn.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename_saturn);
}

void MainWindow::on_Chose_file_Dreamcast_clicked()
//chosing files and saving file path (Dreamcast)
{
    QString filename_Dreamcast = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_Dreamcast = filename_Dreamcast.toUtf8().constData();
}

void MainWindow::on_Chose_file_PC_Engine_HuCard_clicked()
//chosing files and saving file path (PC Engine HuCards)
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zipped archive (*.zip);;HuCard files (*.pce);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC_Engine_HuCards = filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
}


void MainWindow::on_Chose_file_PC_Engine_CDROM_clicked()
//chosing files and saving file path (PC Engine CDROMs)
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Compressed hunks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC_Engine_CDROM = filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
}

void MainWindow::on_Chose_file_SNES_clicked()
//chosing files and saving file path (SNES)
{
    QString filename_SNES = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.smc);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_SNES = filename_SNES.toUtf8().constData();
}



void MainWindow::on_Chose_file_NES_clicked()
//chosing files and saving file path (NES)
{
    QString filename_NES = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.smc);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_NES = filename_NES.toUtf8().constData();
}

void MainWindow::on_Chose_file_GBC_clicked()
//chosing files and saving file path (GBC)
{
    QString filename_GBC = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.gbc);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_GBC = filename_GBC.toUtf8().constData();
}

void MainWindow::on_Chose_file_GBAdvanced_clicked()
{
    QString filename_GBA = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.gba);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_GBA = filename_GBA.toUtf8().constData();
}

void MainWindow::on_Chose_file_PC88_floppy1_clicked()
{
    QString filename_PC88_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Floppy disk image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC88_floppy1 = filename_PC88_floppy1.toUtf8().constData();
}


void MainWindow::on_Chose_file_PC88_floppy2_clicked()
{
    QString filename_PC88_floppy2 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Floppy disk image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC88_floppy2 = filename_PC88_floppy2.toUtf8().constData();
}

void MainWindow::on_Chose_file_PC98_floppy1_clicked()
//chosing files and saving file path (PC-98)
{
    QString filename_PC98_floppy1 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Floppy disk image (*.fdi *.hdm .d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_floppy1 = filename_PC98_floppy1.toUtf8().constData();

}

void MainWindow::on_Chose_file_PC98_floppy2_clicked()
{
    QString filename_PC98_floppy2 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Floppy disk image (*.fdi *.hdm .d88);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_floppy2 = filename_PC98_floppy2.toUtf8().constData();
}

void MainWindow::on_Chose_file_PC98_CDROM_clicked()
{
    QString filename_PC98_CDROM = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Compressed hunk of data (*.chd);;Disk image (*.iso);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_PC98_CDROM = filename_PC98_CDROM.toUtf8().constData();
}

void MainWindow::on_Chose_file_MasterSystem_clicked()
//chosing files and saving file path (Master System)
{
    QString filename_MasterSystem = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.sms);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_MasterSystem = filename_MasterSystem.toUtf8().constData();
}


void MainWindow::on_Chose_file_MegaDrive_clicked()
//chosing files and saving file path (Genesis/Megadrive)
{
    QString filename_Genesis = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.md);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_Genesis = filename_Genesis.toUtf8().constData();

}


void MainWindow::on_Chose_file_SEGA_CD_clicked()
//chosing files and saving file path (sega cd)
{
    QString filename_SEGA_CD = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Compressed Hunk of Data(*.chd);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_SEGA_CD = filename_SEGA_CD.toUtf8().constData();
}

void MainWindow::on_Chose_file_N64_clicked()
{
    QString filename_N64 = QFileDialog::getOpenFileName(
                this,
                tr("Chose Game"),
                "/home",
                "Zip files (*.zip);;Cartridge files (*.z64);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_N64 = filename_N64.toUtf8().constData();
}


// //////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_launch_MAME_clicked()  // Launcher for MAME
{

    std::string option = vertical_strech;
    std::string command = "mame" + option;
    const char *mame_Command = command.c_str();
    system(mame_Command);
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

        std::string machine_cmd = "mame ";                  // run machine command linux version
        //std::string rompath = " -rompath roms/ ";         // assumes the drivers are placed in a "drivers" folder on the same directory as the mame executable
        std::string file1locale = ROM_path;                 // Path pointed in "ROM1"
        std::string load_cd = (" -cdrm ");                  // tell mame to load files onto cd tray
        PS_memcard1 = " -memc1 ~/.mame/memcard/psx.mc1";    // command and location of memory card 1
        PS_memcard2 = " -memc2 ~/.mame/memcard/psx.mc2";    // command and location of memory card 2
        std::string option = vertical_strech;
        std::string command = machine_cmd + region + PS_memcard1 + PS_memcard2 + load_cd + "\"" + file1locale + "\"" + option; // pass "'" before and after file path to send a proper quoted path to console
        const char *PS_Command = command.c_str();
        system(PS_Command);                                 // send whole command to OS command line

}


void MainWindow::on_Launcher_Button_PC98_2_clicked()
{
    std::string machine_cmd = "mame pc8801ma2";             // run machine command linux version
    std::string load_foppy1 = (" -flop1 ");                 // tell mame to load files onto floppy disk tray
    std::string load_floppy2 = (" -flop2 ");                // tell mame to load files onto floppy disk tray
    std::string floppy1_locale = ROM_path_PC88_floppy1;     // Path pointed in "Floppy1"
    std::string floppy2_locale = ROM_path_PC88_floppy2;     // Path pointed in "Floppy2"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_foppy1 + "\""+ floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC88_command = command.c_str();
    system(PC88_command);
}


void MainWindow::on_Launcher_Button_PC98_clicked() // PC98 launcher (NES_2 is a mistake)
{
    std::string machine_cmd = "mame pc9821ce2";             // run machine command linux version
    std::string load_foppy1 = (" -flop1 ");                 // tell mame to load files onto floppy disk tray
    std::string load_floppy2 = (" -flop2 ");                // tell mame to load files onto floppy disk tray
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string CD_locale = ROM_path_PC98_CDROM;            // Path pointed in "CD_ROM"
    std::string floppy1_locale = ROM_path_PC98_floppy1;     // Path pointed in "Floppy1"
    std::string floppy2_locale = ROM_path_PC98_floppy2;     // Path pointed in "Floppy2"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_foppy1 + "\"" + floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + load_cd + "\""+ CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC98_command = command.c_str();
    system(PC98_command);

}


void MainWindow::on_Launcher_Button_PC_Engine_clicked()
{
    std::string machine_cmd = "mame pce";                       // run machine command linux version
    std::string load_HuCard = (" -cart ");                      // tell mame to load files onto HuCard slot
    std::string load_cd = (" -cdrm ");                          // tell mame to load files onto cd tray
    std::string HuCard_locale = ROM_path_PC_Engine_HuCards;     // Path pointed in "Floppy1"
    std::string CD_locale = ROM_path_PC_Engine_CDROM;           // Path pointed in "CD_ROM"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_HuCard + "\"" + HuCard_locale + "\"" + load_cd + "\""+ CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC_Engine_command = command.c_str();
    system(PC_Engine_command);
}


void MainWindow::on_Launcher_Button_MasterSystem_clicked()
{
    std::string machine_cmd = "mame sms";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_MasterSystem;        // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *MasterSystem_command = command.c_str();
    system(MasterSystem_command);
}


void MainWindow::on_Launcher_Button_Megadrive_clicked()
{
    std::string machine_cmd = "mame genesis";               // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Genesis;             // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Genesis_command = command.c_str();
    system(Genesis_command);
}


void MainWindow::on_Launcher_Button_SEGA_CD_clicked()
{
    if (ui->radioButton_NTSC_USA_MegaCD->isChecked()) {
         region_MegaCD = "segacd";
    }

    if (ui->radioButton_NTSC_Japan_MegaCD->isChecked()) {
         region_MegaCD = "megacd2j";
    }

    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_SEGA_CD;             // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + region_MegaCD + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SEGA_CD_command = command.c_str();
    system(SEGA_CD_command);
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

    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Saturn;              // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + region_Saturn + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Saturn_command = command.c_str();
    system(Saturn_command);
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

    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Dreamcast;              // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + region_Dreamcast + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Dreamcast_command = command.c_str();
    system(Dreamcast_command);
}

void MainWindow::on_Launcher_Button_NES_clicked()
{
    std::string machine_cmd = "mame nes";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_NES;                 // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NES_command = command.c_str();
    system(NES_command);
}


void MainWindow::on_Launcher_Button_SNES_clicked()
{


    if (ui->toggle_unevenstretch->isChecked()) {
         vertical_strech = " -unevenstretch";

    }
    else {
        vertical_strech = " ";
    }
    std::string machine_cmd = "mame snes";                  // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_SNES;                // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SNES_command = command.c_str();
    system(SNES_command);

}

void MainWindow::on_Launcher_Button_N64_clicked()
{
    std::string machine_cmd = "mame n64";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_N64;                 // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *N64_command = command.c_str();
    system(N64_command);
}

void MainWindow::on_Launcher_Button_GBC_clicked()
{
    std::string machine_cmd = "mame gbcolor";               // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_GBC;                 // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *GBC_command = command.c_str();
    system(GBC_command);
}


void MainWindow::on_Launcher_Button_GBAdvanced_clicked()
{
    std::string machine_cmd = "mame gba";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_GBA;                 // Path pointed in "ROM1"
    std::string option = vertical_strech;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *GBA_command = command.c_str();
    system(GBA_command);
}


// //////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////


// Menu Bar section
void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::information(this,"About","Developed by Rugaliz 2019");
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
// //////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////






