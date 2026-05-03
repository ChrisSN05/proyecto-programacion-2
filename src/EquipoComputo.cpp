#include "EquipoComputo.h"

using namespace std;

EquipoComputo::EquipoComputo(const string& codigo,
                             const string& nombre,
                             int criticidad,
                             int estado)
    : Equipo(codigo, nombre, criticidad, estado) {
}

void EquipoComputo::degradar() {
    establecerEstado(obtenerEstado() - 4);
}

void EquipoComputo::aplicarMantenimientoEspecifico() {
    establecerEstado(obtenerEstado() + 25);
}

string EquipoComputo::obtenerTipo() const {
    return "COMPUTO";
}

void EquipoComputo::revisarSoftware() {
    establecerEstado(obtenerEstado() + 3);
}