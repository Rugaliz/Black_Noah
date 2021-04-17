#ifndef LAUNCHMETHODS_H
#define LAUNCHMETHODS_H
#include <string>
#include <iostream> // debug
using namespace std;
class LaunchMethods
{
public:
    LaunchMethods();
    void Playstation (string file1locale, string vertical_strech, string glsl_shader, string region);
    string PS_memcard1;
    string PS_memcard2;
    void X68k (string ROM_path_X68k_floppy1, string ROM_path_X68k_floppy2, string ROM_path_X68k_floppy3, string ROM_path_X68k_floppy4, string vertical_strech, string glsl_shader);
    void PC88 (string ROM_path_PC88_floppy1, string ROM_path_PC88_floppy2, string ROM_path_PC88_Cassete,  string vertical_strech, string glsl_shader);
    void PC98 (string ROM_path_PC98_HDD, string ROM_path_PC98_CDROM, string ROM_path_PC98_floppy1, string ROM_path_PC98_floppy2, string vertical_strech, string glsl_shader);
    void FMMarty(string ROM_path_FMMarty_CDROM, string ROM_path_FMMarty_floppy, string vertical_strech, string glsl_shader);
    void PC_Engine (string ROM_path_PC_Engine_HuCards, string ROM_path_PC_Engine_CDROM, string vertical_strech, string glsl_shader);
    void PC_FX (string ROM_path_PC_FX_CDROM, string vertical_strech, string glsl_shader);
    void MasterSystem (string ROM_path_MasterSystem, string vertical_strech, string glsl_shader);
    void MegaDrive (string ROM_path_Genesis, string region_MegaDrive, string vertical_strech, string glsl_shader);
    void SEGA_MD_CD (string ROM_path_SEGA_CD, string vertical_strech, string glsl_shader, string region_MegaCD);
    void SEGA_Saturn (string ROM_path_Saturn, string vertical_strech, string glsl_shader, string region_Saturn);
    void SEGA_Dreamcast (string ROM_path_Dreamcast, string vertical_strech, string glsl_shader, string region_Dreamcast);
    void Nintendo_NES (string ROM_path_NES, string vertical_strech, string glsl_shader);
    void Nintendo_FDS (string ROM_path_FDS, string vertical_strech, string glsl_shader);
    void Nintendo_SNES (string ROM_path_SNES, string vertical_strech, string glsl_shader);
    void Nintendo_64 (string ROM_path_N64, string vertical_strech, string glsl_shader);
    void Nintendo_GBC (string ROM_path_GBC, string vertical_strech, string glsl_shader);
    void Nintendo_GBA (string ROM_path_GBA, string vertical_strech, string glsl_shader);
    void SNK_NGPC (string ROM_path_NGPC, string vertical_strech, string glsl_shader);
    void SNK_Neo_geo_CDz (string ROM_path_Neo_Geo_CDz, string vertical_strech, string glsl_shader);
    void M$_MSX(string ROM_path_MSX_Cass, string ROM_path_MSX_Cart1, string ROM_path_MSX_Cart2, string ROM_path_MSX_Floppy, string vertical_strech, string glsl_shader);
};

#endif // LAUNCHMETHODS_H
