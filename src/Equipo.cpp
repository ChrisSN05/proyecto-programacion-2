#include "Equipo.h"
#include "Incidencia.h"
#include "OperacionInconsistenteException.h"

using namespace std;

Equipo::Equipo(const string &codigo,
               const string &nombre,
               int criticidad,
               int estado)
    : codigo(codigo),
      nombre(nombre),
      criticidad(criticidad),
      estado(estado),
      tiempoInactivo(0),
      ultimoDiaAtencion(0),
      prioridad(0.0) {
}

void Equipo::establecerEstado(int nuevoEstado) {
    if (nuevoEstado < 0) {
        estado = 0;
    } else if (nuevoEstado > 100) {
        estado = 100;
    } else {
        estado = nuevoEstado;
    }
}

void Equipo::prepararMantenimiento() {
}

bool Equipo::cerrarUnaIncidenciaActiva() {
    for (Incidencia *incidencia: incidencias) {
        if (incidencia != nullptr && incidencia->estaActiva()) {
            incidencia->cerrar();
            return true;
        }
    }

    return false;
}

void Equipo::realizarMantenimiento(int diaActual) {
    if (diaActual < 1 || diaActual > 30) {
        throw OperacionInconsistenteException("El dia de mantenimiento esta fuera del rango permitido");
    }

    prepararMantenimiento();
    aplicarMantenimientoEspecifico();
    cerrarUnaIncidenciaActiva();

    tiempoInactivo = 0;
    ultimoDiaAtencion = diaActual;
}

string Equipo::obtenerCodigo() const {
    return codigo;
}

string Equipo::obtenerNombre() const {
    return nombre;
}

int Equipo::obtenerCriticidad() const {
    return criticidad;
}

int Equipo::obtenerEstado() const {
    return estado;
}

int Equipo::obtenerTiempoInactivo() const {
    return tiempoInactivo;
}

int Equipo::obtenerUltimoDiaAtencion() const {
    return ultimoDiaAtencion;
}

double Equipo::obtenerPrioridad() const {
    return prioridad;
}

void Equipo::establecerPrioridad(double nuevaPrioridad) {
    prioridad = nuevaPrioridad;
}

void Equipo::aumentarTiempoInactivo() {
    if (estado<60 || tieneIncidenciasActivas()) {
        tiempoInactivo++;
    }
}

void Equipo::agregarIncidencia(Incidencia *incidencia) {
    if (incidencia == nullptr) {
        throw OperacionInconsistenteException("No se puede agregar una incidencia nula al equipo");
    }

    incidencias.push_back(incidencia);
}

int Equipo::obtenerCantidadIncidenciasActivas() const {
    int contador = 0;

    for (const Incidencia *incidencia: incidencias) {
        if (incidencia != nullptr && incidencia->estaActiva()) {
            contador++;
        }
    }

    return contador;
}

bool Equipo::tieneIncidenciasActivas() const {
    return obtenerCantidadIncidenciasActivas() > 0;
}
