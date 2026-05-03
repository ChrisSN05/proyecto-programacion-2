#include "CargarDatos.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include "EquipoMedico.h"
#include "ArchivoInvalidoException.h"
#include "FormatoInvalidoException.h"
#include "OperacionInconsistenteException.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<string> CargarDatos::separar(const string &linea, char separador) const {
    vector<string> partes;
    string parte;
    stringstream ss(linea);

    while (getline(ss, parte, separador)) {
        partes.push_back(limpiarEspacios(parte));
    }

    return partes;
}

string CargarDatos::limpiarEspacios(const string &texto) const {
    int inicio = 0;
    int fin = static_cast<int>(texto.size()) - 1;

    while (inicio <= fin && texto[inicio] == ' ') {
        inicio++;
    }

    while (fin >= inicio && texto[fin] == ' ') {
        fin--;
    }

    if (inicio > fin) {
        return "";
    }

    return texto.substr(inicio, fin - inicio + 1);
}

int CargarDatos::convertirEntero(const string &texto, const string &campo, int numeroLinea) const {
    try {
        size_t posicion = 0;
        int valor = stoi(texto, &posicion);

        if (posicion != texto.size()) {
            throw FormatoInvalidoException(
                "El campo " + campo + " tiene caracteres invalidos en la linea " + to_string(numeroLinea));
        }

        return valor;
    } catch (const invalid_argument &) {
        throw FormatoInvalidoException("El campo " + campo + " no es numerico en la linea " + to_string(numeroLinea));
    } catch (const out_of_range &) {
        throw FormatoInvalidoException(
            "El campo " + campo + " esta fuera de rango en la linea " + to_string(numeroLinea));
    }
}

void CargarDatos::validarEquipo(const vector<string> &partes, int numeroLinea) const {
    if (partes.size() != 5) {
        throw FormatoInvalidoException("Formato invalido de equipo en la linea " + to_string(numeroLinea));
    }

    if (partes[0] != "COMPUTO" && partes[0] != "LABORATORIO" && partes[0] != "MEDICO") {
        throw FormatoInvalidoException("Tipo de equipo invalido en la linea " + to_string(numeroLinea));
    }

    if (partes[1].empty() || partes[2].empty()) {
        throw FormatoInvalidoException("Codigo o nombre vacio en la linea " + to_string(numeroLinea));
    }
}

void CargarDatos::validarIncidencia(const vector<string> &partes, int numeroLinea) const {
    if (partes.size() != 4) {
        throw FormatoInvalidoException("Formato invalido de incidencia en la linea " + to_string(numeroLinea));
    }

    if (partes[0].empty() || partes[1].empty()) {
        throw FormatoInvalidoException("Codigo de incidencia o equipo vacio en la linea " + to_string(numeroLinea));
    }

    if (partes[2] != "ALTA" && partes[2] != "MEDIA" && partes[2] != "BAJA") {
        throw FormatoInvalidoException("Severidad invalida en la linea " + to_string(numeroLinea));
    }
}

bool CargarDatos::existeEquipo(const vector<unique_ptr<Equipo> > &equipos, const string &codigo) const {
    for (const auto &equipo: equipos) {
        if (equipo->obtenerCodigo() == codigo) {
            return true;
        }
    }

    return false;
}

void CargarDatos::cargarEquipos(const string &ruta,
                                vector<unique_ptr<Equipo> > &equipos) const {
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        throw ArchivoInvalidoException("No se pudo abrir el archivo de equipos: " + ruta);
    }

    equipos.clear();

    string linea;
    int numeroLinea = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;

        if (linea.empty()) {
            continue;
        }

        vector<string> partes = separar(linea, ';');
        validarEquipo(partes, numeroLinea);

        string tipo = partes[0];
        string codigo = partes[1];
        string nombre = partes[2];
        int criticidad = convertirEntero(partes[3], "criticidad", numeroLinea);
        int estado = convertirEntero(partes[4], "estado", numeroLinea);

        if (criticidad < 1 || criticidad > 10) {
            throw FormatoInvalidoException(
                "La criticidad debe estar entre 1 y 10 en la linea " + to_string(numeroLinea));
        }

        if (estado < 0 || estado > 100) {
            throw FormatoInvalidoException("El estado debe estar entre 0 y 100 en la linea " + to_string(numeroLinea));
        }

        if (existeEquipo(equipos, codigo)) {
            throw OperacionInconsistenteException("Codigo de equipo duplicado: " + codigo);
        }

        if (tipo == "COMPUTO") {
            equipos.push_back(make_unique<EquipoComputo>(codigo, nombre, criticidad, estado));
        } else if (tipo == "LABORATORIO") {
            equipos.push_back(make_unique<EquipoLaboratorio>(codigo, nombre, criticidad, estado));
        } else {
            equipos.push_back(make_unique<EquipoMedico>(codigo, nombre, criticidad, estado));
        }
    }

    if (equipos.empty()) {
        throw ArchivoInvalidoException("El archivo de equipos no contiene datos validos");
    }
}

void CargarDatos::cargarIncidencias(const string &ruta,
                                    const vector<unique_ptr<Equipo> > &equipos,
                                    vector<unique_ptr<Incidencia> > &incidencias) const {
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        throw ArchivoInvalidoException("No se pudo abrir el archivo de incidencias: " + ruta);
    }

    incidencias.clear();

    string linea;
    int numeroLinea = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;

        if (linea.empty()) {
            continue;
        }

        vector<string> partes = separar(linea, ';');
        validarIncidencia(partes, numeroLinea);

        string codigo = partes[0];
        string codigoEquipo = partes[1];
        string severidad = partes[2];
        int diaRegistro = convertirEntero(partes[3], "diaRegistro", numeroLinea);

        if (diaRegistro < 1 || diaRegistro > 30) {
            throw FormatoInvalidoException(
                "El dia de incidencia debe estar entre 1 y 30 en la linea " + to_string(numeroLinea));
        }

        if (!existeEquipo(equipos, codigoEquipo)) {
            throw OperacionInconsistenteException(
                "La incidencia " + codigo + " apunta a un equipo inexistente: " + codigoEquipo);
        }

        incidencias.push_back(make_unique<Incidencia>(codigo, codigoEquipo, severidad, diaRegistro));
    }

    if (incidencias.empty()) {
        throw ArchivoInvalidoException("El archivo de incidencias no contiene datos validos");
    }
}
