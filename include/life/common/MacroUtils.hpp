#ifndef MACROUTILS_HPP
#define MACROUTILS_HPP

#include <configure.h>


DV_LIFE_OPEN_NAMESPACE

#ifndef DV_DECL_POINTER_ALIAS
#define DV_DECL_POINTER_ALIAS(Class) \
public: \
    using Ptr = Class*; \
    using ConstPtr = const Class*;
#endif

DV_LIFE_CLOSE_NAMESPACE

#endif // MACROUTILS_HPP
