#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "habitacion.h"
#include "sorts.h"

using namespace std;

void mostrarHabitaciones(const vector<Habitacion> &habitaciones) {

    for (int i = 0; i < habitaciones.size(); i++) {
        cout << habitaciones[i].toString() << endl;
    }
}

int main() {

    vector<Habitacion> habitaciones;
    ifstream archivo("habitaciones.txt");

    int numero;
    string tipo;
    int capacidad;
    double precio;

    if (archivo.is_open()) {

        while (archivo >> numero >> tipo >> capacidad >> precio) {

            Habitacion habitacion(numero, tipo, capacidad, precio);
            habitaciones.push_back(habitacion);
        }

        archivo.close();
    }

    else {

        cout << "No se pudo abrir el archivo habitaciones.txt" << endl;
        return 0;
    }

    cout << "HABITACIONES ORIGINALES" << endl;

    mostrarHabitaciones(habitaciones);

    Sorts<Habitacion> sorts;

    vector<Habitacion> ordenadas = sorts.selectionSort(habitaciones);

    cout << "\nHABITACIONES ORDENADAS POR NUMERO" << endl;

    mostrarHabitaciones(ordenadas);

    return 0;
}
