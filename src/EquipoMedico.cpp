#include "EquipoMedico.h"

using namespace std;

EquipoMedico::EquipoMedico(const string& codigo,
                           const string& nombre,
                           int criticidad,
                           int estado)
    : Equipo(codigo, nombre, criticidad, estado) {
}

void EquipoMedico::degradar() {
    establecerEstado(obtenerEstado() - 5);
}

void EquipoMedico::aplicarMantenimientoEspecifico() {
    establecerEstado(obtenerEstado() + 30);
}

string EquipoMedico::obtenerTipo() const {
    return "MEDICO";
}

void EquipoMedico::calibrarSensores() {
    establecerEstado(obtenerEstado() + 5);
}