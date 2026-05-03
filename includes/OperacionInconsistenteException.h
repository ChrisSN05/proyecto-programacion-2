#ifndef PROYECTO_PROGRAMACION_2_SPIM_OPERACIONINCONSISTENTEEXCEPTION_H
#define PROYECTO_PROGRAMACION_2_SPIM_OPERACIONINCONSISTENTEEXCEPTION_H


#include <stdexcept>
#include <string>

class OperacionInconsistenteException : public std::runtime_error {
public:
    explicit OperacionInconsistenteException(const std::string &mensaje)
        : std::runtime_error(mensaje) {
    }
};
#endif