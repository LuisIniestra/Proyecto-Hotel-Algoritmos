#include <fstream>
#include <iostream>
#include <string>

#include "habitacion.h"
#include "lista.h"

using namespace std;

int main() {
    ListaHabitaciones habitaciones;
    ifstream archivo("habitaciones.txt");
    int numero;
    string tipo;
    int capacidad;
    double precio;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo habitaciones.txt" << endl;
        return 1;
    }

    while (archivo >> numero >> tipo >> capacidad >> precio) {
        Habitacion habitacion(numero, tipo, capacidad, precio);
        habitaciones.agregar(habitacion);
    }
    archivo.close();

    // El orden inicial del sistema siempre es por numero de habitacion.
    habitaciones.ordenar(1);

    int opcion = 0;
    do {
        cout << "\n===== HOTEL =====" << endl;
        cout << "1. Mostrar habitaciones" << endl;
        cout << "2. Ordenar por numero" << endl;
        cout << "3. Ordenar por tipo" << endl;
        cout << "4. Ordenar por capacidad" << endl;
        cout << "5. Ordenar por precio" << endl;
        cout << "6. Buscar habitacion por numero" << endl;
        cout << "7. Salir" << endl;
        cout << "Selecciona una opcion: ";

        if (!(cin >> opcion)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion no valida." << endl;
            continue;
        }

        if (opcion == 1) {
            cout << "\nHABITACIONES REGISTRADAS" << endl;
            habitaciones.mostrar();
        } else if (opcion >= 2 && opcion <= 5) {
            habitaciones.ordenar(opcion - 1);
            cout << "\nHABITACIONES ORDENADAS" << endl;
            habitaciones.mostrar();
        } else if (opcion == 6) {
            cout << "Numero de habitacion: ";
            if (cin >> numero) {
                const Habitacion *encontrada = habitaciones.buscar(numero);
                if (encontrada != 0) {
                    cout << "Habitacion encontrada:" << endl;
                    cout << encontrada->toString() << endl;
                } else {
                    cout << "No se encontro la habitacion " << numero << "." << endl;
                }
            } else {
                if (cin.eof()) break;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Numero no valido." << endl;
            }
        } else if (opcion == 7) {
            cout << "Hasta luego." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 7);

    return 0;
}
