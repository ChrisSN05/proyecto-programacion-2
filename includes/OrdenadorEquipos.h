#ifndef PROYECTO_PROGRAMACION_2_SPIM_ORDENADOREQUIPOS_H
#define PROYECTO_PROGRAMACION_2_SPIM_ORDENADOREQUIPOS_H


#include "Equipo.h"
#include <vector>

class OrdenadorEquipos {
private:
    void ordenarPorPrioridadRecursivo(std::vector<Equipo *> &equipos, int izquierda, int derecha);

    void mezclarPorPrioridad(std::vector<Equipo *> &equipos, int izquierda, int medio, int derecha);

    void ordenarPorCodigoRecursivo(std::vector<Equipo *> &equipos, int izquierda, int derecha);

    void mezclarPorCodigo(std::vector<Equipo *> &equipos, int izquierda, int medio, int derecha);

public:
    void ordenarPorPrioridad(std::vector<Equipo *> &equipos);

    void ordenarPorCodigo(std::vector<Equipo *> &equipos);
};

#endif