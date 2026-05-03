#include "Menu.h"
#include <iostream>
#include <limits>
#include <exception>

using namespace std;

int Menu::leerEntero(const string &mensaje, int minimo, int maximo) const {
    int valor;

    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida, debe ingresar un numero" << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (valor < minimo || valor > maximo) {
            cout << "Valor fuera de rango, debe estar entre " << minimo << " y " << maximo << endl;
            continue;
        }

        return valor;
    }
}

string Menu::leerTexto(const string &mensaje) const {
    string texto;

    cout << mensaje;
    getline(cin, texto);

    return texto;
}

void Menu::mostrarOpciones() const {
    cout << endl;
    cout << "===== Sistema de Planificacion Inteligente de Mantenimiento =====" << endl;
    cout << "1. Regenerar datos de prueba" << endl;
    cout << "2. Cargar datos desde archivos" << endl;
    cout << "3. Registrar equipo manualmente" << endl;
    cout << "4. Registrar incidencia manualmente" << endl;
    cout << "5. Ejecutar simulacion de 30 dias" << endl;
    cout << "6. Ver resumen cargado" << endl;
    cout << "7. Salir" << endl;
}

void Menu::registrarEquipo() {
    cout << endl;
    cout << "Tipos validos: COMPUTO, LABORATORIO, MEDICO" << endl;

    string tipo = leerTexto("Tipo: ");
    string codigo = leerTexto("Codigo: ");
    string nombre = leerTexto("Nombre: ");
    int criticidad = leerEntero("Criticidad (1-10): ", 1, 10);
    int estado = leerEntero("Estado (0-100): ", 0, 100);

    sistema.registrarEquipoManual(tipo, codigo, nombre, criticidad, estado);

    cout << "Equipo registrado correctamente" << endl;
}

void Menu::registrarIncidencia() {
    cout << endl;
    cout << "Severidades validas: ALTA, MEDIA, BAJA" << endl;

    string codigo = leerTexto("Codigo de incidencia: ");
    string codigoEquipo = leerTexto("Codigo del equipo: ");
    string severidad = leerTexto("Severidad: ");
    int diaRegistro = leerEntero("Dia de aparicion (1-30): ", 1, 30);

    sistema.registrarIncidenciaManual(codigo, codigoEquipo, severidad, diaRegistro);

    cout << "Incidencia registrada correctamente" << endl;
}

void Menu::ejecutar() {
    int opcion;

    try {
        sistema.inicializarSistema();
        cout << "Datos iniciales cargados correctamente" << endl;
    } catch (const exception &error) {
        cout << "Error al inicializar datos: " << error.what() << endl;
    }
    do {
        mostrarOpciones();
        opcion = leerEntero("Seleccione una opcion: ", 1, 7);

        try {
            switch (opcion) {
                case 1:
                    sistema.generarDatosPrueba();
                    cout << "Datos de prueba regenerados y cargados correctamente" << endl;
                    break;

                case 2:
                    sistema.cargarDatosDesdeArchivos();
                    cout << "Datos cargados correctamente" << endl;
                    break;

                case 3:
                    registrarEquipo();
                    break;

                case 4:
                    registrarIncidencia();
                    break;

                case 5:
                    sistema.ejecutarSimulacion();
                    cout << "Simulacion finalizada, revise la carpeta Reportes" << endl;
                    break;

                case 6:
                    cout << "Equipos cargados: " << sistema.obtenerCantidadEquipos() << endl;
                    cout << "Incidencias cargadas: " << sistema.obtenerCantidadIncidencias() << endl;
                    break;

                case 7:
                    cout << "Saliendo del sistema" << endl;
                    break;

                default:
                    cout << "Opcion invalida" << endl;
                    break;
            }
        } catch (const exception &error) {
            cout << "Error: " << error.what() << endl;
        }
    } while (opcion != 7);
}
