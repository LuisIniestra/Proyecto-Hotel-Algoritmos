#ifndef INDICE_H_
#define INDICE_H_

#include "habitacion.h"

/*
 * Arbol AVL que funciona como indice de las habitaciones por numero.
 * Cada nodo guarda el numero de la habitacion (llave) y un apuntador a la
 * habitacion que vive en la lista enlazada, por lo que los datos no se
 * duplican. Al ser un arbol balanceado, su altura siempre es O(log n) y
 * la busqueda y la insercion son O(log n) incluso en el peor caso.
 */
class IndiceHabitaciones {
private:
    struct Nodo {
        int numero;
        const Habitacion *habitacion;
        Nodo *izquierda;
        Nodo *derecha;
        int altura;

        Nodo(const Habitacion *dato)
            : numero(dato->getNumero()), habitacion(dato),
              izquierda(0), derecha(0), altura(1) {}
    };

    Nodo *raiz;
    int cantidad;

    // Regresa la altura de un nodo.
    static int altura(Nodo *nodo) {
        return nodo == 0 ? 0 : nodo->altura;
    }

    // Actualiza la altura usando sus hijos.
    static void actualizarAltura(Nodo *nodo) {
        int izq = altura(nodo->izquierda);
        int der = altura(nodo->derecha);
        nodo->altura = 1 + (izq > der ? izq : der);
    }

    // Calcula la diferencia de alturas entre los hijos.
    static int factorBalance(Nodo *nodo) {
        return altura(nodo->izquierda) - altura(nodo->derecha);
    }

    // Hace una rotacion hacia la derecha.
    static Nodo *rotarDerecha(Nodo *a) {
        Nodo *b = a->izquierda;
        a->izquierda = b->derecha;
        b->derecha = a;
        actualizarAltura(a);
        actualizarAltura(b);
        return b;
    }

    // Hace una rotacion hacia la izquierda.
    static Nodo *rotarIzquierda(Nodo *a) {
        Nodo *b = a->derecha;
        a->derecha = b->izquierda;
        b->izquierda = a;
        actualizarAltura(a);
        actualizarAltura(b);
        return b;
    }

    // Revisa el balance del nodo y aplica la rotacion simple o doble necesaria.
    static Nodo *balancear(Nodo *nodo) {
        actualizarAltura(nodo);
        int balance = factorBalance(nodo);

        if (balance > 1) {
            if (factorBalance(nodo->izquierda) < 0) {
                nodo->izquierda = rotarIzquierda(nodo->izquierda);
            }
            return rotarDerecha(nodo);
        }
        if (balance < -1) {
            if (factorBalance(nodo->derecha) > 0) {
                nodo->derecha = rotarDerecha(nodo->derecha);
            }
            return rotarIzquierda(nodo);
        }
        return nodo;
    }

    // Inserta una habitacion por numero y balancea el arbol.
    Nodo *insertar(Nodo *nodo, const Habitacion *dato, bool &insertado) {
        if (nodo == 0) {
            insertado = true;
            return new Nodo(dato);
        }
        if (dato->getNumero() < nodo->numero) {
            nodo->izquierda = insertar(nodo->izquierda, dato, insertado);
        } else if (dato->getNumero() > nodo->numero) {
            nodo->derecha = insertar(nodo->derecha, dato, insertado);
        } else {
            insertado = false; // Numero repetido: no se inserta.
            return nodo;
        }
        return balancear(nodo);
    }

    // Libera los nodos del arbol con un recorrido recursivo.
    void liberar(Nodo *nodo) {
        if (nodo != 0) {
            liberar(nodo->izquierda);
            liberar(nodo->derecha);
            delete nodo;
        }
    }

public:
    // Inicia el arbol vacio.
    IndiceHabitaciones() : raiz(0), cantidad(0) {}

    IndiceHabitaciones(const IndiceHabitaciones &) = delete;
    IndiceHabitaciones &operator=(const IndiceHabitaciones &) = delete;

    // Libera la memoria del arbol.
    ~IndiceHabitaciones() {
        liberar(raiz);
    }

    // Agrega una habitacion al indice si no esta repetida.
    bool insertar(const Habitacion *dato) {
        bool insertado = false;
        raiz = insertar(raiz, dato, insertado);
        if (insertado) {
            cantidad++;
        }
        return insertado;
    }

    // Busca una habitacion por su numero.
    const Habitacion *buscar(int numero) const {
        Nodo *actual = raiz;
        while (actual != 0) {
            if (numero == actual->numero) {
                return actual->habitacion;
            }
            actual = (numero < actual->numero) ? actual->izquierda : actual->derecha;
        }
        return 0;
    }

    // Revisa si el numero ya esta registrado.
    bool contiene(int numero) const {
        return buscar(numero) != 0;
    }

    // Regresa la cantidad de nodos del arbol.
    int size() const { return cantidad; }

    // Regresa la altura actual del arbol.
    int getAltura() const { return altura(raiz); }
};

#endif /* INDICE_H_ */
