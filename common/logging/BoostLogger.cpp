#include "BoostLogger.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>

#include <QStandardPaths>
#include <QString>

#include <string>
#include <locale>


using namespace DVN;

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

static constexpr unsigned int LOG_MAX_FILESIZE_BYTE = 100 * 1024 * 1024;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", SEVERITY)

template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<< (
        std::basic_ostream<CharT, TraitsT>& strm,
        const QString& qs) {
    strm << qs.toStdString();
    return strm;
}


//inline void my_formatter(logging::record_view const& rec, logging::formatting_ostream& strm) {

//    /* qui formatto il testo; prendo gli attributi inseriti nel logger source o nel core
//     * (con scope global o thread) e li stampo su riga
//     */
//    auto timeStamp = logging::extract<boost::posix_time::ptime>("TimeStamp", rec);
//    auto milliseconds = timeStamp->time_of_day().total_milliseconds() % 1000;

//    auto&& facet = new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S.");
//    strm.imbue(std::locale(std::locale(), facet));

//    std::ostringstream msZeroFilled; // aggiungo degli 0 se necessario; 45 -> 045
//    msZeroFilled << std::setw(3) << std::setfill('0') << milliseconds;

//    strm << timeStamp << msZeroFilled.str() << " ";
//    auto&& severity = logging::extract<SEVERITY>("Severity", rec);

//    if (severity) {
//        switch (severity.get<SEVERITY>()) {
//        case SEVERITY::DEBUG: strm << "[DEBUG] "; break;
//        case SEVERITY::INFO: strm << "[INFO] "; break;
//        case SEVERITY::WARN: strm << "[WARN] "; break;
//        case SEVERITY::ERROR: strm << "[ERROR] "; break;
//        case SEVERITY::FATAL: strm << "[FATAL] "; break;
//        }
//    }

//    // Finally, put the record message to the stream
//    strm << rec[expr::smessage];
//}

BoostLogger::BoostLogger() {

    auto prefixPath = QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).at(0);
    auto logPath = prefixPath + "/./" + LOG_PATH +"/";
    auto stdLogPath = logPath.toStdString();
    std::string stdFilename = PROJECT_NAME;
    auto stdCurrentFilepath = stdLogPath+"/./"+stdFilename+".log";

    auto&& core = logging::core::get();
    core->add_global_attribute("TimeStamp", attrs::local_clock());
    logging::register_simple_formatter_factory<QString, char>("QString");

    // questa funzione crea il sink e lo inserisce nel core (il core e' singleton)
    auto&& sink = logging::add_file_log(
        keywords::file_name = stdCurrentFilepath,
        keywords::target_file_name = stdFilename+"-%Y%m%d-%H%M%S.log",
        keywords::target = stdLogPath,
        keywords::auto_flush = true,
        keywords::rotation_size = LOG_MAX_FILESIZE_BYTE,
        keywords::max_files = MAX_NUM_LOG_FILES);

#ifndef LOG_VERBOSE
    core->set_filter(severity > SEVERITY::DEBUG);
#endif

    // aggiungo un formatter al sink
//    sink->set_formatter(&my_formatter);
    sink->set_formatter(&BoostLogger::formatter);

}

BoostLogger::~BoostLogger() { }

void BoostLogger::formatter(const BoostLogger::recordView& rec, BoostLogger::ostream& strm) {

    /* qui formatto il testo; prendo gli attributi inseriti nel logger source o nel core
     * (con scope global o thread) e li stampo su riga
     */
    auto timeStamp = logging::extract<boost::posix_time::ptime>("TimeStamp", rec);
    auto milliseconds = timeStamp->time_of_day().total_milliseconds() % 1000;

    auto&& facet = new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S.");
    strm.imbue(std::locale(std::locale(), facet));

    std::ostringstream msZeroFilled; // aggiungo degli 0 se necessario; 45 -> 045
    msZeroFilled << std::setw(3) << std::setfill('0') << milliseconds;

    strm << timeStamp << msZeroFilled.str() << " ";
    auto&& severity = logging::extract<SEVERITY>("Severity", rec);

    if (severity) {
        switch (severity.get<SEVERITY>()) {
        case SEVERITY::DEBUG: strm << "[DEBUG] "; break;
        case SEVERITY::INFO: strm << "[INFO] "; break;
        case SEVERITY::WARN: strm << "[WARN] "; break;
        case SEVERITY::ERROR: strm << "[ERROR] "; break;
        case SEVERITY::FATAL: strm << "[FATAL] "; break;
        }
    }

    // Finally, put the record message to the stream
    strm << rec[expr::smessage];

}

void BoostLogger::enter(const char* functionName) {
//    BOOST_LOG(lg) << logging::add_value("Severity", SEVERITY::DEBUG) << "ENTER" << functionName;
    BOOST_LOG(lg) << QString("Prova");
    BOOST_LOG_SEV(lg, SEVERITY::DEBUG) << "ENTER " << functionName;
}

void BoostLogger::exit(const char* functionName) {
    BOOST_LOG_SEV(lg, SEVERITY::DEBUG) << "EXIT " << functionName;
}

void BoostLogger::fatal(const char* msg, ...) {
    BOOST_LOG_SEV(lg, SEVERITY::FATAL) << "FATAL " << msg;
    std::abort();
}

BoostLogger& BoostLogger::instance() {

    static BoostLogger logger;
    return logger;

}

