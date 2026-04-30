#ifndef PROYECTO_PROGRAMACION_2_SPIM_BUSCADOREQUIPOS_H
#define PROYECTO_PROGRAMACION_2_SPIM_BUSCADOREQUIPOS_H


#include "Equipo.h"
#include <string>
#include <vector>

class BuscadorEquipos {
public:
    Equipo *buscarPorCodigo(std::vector<Equipo *> equiposOrdenadosPorCodigo,
                            const std::string &codigoBuscado) const;
};
#endif
