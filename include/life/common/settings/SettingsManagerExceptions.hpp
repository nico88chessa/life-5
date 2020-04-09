#ifndef SETTINGSMANAGEREXCEPTIONS_HPP
#define SETTINGSMANAGEREXCEPTIONS_HPP

#include <configure.h>

#include <exception>
#include <string>


DV_LIFE_OPEN_NAMESPACE

namespace exceptions {

class SettingsException : public std::exception {
protected:
    std::string description;

public:
    SettingsException() : description("") { }

    virtual const char* what() const noexcept {
        return description.c_str();
    }

};

class ParameterNotFoundException : public SettingsException {
private:
    std::string group;
    std::string param;

public:
    ParameterNotFoundException(
            const std::string& g,
            const std::string& p) :
        group(g), param(p) {

        this->description = "Settings parameter " + param + \
                            + " of group " + group + " not found";
    }

    virtual const char* what() const noexcept {
        return SettingsException::what();
    }

};

class GroupParameterNotFoundException : public SettingsException {
private:
    const std::string group;

public:
    GroupParameterNotFoundException(const std::string& s) : group(s) {
        description = "Settings group " + this->group + " not found";
    }

    virtual const char* what() const noexcept {
        return SettingsException::what();
    }

};

class TypeMismatchException : public SettingsException {
public:
    TypeMismatchException() {
        description = "Il tipo di dato non e' coerente con quanto richiesto";
    }

    virtual const char* what() const noexcept {
        return SettingsException::what();
    }

};

}

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSMANAGEREXCEPTIONS_HPP
