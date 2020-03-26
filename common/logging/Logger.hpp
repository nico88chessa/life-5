#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifdef FLAG_LOG_BOOST
#include <logging/BoostLogger.hpp>
#endif

#ifdef FLAG_LOG_QT
#include <logging/QtLogger.hpp>

#endif

#endif // LOGGER_HPP
