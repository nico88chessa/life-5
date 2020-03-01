#include "QtLogger.hpp"
#include <QDateTime>

using namespace DVN;

static constexpr char TIME_FORMAT[] = "yyyy-MM-dd hh:mm:ss.zzz";

namespace DVN {

void messageHandlerFunction(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QtLogger::instance().messageHandler(type, context, msg);
}

}

QtLogger::QtLogger() {

    rotateLog();

    auto prefixPath = QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).at(0);

    auto logPath = prefixPath + "/" + LOG_PATH + "/";
    auto filePath = QString(logPath+PROJECT_NAME+"-%1.log").arg(0);

    QDir dir(prefixPath);
    if (!dir.mkpath(logPath))
        this->fatal("FATAL: Impossibile creare le cartelle per il logging dei file.");

    file.open(filePath.toStdString().c_str(), std::ios::out | std::ios::trunc);

    qInstallMessageHandler(messageHandlerFunction);

}

QtLogger::~QtLogger() {

    file.close();

}

void QtLogger::messageHandler(QtMsgType type, MAYBE_UNUSED const QMessageLogContext& context, const QString& msg) {

    QByteArray localMsg = msg.toLocal8Bit();
    QByteArray localTime = QDateTime::currentDateTime().toString(TIME_FORMAT).toLocal8Bit();

    // fprintf(stderr, "%s DEBUG: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    switch (type) {
    case QtDebugMsg:
        file << qPrintable(QString("%0 DEBUG %1\n").arg(localTime.constData()).arg(localMsg.constData()));
        file.flush();
        break;
    case QtInfoMsg:
        file << qPrintable(QString("%0 INFO %1\n").arg(localTime.constData()).arg(localMsg.constData()));
        file.flush();
        break;
    case QtWarningMsg:
        file << qPrintable(QString("%0 WARN %1\n").arg(localTime.constData()).arg(localMsg.constData()));
        file.flush();
        break;
    case QtCriticalMsg:
        file << qPrintable(QString("%0 CRITICAL %1\n").arg(localTime.constData()).arg(localMsg.constData()));
        file.flush();
        break;
    case QtFatalMsg:
        file << qPrintable(QString("%0 FATAL %1\n").arg(localTime.constData()).arg(localMsg.constData()));
        file.flush();
        break;
    }

}

void QtLogger::rotateLog() {

    auto prefixPath = QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).at(0);
    auto logPath = prefixPath + "/" + LOG_PATH +"/";
    auto filePath = QString(logPath + PROJECT_NAME + "-%1.log").arg(MAX_NUM_LOG_FILES);

    // rimuovo l'ultimo file se esiste
    if (QFile::exists(filePath))
        QFile::remove(filePath);

    for (int i=MAX_NUM_LOG_FILES; i>0; --i) {

        if (QFile::exists(QString(logPath + PROJECT_NAME + "-%1.log").arg(i-1)))
            QFile::rename(QString(logPath + PROJECT_NAME + "-%1.log").arg(i-1),
                          QString(logPath + PROJECT_NAME + "-%1.log").arg(i));

    }

}

QtLogger& QtLogger::instance() {

    static QtLogger l;
    return l;

}

void QtLogger::enter(const char* functionName) const {
    qDebug().noquote() << "ENTER" << functionName;
}

void QtLogger::exit(const char* functionName) const {
    qDebug().noquote() << "EXIT" << functionName;
}

QDebug QtLogger::debug() const {
    return qDebug().noquote();
}

QDebug QtLogger::info() const {
    return qInfo().noquote();
}

QDebug QtLogger::warn() const {
    return qWarning().noquote();
}

QDebug QtLogger::error() const {
    return qCritical().noquote();
}

void QtLogger::fatal(const char *msg, ...) const {

    va_list va;
    va_start(va, msg);
    qFatal(msg, va);

}

