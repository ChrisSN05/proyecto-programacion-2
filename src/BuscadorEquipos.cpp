#include "BuscadorEquipos.h"

using namespace std;

Equipo *BuscadorEquipos::buscarPorCodigo(vector<Equipo *> equiposOrdenadosPorCodigo,
                                         const string &codigoBuscado) const {
    int izquierda = 0;
    int derecha = static_cast<int>(equiposOrdenadosPorCodigo.size()) - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (equiposOrdenadosPorCodigo[medio]->obtenerCodigo() == codigoBuscado) {
            return equiposOrdenadosPorCodigo[medio];
        } else if (equiposOrdenadosPorCodigo[medio]->obtenerCodigo() < codigoBuscado) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return nullptr;
}
