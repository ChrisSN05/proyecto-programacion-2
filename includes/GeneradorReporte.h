#ifndef PROYECTO_PROGRAMACION_2_SPIM_GENERADORREPORTE_H
#define PROYECTO_PROGRAMACION_2_SPIM_GENERADORREPORTE_H


#include "Equipo.h"
#include <string>
#include <vector>

class GeneradorReporte {
private:
    std::string calcularRiesgoGlobal(const std::vector<Equipo *> &equipos) const;

    int calcularBacklogPendiente(const std::vector<Equipo *> &equipos) const;

public:
    void generarReporteDiario(int dia,
                              const std::vector<Equipo *> &equiposOrdenados,
                              const std::vector<Equipo *> &equiposAtendidos) const;

    void generarReporteFinal(const std::vector<Equipo *> &equiposOrdenados) const;
};
#endif
