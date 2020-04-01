#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifdef FLAG_LOG_BOOST
#include <life/common/logging/BoostLogger.hpp>
#endif

#ifdef FLAG_LOG_QT
#include <life/common/logging/QtLogger.hpp>

#endif

#endif // LOGGER_HPP
