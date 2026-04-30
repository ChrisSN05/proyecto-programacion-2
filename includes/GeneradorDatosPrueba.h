#ifndef PROYECTO_PROGRAMACION_2_SPIM_GENERADORDATOSPRUEBA_H
#define PROYECTO_PROGRAMACION_2_SPIM_GENERADORDATOSPRUEBA_H


#include <string>

class GeneradorDatosPrueba {
private:
    std::string formatearCodigoEquipo(int numero) const;

    std::string formatearCodigoIncidencia(int numero) const;

public:
    void generar(const std::string &rutaEquipos,
                 const std::string &rutaIncidencias) const;
};
#endif
