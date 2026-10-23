#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "habitacion.h"
#include "sorts.h"

using namespace std;

// Muestra las habitaciones guardadas en el vector.
void mostrarHabitaciones(const vector<Habitacion> &habitaciones) {
    if (habitaciones.empty()) {
        cout << "No hay habitaciones para mostrar." << endl;
        return;
    }

    for (int i = 0; i < static_cast<int>(habitaciones.size()); i++) {
        cout << habitaciones[i].toString() << endl;
    }
}

// Busca una habitacion por numero.
void buscarHabitacion(const vector<Habitacion> &habitaciones, int numero) {
    for (int i = 0; i < static_cast<int>(habitaciones.size()); i++) {
        if (habitaciones[i].getNumero() == numero) {
            cout << "Habitacion encontrada:" << endl;
            cout << habitaciones[i].toString() << endl;
            return;
        }
    }
    cout << "No se encontro la habitacion " << numero << "." << endl;
}

int main() {
    vector<Habitacion> habitaciones;
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
        habitaciones.push_back(habitacion);
    }
    archivo.close();

    Sorts<Habitacion> sorts;
    int opcion = 0;

    do {
        cout << "\n===== HOTEL =====" << endl;
        cout << "1. Mostrar habitaciones" << endl;
        cout << "2. Ordenar por numero" << endl;
        cout << "3. Buscar habitacion por numero" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opcion: ";

        if (!(cin >> opcion)) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion no valida." << endl;
            continue;
        }

        if (opcion == 1) {
            cout << "\nHABITACIONES REGISTRADAS" << endl;
            mostrarHabitaciones(habitaciones);
        }
        else if (opcion == 2) {
            vector<Habitacion> ordenadas = sorts.selectionSort(habitaciones);
            cout << "\nHABITACIONES ORDENADAS POR NUMERO" << endl;
            mostrarHabitaciones(ordenadas);
        }
        else if (opcion == 3) {
            cout << "Numero de habitacion: ";
            if (cin >> numero) {
                buscarHabitacion(habitaciones, numero);
            }
            else {
                if (cin.eof()) {
                    break;
                }
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Numero no valido." << endl;
            }
        }
        else if (opcion == 4) {
            cout << "Hasta luego." << endl;
        }
        else {
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);

    return 0;
}
