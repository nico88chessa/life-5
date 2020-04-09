#ifndef TYPES_HPP
#define TYPES_HPP

#include <configure.h>


DV_LIFE_OPEN_NAMESPACE

#ifdef ANALOG_IO_HIGH_PRECISION
using analogReal = double;
#else
using analogReal = float;
#endif

using IOScopedType = int;
using DIKey = IOScopedType; // tipo che identifica un ingresso digitale (alias)
using DOKey = IOScopedType; // tipo che identifica un uscita digitale (alias)
using AIKey = IOScopedType; // tipo che identifica un ingresso analogica (alias)
using AOKey = IOScopedType; // tipo che identifica un uscita analogica (alias)

DV_LIFE_CLOSE_NAMESPACE

#endif // TYPES_HPP
