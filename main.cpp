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

// Pide el numero de una habitacion y la marca como ocupada o disponible.
// Regresa false solo si se cerro la entrada estandar.
bool cambiarEstado(Hotel &hotel, bool ocupar) {
    int numero;
    if (!leerEntero("Numero de habitacion: ", numero)) {
        return false;
    }

    Hotel::Resultado resultado = ocupar ? hotel.ocupar(numero) : hotel.liberar(numero);
    if (resultado == Hotel::NO_EXISTE) {
        cout << "No se encontro la habitacion " << numero << "." << endl;
    } else if (resultado == Hotel::SIN_CAMBIO) {
        cout << "La habitacion " << numero << " ya estaba "
             << (ocupar ? "ocupada" : "disponible") << "." << endl;
    } else {
        cout << "Habitacion " << numero << " marcada como "
             << (ocupar ? "ocupada" : "disponible") << ". Disponibles: "
             << hotel.disponibles() << " de " << hotel.size() << "." << endl;
    }
    return true;
}

// Guarda en el archivo e informa el resultado.
void guardar(Hotel &hotel, const string &nombreArchivo) {
    if (hotel.guardarArchivo(nombreArchivo)) {
        cout << "Se guardaron " << hotel.size() << " habitaciones en "
             << nombreArchivo << "." << endl;
    } else {
        cout << "Error: no se pudo escribir " << nombreArchivo << "." << endl;
    }
}

// Carga las habitaciones y permite consultar o modificar la lista.
int main() {
    const string nombreArchivo = "habitaciones.txt";
    Hotel hotel;

    int cargadas = hotel.cargarArchivo(nombreArchivo);
    if (cargadas < 0) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }
    cout << "Se cargaron " << cargadas << " habitaciones ("
         << hotel.disponibles() << " disponibles)." << endl;

    int opcion = -1;
    do {
        cout << "\n===== HOTEL =====" << endl;
        cout << "1. Mostrar todas las habitaciones (orden actual: " << hotel.nombreCriterio() << ")" << endl;
        cout << "2. Consultar habitaciones disponibles" << endl;
        cout << "3. Ordenar por numero" << endl;
        cout << "4. Ordenar por tipo" << endl;
        cout << "5. Ordenar por capacidad" << endl;
        cout << "6. Ordenar por precio" << endl;
        cout << "7. Buscar habitacion por numero" << endl;
        cout << "8. Registrar nueva habitacion" << endl;
        cout << "9. Ocupar habitacion (check-in)" << endl;
        cout << "10. Liberar habitacion (check-out)" << endl;
        cout << "11. Guardar cambios en " << nombreArchivo << endl;
        cout << "0. Salir" << endl;

        if (!leerEntero("Selecciona una opcion: ", opcion)) {
            break;
        }

        if (opcion == 1) {
            cout << "\nHABITACIONES REGISTRADAS (" << hotel.size() << ", "
                 << hotel.disponibles() << " disponibles)" << endl;
            hotel.mostrar();
        } else if (opcion == 2) {
            int personas;
            if (!leerEntero("Numero de personas (0 = cualquier capacidad): ", personas)) {
                break;
            }
            cout << "\nHABITACIONES DISPONIBLES (orden: " << hotel.nombreCriterio() << ")" << endl;
            int encontradas = hotel.mostrarDisponibles(personas);
            if (encontradas == 0) {
                cout << "No hay habitaciones disponibles para " << personas << " personas." << endl;
            } else {
                cout << "Total: " << encontradas << endl;
            }
        } else if (opcion >= 3 && opcion <= 6) {
            hotel.ordenar(opcion - 2);
            cout << "\nHABITACIONES ORDENADAS POR " << hotel.nombreCriterio() << endl;
            hotel.mostrar();
        } else if (opcion == 7) {
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
        } else if (opcion == 8) {
            if (!registrarHabitacion(hotel)) {
                break;
            }
        } else if (opcion == 9 || opcion == 10) {
            if (!cambiarEstado(hotel, opcion == 9)) {
                break;
            }
        } else if (opcion == 11) {
            guardar(hotel, nombreArchivo);
        } else if (opcion != 0) {
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);

    // Al salir no se pierden los cambios: se pregunta si se desean guardar.
    if (hotel.hayCambiosSinGuardar()) {
        string respuesta;
        cout << "Hay cambios sin guardar. Deseas guardarlos? (s/n): ";
        if (cin >> respuesta && (respuesta == "s" || respuesta == "S")) {
            guardar(hotel, nombreArchivo);
        } else {
            cout << "Los cambios no se guardaron." << endl;
        }
    }
    cout << "Hasta luego." << endl;
    return 0;
}
