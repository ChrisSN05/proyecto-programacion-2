#include "CalculadorPrioridad.h"

double CalculadorPrioridad::calcular(const Equipo &equipo) const {
    return (equipo.obtenerCriticidad() * 0.5) +
           (equipo.obtenerCantidadIncidenciasActivas() * 0.3) +
           (equipo.obtenerTiempoInactivo() * 0.2);
}

