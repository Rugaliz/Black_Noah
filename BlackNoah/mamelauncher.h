#ifndef MAMELAUNCHER_H
#define MAMELAUNCHER_H

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

// One "-option path" pair, e.g. {"-flop1", "/roms/disk.d88"}.
struct MediaArg {
    QString option;
    QString path;
};

// Everything needed to build a MAME command line, independent of the UI.
struct LaunchRequest {
    QString machine;
    QStringList fixedArgs;     // always passed, e.g. slot options
    QList<MediaArg> media;     // entries with an empty path are skipped
    QStringList videoArgs;     // stretch / shader switches
};

// Splits a whitespace separated option string into separate arguments.
QStringList splitOptions(const QString &options);

// Builds the argument list (without the executable) for a launch request.
QStringList buildArguments(const LaunchRequest &request);

// Starts MAME processes and reports failures. MAME keeps running if the frontend exits.
class MameLauncher : public QObject
{
    Q_OBJECT

public:
    explicit MameLauncher(QObject *parent = nullptr);

    // Path chosen by the user; empty means "search PATH and the application folder".
    void setConfiguredPath(const QString &path);
    QString configuredPath() const { return m_configuredPath; }

    // Absolute path of the MAME executable, or an empty string if none was found.
    QString resolvedExecutable() const;

    // Starts MAME with the given arguments. stderr is kept in a log file named after `logName`.
    void launch(const QStringList &args, const QString &logName);

    // Asynchronously asks MAME for its version; emits versionDetected (empty on failure).
    void queryVersion();

signals:
    void launchFailed(const QString &message);
    void versionDetected(const QString &version);

private:
    QString m_configuredPath;
};

#endif // MAMELAUNCHER_H
