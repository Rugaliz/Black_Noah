#include "systems.h"
#include <QDir>
#include <QFileInfo>

const QString kShaderNone         = " -bgfx_screen_chains none";
const QString kShaderCrtGeom      = " -bgfx_screen_chains crt-geom";
const QString kShaderCrtGeomDeluxe = " -bgfx_screen_chains crt-geom-deluxe";
const QString kShaderLcdGrid      = " -bgfx_screen_chains lcd-grid";

namespace {

// Linux keeps memory cards under ~/.mame; on Windows MAME lives next to the executable.
QString memcardPath(const QString &name)
{
#ifdef Q_OS_WIN
    return "memcard/" + name;
#else
    return QDir::homePath() + "/.mame/memcard/" + name;
#endif
}

QStringList psxMemcardArgs()
{
    QDir().mkpath(QFileInfo(memcardPath("psx.mc1")).absolutePath());
    return {"-memc1", memcardPath("psx.mc1"), "-memc2", memcardPath("psx.mc2")};
}

QList<RadioChoice> crtShaders(const QString &none, const QString &crt, const QString &deluxe)
{
    return {{none, kShaderNone}, {crt, kShaderCrtGeom}, {deluxe, kShaderCrtGeomDeluxe}};
}

QList<RadioChoice> lcdShaders(const QString &none, const QString &lcd)
{
    return {{none, kShaderNone}, {lcd, kShaderLcdGrid}};
}

// Systems with a single cartridge slot that only need the global video settings.
SystemSpec cartSystem(const QString &id, const QString &name, int top, int sub,
                      const QString &machine, const QString &chooseButton,
                      const QString &launchButton)
{
    SystemSpec s;
    s.id = id;
    s.name = name;
    s.topTab = top;
    s.subTab = sub;
    s.launchButton = launchButton;
    s.machine = machine;
    s.media = {{"rom", "-cartridge", name + " ROM", chooseButton}};
    return s;
}

// Systems whose machine depends on the selected region and that boot a single disc.
SystemSpec discRegionSystem(const QString &id, const QString &name, int sub,
                            const QString &chooseButton, const QString &launchButton,
                            const QString &regionKey, QList<RadioChoice> regions)
{
    SystemSpec s;
    s.id = id;
    s.name = name;
    s.topTab = 4;
    s.subTab = sub;
    s.launchButton = launchButton;
    s.regions = std::move(regions);
    s.regionKey = regionKey;
    s.media = {{"disc", "-cdrm", name + " disc", chooseButton}};
    return s;
}

QList<SystemSpec> buildSystems()
{
    QList<SystemSpec> list;

    // ── Misc (top tab 0; sub tab 0 is the plain MAME launcher) ──
    SystemSpec x68k;
    x68k.id = "X68k"; x68k.name = "X68k"; x68k.topTab = 0; x68k.subTab = 1;
    x68k.launchButton = "Launcher_Button_X68k";
    x68k.machine = "x68kxvi";
    x68k.media = {{"flop1", "-flop1", "X68k Floppy 1", "Chose_file_X68k_floppy1"},
                  {"flop2", "-flop2", "X68k Floppy 2", "Chose_file_X68k_floppy2"},
                  {"flop3", "-flop3", "X68k Floppy 3", "Chose_file_X68k_floppy3"},
                  {"flop4", "-flop4", "X68k Floppy 4", "Chose_file_X68k_floppy4"}};
    x68k.shaders = crtShaders("x68k_shader_none", "x68k_shader_CRT_geom", "x68k_shader_CRT_geom_deluxe");
    x68k.shaderKey = "X68K_shader";
    list << x68k;

    SystemSpec marty;
    marty.id = "FMMarty"; marty.name = "FM Towns Marty"; marty.topTab = 0; marty.subTab = 2;
    marty.launchButton = "Launcher_Button_FMMarty";
    marty.machine = "fmtmarty";
    // fmtmarty has a single floppy drive, so the switch is "-flop" (not "-flop1").
    marty.media = {{"floppy", "-flop", "FM Marty Floppy", "Chose_file_FMTownsMarty_floppy"},
                   {"cdrom", "-cdrm", "FM Marty CD-ROM", "Chose_file_FMTownsMarty_CDROM"}};
    marty.shaders = crtShaders("FMTownes_Marty_shader_none", "FMTownes_Marty_shader_crt_geom",
                               "FMTownes_Marty_shader_crt_geom_deluxe");
    marty.shaderKey = "FMTmarty_shader";
    list << marty;

    SystemSpec ngpc = cartSystem("NGPC", "Neo Geo Pocket Color", 0, 3, "ngpc",
                                 "Chose_file_NGPC", "Launcher_Button_NGPcolor");
    ngpc.shaders = lcdShaders("neogeopocketcolor_shader_none_2", "neogeopocketcolor_shader_lcd_grid");
    ngpc.shaderKey = "NGPC_shader";
    list << ngpc;

    SystemSpec neoCd;
    neoCd.id = "NeoGeoCD"; neoCd.name = "Neo Geo CD"; neoCd.topTab = 0; neoCd.subTab = 4;
    neoCd.launchButton = "Launcher_Button_NeoGeoCDz";
    neoCd.machine = "neocdzj";
    neoCd.media = {{"disc", "-cdrm", "Neo Geo CD disc", "Chose_file_NeoGeoCDz"}};
    neoCd.shaders = crtShaders("neogeocd_shader_none", "neogeocd_shader_crt_geom", "neogeocd_shader_crt_geom_deluxe");
    neoCd.shaderKey = "NGCD_shader";
    list << neoCd;

    // ── NEC (top tab 1) ──
    SystemSpec pc88;
    pc88.id = "PC88"; pc88.name = "PC-88"; pc88.topTab = 1; pc88.subTab = 0;
    pc88.launchButton = "Launcher_Button_PC88";
    pc88.machine = "pc8801mc";
    pc88.media = {{"flop1", "-flop1", "PC-88 Floppy 1", "Chose_file_PC88_floppy1"},
                  {"flop2", "-flop2", "PC-88 Floppy 2", "Chose_file_PC88_floppy2"},
                  {"cass", "-cass", "PC-88 Cassette", "Chose_file_PC88_Cassette"}};
    pc88.shaders = crtShaders("pc88_shader_none", "pc88_shader_crt_geom", "pc88_shader_crt_geom_deluxe");
    pc88.shaderKey = "PC88_shader";
    list << pc88;

    SystemSpec pc98;
    pc98.id = "PC98"; pc98.name = "PC-98"; pc98.topTab = 1; pc98.subTab = 1;
    pc98.launchButton = "Launcher_Button_PC98";
    pc98.machine = "pc9821cx3";    // pc9821ce2 was removed from MAME; override in [MachineOverrides]
    pc98.fixedArgs = QStringList{"-cbus:0", "pc9801_86"};
    pc98.media = {{"flop1", "-flop1", "PC-98 Floppy 1", "Chose_file_PC98_floppy1"},
                  {"flop2", "-flop2", "PC-98 Floppy 2", "Chose_file_PC98_floppy2"},
                  {"cdrom", "-cdrm", "PC-98 CD-ROM", "Chose_file_PC98_CDROM"},
                  {"hdd", "-hard", "PC-98 HDD", "Chose_file_PC98_HDD"}};
    pc98.shaders = crtShaders("pc98_shader_none", "pc98_shader_crt_geom", "pc98_shader_crt_geom_deluxe");
    pc98.shaderKey = "PC98_shader";
    list << pc98;

    SystemSpec pce;
    pce.id = "PCEngine"; pce.name = "PC Engine"; pce.topTab = 1; pce.subTab = 2;
    pce.launchButton = "Launcher_Button_PC_Engine";
    pce.machine = "pce";
    pce.media = {{"hucard", "-cart", "PC Engine HuCard", "Chose_file_PC_Engine_HuCard"},
                 {"cdrom", "-cdrm", "PC Engine CD-ROM", "Chose_file_PC_Engine_CDROM"}};
    pce.shaders = crtShaders("pcengine_shader_none", "pcengine_shader_crt_geom", "pcengine_shader_crt_geom_deluxe");
    pce.shaderKey = "PCe_shader";
    list << pce;

    SystemSpec pcfx;
    pcfx.id = "PCFX"; pcfx.name = "PC-FX"; pcfx.topTab = 1; pcfx.subTab = 3;
    pcfx.launchButton = "Launcher_Button_PC_FX";
    pcfx.machine = "pcfx";
    pcfx.media = {{"cdrom", "-cdrm", "PC-FX CD-ROM", "Chose_file_PC_FX_CDROM"}};
    pcfx.shaders = crtShaders("pcfx_shader_none", "pcfx_shader_crt_geom", "pcfx_shader_crt_geom_deluxe");
    pcfx.shaderKey = "PCFX_shader";
    list << pcfx;

    // ── Nintendo (top tab 2) ──
    list << cartSystem("NES", "NES", 2, 0, "nes", "Chose_file_NES", "Launcher_Button_NES");

    SystemSpec fds;
    fds.id = "FDS"; fds.name = "Famicom Disk"; fds.topTab = 2; fds.subTab = 1;
    fds.launchButton = "Launcher_Button_FamicomDisk";
    fds.machine = "fds";
    fds.media = {{"floppy", "-flop", "Famicom Disk image", "Chose_file_FamicomDisk"}};
    list << fds;

    list << cartSystem("SNES", "SNES", 2, 2, "snes", "Chose_file_SNES", "Launcher_Button_SNES");
    list << cartSystem("N64", "N64", 2, 3, "n64", "Chose_file_N64", "Launcher_Button_N64");

    SystemSpec gbc = cartSystem("GBC", "Game Boy Color", 2, 4, "gbcolor",
                                "Chose_file_GBC", "Launcher_Button_GBC");
    gbc.shaders = lcdShaders("gbc_shader_none", "gbc_shader_lcd_grid");
    gbc.shaderKey = "GBC_shader";
    list << gbc;

    list << cartSystem("GBA", "Game Boy Advance", 2, 5, "gba", "Chose_file_GBAdvanced", "Launcher_Button_GBAdvanced");

    // ── Microsoft (top tab 3) ──
    SystemSpec msx;
    msx.id = "MSX"; msx.name = "MSX"; msx.topTab = 3; msx.subTab = 0;
    msx.launchButton = "Launcher_Button_MSX";
    msx.machine = "fsa1fx";
    msx.media = {{"cass", "-cass", "MSX Cassette", "Chose_file_MSX_Cassette"},
                 {"cart1", "-cart1", "MSX Cart 1", "Chose_file_MSX_Cart1"},
                 {"cart2", "-cart2", "MSX Cart 2", "Chose_file_MSX_Cart2"},
                 {"floppy", "-flop", "MSX Floppy", "Chose_file_MSX_Floppy"}};
    list << msx;

    // ── Sega (top tab 4) ──
    list << cartSystem("MasterSystem", "Master System", 4, 0, "sms",
                       "Chose_file_MasterSystem", "Launcher_Button_MasterSystem");

    SystemSpec md = cartSystem("MegaDrive", "Mega Drive", 4, 1, QString(),
                               "Chose_file_MegaDrive", "Launcher_Button_Megadrive");
    md.regions = {{"radioButton_NTSC_USA_MegaDrive", "genesis"},
                  {"radioButton_NTSC_Japan_MegaDrive", "megadrij"}};
    md.regionKey = "region_MegaDrive";
    list << md;

    list << discRegionSystem("SegaCD", "Sega CD", 2, "Chose_file_SEGA_CD", "Launcher_Button_SEGA_CD",
                             "region_MegaCD",
                             {{"radioButton_NTSC_USA_MegaCD", "segacd"},
                              {"radioButton_NTSC_Japan_MegaCD", "megacd2j"}});
    list << discRegionSystem("Saturn", "Saturn", 3, "Chose_file_Saturn", "Launcher_Button_Saturn",
                             "region_Saturn",
                             {{"radioButton_NTSC_USA_Saturn", "saturn"},
                              {"radioButton_PAL_EU_Saturn", "saturneu"},
                              {"radioButton_NTSC_Japan_Saturn", "saturnjp"}});
    list << discRegionSystem("Dreamcast", "Dreamcast", 4, "Chose_file_Dreamcast", "Launcher_Button_Dreamcast",
                             "region_Dreamcast",
                             {{"radioButton_NTSC_USA_Dreamcast", "dc"},
                              {"radioButton_PAL_EU_Dreamcast", "dceu"},
                              {"radioButton_NTSC_Japan_Dreamcast", "dcjp"}});

    // ── Sony (top tab 5) ──
    SystemSpec psx = discRegionSystem("PSX", "PlayStation", 0, "Chose_file_PSX", "Launcher_Button_PSX",
                                      "region_PSX",
                                      {{"radioButton_NTSC_USA", "psu"},
                                       {"radioButton_PAL_EU", "pse"},
                                       {"radioButton_NTSC_Japan", "psj"}});
    psx.topTab = 5;
    psx.extraArgs = psxMemcardArgs;
    list << psx;

    return list;
}

} // namespace

const QList<SystemSpec> &allSystems()
{
    static const QList<SystemSpec> systems = buildSystems();
    return systems;
}
