#ifndef PROYECTO_PROGRAMACION_2_SPIM_ARCHIVOINVALIDOEXCEPTION_H
#define PROYECTO_PROGRAMACION_2_SPIM_ARCHIVOINVALIDOEXCEPTION_H


#include <stdexcept>
#include <string>

class ArchivoInvalidoException : public std::runtime_error {
public:
    explicit ArchivoInvalidoException(const std::string &mensaje)
        : std::runtime_error(mensaje) {
    }
};
#endif
