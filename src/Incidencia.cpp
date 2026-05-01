#include "Incidencia.h"
#include "Equipo.h"

using namespace std;

Incidencia::Incidencia(const string &codigo,
                       const string &codigoEquipo,
                       const string &severidad,
                       int diaRegistro)
    : codigo(codigo),
      codigoEquipo(codigoEquipo),
      severidad(severidad),
      diaRegistro(diaRegistro),
      activa(false),
      cerrada(false),
      equipo(nullptr) {
}

string Incidencia::obtenerCodigo() const {
    return codigo;
}

string Incidencia::obtenerCodigoEquipo() const {
    return codigoEquipo;
}

string Incidencia::obtenerSeveridad() const {
    return severidad;
}

int Incidencia::obtenerDiaRegistro() const {
    return diaRegistro;
}

bool Incidencia::estaActiva() const {
    return activa;
}

bool Incidencia::estaCerrada() const {
    return cerrada;
}

bool Incidencia::debeActivarse(int diaActual) const {
    return !activa && !cerrada && diaActual >= diaRegistro;
}

void Incidencia::activar(Equipo &equipoAsignado) {
    equipo = &equipoAsignado;
    activa = true;
}

void Incidencia::cerrar() {
    activa = false;
    cerrada = true;
}

Equipo *Incidencia::obtenerEquipo() const {
    return equipo;
}
