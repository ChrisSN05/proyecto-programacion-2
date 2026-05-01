#include "GeneradorReporte.h"
#include "ArchivoInvalidoException.h"
#include <filesystem>
#include <fstream>
#include <iomanip>

using namespace std;

int GeneradorReporte::calcularBacklogPendiente(const vector<Equipo *> &equipos) const {
    int total = 0;

    for (const Equipo *equipo: equipos) {
        total += equipo->obtenerCantidadIncidenciasActivas();
    }

    return total;
}

string GeneradorReporte::calcularRiesgoGlobal(const vector<Equipo *> &equipos) const {
    if (equipos.empty()) {
        return "SIN DATOS";
    }

    double suma = 0.0;

    for (const Equipo *equipo: equipos) {
        suma += equipo->obtenerPrioridad();
    }

    double promedio = suma / equipos.size();

    if (promedio >= 7.0) {
        return "ALTO";
    }

    if (promedio >= 4.0) {
        return "MEDIO";
    }

    return "BAJO";
}

void GeneradorReporte::generarReporteDiario(int dia,
                                            const vector<Equipo *> &equiposOrdenados,
                                            const vector<Equipo *> &equiposAtendidos) const {
    filesystem::create_directories("Reportes");

    string ruta = "Reportes/reporte_dia_" + to_string(dia) + ".txt";
    ofstream archivo(ruta);

    if (!archivo.is_open()) {
        throw ArchivoInvalidoException("No se pudo crear el reporte diario: " + ruta);
    }

    archivo << fixed << setprecision(2);

    archivo << "Dia " << dia << endl;
    archivo << "========================================" << endl;
    archivo << "Estado general de la simulacion: EN PROCESO" << endl;
    archivo << "Riesgo global del laboratorio: " << calcularRiesgoGlobal(equiposOrdenados) << endl;
    archivo << "Backlog pendiente: " << calcularBacklogPendiente(equiposOrdenados) << endl;

    archivo << endl;
    archivo << "Top prioridad: ";
    for (int i = 0; i < 3 && i < static_cast<int>(equiposOrdenados.size()); i++) {
        archivo << equiposOrdenados[i]->obtenerCodigo()
                << " (" << equiposOrdenados[i]->obtenerPrioridad() << ")";

        if (i < 2 && i + 1 < static_cast<int>(equiposOrdenados.size())) {
            archivo << ", ";
        }
    }

    archivo << endl;

    archivo << "Equipos atendidos: ";
    for (int i = 0; i < static_cast<int>(equiposAtendidos.size()); i++) {
        archivo << equiposAtendidos[i]->obtenerCodigo();

        if (i + 1 < static_cast<int>(equiposAtendidos.size())) {
            archivo << ", ";
        }
    }

    archivo << endl;

    archivo << endl;
    archivo << "Equipos pendientes de atencion:" << endl;

    bool hayPendientes = false;

    for (const Equipo *equipo: equiposOrdenados) {
        bool fueAtendido = false;

        for (const Equipo *atendido: equiposAtendidos) {
            if (atendido->obtenerCodigo() == equipo->obtenerCodigo()) {
                fueAtendido = true;
                break;
            }
        }

        if (!fueAtendido && (equipo->tieneIncidenciasActivas() || equipo->obtenerEstado() < 60)) {
            archivo << equipo->obtenerCodigo()
                    << " | " << equipo->obtenerNombre()
                    << " | Estado: " << equipo->obtenerEstado()
                    << " | Incidencias activas: " << equipo->obtenerCantidadIncidenciasActivas()
                    << " | Prioridad: " << equipo->obtenerPrioridad()
                    << endl;

            hayPendientes = true;
        }
    }

    if (!hayPendientes) {
        archivo << "No hay equipos pendientes de atencion critica" << endl;
    }

    archivo << endl;
    archivo << "Prioridades calculadas:" << endl;

    for (const Equipo *equipo: equiposOrdenados) {
        archivo << equipo->obtenerCodigo()
                << " | " << equipo->obtenerNombre()
                << " | Tipo: " << equipo->obtenerTipo()
                << " | Criticidad: " << equipo->obtenerCriticidad()
                << " | Incidencias activas: " << equipo->obtenerCantidadIncidenciasActivas()
                << " | Tiempo inactivo: " << equipo->obtenerTiempoInactivo()
                << " | Prioridad: " << equipo->obtenerPrioridad()
                << " | Estado: " << equipo->obtenerEstado()
                << endl;
    }
}

void GeneradorReporte::generarReporteFinal(const vector<Equipo *> &equiposOrdenados) const {
    filesystem::create_directories("Reportes");

    string ruta = "Reportes/reporte_final.txt";
    ofstream archivo(ruta);

    if (!archivo.is_open()) {
        throw ArchivoInvalidoException("No se pudo crear el reporte final");
    }

    archivo << fixed << setprecision(2);

    archivo << "Reporte final de simulacion" << endl;
    archivo << "========================================" << endl;
    archivo << "Estado general de la simulacion: FINALIZADA" << endl;
    archivo << "Cantidad de equipos: " << equiposOrdenados.size() << endl;
    archivo << "Backlog pendiente: " << calcularBacklogPendiente(equiposOrdenados) << endl;
    archivo << "Riesgo global final: " << calcularRiesgoGlobal(equiposOrdenados) << endl;

    archivo << endl;
    archivo << "Equipos pendientes de atencion al finalizar:" << endl;

    bool hayPendientes = false;

    for (const Equipo *equipo: equiposOrdenados) {
        if (equipo->tieneIncidenciasActivas() || equipo->obtenerEstado() < 60) {
            archivo << equipo->obtenerCodigo()
                    << " | " << equipo->obtenerNombre()
                    << " | Estado: " << equipo->obtenerEstado()
                    << " | Incidencias activas: " << equipo->obtenerCantidadIncidenciasActivas()
                    << " | Prioridad: " << equipo->obtenerPrioridad()
                    << endl;

            hayPendientes = true;
        }
    }

    if (!hayPendientes) {
        archivo << "No hay equipos pendientes de atencion critica" << endl;
    }

    archivo << endl;
    archivo << "Estado final de equipos:" << endl;

    for (const Equipo *equipo: equiposOrdenados) {
        archivo << equipo->obtenerCodigo()
                << " | " << equipo->obtenerNombre()
                << " | Tipo: " << equipo->obtenerTipo()
                << " | Estado: " << equipo->obtenerEstado()
                << " | Prioridad: " << equipo->obtenerPrioridad()
                << " | Incidencias activas: " << equipo->obtenerCantidadIncidenciasActivas()
                << endl;
    }
}
