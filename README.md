# Proyecto: Sistema de administración de habitaciones de un hotel

Este programa en C++ almacena habitaciones de un hotel. Cada una tiene un número, tipo, capacidad y precio por noche. Los registros se leen desde `habitaciones.txt` y se guardan en dos estructuras dinámicas: una **lista simplemente enlazada** (que define el orden en que se muestran y se ordena con Merge Sort) y un **árbol AVL** que funciona como índice por número de habitación. Desde un menú, el usuario puede consultar las habitaciones, ordenarlas por número, tipo, capacidad o precio, buscarlas por número y registrar habitaciones nuevas. El programa no tiene un límite fijo de habitaciones: está pensado para que el hotel pueda crecer.

## Descripción del avance 1

Se creó la clase `Habitacion` con los datos de cada registro y se implementó la lectura del archivo `habitaciones.txt`. La primera versión usaba un `vector<Habitacion>` y Selection Sort para ordenar por número. En esa etapa se mostraban los datos y el resultado del ordenamiento una sola vez.

## Descripción del avance 2

En este avance se agregó un menú interactivo para hacer varias consultas sin reiniciar el programa. Al principio se utilizó un vector y búsqueda secuencial.

Después de la retroalimentación del profesor, se cambió el almacenamiento principal a una **lista simplemente enlazada** implementada en `lista.h`, donde cada habitación se guarda en un nodo creado con `new`. También se implementó **Merge Sort sobre los enlaces de la lista**, para ordenar por número, tipo, capacidad y precio. Las habitaciones se ordenan por número automáticamente al cargar el archivo.

Para que el sistema escale cuando crezca el número de habitaciones, se agregó un **árbol AVL** (`indice.h`) como índice por número. Con él, la búsqueda por número pasó de O(n) a O(log n) y se impide registrar números repetidos. También se agregó la opción de **registrar habitaciones nuevas** desde el menú, de modo que las estructuras crecen mientras el programa está en ejecución. La clase `Hotel` (`hotel.h`) coordina la lista y el índice para que siempre estén sincronizados.

### Cambios sobre el primer avance

1. Se conservó `Habitacion` y la lectura de `habitaciones.txt`. Así no es necesario volver a definir los datos del problema.
2. Se agregó el menú interactivo para que el programa no sea una ejecución única.
3. Se sustituyó el vector principal por una lista enlazada dinámica. La cantidad de habitaciones no tiene que fijarse previamente; cada nodo se reserva conforme se lee el archivo y se libera al terminar el programa.
4. Se sustituyó Selection Sort en el funcionamiento actual por Merge Sort. Selection Sort tiene tiempo O(n²), mientras que Merge Sort permite ordenar O(n log n), una mejor decisión si aumenta la cantidad de habitaciones.
5. Se agregó el orden inicial por número y las opciones de ordenar por tipo, capacidad y precio. En los empates se usa el número de habitación como segundo criterio.
6. Se agregó un árbol AVL como índice por número (`indice.h`). Con la lista sola, buscar una habitación o verificar que un número no esté repetido costaba O(n); con el AVL cuesta O(log n) incluso en el peor caso, porque el árbol se mantiene balanceado. Así no se deja como "deuda técnica" para cuando el hotel tenga muchas más habitaciones.
7. Se agregó la opción de registrar habitaciones desde el menú. La nueva habitación se inserta en su posición según el orden actual de la lista y se agrega al índice.
8. La lectura del archivo ahora valida cada línea: las líneas con formato incorrecto, datos inválidos (número o capacidad ≤ 0, precio negativo) o números repetidos se reportan y se omiten, en lugar de detener la carga en silencio. El tipo se guarda en minúsculas para que `Suite` y `suite` se ordenen juntos.
9. Se corrigió el README para que coincida con el código actual. `sorts.h` se conserva en el repositorio como parte del primer avance, pero **no se utiliza en el segundo avance**.

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
7. Registrar una habitación nueva (número, tipo, capacidad y precio).
8. Salir.

Después de cada opción, el menú vuelve a aparecer. Los ordenamientos modifican el orden de los nodos de la lista, así que la opción 1 muestra el orden seleccionado más recientemente (el menú indica cuál es). Las habitaciones registradas se insertan respetando ese orden.

## Descripción de las entradas del avance de proyecto

El archivo `habitaciones.txt` tiene una habitación por línea, sin encabezados, con cuatro campos separados por espacios: número (`int`), tipo (`string` sin espacios), capacidad (`int`) y precio por noche (`double`).

Ejemplo:

```text
305 suite 4 2500
102 individual 1 900
210 doble 2 1500
```

No hay un límite en la cantidad de líneas. Las líneas vacías se ignoran; las líneas con formato incorrecto, datos inválidos o números repetidos se reportan con un aviso y se omiten. El usuario escribe una opción del menú y, según la opción, el número a buscar o los datos de la habitación a registrar.

## Descripción de las salidas del avance de proyecto

El programa muestra el menú y, según la opción seleccionada, lista las habitaciones en el orden actual o presenta el resultado de una búsqueda.

Ejemplo:

```text
Habitacion encontrada:
Habitacion 210 | Tipo: doble | Capacidad: 2 | Precio: $1500
```

Al iniciar se muestra cuántas habitaciones se cargaron. Si no existe el número buscado, se informa que no se encontró. Al registrar, se confirma el alta o se avisa si el número ya existe o los datos no son válidos. Si `habitaciones.txt` no puede abrirse, se muestra un error y el programa termina.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

El programa utiliza Merge Sort sobre la lista enlazada (`mergeSort` y `mezclar` en `lista.h`). `mergeSort` encuentra la mitad de la cadena de nodos con dos apuntadores (uno avanza de uno en uno y otro de dos en dos), la parte en dos, ordena cada mitad recursivamente y las une con `mezclar`. En cada nivel de recursión se recorren O(n) nodos en total (para partir y para mezclar) y hay O(log n) niveles, por lo que el tiempo es **O(n log n) en el mejor, promedio y peor caso**: Merge Sort siempre divide a la mitad, sin importar si los datos ya vienen ordenados.

En espacio, no se crea otro arreglo ni se copian las habitaciones: solo se reacomodan los enlaces `siguiente`. El espacio auxiliar es **O(log n)** por la pila de llamadas recursivas, más O(1) en cada mezcla.

El primer avance utilizaba Selection Sort, que hace O(n²) comparaciones en todos los casos. Con 100,000 habitaciones eso serían alrededor de 5,000 millones de comparaciones, contra aproximadamente 1.7 millones de Merge Sort.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.

**Lista simplemente enlazada (`ListaHabitaciones`, `lista.h`).** Tiene apuntadores `head` y `tail` y un contador. Cada nodo guarda una `Habitacion` y un apuntador al siguiente.

- `agregar` (al final): **O(1)**, porque se mantiene `tail`. Se usa al cargar el archivo.
- `insertarOrdenado`: **O(n)** en el peor y promedio caso (recorre hasta encontrar su posición), **O(1)** en el mejor caso (va al inicio). Se usa al registrar desde el menú.
- `ordenar`: **O(n log n)** por Merge Sort, más O(n) para actualizar `tail`; el total es O(n log n).
- `mostrar`: **O(n)**, recorre todos los nodos.
- `empty` y `size`: **O(1)**.
- Destructor: **O(n)**, libera cada nodo con `delete`.
- Espacio: **O(n)**.

**Árbol AVL (`IndiceHabitaciones`, `indice.h`).** Cada nodo guarda el número de la habitación, un apuntador a la habitación que está en la lista (no se duplican los datos), sus hijos y su altura. Después de cada inserción se revisa el factor de balance y se aplican rotaciones simples o dobles, así que la altura siempre es O(log n).

- `insertar`: **O(log n)** en el peor caso: baja por una rama de altura O(log n) y, de regreso, actualiza alturas y hace a lo más una rotación (simple o doble) de costo O(1).
- `buscar` / `contiene`: **O(1)** en el mejor caso (está en la raíz) y **O(log n)** en el promedio y el peor caso. A diferencia de un BST simple, que puede degenerar en una lista con O(n) si las habitaciones se insertan en orden (por ejemplo, si el archivo ya viene ordenado por número), el AVL garantiza O(log n).
- Destructor: **O(n)**.
- Espacio: **O(n)**.

**Usos combinados (`Hotel`, `hotel.h`).**

- Cargar n habitaciones: n inserciones O(1) en la lista + n inserciones O(log n) en el AVL + un Merge Sort O(n log n) = **O(n log n)**. Se decidió insertar al final y ordenar una sola vez en lugar de usar `insertarOrdenado` n veces, porque eso costaría O(n²).
- Registrar una habitación: verificar duplicado O(log n) + insertar en orden O(n) + insertar en el índice O(log n) = **O(n)**. Es mejor que volver a ordenar toda la lista (O(n log n)).
- Buscar por número: **O(log n)** con el AVL (antes O(n) recorriendo la lista).

### SICT0302: Toma decisiones

#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

Se eligió Merge Sort porque:

1. Es **O(n log n) garantizado**, también en el peor caso. Quick Sort también es O(n log n) en promedio, pero tiene peor caso O(n²), y ese caso aparece justo con datos ya ordenados, lo cual es común aquí: la lista siempre está ordenada por algún criterio cuando el usuario pide otro.
2. **Funciona muy bien sobre listas enlazadas**: solo necesita recorrer los nodos de forma secuencial y cambiar enlaces, sin acceso por índice y sin copiar las habitaciones a un vector auxiliar. Algoritmos como Quick Sort o Heap Sort dependen del acceso directo por posición, que la lista no tiene.
3. Es **estable** y, además, en los empates se usa el número como segundo criterio (`vaPrimero`), por lo que el resultado siempre es el mismo y fácil de leer: por ejemplo, dos suites con el mismo precio aparecen ordenadas por número.

Se ordena por número como opción predeterminada al cargar, y se puede ordenar por tipo, capacidad y precio, que son los criterios útiles para quien busca una habitación.

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

El proyecto no está pensado solo para las 10 habitaciones del archivo de ejemplo, sino para un hotel (o cadena) que puede crecer. Por eso se usan dos estructuras dinámicas, cada una para lo que hace mejor:

- **Lista simplemente enlazada** para guardar las habitaciones y su orden de presentación. Crece nodo por nodo con `new`, sin un tamaño máximo, sin tener que copiar todo al llenarse (como un vector) y con inserción al final en O(1). Además, permite aplicar Merge Sort cambiando solo los enlaces.
- **Árbol AVL** como índice por número. La lista sola obliga a buscar en O(n), y eso también afectaría cada alta, porque hay que verificar que el número no exista. El AVL baja ambas operaciones a O(log n) garantizado. Se prefirió un AVL sobre un BST simple porque un BST se degenera a O(n) si se insertan números en orden, y sobre una tabla hash porque el AVL no requiere fijar un tamaño de tabla ni rehash al crecer, y su peor caso es O(log n), mientras que una hash puede degradarse con colisiones.

Que el AVL guarde apuntadores a las habitaciones de la lista es seguro porque Merge Sort nunca mueve los nodos en memoria: solo cambia el enlace `siguiente`. La clase `Hotel` es la única que modifica ambas estructuras, así se garantiza que estén sincronizadas.

Prueba de escalabilidad: con un archivo de 100,000 habitaciones, el programa carga, busca y ordena por precio y por número en menos de un segundo.

### SICT0303: Implementa acciones científicas

#### Implementa mecanismos para consultar información de las estructras correctos.

- `Hotel::mostrar` → `ListaHabitaciones::mostrar` recorre la lista y muestra todas las habitaciones en el orden actual. El menú indica cuál es ese orden.
- `Hotel::ordenar` reordena la lista por número, tipo, capacidad o precio con Merge Sort.
- `Hotel::buscar` → `IndiceHabitaciones::buscar` baja por el AVL comparando números y regresa un apuntador a la habitación o un apuntador nulo si no existe.
- `Hotel::registrar` verifica en el AVL que el número no exista, inserta la habitación en la lista en su posición según el orden actual y la agrega al índice.

Estas operaciones se usan desde el menú de `main.cpp`. Las entradas del usuario se validan, así que un texto en lugar de un número no detiene el programa.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

`Hotel::cargarArchivo` (`hotel.h`) abre `habitaciones.txt` con `ifstream` y lo lee línea por línea con `getline`. Cada línea se separa con un `stringstream` en número, tipo, capacidad y precio. Antes de insertar se verifica que:

- la línea tenga exactamente los cuatro campos y de tipo correcto;
- el número y la capacidad sean mayores a 0 y el precio no sea negativo;
- el número no esté repetido (consulta al AVL en O(log n)).

Las líneas que no cumplen se reportan indicando su número de línea y se omiten, así una línea mal escrita no detiene la carga del resto. Cada habitación válida se agrega a la lista y al índice. Al final se cierra el archivo y se ordena por número. Si el archivo no puede abrirse, el programa informa el problema y termina sin entrar al menú.
