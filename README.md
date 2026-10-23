# Proyecto: Sistema de administración de habitaciones de un hotel

Este proyecto consiste en un programa en C++ para administrar y organizar la información de las habitaciones de un hotel. Cada habitación tiene un número, tipo, capacidad y precio por noche.

Los datos se encuentran en el archivo `habitaciones.txt` y se almacenan en un `vector<Habitacion>` para poder organizarlos y consultarlos.

## Descripción del avance 1

En el primer avance se desarrolló la clase `Habitacion`, la lectura de datos desde `habitaciones.txt` y el ordenamiento de las habitaciones de menor a mayor por número mediante Selection Sort.

El programa podía mostrar las habitaciones en su orden original y después ordenadas, pero solamente realizaba estas acciones una vez.

## Descripción del avance 2

En este segundo avance se mantiene el almacenamiento de las habitaciones en un `vector<Habitacion>` y se agrega un menú interactivo para que el usuario pueda realizar diferentes operaciones sin tener que ejecutar nuevamente el programa.

Las opciones disponibles son:

1. Mostrar todas las habitaciones.
2. Ordenar las habitaciones por número.
3. Buscar una habitación por número.
4. Salir del programa.

También se agregó una búsqueda secuencial que permite encontrar una habitación a partir de su número.

### Cambios sobre el primer avance

Se agregó un menú interactivo en `main.cpp` para que el usuario pueda elegir qué operación realizar. Con esto se corrige una de las observaciones realizadas por el profesor en el primer avance.

También se implementó una búsqueda secuencial para consultar habitaciones por su número, utilizando el vector donde se encuentran almacenados los datos.

Se decidió mantener `vector<Habitacion>` porque permite almacenar una cantidad variable de registros, recorrerlos y acceder a ellos mediante sus posiciones.

Por último, se corrigió la documentación para que coincida con el funcionamiento del programa. El algoritmo utilizado es Selection Sort y los datos se cargan desde `habitaciones.txt`.

## Instrucciones para compilar el avance de proyecto

Desde la carpeta que contiene los archivos del proyecto, ejecutar el siguiente comando:

```bash
g++ main.cpp -std=c++11 -o segundo_avance
```

## Instrucciones para ejecutar el avance de proyecto

En Linux o macOS:

```bash
./segundo_avance
```

En Windows PowerShell:

```powershell
.\segundo_avance.exe
```

El archivo `habitaciones.txt` debe encontrarse en la carpeta desde la cual se ejecuta el programa.

Al iniciar aparecerá un menú que permite mostrar, ordenar o buscar habitaciones. Después de realizar cada operación, el menú vuelve a aparecer hasta que el usuario selecciona la opción de salir.

## Descripción de las entradas del avance de proyecto

Los datos se encuentran almacenados en el archivo `habitaciones.txt`.

Cada línea contiene cuatro datos separados por espacios:

- Número de habitación.
- Tipo de habitación.
- Capacidad de personas.
- Precio por noche.

Por ejemplo:

```text
305 suite 4 2500
102 individual 1 900
210 doble 2 1500
```

El programa utiliza `ifstream` para leer los registros, crear los objetos de tipo `Habitacion` y guardarlos en un vector mediante `push_back`.

El usuario también debe ingresar una opción del menú y, cuando quiera buscar una habitación, introducir su número.

## Descripción de las salidas del avance de proyecto

El programa muestra en consola la información de las habitaciones almacenadas.

Dependiendo de la opción seleccionada, puede mostrar las habitaciones en el orden en que fueron leídas, ordenarlas de menor a mayor por número o mostrar una habitación específica.

Por ejemplo, al buscar la habitación 210:

```text
Habitacion encontrada:
Habitacion 210 | Tipo: doble | Capacidad: 2 | Precio: $1500
```

Si la habitación solicitada no existe, el programa muestra un mensaje indicando que no fue encontrada.

Si el archivo de datos no puede abrirse, se muestra un mensaje de error y termina la ejecución.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Análisis de complejidad del algoritmo de ordenamiento

En este proyecto se utiliza Selection Sort para ordenar las habitaciones de menor a mayor por número.

Este algoritmo busca el elemento mayor dentro de la parte que todavía no está ordenada y lo coloca en su posición correspondiente al final.

Selection Sort realiza aproximadamente `n(n-1)/2` comparaciones, por lo que su complejidad temporal es:

- Mejor caso: O(n²).
- Caso promedio: O(n²).
- Peor caso: O(n²).

Esto sucede porque el algoritmo realiza las comparaciones aunque los elementos ya se encuentren ordenados.

En cuanto a memoria, nuestra implementación crea una copia del vector original antes de ordenarlo, por lo que utiliza O(n) de espacio adicional. Sin contar esta copia, las variables utilizadas por el algoritmo requieren O(1) de espacio auxiliar.

#### Análisis de complejidad de las estructuras de datos

Para almacenar las habitaciones se utiliza un `vector<Habitacion>`, que permite guardar los registros de manera dinámica.

Al agregar una habitación mediante `push_back`, la complejidad es O(1) amortizado, ya que normalmente se agrega al final del vector. Sin embargo, algunas inserciones pueden requerir O(n) cuando el vector necesita aumentar su capacidad.

La lectura y almacenamiento de las n habitaciones del archivo tiene una complejidad total amortizada de O(n), porque se recorre cada registro y se agrega al vector.

El acceso a una habitación mediante su posición, utilizando `habitaciones[i]`, tiene complejidad O(1), ya que podemos acceder directamente al elemento.

Las operaciones `size()` y `empty()` también tienen complejidad O(1).

Para mostrar todas las habitaciones, se recorre el vector completo mediante un ciclo `for`, por lo que la complejidad es O(n).

En la búsqueda secuencial, el programa compara el número solicitado con los números de las habitaciones almacenadas. En el mejor caso, la habitación se encuentra en la primera posición y la complejidad es O(1). En el caso promedio y en el peor caso, la complejidad es O(n).

Cuando se utiliza Selection Sort, primero se realiza una copia del vector, lo cual requiere O(n) de tiempo y espacio adicional. Después se realiza el ordenamiento, que tiene complejidad O(n²).

El almacenamiento del vector original requiere O(n) de memoria, dependiendo de la cantidad de habitaciones. Al ordenar se crea temporalmente otra copia, por lo que el espacio total utilizado sigue siendo O(n).

### SICT0302: Toma decisiones

#### Selección del algoritmo de ordenamiento

Se decidió mantener Selection Sort porque es un algoritmo sencillo que permite organizar correctamente las habitaciones y corresponde a los algoritmos vistos durante el curso.

Aunque tiene una complejidad O(n²), para la cantidad de habitaciones que se manejan actualmente en el proyecto resulta suficiente.

Además, se implementa directamente en `sorts.h`, sin utilizar funciones de ordenamiento de la biblioteca estándar de C++.

El algoritmo utiliza el operador `>` definido para la clase `Habitacion`, que permite comparar las habitaciones por su número.

#### Selección de la estructura de datos

Se eligió utilizar un `vector<Habitacion>` porque permite almacenar las habitaciones sin necesidad de conocer previamente la cantidad de registros.

También facilita recorrer los datos, acceder a cada habitación mediante su posición y realizar búsquedas.

Para este avance, el vector es suficiente porque las consultas son sencillas y no es necesario utilizar estructuras más complejas.

Su implementación se encuentra en `main.cpp`, donde se almacenan los registros leídos desde el archivo y se utilizan para las diferentes operaciones del menú.

### SICT0303: Implementa acciones científicas

#### Mecanismos para consultar información de las estructuras

El programa cuenta con funciones que permiten consultar la información almacenada en el vector.

La función `mostrarHabitaciones` recorre todos los elementos y muestra los datos de cada habitación.

También se implementó la función `buscarHabitacion`, que realiza una búsqueda secuencial comparando el número solicitado por el usuario con el valor obtenido mediante `getNumero()`.

Si encuentra la habitación, muestra su información. En caso contrario, indica que no existe dentro de los registros almacenados.

Adicionalmente, el usuario puede consultar las habitaciones ordenadas por número utilizando Selection Sort desde el menú.

#### Mecanismos de lectura de archivos para cargar datos

Para cargar los registros se utiliza `ifstream`, que permite leer la información desde el archivo `habitaciones.txt`.

El programa abre el archivo y utiliza un ciclo `while` para leer el número, tipo, capacidad y precio de cada habitación.

Con estos datos se crea un objeto de tipo `Habitacion`, que después se agrega al vector mediante `push_back`.

Cuando termina la lectura, el archivo se cierra y las habitaciones quedan almacenadas para ser utilizadas durante la ejecución.

También se verifica que el archivo pueda abrirse correctamente. Si ocurre un error, se muestra un mensaje y el programa termina.
