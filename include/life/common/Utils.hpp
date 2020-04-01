#ifndef UTILS_HPP
#define UTILS_HPP

#include <configure.h>

#include <QString>

#include <life/common/Types.hpp>


DV_LIFE_OPEN_NAMESPACE

namespace utils {

class EnumUtils {

public:

/* NOTE Nic 30/03/2020
 * questa funzione definisce una classe di funzioni dipendente da T
 * se specializzo questa funzione con un parametro T, il compilatore
 * segnala che la funzione e' gia definita (perche' appunto qui
 * definisco una classe di funzioni); per evitare questo problema,
 * specializzo le classi nel .cpp
 */
template <typename T>
static QLatin1String getEnumName(MAYBE_UNUSED T e) noexcept {
    return QLatin1String("");
}

};

}

DV_LIFE_CLOSE_NAMESPACE

#endif // UTILS_HPP
