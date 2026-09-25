#ifndef HABITACION_H_
#define HABITACION_H_

#include <string>
#include <sstream>

class Habitacion {

private:

    int numero;
    std::string tipo;
    int capacidad;
    double precio;

public:

    Habitacion();
    Habitacion(int, std::string, int, double);

    int getNumero() const;
    std::string getTipo() const;
    int getCapacidad() const;
    double getPrecio() const;

    std::string toString() const;
};


Habitacion::Habitacion() {

    numero = 0;
    tipo = "";
    capacidad = 0;
    precio = 0;
}


Habitacion::Habitacion(int num, std::string tip, int cap, double pre) {

    numero = num;
    tipo = tip;
    capacidad = cap;
    precio = pre;
}


int Habitacion::getNumero() const {

    return numero;
}


std::string Habitacion::getTipo() const {

    return tipo;
}


int Habitacion::getCapacidad() const {

    return capacidad;
}


double Habitacion::getPrecio() const {

    return precio;
}


std::string Habitacion::toString() const {

    std::stringstream aux;

    aux << "Habitacion " << numero
        << " | Tipo: " << tipo
        << " | Capacidad: " << capacidad
        << " | Precio: $" << precio;

    return aux.str();
}

/*
 * Este operador permite comparar dos habitaciones.
 * Para este avance las habitaciones se comparan por numero.
 */
bool operator>(const Habitacion &left, const Habitacion &right) {

    return left.getNumero() > right.getNumero();
}


#endif /* HABITACION_H_ */
