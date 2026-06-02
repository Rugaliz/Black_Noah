#include "launchmethods.h"
#include <QDir>
#include <QProcess>
#include <QString>
#include <QStringList>

static QStringList parseOptions(const std::string &stretch, const std::string &shader)
{
    QString opts = QString::fromStdString(stretch + " " + shader).simplified();
    return opts.isEmpty() ? QStringList{} : opts.split(' ', Qt::SkipEmptyParts);
}

static bool launchCart(const std::string &machine, const std::string &rom,
                       const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << QString::fromStdString(machine) << "-cartridge" << QString::fromStdString(rom);
    args << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

static bool launchCD(const std::string &machine, const std::string &rom,
                     const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << QString::fromStdString(machine) << "-cdrm" << QString::fromStdString(rom);
    args << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::Playstation(const std::string &file, const std::string &stretch,
                                const std::string &shader, const std::string &region)
{
    QStringList args;
    args << QString::fromStdString(region)
         << "-memc1" << QDir::homePath() + "/.mame/memcard/psx.mc1"
         << "-memc2" << QDir::homePath() + "/.mame/memcard/psx.mc2"
         << "-cdrm"  << QString::fromStdString(file)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::X68k(const std::string &flop1, const std::string &flop2,
                         const std::string &flop3, const std::string &flop4,
                         const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << "x68kxvi"
         << "-flop1" << QString::fromStdString(flop1)
         << "-flop2" << QString::fromStdString(flop2)
         << "-flop3" << QString::fromStdString(flop3)
         << "-flop4" << QString::fromStdString(flop4)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::PC88(const std::string &flop1, const std::string &flop2,
                         const std::string &cassette, const std::string &stretch,
                         const std::string &shader)
{
    QStringList args;
    args << "pc8801mc"
         << "-flop1" << QString::fromStdString(flop1)
         << "-flop2" << QString::fromStdString(flop2)
         << "-cass"  << QString::fromStdString(cassette)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::PC98(const std::string &hdd, const std::string &cdrom,
                         const std::string &flop1, const std::string &flop2,
                         const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << "pc9821ce2" << "-cbus0" << "pc9801_86"
         << "-flop1" << QString::fromStdString(flop1)
         << "-flop2" << QString::fromStdString(flop2)
         << "-cdrm"  << QString::fromStdString(cdrom)
         << "-hard"  << QString::fromStdString(hdd)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::FMMarty(const std::string &cdrom, const std::string &floppy,
                            const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << "fmtmarty"
         << "-flop1" << QString::fromStdString(floppy)
         << "-cdrm"  << QString::fromStdString(cdrom)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::PC_Engine(const std::string &hucard, const std::string &cdrom,
                              const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << "pce"
         << "-cart" << QString::fromStdString(hucard)
         << "-cdrm" << QString::fromStdString(cdrom)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::Nintendo_FDS(const std::string &floppy, const std::string &stretch,
                                 const std::string &shader)
{
    QStringList args;
    args << "fds" << "-flop" << QString::fromStdString(floppy) << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::MSX(const std::string &cass, const std::string &cart1,
                        const std::string &cart2, const std::string &floppy,
                        const std::string &stretch, const std::string &shader)
{
    QStringList args;
    args << "fsa1fx"
         << "-cass"  << QString::fromStdString(cass)
         << "-cart1" << QString::fromStdString(cart1)
         << "-cart2" << QString::fromStdString(cart2)
         << "-flop"  << QString::fromStdString(floppy)
         << parseOptions(stretch, shader);
    return QProcess::startDetached("mame", args);
}

bool LaunchMethods::PC_FX(const std::string &cdrom, const std::string &stretch, const std::string &shader)           { return launchCD("pcfx",    cdrom, stretch, shader); }
bool LaunchMethods::MasterSystem(const std::string &rom, const std::string &stretch, const std::string &shader)       { return launchCart("sms",   rom,   stretch, shader); }
bool LaunchMethods::Nintendo_NES(const std::string &rom, const std::string &stretch, const std::string &shader)       { return launchCart("nes",   rom,   stretch, shader); }
bool LaunchMethods::Nintendo_SNES(const std::string &rom, const std::string &stretch, const std::string &shader)      { return launchCart("snes",  rom,   stretch, shader); }
bool LaunchMethods::Nintendo_64(const std::string &rom, const std::string &stretch, const std::string &shader)        { return launchCart("n64",   rom,   stretch, shader); }
bool LaunchMethods::Nintendo_GBC(const std::string &rom, const std::string &stretch, const std::string &shader)       { return launchCart("gbcolor", rom, stretch, shader); }
bool LaunchMethods::Nintendo_GBA(const std::string &rom, const std::string &stretch, const std::string &shader)       { return launchCart("gba",   rom,   stretch, shader); }
bool LaunchMethods::SNK_NGPC(const std::string &rom, const std::string &stretch, const std::string &shader)           { return launchCart("ngpc",  rom,   stretch, shader); }
bool LaunchMethods::SNK_Neo_geo_CDz(const std::string &cdrom, const std::string &stretch, const std::string &shader)  { return launchCD("neocdzj", cdrom, stretch, shader); }

bool LaunchMethods::MegaDrive(const std::string &rom, const std::string &region, const std::string &stretch, const std::string &shader)     { return launchCart(region, rom,   stretch, shader); }
bool LaunchMethods::SEGA_MD_CD(const std::string &cdrom, const std::string &stretch, const std::string &shader, const std::string &region)  { return launchCD(region,   cdrom, stretch, shader); }
bool LaunchMethods::SEGA_Saturn(const std::string &cdrom, const std::string &stretch, const std::string &shader, const std::string &region)  { return launchCD(region,   cdrom, stretch, shader); }
bool LaunchMethods::SEGA_Dreamcast(const std::string &cdrom, const std::string &stretch, const std::string &shader, const std::string &region) { return launchCD(region, cdrom, stretch, shader); }
