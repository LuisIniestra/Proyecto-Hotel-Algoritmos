# Proyecto: Sistema de administración de habitaciones de un hotel

Este programa en C++ administra las habitaciones de un hotel. Cada habitación tiene un número, tipo, capacidad, precio por noche y un estado (**disponible** u **ocupada**). Los registros se leen desde `habitaciones.txt` y se guardan en dos estructuras dinámicas: una **lista simplemente enlazada**, que define el orden en que se muestran y se ordena con Merge Sort, y un **árbol AVL** que funciona como índice por número de habitación.

Desde un menú, el personal del hotel puede consultar qué habitaciones están disponibles para cierta cantidad de personas, ocupar y liberar habitaciones (check-in y check-out), ordenarlas por número, tipo, capacidad o precio, buscarlas por número, registrar habitaciones nuevas y guardar todos los cambios de regreso en `habitaciones.txt`. El programa no tiene un límite fijo de habitaciones: está pensado para que el hotel pueda crecer.

## Descripción del avance 1

Se creó la clase `Habitacion` con los datos de cada registro y se implementó la lectura del archivo `habitaciones.txt`. La primera versión usaba un `vector<Habitacion>` y Selection Sort para ordenar por número. En esa etapa se mostraban los datos y el resultado del ordenamiento una sola vez.

## Descripción del avance 2

Se agregó un menú interactivo para hacer varias consultas sin reiniciar el programa. Después de la retroalimentación del profesor, se cambió el almacenamiento principal a una **lista simplemente enlazada** implementada en `lista.h`, donde cada habitación se guarda en un nodo creado con `new`. También se implementó **Merge Sort sobre los enlaces de la lista**, para ordenar por número, tipo, capacidad y precio. Las habitaciones se ordenan por número automáticamente al cargar el archivo.

### Cambios sobre el primer avance

1. Se conservó `Habitacion` y la lectura de `habitaciones.txt`. Así no es necesario volver a definir los datos del problema.
2. Se agregó el menú interactivo para que el programa no sea una ejecución única.
3. Se sustituyó el vector principal por una lista enlazada dinámica. La cantidad de habitaciones no tiene que fijarse previamente; cada nodo se reserva conforme se lee el archivo y se libera al terminar el programa.
4. Se sustituyó Selection Sort por Merge Sort. Selection Sort tiene tiempo O(n²), mientras que Merge Sort ordena en O(n log n), una mejor decisión si aumenta la cantidad de habitaciones.
5. Se agregó el orden inicial por número y las opciones de ordenar por tipo, capacidad y precio. En los empates se usa el número de habitación como segundo criterio.

## Descripción del avance 3

Para que el sistema escale cuando crezca el número de habitaciones, se agregó un **árbol AVL** (`indice.h`) como índice por número y la opción de **registrar habitaciones nuevas** desde el menú, de modo que las estructuras crecen mientras el programa está en ejecución. La clase `Hotel` (`hotel.h`) coordina la lista y el índice para que siempre estén sincronizados.

### Cambios sobre el segundo avance

1. Se agregó un árbol AVL como índice por número (`indice.h`). Con la lista sola, buscar una habitación o verificar que un número no esté repetido costaba O(n); con el AVL cuesta O(log n) incluso en el peor caso, porque el árbol se mantiene balanceado. Así no se deja como "deuda técnica" para cuando el hotel tenga muchas más habitaciones.
2. Se agregó la opción de registrar habitaciones desde el menú. La nueva habitación se inserta en su posición según el orden actual de la lista y se agrega al índice.
3. La lectura del archivo valida cada línea: las líneas con formato incorrecto, datos inválidos (número o capacidad ≤ 0, precio negativo) o números repetidos se reportan y se omiten, en lugar de detener la carga en silencio. El tipo se guarda en minúsculas para que `Suite` y `suite` se ordenen juntos.
4. `sorts.h` se conserva en el repositorio como parte del primer avance, pero **ya no se utiliza**.

## Entrega final

La entrega final convierte el programa en una herramienta útil para la operación diaria del hotel: además de administrar el catálogo de habitaciones, permite saber **qué habitaciones están disponibles** y **guardar los cambios** para que no se pierdan al cerrar el programa.

### Cambios sobre el tercer avance

1. **Estado de cada habitación.** `Habitacion` ahora guarda si está disponible u ocupada. Razón: atender la retroalimentación de Cultura digital; lo que más le sirve a quien atiende la recepción es saber qué habitaciones puede ofrecer.
2. **Consulta de habitaciones disponibles** (opción 2). Se indica el número de personas y se muestran solo las habitaciones disponibles con capacidad suficiente, en el orden elegido (por ejemplo, ordenadas por precio para ofrecer la más económica primero).
3. **Ocupar y liberar habitaciones** (check-in y check-out, opciones 9 y 10). Se localizan con el AVL en O(log n) y se cambia su estado. El programa avisa si la habitación no existe o si ya tenía ese estado.
4. **Escritura de archivo** (opción 11). `Hotel::guardarArchivo` escribe todas las habitaciones, incluidas las nuevas y su estado, en `habitaciones.txt` con el mismo formato que se lee. Si al salir hay cambios sin guardar, el programa pregunta si se desean guardar. Razón: sin escritura, las altas y los check-in se perdían al cerrar el programa.
5. **El archivo acepta un quinto campo** con el estado. Es opcional: un archivo con solo cuatro campos (como el de avances anteriores) sigue funcionando y sus habitaciones se cargan como disponibles.
6. Se agregó el análisis de complejidad de los demás componentes y la complejidad final del programa.

## Instrucciones para compilar el proyecto

Con `g++` y desde la carpeta que contiene todos los archivos:

```bash
g++ main.cpp -std=c++11 -o final
```

## Instrucciones para ejecutar el proyecto

En Linux o macOS:

```bash
./final
```

En Windows PowerShell:

```powershell
.\final.exe
```

`habitaciones.txt` debe estar en el directorio desde el que se ejecuta el programa.

El menú tiene estas opciones:

1. Mostrar todas las habitaciones en su orden actual (inicialmente por número).
2. Consultar habitaciones disponibles para cierta cantidad de personas.
3. Ordenar por número, de menor a mayor.
4. Ordenar por tipo, alfabéticamente.
5. Ordenar por capacidad, de menor a mayor.
6. Ordenar por precio, de menor a mayor.
7. Buscar una habitación por número.
8. Registrar una habitación nueva (número, tipo, capacidad y precio). Se registra como disponible.
9. Ocupar una habitación (check-in).
10. Liberar una habitación (check-out).
11. Guardar los cambios en `habitaciones.txt`.
0. Salir (si hay cambios sin guardar, pregunta si se desean guardar).

Después de cada opción, el menú vuelve a aparecer. Los ordenamientos modifican el orden de los nodos de la lista, así que las opciones 1 y 2 muestran el orden seleccionado más recientemente (el menú indica cuál es).

## Descripción de las entradas del proyecto

El archivo `habitaciones.txt` tiene una habitación por línea, sin encabezados, con campos separados por espacios: número (`int`), tipo (`string` sin espacios), capacidad (`int`), precio por noche (`double`) y, de forma opcional, el estado (`disponible` u `ocupada`). Si no se indica el estado, la habitación se carga como disponible.

Ejemplo:

```text
101 individual 2 750.00 disponible
204 doble 3 1800.00 ocupada
305 suite 4 2500.00 ocupada
407 suite 5 3200
```

No hay un límite en la cantidad de líneas. Las líneas vacías se ignoran; las líneas con formato incorrecto, datos inválidos, un estado distinto de `disponible`/`ocupada` o números repetidos se reportan con un aviso y se omiten.

Desde el teclado, el usuario escribe una opción del menú y, según la opción, el número de personas, el número de habitación o los datos de la habitación a registrar. Las entradas no numéricas se rechazan y se vuelven a pedir.

## Descripción de las salidas del proyecto

Al iniciar se muestra cuántas habitaciones se cargaron y cuántas están disponibles. Cada habitación se presenta así:

```text
Habitacion 210 | Tipo: doble | Capacidad: 2 | Precio: $1500 | Estado: disponible
```

Ejemplo de consulta de disponibilidad para 4 personas:

```text
HABITACIONES DISPONIBLES (orden: numero)
Habitacion 301 | Tipo: suite | Capacidad: 4 | Precio: $2700 | Estado: disponible
Habitacion 407 | Tipo: suite | Capacidad: 5 | Precio: $3200 | Estado: disponible
Total: 2
```

Al ocupar o liberar una habitación se confirma el cambio y se muestra cuántas quedan disponibles. Al guardar, el archivo `habitaciones.txt` se **sobrescribe** con todas las habitaciones ordenadas por número y con los cinco campos, por ejemplo `305 suite 4 2500.00 ocupada`, de modo que la siguiente ejecución carga el estado actualizado. Si `habitaciones.txt` no puede abrirse al iniciar, se muestra un error y el programa termina.

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
- `mostrarDisponibles`: **O(n)**, recorre todos los nodos y muestra solo los que están disponibles y tienen capacidad suficiente. No puede ser menor que O(n) porque, en el peor caso, todas las habitaciones cumplen el filtro y hay que mostrarlas.
- `empty` y `size`: **O(1)**.
- Destructor: **O(n)**, libera cada nodo con `delete`.
- Espacio: **O(n)**.

**Árbol AVL (`IndiceHabitaciones`, `indice.h`).** Cada nodo guarda el número de la habitación, un apuntador a la habitación que está en la lista (no se duplican los datos), sus hijos y su altura. Después de cada inserción se revisa el factor de balance y se aplican rotaciones simples o dobles, así que la altura siempre es O(log n).

- `insertar`: **O(log n)** en el peor caso: baja por una rama de altura O(log n) y, de regreso, actualiza alturas y hace a lo más una rotación (simple o doble) de costo O(1).
- `buscar` / `contiene`: **O(1)** en el mejor caso (está en la raíz) y **O(log n)** en el promedio y el peor caso. A diferencia de un BST simple, que puede degenerar en una lista con O(n) si las habitaciones se insertan en orden (por ejemplo, si el archivo ya viene ordenado por número), el AVL garantiza O(log n).
- `escribirOrdenado`: **O(n)**, recorrido inorden que visita cada nodo una vez. Usa O(log n) de espacio en la pila de recursión, porque esa es la altura del árbol.
- Destructor: **O(n)**.
- Espacio: **O(n)**.

**Usos combinados (`Hotel`, `hotel.h`).**

- Cargar n habitaciones: n inserciones O(1) en la lista + n inserciones O(log n) en el AVL + un Merge Sort O(n log n) = **O(n log n)**. Se decidió insertar al final y ordenar una sola vez en lugar de usar `insertarOrdenado` n veces, porque eso costaría O(n²).
- Registrar una habitación: verificar duplicado O(log n) + insertar en orden O(n) + insertar en el índice O(log n) = **O(n)**. Es mejor que volver a ordenar toda la lista (O(n log n)).
- Buscar por número: **O(log n)** con el AVL (antes O(n) recorriendo la lista).
- Ocupar o liberar una habitación (`ocupar`, `liberar`): búsqueda en el AVL O(log n) + cambio de estado O(1) = **O(log n)**. Como el AVL apunta a la misma habitación que está en la lista, el cambio se ve en ambas estructuras sin recorrer la lista.
- Contar disponibles (`disponibles`): **O(1)**, porque `Hotel` mantiene un contador de ocupadas que se actualiza en cada check-in, check-out y alta, en lugar de recorrer la lista.
- Guardar en archivo (`guardarArchivo`): **O(n)** con el recorrido inorden del AVL.

#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.

Sea **n** el número de habitaciones y **k** el número de opciones que el usuario elige en el menú durante una ejecución.

**Componentes auxiliares**

- Constructores, getters y `setDisponible` (`habitacion.h`): **O(1)**, porque solo asignan o regresan un dato.
- `toString` y `toArchivo` (`habitacion.h`): **O(1)**, porque arman una línea con un número fijo de campos.
- `normalizarTipo` (`hotel.h`): **O(m)**, donde m es el número de letras del tipo. Como el tipo es una palabra corta que no depende de n, en la práctica es O(1).
- `datosValidos` (`hotel.h`): **O(1)**, son cuatro comparaciones.
- `nombreCriterio`, `disponibles` y `hayCambiosSinGuardar` (`hotel.h`): **O(1)**, regresan un valor que ya está guardado.
- `leerEntero` y `leerDouble` (`main.cpp`): **O(1)** por cada lectura válida. Cada intento es O(1) y solo se repite si el usuario escribe un valor inválido.
- `registrarHabitacion` (`main.cpp`): **O(n)**. Leer los datos es O(1), verificar el número en el AVL es O(log n) y `Hotel::registrar` es O(n).
- `cambiarEstado` (`main.cpp`): **O(log n)**, porque llama a `ocupar` o `liberar`.
- `guardar` (`main.cpp`): **O(n)**, porque llama a `guardarArchivo`.

**Lectura del archivo (`cargarArchivo`)**

Cada línea se separa y valida en O(1); verificar duplicados en el AVL cuesta O(log n); insertar en la lista O(1) y en el AVL O(log n). Para n líneas son O(n log n), y al final un Merge Sort O(n log n). Total: **O(n log n)**.

**Escritura del archivo (`guardarArchivo`)**

Recorrido inorden del AVL: cada habitación se convierte a texto y se escribe en O(1), en total **O(n)**. Se escribe desde el AVL y no desde la lista porque el AVL ya está ordenado por número; escribir en orden desde la lista obligaría a reordenarla en O(n log n) y cambiaría el orden que el usuario eligió.

**Cada opción del menú (`main`)**

- Opción 1, mostrar todas: **O(n)**.
- Opción 2, consultar disponibles: **O(n)**.
- Opciones 3 a 6, ordenar y mostrar: O(n log n) + O(n) = **O(n log n)**.
- Opción 7, buscar por número: **O(log n)**.
- Opción 8, registrar: **O(n)**.
- Opciones 9 y 10, ocupar y liberar: **O(log n)**.
- Opción 11, guardar: **O(n)**.
- Opción 0, salir (con o sin guardar): **O(n)**.

**Complejidad final del programa**

- Inicio: cargar el archivo, **O(n log n)**.
- Cada opción del menú cuesta, en el peor caso, **O(n log n)** (ordenar).
- Al salir: guardar O(n) y liberar la lista y el árbol O(n).

Para una ejecución con k opciones: O(n log n) + k · O(n log n) + O(n) = **O((k + 1) · n log n)**. Es decir, el programa es **O(n log n)** por operación, y lo que domina es el ordenamiento con Merge Sort. Las operaciones más frecuentes en la recepción (buscar, ocupar y liberar) son O(log n) gracias al AVL. El espacio total es **O(n)**: la lista y el árbol guardan un nodo por habitación, y las recursiones (Merge Sort y recorrido del AVL) solo agregan O(log n).

Si se hubiera usado Selection Sort y búsqueda secuencial, como en el primer avance, ordenar costaría O(n²) y cada check-in O(n), lo que haría al programa O(k · n²).

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
- `Hotel::mostrarDisponibles` → `ListaHabitaciones::mostrarDisponibles` recorre la lista y muestra solo las habitaciones disponibles con capacidad para el número de personas indicado, respetando el orden elegido.
- `Hotel::ocupar` y `Hotel::liberar` buscan la habitación en el AVL y cambian su estado; regresan si la habitación no existe, si cambió o si ya tenía ese estado, para que el menú informe el resultado.
- `Hotel::registrar` verifica en el AVL que el número no exista, inserta la habitación en la lista en su posición según el orden actual y la agrega al índice.

Estas operaciones se usan desde el menú de `main.cpp`. Las entradas del usuario se validan, así que un texto en lugar de un número no detiene el programa.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

`Hotel::cargarArchivo` (`hotel.h`) abre `habitaciones.txt` con `ifstream` y lo lee línea por línea con `getline`. Cada línea se separa con un `stringstream` en número, tipo, capacidad, precio y, si existe, estado. Antes de insertar se verifica que:

- la línea tenga los cuatro campos obligatorios y de tipo correcto, y a lo más un quinto campo que sea `disponible` u `ocupada`;
- el número y la capacidad sean mayores a 0 y el precio no sea negativo;
- el número no esté repetido (consulta al AVL en O(log n)).

Las líneas que no cumplen se reportan indicando su número de línea y se omiten, así una línea mal escrita no detiene la carga del resto. Cada habitación válida se agrega a la lista y al índice con su estado, y se actualiza el contador de ocupadas. Como el estado es opcional, el programa sigue leyendo archivos con el formato de los avances anteriores. Al final se cierra el archivo y se ordena por número. Si el archivo no puede abrirse, el programa informa el problema y termina sin entrar al menú.

#### Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta.

`Hotel::guardarArchivo` (`hotel.h`) abre `habitaciones.txt` con `ofstream` y escribe una línea por habitación usando `Habitacion::toArchivo`, con el mismo formato que lee `cargarArchivo`: número, tipo, capacidad, precio y estado. Por eso lo que se guarda se puede volver a cargar sin cambios, y en la siguiente ejecución se conservan las habitaciones registradas y cuáles están ocupadas.

Detalles para que la escritura sea correcta:

- Las habitaciones se escriben **ordenadas por número** mediante un recorrido inorden del AVL (`IndiceHabitaciones::escribirOrdenado`), sin importar el orden en que el usuario esté viendo la lista.
- El precio se escribe con `std::fixed` y dos decimales (`2500.00`), así no se pierden centavos ni se usa notación científica con precios grandes, que no se podría leer después.
- Después de cerrar el archivo se revisa `fail()`; si la escritura falló, se informa el error y los cambios se siguen marcando como pendientes.
- Se puede guardar en cualquier momento con la opción 11, y si el usuario sale con cambios sin guardar, el programa pregunta si desea guardarlos para que no se pierdan.

Se probó guardando 100,000 habitaciones, volviendo a cargar el archivo y verificando que se recuperaran todas, en orden por número y con el mismo número de habitaciones ocupadas.
