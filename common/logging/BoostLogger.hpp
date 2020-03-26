#ifndef BOOSTLOGGER_H
#define BOOSTLOGGER_H

#include "configure.h"

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/record_ostream.hpp>


class QString;

/*
 * NOTE NIC 26/03/202
 * qui si puo' separare header e source perche' il tipo std::basic_ostream e' definito
 */
template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm, const QString& qs);

namespace DVN {

enum class SEVERITY : int {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class BoostLogger {
public:
    using lgSourceType = boost::log::sources::severity_logger_mt<SEVERITY>;

public:
    static BoostLogger& instance();

private:

    using recordView = boost::log::record_view;
    using ostream = boost::log::formatting_ostream;
    BoostLogger();
    ~BoostLogger();

    BoostLogger(const BoostLogger&) = delete;
    BoostLogger& operator=(const BoostLogger&) = delete;

    static void formatter(const recordView& rec, ostream& strm);

public:
    void enter(const char* functionName);
    void exit(const char* functionName);

    [[noreturn]] void fatal(const char* msg, ...);

    inline lgSourceType& get() { return lg; }

private:
    lgSourceType lg;

};

#define trace(LEVEL) BOOST_LOG_SEV(BoostLogger::instance().get(), LEVEL)

#define traceEnter BoostLogger::instance().enter(__PRETTY_FUNCTION__)
#define traceExit BoostLogger::instance().exit(__PRETTY_FUNCTION__)
#define traceDebug() trace(SEVERITY::DEBUG)
#define traceInfo() trace(SEVERITY::INFO)
#define traceWarn() trace(SEVERITY::WARN)
#define traceErr() trace(SEVERITY::ERROR)
#define traceFatal BoostLogger::instance().fatal

}

#endif // BOOSTLOGGER_H
