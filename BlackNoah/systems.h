#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <QList>
#include <QString>
#include <QStringList>

// One media slot of an emulated system, e.g. "floppy 1" => "-flop1".
struct MediaSlotSpec {
    QString id;            // settings key, unique within the system
    QString option;        // MAME media switch
    QString label;         // shown to the user
    QString chooseButton;  // name of the "Set ..." button in the .ui
};

// A radio button in the .ui and the value it stands for.
struct RadioChoice {
    QString radio;
    QString value;
};

// Static description of a system tab. The first entry of `shaders` is the default.
struct SystemSpec {
    QString id;
    QString name;
    int topTab;                     // index in the vendor tab widget
    int subTab;                     // index in the vendor's system tab widget
    QString launchButton;
    QString machine;                // used when `regions` is empty
    QList<RadioChoice> regions;     // value = MAME machine; first is the default
    QString regionKey;              // settings key for the chosen region
    QStringList fixedArgs;
    QStringList (*extraArgs)() = nullptr;   // computed at launch time
    QList<MediaSlotSpec> media;
    QList<RadioChoice> shaders;     // empty: follow the global shader toggle
    QString shaderKey;              // settings key for the chosen shader
};

// Shader switches offered by the UI.
extern const QString kShaderNone;
extern const QString kShaderCrtGeom;
extern const QString kShaderCrtGeomDeluxe;
extern const QString kShaderLcdGrid;

const QList<SystemSpec> &allSystems();

#endif // SYSTEMS_H
