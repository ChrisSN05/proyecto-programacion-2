#ifndef PROYECTO_PROGRAMACION_2_SPIM_SISTEMAMANTENIMIENTO_H
#define PROYECTO_PROGRAMACION_2_SPIM_SISTEMAMANTENIMIENTO_H


#include "Equipo.h"
#include "Incidencia.h"
#include "CargarDatos.h"
#include "GeneradorDatosPrueba.h"
#include <memory>
#include <string>
#include <vector>

class SistemaMantenimiento {
private:
    std::vector<std::unique_ptr<Equipo> > equipos;
    std::vector<std::unique_ptr<Incidencia> > incidencias;

    CargarDatos cargarDatos;
    GeneradorDatosPrueba generadorDatosPrueba;

    bool existeEquipo(const std::string &codigo) const;

    bool existenArchivosBase() const;

    void validarCodigoNoVacio(const std::string &codigo) const;

    void validarRango(const std::string &campo, int valor, int minimo, int maximo) const;

public:
    void inicializarSistema();

    void generarDatosPrueba();

    void cargarDatosDesdeArchivos();

    void registrarEquipoManual(const std::string &tipo,
                               const std::string &codigo,
                               const std::string &nombre,
                               int criticidad,
                               int estado);

    void registrarIncidenciaManual(const std::string &codigo,
                                   const std::string &codigoEquipo,
                                   const std::string &severidad,
                                   int diaRegistro);

    void ejecutarSimulacion();

    int obtenerCantidadEquipos() const;

    int obtenerCantidadIncidencias() const;
};
#endif
