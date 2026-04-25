#ifndef PROYECTO_PROGRAMACION_2_SPIM_SIMULADOR_H
#define PROYECTO_PROGRAMACION_2_SPIM_SIMULADOR_H


#include "Equipo.h"
#include "Incidencia.h"
#include "CalculadorPrioridad.h"
#include "OrdenadorEquipos.h"
#include "BuscadorEquipos.h"
#include "GeneradorReporte.h"
#include <memory>
#include <vector>

class Simulador {
private:
    std::vector<std::unique_ptr<Equipo> > &equipos;
    std::vector<std::unique_ptr<Incidencia> > &incidencias;

    CalculadorPrioridad calculadorPrioridad;
    OrdenadorEquipos ordenadorEquipos;
    BuscadorEquipos buscadorEquipos;
    GeneradorReporte generadorReporte;

    std::vector<Equipo *> obtenerPunterosEquipos() const;

    void actualizarIncidencias(int diaActual);

    void degradarEquipos();

    void calcularPrioridades();

    std::vector<Equipo *> seleccionarEquiposAtendidos(const std::vector<Equipo *> &equiposOrdenados) const;

    void aplicarMantenimiento(std::vector<Equipo *> &equiposAtendidos, int diaActual);

public:
    Simulador(std::vector<std::unique_ptr<Equipo> > &equipos,
              std::vector<std::unique_ptr<Incidencia> > &incidencias);

    void ejecutar();
};

#endif
