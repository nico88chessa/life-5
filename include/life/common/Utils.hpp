#ifndef UTILS_HPP
#define UTILS_HPP

#include <configure.h>

#include <QString>


DV_LIFE_OPEN_NAMESPACE

enum class IOType;

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
    static QString enumToName(MAYBE_UNUSED T e) noexcept {
        return "";
    }

    template <typename T>
    static T nameToEnum(MAYBE_UNUSED QLatin1String str) noexcept {
        return T();
    }

};



class IOUtils {
public:

    static bool isGenericDigitalInput(IOType type);

    static bool isGenericAnalogInput(IOType type);

};

}

DV_LIFE_CLOSE_NAMESPACE

#endif // UTILS_HPP
