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

    // Los empates se resuelven por numero para mantener un orden claro.
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

    Nodo *mergeSort(Nodo *inicio, int criterio) {
        if (inicio == 0 || inicio->siguiente == 0) return inicio;

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
    ListaHabitaciones() : head(0), tail(0), cantidad(0) {}

    // Evita copiar punteros de una lista con propiedad de sus nodos.
    ListaHabitaciones(const ListaHabitaciones &) = delete;
    ListaHabitaciones &operator=(const ListaHabitaciones &) = delete;

    ~ListaHabitaciones() {
        Nodo *actual = head;
        while (actual != 0) {
            Nodo *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void agregar(const Habitacion &habitacion) {
        Nodo *nuevo = new Nodo(habitacion);
        if (head == 0) {
            head = nuevo;
        } else {
            tail->siguiente = nuevo;
        }
        tail = nuevo;
        cantidad++;
    }

    bool empty() const { return head == 0; }
    int size() const { return cantidad; }

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

    const Habitacion *buscar(int numero) const {
        Nodo *actual = head;
        while (actual != 0) {
            if (actual->habitacion.getNumero() == numero) {
                return &actual->habitacion;
            }
            actual = actual->siguiente;
        }
        return 0;
    }

    // Criterio: 1 numero, 2 tipo, 3 capacidad, 4 precio.
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
