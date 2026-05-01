#include "Simulador.h"
#include "EquipoComputo.h"
#include "EquipoMedico.h"
#include "OperacionInconsistenteException.h"
#include <iostream>

using namespace std;

Simulador::Simulador(vector<unique_ptr<Equipo> > &equipos,
                     vector<unique_ptr<Incidencia> > &incidencias)
    : equipos(equipos),
      incidencias(incidencias) {
}

vector<Equipo *> Simulador::obtenerPunterosEquipos() const {
    vector<Equipo *> punteros;

    for (const auto &equipo: equipos) {
        punteros.push_back(equipo.get());
    }

    return punteros;
}

void Simulador::actualizarIncidencias(int diaActual) {
    vector<Equipo *> equiposPorCodigo = obtenerPunterosEquipos();
    ordenadorEquipos.ordenarPorCodigo(equiposPorCodigo);

    for (auto &incidencia: incidencias) {
        if (incidencia->debeActivarse(diaActual)) {
            Equipo *equipo = buscadorEquipos.buscarPorCodigo(equiposPorCodigo, incidencia->obtenerCodigoEquipo());

            if (equipo == nullptr) {
                throw OperacionInconsistenteException(
                    "No se encontro el equipo de la incidencia: " + incidencia->obtenerCodigo());
            }

            incidencia->activar(*equipo);
            equipo->agregarIncidencia(incidencia.get());
        }
    }
}

void Simulador::degradarEquipos() {
    for (auto &equipo: equipos) {
        equipo->degradar();
        equipo->aumentarTiempoInactivo();
    }
}

void Simulador::calcularPrioridades() {
    for (auto &equipo: equipos) {
        double prioridad = calculadorPrioridad.calcular(*equipo);
        equipo->establecerPrioridad(prioridad);
    }
}

vector<Equipo *> Simulador::seleccionarEquiposAtendidos(const vector<Equipo *> &equiposOrdenados) const {
    vector<Equipo *> seleccionados;

    for (int i = 0; i < 3 && i < static_cast<int>(equiposOrdenados.size()); i++) {
        seleccionados.push_back(equiposOrdenados[i]);
    }

    return seleccionados;
}

void Simulador::aplicarMantenimiento(vector<Equipo *> &equiposAtendidos, int diaActual) {
    for (Equipo *equipo: equiposAtendidos) {
        EquipoComputo *equipoComputo = dynamic_cast<EquipoComputo *>(equipo);
        if (equipoComputo != nullptr) {
            equipoComputo->revisarSoftware();
        }

        EquipoMedico *equipoMedico = dynamic_cast<EquipoMedico *>(equipo);
        if (equipoMedico != nullptr) {
            equipoMedico->calibrarSensores();
        }

        equipo->realizarMantenimiento(diaActual);
    }
}

void Simulador::ejecutar() {
    if (equipos.empty()) {
        throw OperacionInconsistenteException("No se puede ejecutar la simulacion sin equipos");
    }

    if (incidencias.empty()) {
        throw OperacionInconsistenteException("No se puede ejecutar la simulacion sin incidencias");
    }

    for (int dia = 1; dia <= 30; dia++) {
        degradarEquipos();
        actualizarIncidencias(dia);
        calcularPrioridades();

        vector<Equipo *> equiposOrdenados = obtenerPunterosEquipos();
        ordenadorEquipos.ordenarPorPrioridad(equiposOrdenados);

        vector<Equipo *> equiposAtendidos = seleccionarEquiposAtendidos(equiposOrdenados);

        aplicarMantenimiento(equiposAtendidos, dia);
        calcularPrioridades();

        equiposOrdenados = obtenerPunterosEquipos();
        ordenadorEquipos.ordenarPorPrioridad(equiposOrdenados);

        generadorReporte.generarReporteDiario(dia, equiposOrdenados, equiposAtendidos);

        cout << "Dia " << dia << " simulado correctamente" << endl;
    }

    vector<Equipo *> equiposOrdenados = obtenerPunterosEquipos();
    ordenadorEquipos.ordenarPorPrioridad(equiposOrdenados);
    generadorReporte.generarReporteFinal(equiposOrdenados);
}
