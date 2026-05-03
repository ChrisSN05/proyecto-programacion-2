#ifndef PROYECTO_PROGRAMACION_2_SPIM_MENU_H
#define PROYECTO_PROGRAMACION_2_SPIM_MENU_H


#include "SistemaMantenimiento.h"
#include <string>

class Menu {
private:
    SistemaMantenimiento sistema;

    int leerEntero(const std::string &mensaje, int minimo, int maximo) const;

    std::string leerTexto(const std::string &mensaje) const;

    void mostrarOpciones() const;

    void registrarEquipo();

    void registrarIncidencia();

public:
    void ejecutar();
};
#endif