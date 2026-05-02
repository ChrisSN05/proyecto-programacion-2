#include "EquipoLaboratorio.h"

using namespace std;

EquipoLaboratorio::EquipoLaboratorio(const string& codigo,
                                     const string& nombre,
                                     int criticidad,
                                     int estado)
    : Equipo(codigo, nombre, criticidad, estado) {
}

void EquipoLaboratorio::degradar() {
    establecerEstado(obtenerEstado() - 3);
}

void EquipoLaboratorio::aplicarMantenimientoEspecifico() {
    establecerEstado(obtenerEstado() + 20);
}

string EquipoLaboratorio::obtenerTipo() const {
    return "LABORATORIO";
}