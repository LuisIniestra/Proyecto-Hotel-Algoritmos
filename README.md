# Proyecto: Sistema de administración de habitaciones de un hotel

Este programa en C++ almacena habitaciones de un hotel. Cada una tiene un número, tipo, capacidad y precio por noche. Los registros se leen desde `habitaciones.txt` y se guardan en una lista simplemente enlazada creada con nodos dinámicos. El usuario puede consultar las habitaciones, buscarlas por número y ordenarlas por distintos criterios desde un menú.

## Descripción del avance 1

Se creó la clase `Habitacion` con los datos de cada registro y se implementó la lectura del archivo `habitaciones.txt`. La primera versión usaba un `vector<Habitacion>` y Selection Sort para ordenar por número. En esa etapa se mostraban los datos y el resultado del ordenamiento una sola vez.

## Descripción del avance 2

En este avance se agregó un menú interactivo para hacer varias consultas sin reiniciar el programa. Al principio se utilizó un vector y búsqueda secuencial.

Después de la retroalimentación del profesor, se cambió el almacenamiento principal a una **lista simplemente enlazada** implementada en `lista.h`, donde cada habitación se guarda en un nodo creado con `new`. También se implementó **Merge Sort sobre los enlaces de la lista**, para ordenar por número, tipo, capacidad y precio. Las habitaciones se ordenan por número automáticamente al cargar el archivo.

### Cambios sobre el primer avance

1. Se conservó `Habitacion` y la lectura de `habitaciones.txt`. Así no es necesario volver a definir los datos del problema.
2. Se agregó el menú interactivo para que el programa no sea una ejecución única.
3. Se sustituyó el vector principal por una lista enlazada dinámica. La cantidad de habitaciones no tiene que fijarse previamente; cada nodo se reserva conforme se lee el archivo y se libera al terminar el programa.
4. Se sustituyó Selection Sort en el funcionamiento actual por Merge Sort. Selection Sort tiene tiempo O(n²), mientras que Merge Sort permite ordenar O(n log n), una mejor decisión si aumenta la cantidad de habitaciones.
5. Se agregó el orden inicial por número y las opciones de ordenar por tipo, capacidad y precio. En los empates se usa el número de habitación como segundo criterio.
6. Se corrigió el README para que coincida con el código actual. `sorts.h` se conserva en el repositorio como parte del primer avance, pero **no se utiliza en el segundo avance**.

## Instrucciones para compilar el avance de proyecto

Con `g++` y desde la carpeta que contiene todos los archivos:

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

`habitaciones.txt` debe estar en el directorio desde el que se ejecuta el programa.

El menú tiene estas opciones:

1. Mostrar habitaciones en su orden actual (inicialmente por número).
2. Ordenar por número, de menor a mayor.
3. Ordenar por tipo, alfabéticamente.
4. Ordenar por capacidad, de menor a mayor.
5. Ordenar por precio, de menor a mayor.
6. Buscar una habitación por número.
7. Salir.

Después de mostrar, ordenar o buscar, el menú vuelve a aparecer. Los ordenamientos modifican el orden de los nodos de la lista, así que la opción 1 muestra el orden seleccionado más recientemente.

## Descripción de las entradas del avance de proyecto

El archivo `habitaciones.txt` tiene una habitación por línea, sin encabezados, con cuatro campos separados por espacios: número (`int`), tipo (`string` sin espacios), capacidad (`int`) y precio por noche (`double`).

Ejemplo:

```text
305 suite 4 2500
102 individual 1 900
210 doble 2 1500
```

El programa utiliza `ifstream` para leer los cuatro campos y `agregar` para insertar cada habitación al final de la lista. El usuario escribe una opción del menú y, cuando elige buscar, también el número deseado.

## Descripción de las salidas del avance de proyecto

El programa muestra el menú y, según la opción seleccionada, lista las habitaciones en el orden actual o presenta el resultado de una búsqueda.

Ejemplo:

```text
Habitacion encontrada:
Habitacion 210 | Tipo: doble | Capacidad: 2 | Precio: $1500
```

Si no existe el número, se informa que no se encontró. Si `habitaciones.txt` no puede abrirse, se muestra un error y el programa termina.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Análisis de complejidad del algoritmo de ordenamiento

El segundo avance utiliza Merge Sort en `lista.h`. La función `mergeSort` divide una cadena de nodos en dos, ordena cada parte y la combina mediante `mezclar`. Se recorren O(n) nodos por nivel y hay O(log n) niveles de división. Por ello su tiempo es **O(n log n)** en el mejor, promedio y peor caso. No se crea otro arreglo ni se duplican las habitaciones: se reacomodan los enlaces. La implementación utiliza **O(log n)** espacio auxiliar por las llamadas recursivas de división, más espacio constante en cada combinación.

El primer avance utilizó Selection Sort, que realiza O(n²) comparaciones en todos los casos. Se cambió a Merge Sort para que el ordenamiento escale mejor conforme aumenten los registros.

#### Análisis de complejidad de las estructuras de datos y sus usos

La estructura principal es `ListaHabitaciones`, una lista simplemente enlazada en `lista.h` con punteros `head` y `tail` y un contador de nodos. Cada nodo contiene una `Habitacion` y un puntero al siguiente.

- **Agregar al final (`agregar`): O(1)** por registro, porque se mantiene `tail`. Cargar n registros del archivo toma O(n) tiempo en total.
- **Consultar si está vacía (`empty`) y su tamaño (`size`): O(1)**, porque se revisa `head` o se devuelve el contador.
- **Mostrar habitaciones (`mostrar`): O(n)**, ya que recorre todos los nodos.
- **Buscar por número (`buscar`): O(1)** en el mejor caso si está en el primer nodo; **O(n)** en el promedio y peor caso, cuando se recorren varios o todos los nodos.
- **Ordenar (`ordenar`): O(n log n)** por Merge Sort, más O(n) para actualizar el puntero `tail`. El total sigue siendo O(n log n).
- **Liberar los nodos (destructor): O(n)**, porque se recorre la lista y se hace `delete` de cada nodo.

El almacenamiento de n habitaciones en la lista requiere **O(n)** espacio. La lectura de archivo se hace registro por registro; el ordenamiento agrega O(log n) espacio auxiliar por recursión. Al iniciar, el programa ordena por número antes de presentar el menú.

### SICT0302: Toma decisiones

#### Selección del algoritmo de ordenamiento

Se eligió Merge Sort porque O(n log n) es más adecuado que O(n²) al crecer la cantidad de habitaciones. Además, el algoritmo puede aplicarse directamente a una lista enlazada separando y uniendo cadenas de nodos, sin copiar los registros a un vector.

La función `vaPrimero` compara según el criterio indicado: número, tipo, capacidad o precio. Cuando dos habitaciones tienen el mismo tipo, capacidad o precio, se compara el número para conservar un orden definido. La implementación está en `lista.h`.

#### Selección de la estructura de datos

Se eligió una lista simplemente enlazada implementada con nodos dinámicos porque el programa debe poder cargar una cantidad variable de habitaciones sin establecer un límite fijo en el código. El puntero `tail` facilita las inserciones al final con O(1), y la lista permite hacer Merge Sort cambiando los enlaces de sus nodos.

La lista tiene una limitación: no ofrece acceso directo por posición como un vector y la búsqueda por número sigue siendo O(n). Si el hotel llegara a necesitar muchísimas consultas por número, sería útil estudiar un índice adicional, como un árbol balanceado o una tabla hash. Para este avance se priorizó aplicar correctamente una estructura dinámica y un ordenamiento que no dependa de un tamaño pequeño de prueba.

### SICT0303: Implementa acciones científicas

#### Mecanismos para consultar información de las estructuras

`mostrar` recorre la lista y presenta todas las habitaciones. `buscar` avanza por sus nodos, compara el número de la habitación con `getNumero()` y devuelve la habitación encontrada o un puntero nulo. El menú permite consultar los registros en el orden predeterminado o elegir otros criterios de ordenamiento. Estas operaciones se implementaron en `lista.h` y se utilizan desde `main.cpp`.

#### Mecanismos de lectura de archivos para cargar datos

`main.cpp` abre `habitaciones.txt` mediante `ifstream`. El ciclo `while (archivo >> numero >> tipo >> capacidad >> precio)` lee los cuatro campos de cada registro; construye un objeto `Habitacion` y lo inserta mediante `habitaciones.agregar(habitacion)`. Se cierra el archivo después de la carga. Si no se puede abrir, el programa informa el problema y termina sin entrar al menú.
