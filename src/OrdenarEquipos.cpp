#include "OrdenadorEquipos.h"

using namespace std;

void OrdenadorEquipos::ordenarPorPrioridad(vector<Equipo*>& equipos) {
    if (!equipos.empty()) {
        ordenarPorPrioridadRecursivo(equipos, 0, static_cast<int>(equipos.size()) - 1);
    }
}

void OrdenadorEquipos::ordenarPorPrioridadRecursivo(vector<Equipo*>& equipos, int izquierda, int derecha) {
    if (izquierda >= derecha) {
        return;
    }

    int medio = izquierda + (derecha - izquierda) / 2;

    ordenarPorPrioridadRecursivo(equipos, izquierda, medio);
    ordenarPorPrioridadRecursivo(equipos, medio + 1, derecha);
    mezclarPorPrioridad(equipos, izquierda, medio, derecha);
}

void OrdenadorEquipos::mezclarPorPrioridad(vector<Equipo*>& equipos, int izquierda, int medio, int derecha) {
    vector<Equipo*> temporal;

    int i = izquierda;
    int j = medio + 1;

    while (i <= medio && j <= derecha) {
        if (equipos[i]->obtenerPrioridad() >= equipos[j]->obtenerPrioridad()) {
            temporal.push_back(equipos[i]);
            i++;
        } else {
            temporal.push_back(equipos[j]);
            j++;
        }
    }

    while (i <= medio) {
        temporal.push_back(equipos[i]);
        i++;
    }

    while (j <= derecha) {
        temporal.push_back(equipos[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temporal.size()); k++) {
        equipos[izquierda + k] = temporal[k];
    }
}

void OrdenadorEquipos::ordenarPorCodigo(vector<Equipo*>& equipos) {
    if (!equipos.empty()) {
        ordenarPorCodigoRecursivo(equipos, 0, static_cast<int>(equipos.size()) - 1);
    }
}

void OrdenadorEquipos::ordenarPorCodigoRecursivo(vector<Equipo*>& equipos, int izquierda, int derecha) {
    if (izquierda >= derecha) {
        return;
    }

    int medio = izquierda + (derecha - izquierda) / 2;

    ordenarPorCodigoRecursivo(equipos, izquierda, medio);
    ordenarPorCodigoRecursivo(equipos, medio + 1, derecha);
    mezclarPorCodigo(equipos, izquierda, medio, derecha);
}

void OrdenadorEquipos::mezclarPorCodigo(vector<Equipo*>& equipos, int izquierda, int medio, int derecha) {
    vector<Equipo*> temporal;

    int i = izquierda;
    int j = medio + 1;

    while (i <= medio && j <= derecha) {
        if (equipos[i]->obtenerCodigo() <= equipos[j]->obtenerCodigo()) {
            temporal.push_back(equipos[i]);
            i++;
        } else {
            temporal.push_back(equipos[j]);
            j++;
        }
    }

    while (i <= medio) {
        temporal.push_back(equipos[i]);
        i++;
    }

    while (j <= derecha) {
        temporal.push_back(equipos[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temporal.size()); k++) {
        equipos[izquierda + k] = temporal[k];
    }
}