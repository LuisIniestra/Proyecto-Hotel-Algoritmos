#include <iostream>
#include <limits>
#include <string>

#include "habitacion.h"
#include "hotel.h"

using namespace std;

// Lee un numero entero y revisa que la entrada sea valida.
bool leerEntero(const string &mensaje, int &valor) {
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            return true;
        }
        if (cin.eof()) {
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor no valido, intenta de nuevo." << endl;
    }
}

// Lee un numero decimal y revisa que la entrada sea valida.
bool leerDouble(const string &mensaje, double &valor) {
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            return true;
        }
        if (cin.eof()) {
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor no valido, intenta de nuevo." << endl;
    }
}

// Pide los datos y registra una habitacion si son correctos.
bool registrarHabitacion(Hotel &hotel) {
    int numero, capacidad;
    string tipo;
    double precio;

    if (!leerEntero("Numero de habitacion: ", numero)) {
        return false;
    }
    if (hotel.buscar(numero) != 0) {
        cout << "Ya existe la habitacion " << numero << "." << endl;
        return true;
    }
    cout << "Tipo (una palabra, ej. individual, doble, suite): ";
    if (!(cin >> tipo)) {
        return false;
    }
    if (!leerEntero("Capacidad: ", capacidad)) {
        return false;
    }
    if (!leerDouble("Precio por noche: ", precio)) {
        return false;
    }

    tipo = Hotel::normalizarTipo(tipo);
    if (!Hotel::datosValidos(numero, tipo, capacidad, precio)) {
        cout << "Datos no validos: numero y capacidad deben ser mayores a 0 "
             << "y el precio no puede ser negativo." << endl;
        return true;
    }

    hotel.registrar(Habitacion(numero, tipo, capacidad, precio));
    cout << "Habitacion " << numero << " registrada. Total: " << hotel.size() << "." << endl;
    return true;
}

// Carga las habitaciones y permite consultar o modificar la lista.
int main() {
    Hotel hotel;

    int cargadas = hotel.cargarArchivo("habitaciones.txt");
    if (cargadas < 0) {
        cout << "No se pudo abrir el archivo habitaciones.txt" << endl;
        return 1;
    }
    cout << "Se cargaron " << cargadas << " habitaciones." << endl;

    int opcion = 0;
    do {
        cout << "\n===== HOTEL =====" << endl;
        cout << "1. Mostrar habitaciones (orden actual: " << hotel.nombreCriterio() << ")" << endl;
        cout << "2. Ordenar por numero" << endl;
        cout << "3. Ordenar por tipo" << endl;
        cout << "4. Ordenar por capacidad" << endl;
        cout << "5. Ordenar por precio" << endl;
        cout << "6. Buscar habitacion por numero" << endl;
        cout << "7. Registrar nueva habitacion" << endl;
        cout << "8. Salir" << endl;

        if (!leerEntero("Selecciona una opcion: ", opcion)) {
            break;
        }

        if (opcion == 1) {
            cout << "\nHABITACIONES REGISTRADAS (" << hotel.size() << ")" << endl;
            hotel.mostrar();
        } else if (opcion >= 2 && opcion <= 5) {
            hotel.ordenar(opcion - 1);
            cout << "\nHABITACIONES ORDENADAS POR " << hotel.nombreCriterio() << endl;
            hotel.mostrar();
        } else if (opcion == 6) {
            int numero;
            if (!leerEntero("Numero de habitacion: ", numero)) {
                break;
            }
            const Habitacion *encontrada = hotel.buscar(numero);
            if (encontrada != 0) {
                cout << "Habitacion encontrada:" << endl;
                cout << encontrada->toString() << endl;
            } else {
                cout << "No se encontro la habitacion " << numero << "." << endl;
            }
        } else if (opcion == 7) {
            if (!registrarHabitacion(hotel)) {
                break;
            }
        } else if (opcion == 8) {
            cout << "Hasta luego." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 8);

    return 0;
}
