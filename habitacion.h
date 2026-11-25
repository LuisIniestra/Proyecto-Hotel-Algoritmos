#ifndef HABITACION_H_
#define HABITACION_H_

#include <string>
#include <sstream>
#include <iomanip>

class Habitacion {

private:

    int numero;
    std::string tipo;
    int capacidad;
    double precio;
    bool disponible;

public:

    Habitacion();
    Habitacion(int, std::string, int, double, bool = true);

    int getNumero() const;
    std::string getTipo() const;
    int getCapacidad() const;
    double getPrecio() const;
    bool isDisponible() const;

    void setDisponible(bool);

    std::string toString() const;
    std::string toArchivo() const;
};


// Inicia una habitacion sin datos.
Habitacion::Habitacion() {

    numero = 0;
    tipo = "";
    capacidad = 0;
    precio = 0;
    disponible = true;
}


// Guarda los datos de una habitacion.
Habitacion::Habitacion(int num, std::string tip, int cap, double pre, bool disp) {

    numero = num;
    tipo = tip;
    capacidad = cap;
    precio = pre;
    disponible = disp;
}


// Regresa el numero de habitacion.
int Habitacion::getNumero() const {

    return numero;
}


// Regresa el tipo de habitacion.
std::string Habitacion::getTipo() const {

    return tipo;
}


// Regresa la capacidad de personas.
int Habitacion::getCapacidad() const {

    return capacidad;
}


// Regresa el precio por noche.
double Habitacion::getPrecio() const {

    return precio;
}


// Indica si la habitacion esta libre para hospedar a alguien.
bool Habitacion::isDisponible() const {

    return disponible;
}


// Cambia el estado de la habitacion (true = disponible, false = ocupada).
void Habitacion::setDisponible(bool disp) {

    disponible = disp;
}


// Convierte los datos a texto para mostrarlos.
std::string Habitacion::toString() const {

    std::stringstream aux;

    aux << "Habitacion " << numero
        << " | Tipo: " << tipo
        << " | Capacidad: " << capacidad
        << " | Precio: $" << precio
        << " | Estado: " << (disponible ? "disponible" : "ocupada");

    return aux.str();
}


// Convierte los datos a una linea con el mismo formato de habitaciones.txt.
// El precio se escribe con dos decimales para no perder centavos ni usar
// notacion cientifica con precios grandes.
std::string Habitacion::toArchivo() const {

    std::stringstream aux;

    aux << numero << " " << tipo << " " << capacidad << " "
        << std::fixed << std::setprecision(2) << precio << " "
        << (disponible ? "disponible" : "ocupada");

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
