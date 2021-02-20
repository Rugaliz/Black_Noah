#ifndef LAUNCHMETHODS_H
#define LAUNCHMETHODS_H
#include <string>
#include <iostream> // debug
class LaunchMethods
{
public:
    LaunchMethods();
    void Playstation (std::string file1locale, std::string vertical_strech, std::string glsl_shader, std::string region);
    std::string PS_memcard1;
    std::string PS_memcard2;
    void X68k (std::string ROM_path_X68k_floppy1, std::string ROM_path_X68k_floppy2, std::string ROM_path_X68k_floppy3, std::string ROM_path_X68k_floppy4, std::string vertical_strech, std::string glsl_shader);
    void PC88 (std::string ROM_path_PC88_floppy1, std::string ROM_path_PC88_floppy2, std::string ROM_path_PC88_Cassete,  std::string vertical_strech, std::string glsl_shader);
    void PC98 (std::string ROM_path_PC98_HDD, std::string ROM_path_PC98_CDROM, std::string ROM_path_PC98_floppy1, std::string ROM_path_PC98_floppy2, std::string vertical_strech, std::string glsl_shader);
    void FMMarty(std::string ROM_path_FMMarty_CDROM, std::string ROM_path_FMMarty_floppy, std::string vertical_strech, std::string glsl_shader);
    void PC_Engine (std::string ROM_path_PC_Engine_HuCards, std::string ROM_path_PC_Engine_CDROM, std::string vertical_strech, std::string glsl_shader);
    void PC_FX (std::string ROM_path_PC_FX_CDROM, std::string vertical_strech, std::string glsl_shader);
    void MasterSystem (std::string ROM_path_MasterSystem, std::string vertical_strech, std::string glsl_shader);
    void MegaDrive (std::string ROM_path_Genesis, std::string region_MegaDrive, std::string vertical_strech, std::string glsl_shader);
    void SEGA_MD_CD (std::string ROM_path_SEGA_CD, std::string vertical_strech, std::string glsl_shader, std::string region_MegaCD);
    void SEGA_Saturn (std::string ROM_path_Saturn, std::string vertical_strech, std::string glsl_shader, std::string region_Saturn);
    void SEGA_Dreamcast (std::string ROM_path_Dreamcast, std::string vertical_strech, std::string glsl_shader, std::string region_Dreamcast);
    void Nintendo_NES (std::string region_NES,std::string ROM_path_NES, std::string vertical_strech, std::string glsl_shader);
    void Nintendo_FDS (std::string ROM_path_FDS, std::string vertical_strech, std::string glsl_shader);
    void Nintendo_SNES (std::string ROM_path_SNES, std::string vertical_strech, std::string glsl_shader);
    void Nintendo_64 (std::string ROM_path_N64, std::string vertical_strech, std::string glsl_shader);
    void Nintendo_GBC (std::string ROM_path_GBC, std::string vertical_strech, std::string glsl_shader);
    void Nintendo_GBA (std::string ROM_path_GBA, std::string vertical_strech, std::string glsl_shader);
    void SNK_NGPC (std::string ROM_path_NGPC, std::string vertical_strech, std::string glsl_shader);
    void SNK_Neo_geo_CDz (std::string ROM_path_Neo_Geo_CDz, std::string vertical_strech, std::string glsl_shader);
    void M$_MSX(std::string ROM_path_MSX_Cass, std::string ROM_path_MSX_Cart1, std::string ROM_path_MSX_Cart2, std::string ROM_path_MSX_Floppy, std::string vertical_strech, std::string glsl_shader);
};

#endif // LAUNCHMETHODS_H
