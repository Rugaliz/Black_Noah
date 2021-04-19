#include "launchmethods.h"
#include "os_tools.h"   // debuging
#include <string>
#include <iostream>
#include <regex>
static OS_Check OSC;
using namespace std;
//OS_Check os_Check;          // Import classes from OS_Check
string PS_memcard1 = "";
string PS_memcard2 = "";
string load_cd = (" -cdrm ");                              // tell mame to load files onto cd tray
string load_cassete = (" -cass ");                         // tell MAME to load cassete file into slot
string load_Cartridge = (" -cartridge ");                  // tell mame to load files onto cartridge slot
string load_Cartridge1 = (" -cart1 ");                     // tell mame to load files onto cartridge slot
string load_Cartridge2 = (" -cart2 ");                     // tell mame to load files onto cartridge slot
string load_floppy = (" -flop ");                          // tell mame to load files onto floppy tray
string load_floppy1 = (" -flop1 ");                        // tell mame to load files onto floppy tray 1
string load_floppy2 = (" -flop2 ");                        // tell mame to load files onto floppy tray 2
string load_floppy3 = (" -flop3 ");                        // tell mame to load files onto floppy tray 3
string load_floppy4 = (" -flop4 ");                        // tell mame to load files onto floppy tray 4
LaunchMethods::LaunchMethods() {}

void LaunchMethods::Playstation (string file1locale, string vertical_strech, string glsl_shader, string region) {
    string machine_cmd = "mame ";                          // run machine command linux version
    PS_memcard1 = " -memc1 ~/.mame/memcard/psx.mc1";            // command and location of memory card 1
    PS_memcard2 = " -memc2 ~/.mame/memcard/psx.mc2";            // command and location of memory card 2
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + region + PS_memcard1 + PS_memcard2 + load_cd + "\"" + file1locale + "\"" + option;
    // pass "'" before and after file path to send a proper quoted path to console
    const char *PS_Command = command.c_str();                   // convert string to prefered format
    system(PS_Command);                                         // send whole command to OS command line
}

void LaunchMethods::X68k (string ROM_path_X68k_floppy1, string ROM_path_X68k_floppy2, string ROM_path_X68k_floppy3, string ROM_path_X68k_floppy4, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame x68kxvi";                // run machine command linux version
    string floppy1_locale = ROM_path_X68k_floppy1;      // Path pointed in "Floppy1"
    string floppy2_locale = ROM_path_X68k_floppy2;      // Path pointed in "Floppy2"
    string floppy3_locale = ROM_path_X68k_floppy3;      // Path pointed in "Floppy3"
    string floppy4_locale = ROM_path_X68k_floppy4;      // Path pointed in "Floppy4"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_floppy1 + "\""+ floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + load_floppy3 + "\""+ floppy3_locale + "\"" + load_floppy4 + "\""+ floppy4_locale + "\"" + option;
    // pass "'" before and after file path to send a proper quoted path to console
    const char *X68k_command = command.c_str();
    system(X68k_command);
}

void LaunchMethods::PC88 (string ROM_path_PC88_floppy1, string ROM_path_PC88_floppy2, string ROM_path_PC88_Cassete,  string vertical_strech, string glsl_shader) {
  string machine_cmd = "mame pc8801mc ";               // pc8801mc has more ram and comes the more advanced YM2608 sound card)
  string floppy1_locale = ROM_path_PC88_floppy1;       // Path pointed in "Floppy1"
  string floppy2_locale = ROM_path_PC88_floppy2;       // Path pointed in "Floppy2"
  string option = vertical_strech + glsl_shader;
  string command = machine_cmd + load_floppy1 + "\""+ floppy1_locale + "\"" + load_floppy2 + "\"" + floppy2_locale + "\"" + load_cassete + "\"" + ROM_path_PC88_Cassete + "\""  + option;    // pass "'" before and after file path to send a proper quoted path to console
  const char *PC88_command = command.c_str();
  system(PC88_command);
}

void LaunchMethods::PC98 (string ROM_path_PC98_HDD, string ROM_path_PC98_CDROM, string ROM_path_PC98_floppy1, string ROM_path_PC98_floppy2, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame pc9821ce2";             // run machine command linux version
    string sound_card = " -cbus0 pc9801_86";           // change to board pc9801_86 which contains the improved YM2608 soudncard over the default pc9801_26
    string load_hdd = (" -hard ");                     // tell mame to load files onto emulated hard drive disk
    string HDD_locale = ROM_path_PC98_HDD;             // Path pointed in "Hard Disk"
    string CD_locale = ROM_path_PC98_CDROM;            // Path pointed in "CD_ROM"
    string floppy1_locale = ROM_path_PC98_floppy1;     // Path pointed in "Floppy1"
    string floppy2_locale = ROM_path_PC98_floppy2;     // Path pointed in "Floppy2"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + sound_card + load_floppy1 + "\"" + floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + load_cd + "\""+ CD_locale + "\"" + load_hdd + "\""+ HDD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC98_command = command.c_str();
    system(PC98_command);
}

void LaunchMethods::FMMarty (string ROM_path_FMMarty_CDROM, string ROM_path_FMMarty_floppy, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame fmtmarty";              // run machine command linux version
    string CD_locale = ROM_path_FMMarty_CDROM;         // Path pointed in "CD_ROM"
    string floppy1_locale = ROM_path_FMMarty_floppy;   // Path pointed in "Floppy"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd  + load_floppy1 + "\"" + floppy1_locale + "\"" + load_cd + "\"" + CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *FMMarty_command = command.c_str();
    system(FMMarty_command);
}

void LaunchMethods::PC_Engine (string ROM_path_PC_Engine_HuCards, string ROM_path_PC_Engine_CDROM, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame pce";                   // run machine command linux version
    string load_HuCard = (" -cart ");                  // tell mame to load files onto HuCard slot
    string HuCard_locale = ROM_path_PC_Engine_HuCards; // Path pointed in "HUCard"
    string directory;
    const size_t last_slash_idx = ROM_path_PC_Engine_CDROM.rfind('\/');
    if (string::npos != last_slash_idx)
    {
        directory = ROM_path_PC_Engine_CDROM.substr(0, last_slash_idx);
    }
//    if (std::regex_match (ROM_path_PC_Engine_CDROM, std::regex("(Japan)") )) {
//        HuCard_locale = directory + "/[BIOS] TurboGrafx CD Super System Card (USA) (v3.0).zip";
//    }
//    directory = OSC.Get_dir_from_file(ROM_path_PC_Engine_CDROM);
//    cout <<  HuCard_locale + "/[BIOS] Super CD-ROM System (Japan) (v3.0).zip" << endl;
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_HuCard + "\"" + HuCard_locale + "\"" + load_cd + "\"" + ROM_path_PC_Engine_CDROM + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC_Engine_command = command.c_str();
    system(PC_Engine_command);
}

void LaunchMethods::PC_FX (string ROM_path_PC_FX_CDROM, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame pcfx";                  // run machine command linux version
    string CD_locale = ROM_path_PC_FX_CDROM;           // Path pointed in "CD_ROM"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd  + load_cd + "\"" + CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC_FX_command = command.c_str();
    system(PC_FX_command);
}

void LaunchMethods::MasterSystem(string ROM_path_MasterSystem, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame sms";                   // run machine command linux version
    string file1locale = ROM_path_MasterSystem;        // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_Cartridge + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *MasterSystem_command = command.c_str();
    system(MasterSystem_command);
}

void LaunchMethods::MegaDrive (string ROM_path_Genesis, string region_MegaDrive,string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame ";                      // run machine command linux version
    string file1locale = ROM_path_Genesis;             // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + region_MegaDrive + load_Cartridge + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Genesis_command = command.c_str();
    system(Genesis_command);
}

void LaunchMethods::SEGA_MD_CD (string ROM_path_SEGA_CD, string vertical_strech, string glsl_shader, string region_MegaCD) {
    string machine_cmd = "mame ";                      // run machine command linux version
    string file1locale = ROM_path_SEGA_CD;             // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + region_MegaCD + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SEGA_CD_command = command.c_str();
    system(SEGA_CD_command);
}

void LaunchMethods::SEGA_Saturn (string ROM_path_Saturn, string vertical_strech, string glsl_shader, string region_Saturn) {
    string machine_cmd = "mame ";                      // run machine command linux version
    string file1locale = ROM_path_Saturn;              // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + region_Saturn + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Saturn_command = command.c_str();
    system(Saturn_command);
}

void LaunchMethods::SEGA_Dreamcast (string ROM_path_Dreamcast, string vertical_strech, string glsl_shader, string region_Dreamcast) {
    string machine_cmd = "mame ";                      // run machine command linux version
    string file1locale = ROM_path_Dreamcast;           // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + region_Dreamcast + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Dreamcast_command = command.c_str();
    system(Dreamcast_command);
}

void LaunchMethods::Nintendo_NES (string ROM_path_NES, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame nes ";                      // run machine command linux version
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd  + load_Cartridge + "\"" + ROM_path_NES + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NES_command = command.c_str();
    system(NES_command);
}

void LaunchMethods::Nintendo_FDS (string ROM_path_FDS, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame  fds";                  // run machine command linux version
    string file1locale = ROM_path_FDS;                 // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_floppy + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NES_command = command.c_str();
    system(NES_command);
}

void LaunchMethods::Nintendo_SNES (string ROM_path_SNES, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame snes";                  // run machine command linux version
    string file1locale = ROM_path_SNES;                // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_Cartridge + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SNES_command = command.c_str();
    system(SNES_command);
}

void LaunchMethods::Nintendo_64 (string ROM_path_N64, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame n64";                   // run machine command linux version
    string file1locale = ROM_path_N64;                 // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_Cartridge + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *N64_command = command.c_str();
    system(N64_command);
}

void LaunchMethods::Nintendo_GBC (string ROM_path_GBC, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame gbcolor";               // run machine command linux version
    string file1locale = ROM_path_GBC;                 // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_Cartridge + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *GBC_command = command.c_str();
    system(GBC_command);
}

void LaunchMethods::Nintendo_GBA (string ROM_path_GBA, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame gba";                   // run machine command linux version
    string file1locale = ROM_path_GBA;                 // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_Cartridge + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *GBA_command = command.c_str();
    system(GBA_command);
}

void LaunchMethods::SNK_NGPC (string ROM_path_NGPC, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame ngpc";                  // run machine command linux version
    string file1locale = ROM_path_NGPC;                // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_Cartridge + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NGPC_command = command.c_str();
    system(NGPC_command);
}

void LaunchMethods::SNK_Neo_geo_CDz (string ROM_path_Neo_Geo_CDz, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame neocdzj";               // run machine command linux version
    string file1locale = ROM_path_Neo_Geo_CDz;         // Path pointed in "ROM1"
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SNK_Neo_geo_CDz_command = command.c_str();
    system(SNK_Neo_geo_CDz_command);
}

void LaunchMethods::M$_MSX(string ROM_path_MSX_Cass, string ROM_path_MSX_Cart1, string ROM_path_MSX_Cart2, string ROM_path_MSX_Floppy, string vertical_strech, string glsl_shader) {
    string machine_cmd = "mame fsa1fx";               // Launch machine in MAME
    string option = vertical_strech + glsl_shader;
    string command = machine_cmd + load_cassete + "\"" + ROM_path_MSX_Cass + "\"" + load_Cartridge1 + "\"" + ROM_path_MSX_Cart1 + "\"" + load_Cartridge2 + "\"" + ROM_path_MSX_Cart2 + "\"" + load_floppy + "\"" + ROM_path_MSX_Floppy + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *MSX_command = command.c_str();
    system(MSX_command);
}



