#include "mamelauncher.h"
#include <QtTest>

class TestMameLauncher : public QObject
{
    Q_OBJECT

private slots:
    void splitOptionsHandlesWhitespace();
    void buildArgumentsSkipsEmptyMedia();
    void buildArgumentsKeepsOrder();
    void buildArgumentsWithoutMedia();
};

void TestMameLauncher::splitOptionsHandlesWhitespace()
{
    QCOMPARE(splitOptions(""), QStringList());
    QCOMPARE(splitOptions("   "), QStringList());
    QCOMPARE(splitOptions(" -unevenstretch  -nogl_glsl "), (QStringList{"-unevenstretch", "-nogl_glsl"}));
}

void TestMameLauncher::buildArgumentsSkipsEmptyMedia()
{
    LaunchRequest request;
    request.machine = "x68kxvi";
    request.media = {{"-flop1", "/roms/a.d88"}, {"-flop2", ""}, {"-flop3", ""}, {"-flop4", "/roms/d.d88"}};

    QCOMPARE(buildArguments(request),
             (QStringList{"x68kxvi", "-flop1", "/roms/a.d88", "-flop4", "/roms/d.d88"}));
}

void TestMameLauncher::buildArgumentsKeepsOrder()
{
    LaunchRequest request;
    request.machine = "psu";
    request.fixedArgs = QStringList{"-memc1", "a.mc1"};
    request.media = {{"-cdrm", "/roms/game.cue"}};
    request.videoArgs = QStringList{"-nounevenstretch", "-nogl_glsl"};

    QCOMPARE(buildArguments(request),
             (QStringList{"psu", "-memc1", "a.mc1", "-cdrm", "/roms/game.cue", "-nounevenstretch", "-nogl_glsl"}));
}

void TestMameLauncher::buildArgumentsWithoutMedia()
{
    LaunchRequest request;
    request.machine = "mame";
    QCOMPARE(buildArguments(request), QStringList{"mame"});
}

QTEST_APPLESS_MAIN(TestMameLauncher)
#include "tst_mamelauncher.moc"
