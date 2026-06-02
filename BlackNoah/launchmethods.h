#ifndef LAUNCHMETHODS_H
#define LAUNCHMETHODS_H
#include <string>

class LaunchMethods
{
public:
    LaunchMethods() = default;
    bool Playstation(const std::string &file, const std::string &stretch, const std::string &shader, const std::string &region);
    bool X68k(const std::string &flop1, const std::string &flop2, const std::string &flop3, const std::string &flop4, const std::string &stretch, const std::string &shader);
    bool PC88(const std::string &flop1, const std::string &flop2, const std::string &cassette, const std::string &stretch, const std::string &shader);
    bool PC98(const std::string &hdd, const std::string &cdrom, const std::string &flop1, const std::string &flop2, const std::string &stretch, const std::string &shader);
    bool FMMarty(const std::string &cdrom, const std::string &floppy, const std::string &stretch, const std::string &shader);
    bool PC_Engine(const std::string &hucard, const std::string &cdrom, const std::string &stretch, const std::string &shader);
    bool PC_FX(const std::string &cdrom, const std::string &stretch, const std::string &shader);
    bool MasterSystem(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool MegaDrive(const std::string &rom, const std::string &region, const std::string &stretch, const std::string &shader);
    bool SEGA_MD_CD(const std::string &cdrom, const std::string &stretch, const std::string &shader, const std::string &region);
    bool SEGA_Saturn(const std::string &cdrom, const std::string &stretch, const std::string &shader, const std::string &region);
    bool SEGA_Dreamcast(const std::string &cdrom, const std::string &stretch, const std::string &shader, const std::string &region);
    bool Nintendo_NES(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool Nintendo_FDS(const std::string &floppy, const std::string &stretch, const std::string &shader);
    bool Nintendo_SNES(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool Nintendo_64(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool Nintendo_GBC(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool Nintendo_GBA(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool SNK_NGPC(const std::string &rom, const std::string &stretch, const std::string &shader);
    bool SNK_Neo_geo_CDz(const std::string &cdrom, const std::string &stretch, const std::string &shader);
    bool MSX(const std::string &cass, const std::string &cart1, const std::string &cart2, const std::string &floppy, const std::string &stretch, const std::string &shader);
};

#endif // LAUNCHMETHODS_H
