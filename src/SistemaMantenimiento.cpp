#include "SistemaMantenimiento.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include "EquipoMedico.h"
#include "Simulador.h"
#include "OperacionInconsistenteException.h"
#include "FormatoInvalidoException.h"

using namespace std;

bool SistemaMantenimiento::existeEquipo(const string &codigo) const {
    for (const auto &equipo: equipos) {
        if (equipo->obtenerCodigo() == codigo) {
            return true;
        }
    }

    return false;
}

void SistemaMantenimiento::validarCodigoNoVacio(const string &codigo) const {
    if (codigo.empty()) {
        throw FormatoInvalidoException("El codigo no puede estar vacio");
    }
}

void SistemaMantenimiento::validarRango(const string &campo, int valor, int minimo, int maximo) const {
    if (valor < minimo || valor > maximo) {
        throw FormatoInvalidoException(
            "El campo " + campo + " debe estar entre " + to_string(minimo) + " y " + to_string(maximo));
    }
}

void SistemaMantenimiento::generarDatosPrueba() {
    generadorDatosPrueba.generar("Archivos/equipos.txt", "Archivos/incidencias.txt");
}

void SistemaMantenimiento::cargarDatosDesdeArchivos() {
    cargadorDatos.cargarEquipos("Archivos/equipos.txt", equipos);
    cargadorDatos.cargarIncidencias("Archivos/incidencias.txt", equipos, incidencias);
}

void SistemaMantenimiento::registrarEquipoManual(const string &tipo,
                                                 const string &codigo,
                                                 const string &nombre,
                                                 int criticidad,
                                                 int estado) {
    validarCodigoNoVacio(codigo);

    if (nombre.empty()) {
        throw FormatoInvalidoException("El nombre del equipo no puede estar vacio");
    }

    validarRango("criticidad", criticidad, 1, 10);
    validarRango("estado", estado, 0, 100);

    if (existeEquipo(codigo)) {
        throw OperacionInconsistenteException("Ya existe un equipo con el codigo: " + codigo);
    }

    if (tipo == "COMPUTO") {
        equipos.push_back(make_unique<EquipoComputo>(codigo, nombre, criticidad, estado));
    } else if (tipo == "LABORATORIO") {
        equipos.push_back(make_unique<EquipoLaboratorio>(codigo, nombre, criticidad, estado));
    } else if (tipo == "MEDICO") {
        equipos.push_back(make_unique<EquipoMedico>(codigo, nombre, criticidad, estado));
    } else {
        throw FormatoInvalidoException("Tipo de equipo invalido, use COMPUTO, LABORATORIO o MEDICO");
    }
}

void SistemaMantenimiento::registrarIncidenciaManual(const string &codigo,
                                                     const string &codigoEquipo,
                                                     const string &severidad,
                                                     int diaRegistro) {
    validarCodigoNoVacio(codigo);
    validarCodigoNoVacio(codigoEquipo);
    validarRango("diaRegistro", diaRegistro, 1, 30);

    if (severidad != "ALTA" && severidad != "MEDIA" && severidad != "BAJA") {
        throw FormatoInvalidoException("La severidad debe ser ALTA, MEDIA o BAJA");
    }

    if (!existeEquipo(codigoEquipo)) {
        throw OperacionInconsistenteException("No existe el equipo indicado para la incidencia");
    }

    incidencias.push_back(make_unique<Incidencia>(codigo, codigoEquipo, severidad, diaRegistro));
}

void SistemaMantenimiento::ejecutarSimulacion() {
    Simulador simulador(equipos, incidencias);
    simulador.ejecutar();
}

int SistemaMantenimiento::obtenerCantidadEquipos() const {
    return static_cast<int>(equipos.size());
}

int SistemaMantenimiento::obtenerCantidadIncidencias() const {
    return static_cast<int>(incidencias.size());
}
