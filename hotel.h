#ifndef HOTEL_H_
#define HOTEL_H_

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "habitacion.h"
#include "lista.h"
#include "indice.h"

/*
 * Hotel coordina las dos estructuras dinamicas del proyecto:
 *  - ListaHabitaciones: guarda las habitaciones y define el orden en que se
 *    muestran. Se ordena con Merge Sort por numero, tipo, capacidad o precio.
 *  - IndiceHabitaciones: arbol AVL por numero para buscar en O(log n) y
 *    evitar numeros repetidos sin recorrer toda la lista.
 * Toda alta pasa por esta clase para que ambas estructuras esten siempre
 * sincronizadas.
 */
class Hotel {
private:
    ListaHabitaciones lista;
    IndiceHabitaciones indice;
    int criterioActual; // 1 numero, 2 tipo, 3 capacidad, 4 precio

public:
    // Inicia el hotel con el orden por numero.
    Hotel() : criterioActual(1) {}

    // Convierte el tipo de habitacion a minusculas.
    static std::string normalizarTipo(std::string tipo) {
        for (size_t i = 0; i < tipo.size(); i++) {
            tipo[i] = std::tolower(static_cast<unsigned char>(tipo[i]));
        }
        return tipo;
    }

    // Comprueba que los datos de una habitacion sean validos.
    static bool datosValidos(int numero, const std::string &tipo, int capacidad, double precio) {
        return numero > 0 && !tipo.empty() && capacidad > 0 && precio >= 0;
    }

    // Carga el archivo y omite las lineas incorrectas o repetidas.
    int cargarArchivo(const std::string &nombre) {
        std::ifstream archivo(nombre.c_str());
        if (!archivo.is_open()) {
            return -1;
        }

        std::string linea;
        int numeroLinea = 0;
        int cargadas = 0;
        while (std::getline(archivo, linea)) {
            numeroLinea++;
            if (linea.find_first_not_of(" \t\r") == std::string::npos) {
                continue; // Linea vacia.
            }

            std::stringstream campos(linea);
            int numero, capacidad;
            std::string tipo, sobrante;
            double precio;
            if (!(campos >> numero >> tipo >> capacidad >> precio) || (campos >> sobrante) ||
                !datosValidos(numero, tipo, capacidad, precio)) {
                std::cout << "Aviso: linea " << numeroLinea
                          << " con formato invalido, se omite." << std::endl;
                continue;
            }
            if (indice.contiene(numero)) {
                std::cout << "Aviso: linea " << numeroLinea << ", la habitacion "
                          << numero << " esta repetida, se omite." << std::endl;
                continue;
            }

            const Habitacion *guardada =
                lista.agregar(Habitacion(numero, normalizarTipo(tipo), capacidad, precio));
            indice.insertar(guardada);
            cargadas++;
        }
        archivo.close();

        ordenar(1); // El orden por defecto es por numero.
        return cargadas;
    }

    // Registra una habitacion nueva en la lista y el indice.
    bool registrar(const Habitacion &habitacion) {
        if (indice.contiene(habitacion.getNumero())) {
            return false;
        }
        const Habitacion *guardada = lista.insertarOrdenado(habitacion, criterioActual);
        indice.insertar(guardada);
        return true;
    }

    // Cambia el orden de las habitaciones.
    void ordenar(int criterio) {
        lista.ordenar(criterio);
        criterioActual = criterio;
    }

    // Busca la habitacion usando el indice AVL.
    const Habitacion *buscar(int numero) const {
        return indice.buscar(numero);
    }

    // Muestra todas las habitaciones.
    void mostrar() const {
        lista.mostrar();
    }

    // Regresa la cantidad de habitaciones registradas.
    int size() const { return lista.size(); }

    // Regresa la altura del indice AVL.
    int alturaIndice() const { return indice.getAltura(); }

    // Indica el criterio de ordenamiento actual.
    std::string nombreCriterio() const {
        switch (criterioActual) {
            case 2: return "tipo";
            case 3: return "capacidad";
            case 4: return "precio";
            default: return "numero";
        }
    }
};

#endif /* HOTEL_H_ */
