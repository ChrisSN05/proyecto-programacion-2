#ifndef PROYECTO_PROGRAMACION_2_SPIM_FORMATOINVALIDOEXCEPTION_H
#define PROYECTO_PROGRAMACION_2_SPIM_FORMATOINVALIDOEXCEPTION_H

#include <stdexcept>
#include <string>

class FormatoInvalidoException : public std::runtime_error {
public:
    explicit FormatoInvalidoException(const std::string &mensaje)
        : std::runtime_error(mensaje) {
    }
};
#endif