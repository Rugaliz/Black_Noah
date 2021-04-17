#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "os_check.h"
#include "launchmethods.h"
#include <string>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
using namespace std;
string cmd = "";
string filename = "";
string ROM_path_PSX = "";
string ROM_path_Saturn = "";
string ROM_path_SNES = "";
string ROM_path_NES = "";
string ROM_path_FDS = "";
string ROM_path_N64 = "";
string ROM_path_GBC = "";
string ROM_path_GBA = "";
string ROM_path_MasterSystem = "";
string ROM_path_SEGA_CD = "";
string ROM_path_Dreamcast = "";
string ROM_path_PC_Engine_HuCards = "";
string ROM_path_PC_Engine_CDROM = "";
string ROM_path_PC_FX_CDROM = "";
string ROM_path_Genesis = "";
string ROM_path_X68k_floppy1 = "";
string ROM_path_X68k_floppy2 = "";
string ROM_path_X68k_floppy3 = "";
string ROM_path_X68k_floppy4 = "";
string ROM_path_PC88_floppy1 = "";
string ROM_path_PC88_floppy2 = "";
string ROM_path_PC88_Cassete = "";
string ROM_path_PC98_floppy1 = "";
string ROM_path_PC98_floppy2 = "";
string ROM_path_PC98_CDROM = "";
string ROM_path_PC98_HDD = "";
string ROM_path_FMMarty_floppy = "";
string ROM_path_FMMarty_CDROM = "";
string ROM_path_NGPC = "";
string ROM_path_Neo_Geo_CDz = "";
string ROM_path_MSX_Cass = "";
string ROM_path_MSX_Cart1 = "";
string ROM_path_MSX_Cart2 = "";
string ROM_path_MSX_Floppy = "";
string Shader = "";
string region_PSX = "";
string region_MegaCD = "";
string filter = "";
string region_Saturn = "";
string region_Dreamcast = "";
string region_MegaDrive = "";
string region_NES = "";
string vertical_strech = "";
string glsl_shader = "";
string Last_Directory = "/home" ;
string ROM_Dir = "/mnt/5d177ccc-1e73-4fe0-bddb-35050aa0b254/ROMs";
string Selected_File_Misc = "";
string Selected_File_NEC = "";
string Selected_File_Nintendo = "";
string Selected_File_Sega = "";
string Selected_File_Sony = "";


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
    ui->radioButton_NTSC_USA_MegaDrive->setChecked(true);   // set radiobutton of region set by default to ntsc
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

    FileExplorer = new QFileSystemModel(this);
    FileExplorer->setRootPath(QString::fromStdString(ROM_Dir));
    ui->treeViewMisc->setModel(FileExplorer);
    ui->treeViewMisc->header()->resizeSection(0 /*column index*/, 600 /*width*/);
    ui->treeViewMisc->setRootIndex(FileExplorer->setRootPath(QString::fromStdString(ROM_Dir)));
    ui->treeViewNEC->setModel(FileExplorer);
    ui->treeViewNEC->header()->resizeSection(0 /*column index*/, 600 /*width*/);
    ui->treeViewNEC->setRootIndex(FileExplorer->setRootPath(QString::fromStdString(ROM_Dir)));
    ui->treeViewNintendo->setModel(FileExplorer);
    ui->treeViewNintendo->header()->resizeSection(0 /*column index*/, 600 /*width*/);
    ui->treeViewNintendo->setRootIndex(FileExplorer->setRootPath(QString::fromStdString(ROM_Dir)));
    ui->treeViewSega->setModel(FileExplorer);
    ui->treeViewSega->header()->resizeSection(0 /*column index*/, 600 /*width*/);
    ui->treeViewSega->setRootIndex(FileExplorer->setRootPath(QString::fromStdString(ROM_Dir)));
    ui->treeViewSony->setModel(FileExplorer);
    ui->treeViewSony->header()->resizeSection(0 /*column index*/, 600 /*width*/);
    ui->treeViewSony->setRootIndex(FileExplorer->setRootPath(QString::fromStdString(ROM_Dir)));

}

// Place method and class imports after Qwidget constructor to avoid compiler errors
static LaunchMethods LM;           // Import methods to launch various systems
//static OS_Check os_Check;          // Import classes from OS_Check
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
void MainWindow::on_Chose_file_PSX_clicked()
//chosing files and saving file path (Playstation)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PSX = Selected_File_Sony;//filename.toUtf8().constData();
    Last_Directory = ROM_path_PSX;
    //QMessageBox::information(this,tr("File Name"),filename);
}

void MainWindow::on_Chose_file_X68k_floppy1_clicked()
//chosing files and saving file path (X68k)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_X68k_floppy1 = Selected_File_Misc;//filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path_X68k_floppy1;
}

void MainWindow::on_Chose_file_X68k_floppy2_clicked()
//chosing files and saving file path (X68k)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_X68k_floppy2 = Selected_File_Misc;//filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path_X68k_floppy2;
}

void MainWindow::on_Chose_file_X68k_floppy3_clicked()
//chosing files and saving file path (X68k)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_X68k_floppy3 = Selected_File_Misc; //filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path_X68k_floppy3;
}

void MainWindow::on_Chose_file_X68k_floppy4_clicked()
//chosing files and saving file path (X68k)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_X68k_floppy1 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.dim);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_X68k_floppy4 = Selected_File_Misc;//filename_X68k_floppy1.toUtf8().constData();
    Last_Directory = ROM_path_X68k_floppy4;
}

void MainWindow::on_Chose_file_FMTownsMarty_floppy_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_FMMarty_Floppy = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.fdi *.FDI *.hdm *.d88);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_FMMarty_floppy = Selected_File_Misc;//filename_FMMarty_Floppy.toUtf8().constData();
    Last_Directory = ROM_path_FMMarty_floppy;
}

void MainWindow::on_Chose_file_FMTownsMarty_CDROM_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_FMMarty_CDROM = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hunk of data (*.chd);;Disk image (*.iso);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_FMMarty_CDROM = Selected_File_Misc;//filename_FMMarty_CDROM.toUtf8().constData();
    Last_Directory = ROM_path_FMMarty_CDROM;
}

void MainWindow::on_Chose_file_NGPC_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_NGPC = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Bin files (*.bin);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_NGPC = Selected_File_Misc;//filename_NGPC.toUtf8().constData();
    Last_Directory = ROM_path_NGPC;
}

void MainWindow::on_Chose_file_NeoGeoCDz_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_Neo_Geo_CDz = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed Hunk of Data(*.chd);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_Neo_Geo_CDz = Selected_File_Misc;//filename_Neo_Geo_CDz.toUtf8().constData();
    Last_Directory = ROM_path_Neo_Geo_CDz;
}

void MainWindow::on_Chose_file_PC_Engine_HuCard_clicked()
//chosing files and saving file path (PC Engine HuCards)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zipped archive (*.zip);;HuCard files (*.pce);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC_Engine_HuCards = Selected_File_NEC;//filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
    Last_Directory = ROM_path_PC_Engine_HuCards;
}

void MainWindow::on_Chose_file_PC_Engine_CDROM_clicked()
//chosing files and saving file path (PC Engine CDROMs)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hunks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC_Engine_CDROM = Selected_File_NEC;//filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
    Last_Directory = ROM_path_PC_Engine_CDROM;
}

void MainWindow::on_Chose_file_PC_FX_CDROM_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hunks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC_FX_CDROM = Selected_File_NEC;//filename.toUtf8().constData();
    //QMessageBox::information(this,tr("File Name"),filename);
    Last_Directory = ROM_path_PC_FX_CDROM;
}

void MainWindow::on_Chose_file_PC88_floppy1_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC88_floppy1 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC88_floppy1 =  Selected_File_NEC;//filename_PC88_floppy1.toUtf8().constData();
    Last_Directory = ROM_path_PC88_floppy1;
}

void MainWindow::on_Chose_file_PC88_floppy2_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC88_floppy2 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC88_floppy2 =  Selected_File_NEC;//filename_PC88_floppy2.toUtf8().constData();
    Last_Directory = ROM_path_PC88_floppy2;
}

void MainWindow::on_Chose_file_PC88_Cassete_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC88_cassete = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Cassete image (*.d88);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC88_Cassete =  Selected_File_NEC;//filename_PC88_cassete.toUtf8().constData();
    Last_Directory = ROM_path_PC88_Cassete;
}


void MainWindow::on_Chose_file_PC98_floppy1_clicked()
//chosing files and saving file path (PC-98)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC98_floppy1 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.fdi *.fdd *.FDI *.hdm *.d88);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC98_floppy1 =  Selected_File_NEC;//filename_PC98_floppy1.toUtf8().constData();
    Last_Directory = ROM_path_PC98_floppy1;

}

void MainWindow::on_Chose_file_PC98_floppy2_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC98_floppy2 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Floppy disk image (*.fdi *.fdd *.FDI *.hdm *.d88);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC98_floppy2 =  Selected_File_NEC;//filename_PC98_floppy2.toUtf8().constData();
    Last_Directory = ROM_path_PC98_floppy2;
}

void MainWindow::on_Chose_file_PC98_CDROM_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC98_CDROM = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hunk of data (*.chd);;Disk image (*.iso);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC98_CDROM =  Selected_File_NEC;//filename_PC98_CDROM.toUtf8().constData();
    Last_Directory = ROM_path_PC98_CDROM;
}

void MainWindow::on_Chose_file_PC98_HDD_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_PC98_HDD = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Hard Disk Image (*.hdi);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_PC98_HDD =  Selected_File_NEC;//filename_PC98_HDD.toUtf8().constData();
    Last_Directory = ROM_path_PC98_HDD;
}

void MainWindow::on_Chose_file_NES_clicked()
//chosing files and saving file path (NES)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_NES = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.nes);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_NES = Selected_File_Nintendo;//filename_NES.toUtf8().constData();
    Last_Directory = ROM_path_NES;
}

void MainWindow::on_Chose_file_FamicomDisk_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_FDS = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Floppy disk files (*.fds);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_FDS = Selected_File_Nintendo;//filename_FDS.toUtf8().constData();
    Last_Directory = ROM_path_FDS;
}

void MainWindow::on_Chose_file_SNES_clicked()
//chosing files and saving file path (SNES)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_SNES = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.smc);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_SNES = Selected_File_Nintendo;//filename_SNES.toUtf8().constData();
    Last_Directory = ROM_path_SNES;
}

void MainWindow::on_Chose_file_GBC_clicked()
//chosing files and saving file path (GBC)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_GBC = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.gbc);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_GBC = Selected_File_Nintendo;//filename_GBC.toUtf8().constData();
    Last_Directory = ROM_path_GBC;
}

void MainWindow::on_Chose_file_GBAdvanced_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_GBA = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.gba);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_GBA = Selected_File_Nintendo;//filename_GBA.toUtf8().constData();
    Last_Directory = ROM_path_GBA;
}

void MainWindow::on_Chose_file_N64_clicked()
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_N64 = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.z64);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_N64 = Selected_File_Nintendo;//filename_N64.toUtf8().constData();
    Last_Directory = ROM_path_N64;
}

void MainWindow::on_Chose_file_MasterSystem_clicked()
//chosing files and saving file path (Master System)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_MasterSystem = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.sms);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_MasterSystem = Selected_File_Sega;//filename_MasterSystem.toUtf8().constData();
    Last_Directory = ROM_path_MasterSystem;
}


void MainWindow::on_Chose_file_MegaDrive_clicked()
//chosing files and saving file path (Genesis/Megadrive)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_Genesis = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Zip files (*.zip);;Cartridge files (*.md);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_Genesis = Selected_File_Sega;//filename_Genesis.toUtf8().constData();
    Last_Directory = ROM_path_Genesis;

}

void MainWindow::on_Chose_file_SEGA_CD_clicked()
//chosing files and saving file path (sega cd)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_SEGA_CD = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed Hunk of Data(*.chd);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_SEGA_CD = Selected_File_Sega;//filename_SEGA_CD.toUtf8().constData();
    Last_Directory = ROM_path_SEGA_CD;
}

void MainWindow::on_Chose_file_Saturn_clicked()
//chosing files and saving file path (Saturn)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_saturn = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_Saturn = Selected_File_Sega;//filename_saturn.toUtf8().constData();
    Last_Directory = ROM_path_Saturn;
}

void MainWindow::on_Chose_file_Dreamcast_clicked()
//chosing files and saving file path (Dreamcast)
{
//    QString QLast_Directory = QString::fromStdString(Last_Directory);
//    QString filename_Dreamcast = QFileDialog::getOpenFileName(
//                this,
//                tr("Chose Game"),
//                QLast_Directory,
//                "Compressed hundks of data (*.chd);;Cue Sheet (*.cue);;All files (*.*)"  // determines types of files and name to display in window
//                );
    ROM_path_Dreamcast = Selected_File_Sega;//filename_Dreamcast.toUtf8().constData();
    Last_Directory = ROM_path_Dreamcast;
}



void MainWindow::on_Chose_file_MSX_Cassete_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_MSX_Cass = QFileDialog::getOpenFileName(
                this,
                tr("Chose Cassete"),
                QLast_Directory,
                "Zip files(*.zip);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_MSX_Cass = filename_MSX_Cass.toUtf8().constData();
    Last_Directory = ROM_path_MSX_Cass;
}

void MainWindow::on_Chose_file_MSX_Cart1_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_MSX_Cass = QFileDialog::getOpenFileName(
                this,
                tr("Chose Cartridge"),
                QLast_Directory,
                "Zip files(*.zip);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_MSX_Cart1 = filename_MSX_Cass.toUtf8().constData();
    Last_Directory = ROM_path_MSX_Cart1;
}

void MainWindow::on_Chose_file_MSX_Cart2_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_MSX_Cass = QFileDialog::getOpenFileName(
                this,
                tr("Chose Cartridge"),
                QLast_Directory,
                "Zip files(*.zip);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_MSX_Cart2 = filename_MSX_Cass.toUtf8().constData();
    Last_Directory = ROM_path_MSX_Cart2;
}

void MainWindow::on_Chose_file_MSX_Floppy_clicked()
{
    QString QLast_Directory = QString::fromStdString(Last_Directory);
    QString filename_MSX_Cass = QFileDialog::getOpenFileName(
                this,
                tr("Chose Floppy"),
                QLast_Directory,
                "Zip files(*.zip);;All files (*.*)"  // determines types of files and name to display in window
                );
    ROM_path_MSX_Floppy = filename_MSX_Cass.toUtf8().constData();
    Last_Directory = ROM_path_MSX_Floppy;
}

// Launchers section ***###***//////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_launch_MAME_clicked()  // Launcher for MAME
{

    string option = vertical_strech + glsl_shader;
    string command = "mame" + option;
    const char *mame_Command = command.c_str();
    system(mame_Command);
}

void MainWindow::on_Launcher_Button_X68k_clicked()
{
    LM.X68k(ROM_path_X68k_floppy1, ROM_path_X68k_floppy2, ROM_path_X68k_floppy3, ROM_path_X68k_floppy4, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_clicked() // Sony Playstation
{
    if (ui->radioButton_NTSC_USA->isChecked()) {
        region_PSX = "psu";
    }
    if (ui->radioButton_PAL_EU->isChecked()) {
        region_PSX = "pse";
    }
    if (ui->radioButton_NTSC_Japan->isChecked()) {
        region_PSX = "psj";
    }
    LM.Playstation(ROM_path_PSX, vertical_strech, glsl_shader, region_PSX);    // Playstation launcher method from class launchmethods
}

void MainWindow::on_Launcher_Button_PC88_clicked()
{
    LM.PC88(ROM_path_PC88_floppy1, ROM_path_PC88_floppy2, ROM_path_PC88_Cassete, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_PC98_clicked() // PC98 launcher (NES_2 is a mistake)
{
    LM.PC98(ROM_path_PC98_HDD, ROM_path_PC98_CDROM, ROM_path_PC98_floppy1, ROM_path_PC98_floppy2, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_FMMarty_clicked() // FM Towns Marty launcher
{
    LM.FMMarty(ROM_path_FMMarty_CDROM, ROM_path_FMMarty_floppy, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_PC_Engine_clicked()
{
    LM.PC_Engine(ROM_path_PC_Engine_HuCards, ROM_path_PC_Engine_CDROM, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_PC_FX_clicked()
{
    LM.PC_FX(ROM_path_PC_FX_CDROM, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_MasterSystem_clicked()
{
    LM.MasterSystem(ROM_path_MasterSystem, vertical_strech, glsl_shader);
}


void MainWindow::on_Launcher_Button_Megadrive_clicked()
{
    if (ui->radioButton_NTSC_USA_MegaDrive->isChecked()) {
         region_MegaDrive = "genesis";
    }

    if (ui->radioButton_NTSC_Japan_MegaDrive->isChecked()) {
         region_MegaDrive = "megadrij";
    }

    LM.MegaDrive(ROM_path_Genesis, region_MegaDrive, vertical_strech, glsl_shader);
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

void MainWindow::on_Launcher_Button_FamicomDisk_clicked()
{
    LM.Nintendo_FDS(ROM_path_FDS, vertical_strech, glsl_shader);
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

void MainWindow::on_Launcher_Button_NGPcolor_clicked()
{
    LM.SNK_NGPC(ROM_path_NGPC, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_NeoGeoCDz_clicked()
{
    LM.SNK_Neo_geo_CDz(ROM_path_Neo_Geo_CDz, vertical_strech, glsl_shader);
}

void MainWindow::on_Launcher_Button_MSX_clicked()
{
    LM.M$_MSX(ROM_path_MSX_Cass, ROM_path_MSX_Cart1, ROM_path_MSX_Cart2, ROM_path_MSX_Floppy, vertical_strech, glsl_shader);
}


// Menu Bar section
void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::information(this,"About","Developed by Rugaliz 2019-2021");
}

void MainWindow::on_actionExit_triggered()
{
    close();
}



void MainWindow::on_treeViewMisc_clicked(const QModelIndex &index)
{
    QString TreeDir = FileExplorer-> fileInfo(index).absoluteFilePath();
    Selected_File_Misc = TreeDir.toUtf8().constData();
}

void MainWindow::on_treeViewNEC_clicked(const QModelIndex &index)
{
    QString TreeDir = FileExplorer-> fileInfo(index).absoluteFilePath();
    Selected_File_NEC = TreeDir.toUtf8().constData();
}

void MainWindow::on_treeViewNintendo_clicked(const QModelIndex &index)
{
    QString TreeDir = FileExplorer-> fileInfo(index).absoluteFilePath();
    Selected_File_Nintendo = TreeDir.toUtf8().constData();
}

void MainWindow::on_treeViewSega_clicked(const QModelIndex &index)
{
    QString TreeDir = FileExplorer-> fileInfo(index).absoluteFilePath();
    Selected_File_Sega = TreeDir.toUtf8().constData();
}

void MainWindow::on_treeViewSony_clicked(const QModelIndex &index)
{
    QString TreeDir = FileExplorer-> fileInfo(index).absoluteFilePath();
    Selected_File_Sony = TreeDir.toUtf8().constData();
}
