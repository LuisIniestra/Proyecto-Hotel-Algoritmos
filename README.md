# Proyecto: Sistema de administración de habitaciones de un hotel

Este proyecto consiste en un programa para administrar y organizar la información de las habitaciones de un hotel. Cada habitación cuenta con datos como número de habitación, tipo, capacidad y precio por noche.

Los datos de las habitaciones se encuentran precargados directamente dentro del programa. El objetivo es poder organizar esta información utilizando algoritmos de ordenamiento para que los datos puedan ser consultados de una manera más sencilla.

El proyecto se irá ampliando durante los siguientes avances para incorporar mecanismos de búsqueda y estructuras de datos que permitan acceder a la información de manera más eficiente.

## Descripción del avance 1

En este primer avance se desarrolló la parte del programa encargada de almacenar, mostrar y ordenar las habitaciones del hotel.

Al iniciar el programa ya existe un conjunto de habitaciones precargadas, por lo que el usuario no necesita ingresar manualmente los datos.

El programa presenta un menú desde el cual se pueden realizar diferentes acciones sobre las habitaciones almacenadas, como:

- Mostrar las habitaciones en su orden original.
- Ordenar las habitaciones por número.
- Ordenar las habitaciones por precio por noche.
- Ordenar las habitaciones por capacidad.
- Salir del programa.

Para realizar el ordenamiento se implementa el algoritmo Merge Sort. El algoritmo fue adaptado para trabajar con los objetos que representan las habitaciones y poder compararlos utilizando diferentes atributos.

En este avance no se utilizan funciones de ordenamiento de la biblioteca estándar de C++, ya que el propósito es implementar directamente los algoritmos vistos durante el curso.

## Instrucciones para compilar el avance de proyecto

Ejecuta el siguiente comando en la terminal:

`g++ main.cpp -std=c++11 -o primer_avance`

## Instrucciones para ejecutar el avance de proyecto

Ejecuta el siguiente comando en la terminal:

`./primer_avance`

## Descripción de las entradas del avance de proyecto

Los datos que utiliza el programa se encuentran precargados directamente dentro de `main.cpp`.

Cada habitación almacena la siguiente información:

- Número de habitación.
- Tipo de habitación.
- Capacidad de personas.
- Precio por noche.

Por ejemplo:

`Habitación 203 | Doble | Capacidad: 2 | Precio: $1500`

La entrada del usuario consiste únicamente en seleccionar una opción del menú para indicar la operación que quiere realizar.

## Descripción de las salidas del avance de proyecto

El programa muestra en consola la información de las habitaciones almacenadas.

Dependiendo de la opción seleccionada por el usuario, las habitaciones pueden mostrarse en su orden original o después de haber sido ordenadas por número, precio o capacidad.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

### SICT0302: Toma decisiones
