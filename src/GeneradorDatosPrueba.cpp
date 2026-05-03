#include "GeneradorDatosPrueba.h"
#include "ArchivoInvalidoException.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

string GeneradorDatosPrueba::formatearCodigoEquipo(int numero) const {
    stringstream ss;
    ss << "EQ-" << setw(3) << setfill('0') << numero;
    return ss.str();
}

string GeneradorDatosPrueba::formatearCodigoIncidencia(int numero) const {
    stringstream ss;
    ss << "INC-" << setw(3) << setfill('0') << numero;
    return ss.str();
}

void GeneradorDatosPrueba::generar(const string &rutaEquipos,
                                   const string &rutaIncidencias) const {
    filesystem::create_directories(filesystem::path(rutaEquipos).parent_path());
    filesystem::create_directories(filesystem::path(rutaIncidencias).parent_path());

    ofstream archivoEquipos(rutaEquipos);
    ofstream archivoIncidencias(rutaIncidencias);

    if (!archivoEquipos.is_open()) {
        throw ArchivoInvalidoException("No se pudo crear el archivo de equipos");
    }

    if (!archivoIncidencias.is_open()) {
        throw ArchivoInvalidoException("No se pudo crear el archivo de incidencias");
    }

    for (int i = 1; i <= 100; i++) {
        string tipo;

        if (i % 3 == 0) {
            tipo = "MEDICO";
        } else if (i % 3 == 1) {
            tipo = "COMPUTO";
        } else {
            tipo = "LABORATORIO";
        }

        int criticidad = 1 + ((i * 7) % 10);
        int estado = 55 + ((i * 13) % 46);

        archivoEquipos << tipo << ";"
                << formatearCodigoEquipo(i) << ";"
                << "Equipo " << i << ";"
                << criticidad << ";"
                << estado << endl;
    }

    for (int i = 1; i <= 300; i++) {
        int numeroEquipo = 1 + ((i * 17) % 100);
        int dia = 1 + ((i * 7) % 30);

        string severidad;

        if (i % 3 == 0) {
            severidad = "ALTA";
        } else if (i % 3 == 1) {
            severidad = "MEDIA";
        } else {
            severidad = "BAJA";
        }

        archivoIncidencias << formatearCodigoIncidencia(i) << ";"
                << formatearCodigoEquipo(numeroEquipo) << ";"
                << severidad << ";"
                << dia << endl;
    }
}
