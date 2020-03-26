#ifndef QTLOGGER_HPP
#define QTLOGGER_HPP

#include <QDebug>
#include <QString>
#include <QMessageLogger>
#include <QFile>
#include <QStandardPaths>
#include <QtGlobal>
#include <QDir>

#include "configure.h"
#include "fstream"


namespace DVN {

class QtLogger {

    friend inline void messageHandlerFunction(QtMsgType type, const QMessageLogContext& context, const QString& msg);

private:
    std::ofstream file;

private:
    QtLogger();

    ~QtLogger();

    void messageHandler(QtMsgType type,
                        const QMessageLogContext &context,
                        const QString &msg);
    void rotateLog();
    void deleteLastLogIfNeeded();


public:
    QtLogger(const QtLogger& l) = delete;
    void operator=(const QtLogger& l) = delete;
    static QtLogger& instance();

    void enter(const char* functionName) const;
    void exit(const char* functionName) const;

    QDebug debug() const;
    QDebug info() const;
    QDebug warn() const;
    QDebug error() const;
    [[noreturn]] void fatal(const char* msg, ...) const;

};

//void messageHandlerFunction(QtMsgType type, const QMessageLogContext& context, const QString& msg);

#ifdef LOG_VERBOSE
#define traceEnter QtLogger::instance().enter(QT_MESSAGELOG_FUNC)
#define traceExit QtLogger::instance().exit(QT_MESSAGELOG_FUNC)
#define traceDebug QtLogger::instance().debug
#else
#define traceEnter
#define traceExit
// vedere qlogging.h per questo trick
#define traceDebug if (false) QMessageLogger().noDebug
#endif

#define traceInfo QtLogger::instance().info
#define traceWarn QtLogger::instance().warn
#define traceErr QtLogger::instance().error
#define traceFatal QtLogger::instance().fatal

}

#endif // LOGGER_HPP
