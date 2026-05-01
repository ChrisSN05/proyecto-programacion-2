#ifndef PROYECTO_PROGRAMACION_2_SPIM_INCIDENCIA_H
#define PROYECTO_PROGRAMACION_2_SPIM_INCIDENCIA_H


#include <string>

class Equipo;


class Incidencia {
private:
    std::string codigo;
    std::string descripcion;
    std::string severidad;
    int diaRegistro;
    bool activa;
    bool cerrada;
    Equipo *equipo;

public:
    Incidencia(const std::string &codigo,
               const std::string &descripcion,
               const std::string &severidad,
               int diaRegistro);

    std::string obtenerCodigo() const;

    std::string obtenerCodigoEquipo() const;

    std::string obtenerSeveridad() const;

    int obtenerDiaRegistro() const;

    bool estaActiva() const;

    bool estaCerrada() const;

    bool debeActivarse(int diaActual) const;

    void activar(Equipo &equipoAsignado);

    void cerrar();

    Equipo *obtenerEquipo() const;
};

#endif
