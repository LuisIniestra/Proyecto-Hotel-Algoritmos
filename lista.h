#ifndef LISTA_H_
#define LISTA_H_

#include <iostream>
#include <string>
#include "habitacion.h"

// Lista enlazada de habitaciones. Cada nodo se crea dinamicamente.
class ListaHabitaciones {
private:
    struct Nodo {
        Habitacion habitacion;
        Nodo *siguiente;

        Nodo(const Habitacion &dato) : habitacion(dato), siguiente(0) {}
    };

    Nodo *head;
    Nodo *tail;
    int cantidad;

    // Compara habitaciones segun el criterio y desempata por numero.
    bool vaPrimero(const Habitacion &a, const Habitacion &b, int criterio) const {
        if (criterio == 2 && a.getTipo() != b.getTipo()) {
            return a.getTipo() < b.getTipo();
        }
        if (criterio == 3 && a.getCapacidad() != b.getCapacidad()) {
            return a.getCapacidad() < b.getCapacidad();
        }
        if (criterio == 4 && a.getPrecio() != b.getPrecio()) {
            return a.getPrecio() < b.getPrecio();
        }
        return a.getNumero() <= b.getNumero();
    }

    // Une dos cadenas de nodos que ya estan ordenadas.
    Nodo *mezclar(Nodo *izquierda, Nodo *derecha, int criterio) {
        Nodo auxiliar{Habitacion()};
        Nodo *ultimo = &auxiliar;

        while (izquierda != 0 && derecha != 0) {
            if (vaPrimero(izquierda->habitacion, derecha->habitacion, criterio)) {
                ultimo->siguiente = izquierda;
                izquierda = izquierda->siguiente;
            } else {
                ultimo->siguiente = derecha;
                derecha = derecha->siguiente;
            }
            ultimo = ultimo->siguiente;
        }
        if (izquierda != 0) {
            ultimo->siguiente = izquierda;
        } else {
            ultimo->siguiente = derecha;
        }
        return auxiliar.siguiente;
    }

    // Divide la lista en dos partes y las ordena con Merge Sort.
    Nodo *mergeSort(Nodo *inicio, int criterio) {
        if (inicio == 0 || inicio->siguiente == 0) {
            return inicio;
        }

        Nodo *lento = inicio;
        Nodo *rapido = inicio->siguiente;
        while (rapido != 0 && rapido->siguiente != 0) {
            lento = lento->siguiente;
            rapido = rapido->siguiente->siguiente;
        }

        Nodo *derecha = lento->siguiente;
        lento->siguiente = 0;
        Nodo *izquierda = mergeSort(inicio, criterio);
        derecha = mergeSort(derecha, criterio);
        return mezclar(izquierda, derecha, criterio);
    }

public:
    // Inicia una lista vacia.
    ListaHabitaciones() : head(0), tail(0), cantidad(0) {}

    // Evita copiar punteros de una lista con propiedad de sus nodos.
    ListaHabitaciones(const ListaHabitaciones &) = delete;
    ListaHabitaciones &operator=(const ListaHabitaciones &) = delete;

    // Libera todos los nodos al terminar el programa.
    ~ListaHabitaciones() {
        Nodo *actual = head;
        while (actual != 0) {
            Nodo *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    // Agrega al final y regresa la direccion para el indice AVL.
    Habitacion *agregar(const Habitacion &habitacion) {
        Nodo *nuevo = new Nodo(habitacion);
        if (head == 0) {
            head = nuevo;
        } else {
            tail->siguiente = nuevo;
        }
        tail = nuevo;
        cantidad++;
        return &nuevo->habitacion;
    }

    // Inserta una nueva habitacion segun el orden actual.
    Habitacion *insertarOrdenado(const Habitacion &habitacion, int criterio) {
        Nodo *nuevo = new Nodo(habitacion);
        if (head == 0 || vaPrimero(habitacion, head->habitacion, criterio)) {
            nuevo->siguiente = head;
            head = nuevo;
            if (tail == 0) {
                tail = nuevo;
            }
        } else {
            Nodo *actual = head;
            while (actual->siguiente != 0 &&
                   !vaPrimero(habitacion, actual->siguiente->habitacion, criterio)) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
            if (nuevo->siguiente == 0) {
                tail = nuevo;
            }
        }
        cantidad++;
        return &nuevo->habitacion;
    }

    // Revisa si la lista esta vacia.
    bool empty() const { return head == 0; }

    // Regresa el numero de habitaciones.
    int size() const { return cantidad; }

    // Muestra las habitaciones en el orden actual.
    void mostrar() const {
        if (empty()) {
            std::cout << "No hay habitaciones para mostrar." << std::endl;
            return;
        }
        Nodo *actual = head;
        while (actual != 0) {
            std::cout << actual->habitacion.toString() << std::endl;
            actual = actual->siguiente;
        }
    }

    // Muestra solo las habitaciones disponibles con capacidad suficiente
    // para la cantidad de personas indicada. Regresa cuantas mostro.
    int mostrarDisponibles(int personas) const {
        int encontradas = 0;
        Nodo *actual = head;
        while (actual != 0) {
            if (actual->habitacion.isDisponible() &&
                actual->habitacion.getCapacidad() >= personas) {
                std::cout << actual->habitacion.toString() << std::endl;
                encontradas++;
            }
            actual = actual->siguiente;
        }
        return encontradas;
    }

    // Ordena por numero, tipo, capacidad o precio.
    void ordenar(int criterio) {
        head = mergeSort(head, criterio);
        tail = head;
        if (tail != 0) {
            while (tail->siguiente != 0) {
                tail = tail->siguiente;
            }
        }
    }
};

#endif /* LISTA_H_ */
