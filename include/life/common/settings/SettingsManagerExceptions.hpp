#ifndef SETTINGSMANAGEREXCEPTIONS_HPP
#define SETTINGSMANAGEREXCEPTIONS_HPP

#include <configure.h>

#include <exception>
#include <string>


DV_LIFE_OPEN_NAMESPACE

namespace exceptions {

class SettingsManagerParameterNotFoundException : public std::exception {
private:
    const std::string group;
    const std::string param;

public:
    SettingsManagerParameterNotFoundException(
            const std::string& g,
            const std::string& p) :
        group(g), param(p) { }

    virtual const char* what() const noexcept {
        std::string temp = "Settings parameter " + param + \
                + " of group " + group + " not found";
        return temp.c_str();
    }

};

class SettingsManagerGroupParameterNotFoundException : public std::exception {
private:
    const std::string group;

public:
    SettingsManagerGroupParameterNotFoundException(const std::string& s) : group(s) { }

    virtual const char* what() const noexcept {
        std::string temp = "Settings group " + this->group + " not found";
        return temp.c_str();
    }

};

class SettingsManagerTypeMismatchException : public std::exception {
public:
    SettingsManagerTypeMismatchException() { }

    virtual const char* what() const noexcept {
        std::string temp = "Il tipo di dato non e' coerente con quanto richiesto";
        return temp.c_str();
    }

};

class DisableMandatoryGroupException : public std::exception {
public:
    DisableMandatoryGroupException() { }

    virtual const char* what() const noexcept {
        std::string temp = "Un gruppo obbligatorio non puo' essere disabilitato";
        return temp.c_str();
    }

};

}

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSMANAGEREXCEPTIONS_HPP
