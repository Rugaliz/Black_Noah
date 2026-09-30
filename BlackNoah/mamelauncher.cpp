#include "mamelauncher.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QStandardPaths>

namespace {

constexpr int kMaxLogLines = 8;

QString tailOfLog(const QString &logPath)
{
    QFile file(logPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    const QStringList lines = QString::fromLocal8Bit(file.readAll()).trimmed().split('\n');
    return lines.mid(qMax(0, lines.size() - kMaxLogLines)).join('\n');
}

} // namespace

QStringList splitOptions(const QString &options)
{
    const QString simplified = options.simplified();
    return simplified.isEmpty() ? QStringList{} : simplified.split(' ', Qt::SkipEmptyParts);
}

QStringList buildArguments(const LaunchRequest &request)
{
    QStringList args{request.machine};
    args += request.fixedArgs;
    for (const MediaArg &media : request.media) {
        if (!media.path.isEmpty())
            args << media.option << media.path;
    }
    args += request.videoArgs;
    return args;
}

MameLauncher::MameLauncher(QObject *parent) : QObject(parent) {}

void MameLauncher::setConfiguredPath(const QString &path)
{
    m_configuredPath = path;
}

QString MameLauncher::resolvedExecutable() const
{
    if (!m_configuredPath.isEmpty() && QFileInfo(m_configuredPath).isExecutable())
        return m_configuredPath;

    const QString onPath = QStandardPaths::findExecutable("mame");
    if (!onPath.isEmpty())
        return onPath;

    // Windows layout: BlackNoah.exe sits in the MAME folder.
    return QStandardPaths::findExecutable("mame", {QCoreApplication::applicationDirPath()});
}

void MameLauncher::launch(const QStringList &args, const QString &logName)
{
    const QString exe = resolvedExecutable();
    if (exe.isEmpty()) {
        emit launchFailed(tr("MAME was not found. Install it, or choose its location with "
                             "File > Set MAME executable."));
        return;
    }

    const QString logDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/logs";
    QDir().mkpath(logDir);
    const QString logPath = logDir + "/" + logName + ".log";

    // Deliberately parentless and file-redirected (no pipes): MAME must survive the frontend
    // closing. The process object cleans itself up when MAME exits.
    auto *process = new QProcess;
    process->setStandardInputFile(QProcess::nullDevice());
    process->setStandardOutputFile(QProcess::nullDevice());
    process->setStandardErrorFile(logPath, QIODevice::Truncate);

    connect(process, &QProcess::errorOccurred, this, [this, process, exe](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart) {
            emit launchFailed(tr("Failed to start %1.").arg(exe));
            process->deleteLater();
        }
    });
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [this, process, logPath](int exitCode, QProcess::ExitStatus status) {
        if (status == QProcess::NormalExit && exitCode != 0) {
            const QString details = tailOfLog(logPath);
            emit launchFailed(tr("MAME exited with code %1.").arg(exitCode)
                              + (details.isEmpty() ? QString() : "\n\n" + details));
        }
        process->deleteLater();
    });
    process->start(exe, args);
}

void MameLauncher::queryVersion()
{
    const QString exe = resolvedExecutable();
    if (exe.isEmpty()) {
        emit versionDetected({});
        return;
    }

    auto *process = new QProcess(this);
    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart) {
            emit versionDetected({});
            process->deleteLater();
        }
    });
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [this, process](int exitCode, QProcess::ExitStatus) {
        // Output looks like "0.289 (mame0289)"; the first word is the version.
        const QStringList words = QString::fromLocal8Bit(process->readAllStandardOutput())
                                      .simplified().split(' ', Qt::SkipEmptyParts);
        emit versionDetected(exitCode == 0 && !words.isEmpty() ? words.first() : QString());
        process->deleteLater();
    });
    process->start(exe, {"-version"});
}
