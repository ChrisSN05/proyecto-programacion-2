#ifndef PROYECTO_PROGRAMACION_2_SPIM_EQUIPO_H
#define PROYECTO_PROGRAMACION_2_SPIM_EQUIPO_H


#include <string>
#include <vector>

class Incidencia;

class Equipo {
private:
    std::string codigo;
    std::string nombre;
    int criticidad;
    int estado;
    int tiempoInactivo;
    int ultimoDiaAtencion;
    double prioridad;
    std::vector<Incidencia *> incidencias;

protected:
    void establecerEstado(int nuevoEstado);

    virtual void prepararMantenimiento();

    virtual void aplicarMantenimientoEspecifico() = 0;

    bool cerrarUnaIncidenciaActiva();

public:
    Equipo(const std::string &codigo,
           const std::string &nombre,

           int criticidad,
           int estado);

    virtual ~Equipo() = default;

    virtual void degradar() = 0;

    virtual std::string obtenerTipo() const = 0;

    void realizarMantenimiento(int diaActual);

    std::string obtenerCodigo() const;

    std::string obtenerNombre() const;

    int obtenerCriticidad() const;

    int obtenerEstado() const;

    int obtenerTiempoInactivo() const;

    int obtenerUltimoDiaAtencion() const;

    double obtenerPrioridad() const;

    void establecerPrioridad(double nuevaPrioridad);

    void aumentarTiempoInactivo();

    void agregarIncidencia(Incidencia *incidencia);

    int obtenerCantidadIncidenciasActivas() const;

    bool tieneIncidenciasActivas() const;
};

#endif
