#ifndef PROYECTO_PROGRAMACION_2_SPIM_CARGARDATOS_H
#define PROYECTO_PROGRAMACION_2_SPIM_CARGARDATOS_H


#include "Equipo.h"
#include "Incidencia.h"
#include <memory>
#include <string>
#include <vector>

class CargadorDatos {
private:
    std::vector<std::string> separar(const std::string &linea, char separador) const;

    std::string limpiarEspacios(const std::string &texto) const;

    int convertirEntero(const std::string &texto, const std::string &campo, int numeroLinea) const;

    void validarEquipo(const std::vector<std::string> &partes, int numeroLinea) const;

    void validarIncidencia(const std::vector<std::string> &partes, int numeroLinea) const;

    bool existeEquipo(const std::vector<std::unique_ptr<Equipo> > &equipos,
                      const std::string &codigo) const;

public:
    void cargarEquipos(const std::string &ruta,
                       std::vector<std::unique_ptr<Equipo> > &equipos) const;

    void cargarIncidencias(const std::string &ruta,
                           const std::vector<std::unique_ptr<Equipo> > &equipos,
                           std::vector<std::unique_ptr<Incidencia> > &incidencias) const;
};
#endif