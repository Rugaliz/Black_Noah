#include "launchmethods.h"
#include "default_settings.h"
#include "os_check.h"   // debuging
#include <string>
#include <iostream>


static Default_Settings defSet;    //Import classe default default_settings
static OS_Check os_Check;          // Import classes from OS_Check
static std::string PS_memcard1 ="";
static std::string PS_memcard2 ="";

LaunchMethods::LaunchMethods() {}

void LaunchMethods::Playstation (std::string file1locale, std::string vertical_strech, std::string glsl_shader, std::string region) {
    std::string machine_cmd = "mame ";                          // run machine command linux version
    std::string load_cd = (" -cdrm ");                          // tell mame to load files onto cd tray
    PS_memcard1 = " -memc1 ~/.mame/memcard/psx.mc1";            // command and location of memory card 1
    PS_memcard2 = " -memc2 ~/.mame/memcard/psx.mc2";            // command and location of memory card 2
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + region + PS_memcard1 + PS_memcard2 + load_cd + "\"" + file1locale + "\"" + option;
    // pass "'" before and after file path to send a proper quoted path to console
    const char *PS_Command = command.c_str();                   // convert string to prefered format
    system(PS_Command);                                         // send whole command to OS command line
}

void LaunchMethods::X68k (std::string ROM_path_X68k_floppy1, std::string ROM_path_X68k_floppy2, std::string ROM_path_X68k_floppy3, std::string ROM_path_X68k_floppy4, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame x68000";                 // run machine command linux version
    std::string load_floppy1 = (" -flop1 ");                 // tell mame to load files onto floppy disk tray 1
    std::string load_floppy2 = (" -flop2 ");                 // tell mame to load files onto floppy disk tray 2
    std::string load_floppy3 = (" -flop3 ");                 // tell mame to load files onto floppy disk tray 3
    std::string load_floppy4 = (" -flop4 ");                 // tell mame to load files onto floppy disk tray 4
    std::string floppy1_locale = ROM_path_X68k_floppy1;      // Path pointed in "Floppy1"
    std::string floppy2_locale = ROM_path_X68k_floppy2;      // Path pointed in "Floppy2"
    std::string floppy3_locale = ROM_path_X68k_floppy3;      // Path pointed in "Floppy3"
    std::string floppy4_locale = ROM_path_X68k_floppy4;      // Path pointed in "Floppy4"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_floppy1 + "\""+ floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + load_floppy3 + "\""+ floppy3_locale + "\"" + load_floppy4 + "\""+ floppy4_locale + "\"" + option;
    // pass "'" before and after file path to send a proper quoted path to console
    const char *X68k_command = command.c_str();
    system(X68k_command);
}

void LaunchMethods::PC88 (std::string ROM_path_PC88_floppy1, std::string ROM_path_PC88_floppy2, std::string vertical_strech, std::string glsl_shader) {
  std::string machine_cmd = "mame pc88va";                  // pc8801va has more ram and comes with YM2203, va2 uses the more advanced YM2608 sound card)
  std::string load_floppy1 = (" -flop1 ");                  // tell mame to load files onto floppy disk tray
  std::string load_floppy2 = (" -flop2 ");                  // tell mame to load files onto floppy disk tray
  std::string floppy1_locale = ROM_path_PC88_floppy1;       // Path pointed in "Floppy1"
  std::string floppy2_locale = ROM_path_PC88_floppy2;       // Path pointed in "Floppy2"
  std::string option = vertical_strech + glsl_shader;
  std::string command = machine_cmd + load_floppy1 + "\""+ floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
  const char *PC88_command = command.c_str();
  system(PC88_command);
}

void LaunchMethods::PC98 (std::string ROM_path_PC98_HDD, std::string ROM_path_PC98_CDROM, std::string ROM_path_PC98_floppy1, std::string ROM_path_PC98_floppy2, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame pc9821";                // run machine command linux version
    std::string sound_card = " -cbus0 pc9801_86";           // change to board pc9801_86 which contains the improved YM2608 soudncard over the default pc9801_26
    std::string load_foppy1 = (" -flop1 ");                 // tell mame to load files onto floppy disk tray
    std::string load_floppy2 = (" -flop2 ");                // tell mame to load files onto floppy disk tray
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string load_hdd = (" -hard ");                     // tell mame to load files onto emulated hard drive disk
    std::string HDD_locale = ROM_path_PC98_HDD;             // Path pointed in "Hard Disk"
    std::string CD_locale = ROM_path_PC98_CDROM;            // Path pointed in "CD_ROM"
    std::string floppy1_locale = ROM_path_PC98_floppy1;     // Path pointed in "Floppy1"
    std::string floppy2_locale = ROM_path_PC98_floppy2;     // Path pointed in "Floppy2"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + sound_card + load_foppy1 + "\"" + floppy1_locale + "\"" + load_floppy2 + "\""+ floppy2_locale + "\"" + load_cd + "\""+ CD_locale + "\"" + load_hdd + "\""+ HDD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC98_command = command.c_str();
    system(PC98_command);
}

void LaunchMethods::FMMarty (std::string ROM_path_FMMarty_CDROM, std::string ROM_path_FMMarty_floppy, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame fmtmarty";              // run machine command linux version
    std::string load_foppy1 = (" -flop ");                  // tell mame to load files onto floppy disk tray
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string CD_locale = ROM_path_FMMarty_CDROM;         // Path pointed in "CD_ROM"
    std::string floppy1_locale = ROM_path_FMMarty_floppy;   // Path pointed in "Floppy"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd  + load_foppy1 + "\"" + floppy1_locale + "\"" + load_cd + "\"" + CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *FMMarty_command = command.c_str();
    system(FMMarty_command);
}

void LaunchMethods::PC_Engine (std::string ROM_path_PC_Engine_HuCards, std::string ROM_path_PC_Engine_CDROM, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame pce";                   // run machine command linux version
    std::string load_HuCard = (" -cart ");                  // tell mame to load files onto HuCard slot
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string HuCard_locale = ROM_path_PC_Engine_HuCards; // Path pointed in "HUCard"
    std::string CD_locale = ROM_path_PC_Engine_CDROM;       // Path pointed in "CD_ROM"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_HuCard + "\"" + HuCard_locale + "\"" + load_cd + "\""+ CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC_Engine_command = command.c_str();
    system(PC_Engine_command);
}

void LaunchMethods::PC_FX (std::string ROM_path_PC_FX_CDROM, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame pcfx";                  // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string CD_locale = ROM_path_PC_FX_CDROM;           // Path pointed in "CD_ROM"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd  + load_cd + "\"" + CD_locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *PC_FX_command = command.c_str();
    system(PC_FX_command);
}

void LaunchMethods::MasterSystem(std::string ROM_path_MasterSystem, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame sms";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_MasterSystem;        // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *MasterSystem_command = command.c_str();
    system(MasterSystem_command);
}

void LaunchMethods::MegaDrive (std::string ROM_path_Genesis, std::string region_MegaDrive,std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame ";               // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Genesis;             // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + region_MegaDrive + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Genesis_command = command.c_str();
    system(Genesis_command);
}

void LaunchMethods::SEGA_MD_CD (std::string ROM_path_SEGA_CD, std::string vertical_strech, std::string glsl_shader, std::string region_MegaCD) {
    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_SEGA_CD;             // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + region_MegaCD + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SEGA_CD_command = command.c_str();
    system(SEGA_CD_command);
}

void LaunchMethods::SEGA_Saturn (std::string ROM_path_Saturn, std::string vertical_strech, std::string glsl_shader, std::string region_Saturn) {
    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Saturn;              // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + region_Saturn + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Saturn_command = command.c_str();
    system(Saturn_command);
}

void LaunchMethods::SEGA_Dreamcast (std::string ROM_path_Dreamcast, std::string vertical_strech, std::string glsl_shader, std::string region_Dreamcast) {
    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Dreamcast;           // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + region_Dreamcast + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *Dreamcast_command = command.c_str();
    system(Dreamcast_command);
}

void LaunchMethods::Nintendo_NES (std::string region_NES, std::string ROM_path_NES, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame ";                      // run machine command linux version
    std::string load_Cartridge = (" -cartridge ");          // tell mame to load files onto cartridge slot
    std::string file1locale = ROM_path_NES;                 // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + region_NES + load_Cartridge + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NES_command = command.c_str();
    system(NES_command);
}

void LaunchMethods::Nintendo_FDS (std::string ROM_path_FDS, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame  fds";                  // run machine command linux version
    std::string load_cd = (" -flop ");                      // tell mame to load game onto floppy drive
    std::string file1locale = ROM_path_FDS;                 // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NES_command = command.c_str();
    system(NES_command);
}

void LaunchMethods::Nintendo_SNES (std::string ROM_path_SNES, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame snes";                  // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_SNES;                // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SNES_command = command.c_str();
    system(SNES_command);
}

void LaunchMethods::Nintendo_64 (std::string ROM_path_N64, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame n64";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_N64;                 // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *N64_command = command.c_str();
    system(N64_command);
}

void LaunchMethods::Nintendo_GBC (std::string ROM_path_GBC, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame gbcolor";               // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_GBC;                 // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *GBC_command = command.c_str();
    system(GBC_command);
}

void LaunchMethods::Nintendo_GBA (std::string ROM_path_GBA, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame gba";                   // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_GBA;                 // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *GBA_command = command.c_str();
    system(GBA_command);
}

void LaunchMethods::SNK_NGPC (std::string ROM_path_NGPC, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame ngpc";                  // run machine command linux version
    std::string load_cd = (" -cartridge ");                 // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_NGPC;                // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\"" + file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *NGPC_command = command.c_str();
    system(NGPC_command);
}

void LaunchMethods::SNK_Neo_geo_CDz (std::string ROM_path_Neo_Geo_CDz, std::string vertical_strech, std::string glsl_shader) {
    std::string machine_cmd = "mame neocdzj";               // run machine command linux version
    std::string load_cd = (" -cdrm ");                      // tell mame to load files onto cd tray
    std::string file1locale = ROM_path_Neo_Geo_CDz;         // Path pointed in "ROM1"
    std::string option = vertical_strech + glsl_shader;
    std::string command = machine_cmd + load_cd + "\""+ file1locale + "\"" + option;    // pass "'" before and after file path to send a proper quoted path to console
    const char *SNK_Neo_geo_CDz_command = command.c_str();
    system(SNK_Neo_geo_CDz_command);
}
