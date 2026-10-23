# Proyecto: Sistema de administración de habitaciones de un hotel

Programa en C++ para organizar y consultar habitaciones de un hotel. Cada habitación tiene número, tipo, capacidad y precio por noche. La información se lee del archivo `habitaciones.txt` y se almacena en un `vector<Habitacion>`.

## Descripción del avance 1

Se creó la clase `Habitacion` en `habitacion.h`, se implementó la lectura desde `habitaciones.txt` y se ordenaron las habitaciones de menor a mayor por número con Selection Sort de `sorts.h`. El programa mostraba los datos originales y ordenados, pero solo hacía una ejecución.

## Descripción del avance 2

El programa conserva los registros en un `vector<Habitacion>`. Ahora incluye un menú para mostrar todas las habitaciones, ordenarlas por número, buscar una habitación por número y salir. Permite hacer varias consultas durante la misma ejecución.

### Cambios sobre el primer avance

1. **Menú interactivo:** se agregó en `main.cpp` para que el usuario elija distintas acciones sin reiniciar el programa. Corrige la primera observación del profesor.
2. **Búsqueda secuencial:** se agregó una función para consultar por número directamente dentro del vector.
3. **Uso de la estructura de datos:** se mantiene `vector<Habitacion>` porque permite cargar una cantidad variable de registros, acceder por índice y recorrer la información.
4. **Documentación corregida:** el algoritmo realmente utilizado es **Selection Sort**, no Merge Sort; los registros provienen de **`habitaciones.txt`**, no están precargados en el código. El README ahora coincide con el funcionamiento del programa. Esto atiende las otras observaciones del profesor.

## Instrucciones para compilar el avance de proyecto

Desde la carpeta que contiene `main.cpp`, `habitacion.h`, `sorts.h` y `habitaciones.txt`, con `g++` instalado:

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

Hay que ejecutar el programa desde la carpeta donde se encuentra `habitaciones.txt`, porque se abre con una ruta relativa. Aparece un menú con estas opciones:

1. **Mostrar habitaciones:** muestra los registros en el orden en que fueron leídos.
2. **Ordenar por número:** ordena una copia con Selection Sort y la muestra de menor a mayor.
3. **Buscar habitación por número:** solicita el número entero y muestra la habitación si se encuentra.
4. **Salir:** termina el programa.

Después de cada consulta vuelve a mostrarse el menú. Ante entradas inválidas se muestra un mensaje y se permite continuar.

## Descripción de las entradas del avance de proyecto

El archivo `habitaciones.txt` contiene una habitación por línea, con el siguiente formato, sin encabezado:

```text
305 suite 4 2500
102 individual 1 900
210 doble 2 1500
```

Cada línea tiene cuatro datos separados por espacios: **número** (int), **tipo** (string sin espacios), **capacidad** (int) y **precio por noche** (double). El archivo del proyecto contiene diez habitaciones. `main.cpp` lee estos campos con `ifstream`, construye objetos `Habitacion` y los guarda con `push_back`.

El usuario introduce una opción del 1 al 4. Al buscar, también introduce el número de habitación.

## Descripción de las salidas del avance de proyecto

El programa muestra el menú, las habitaciones originales, las habitaciones ordenadas por número o la información de una habitación concreta. Por ejemplo, al buscar el número 210:

```text
Habitacion encontrada:
Habitacion 210 | Tipo: doble | Capacidad: 2 | Precio: $1500
```

Si el número no existe, aparece `No se encontro la habitacion 999.` (con el número consultado). Si no se puede abrir el archivo, el programa muestra un error y termina.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Análisis de complejidad del algoritmo de ordenamiento

En `sorts.h`, Selection Sort busca el mayor elemento de la sección pendiente y lo coloca al final. Realiza aproximadamente `n(n-1)/2` comparaciones. Su complejidad temporal es **O(n²)** en el mejor caso, promedio y peor caso, independientemente del orden inicial. La implementación copia el vector, por lo que ocupa **O(n)** espacio adicional. Sin contar la copia, las variables de control y los intercambios usan **O(1)** espacio auxiliar.

#### Análisis de complejidad de las estructuras de datos y cada uso

La estructura empleada es `vector<Habitacion>`, con `n` registros. Sus operaciones en este programa son:

| Uso | Archivo o función | Tiempo |
| --- | --- | --- |
| Agregar una habitación con `push_back` | `main.cpp`, lectura del archivo | O(1) amortizado por inserción |
| Cargar `n` habitaciones | `main.cpp` | O(n) total amortizado |
| Acceder por índice `habitaciones[i]` | Mostrar y buscar | O(1) por acceso |
| Consultar `size()` y `empty()` | Recorridos y visualización | O(1) |
| Recorrer para mostrar todos los datos | `mostrarHabitaciones` | O(n) |
| Buscar un número | `buscarHabitacion` | O(1) mejor caso; O(n) promedio y peor caso |
| Copiar el vector antes de ordenar | `selectionSort` | O(n) tiempo y O(n) espacio |
| Ordenar con Selection Sort | `selectionSort` | O(n²) tiempo |

El vector original ocupa **O(n)** espacio. Cuando se ordena, se crea temporalmente una copia de `n` elementos; la memoria total continúa siendo **O(n)**. Los archivos se leen una sola vez al iniciar el programa.

### SICT0302: Toma decisiones

#### Selección del algoritmo de ordenamiento

Se conserva **Selection Sort** porque es un algoritmo sencillo y visto en clase. Es adecuado para demostrar el ordenamiento de los diez registros de prueba. Utiliza el `operator>` de `Habitacion` para comparar números. Aunque O(n²) no es lo ideal para un catálogo muy grande, permite implementar el algoritmo directamente sin usar `std::sort`. Está en `sorts.h`, y se llama desde la opción 2 del menú.

#### Selección de la estructura de datos

Se eligió **`vector<Habitacion>`** porque no es necesario fijar previamente la cantidad de habitaciones. Se pueden cargar registros con `push_back`, recorrerlos para mostrarlos y acceder a sus posiciones para buscar. Para las consultas sencillas de este avance, un vector es suficiente y no requiere agregar estructuras más complejas. Su uso se puede ver en `main.cpp`.

### SICT0303: Implementa acciones científicas

#### Mecanismos para consultar información de las estructuras

En `main.cpp`, `mostrarHabitaciones` recorre el vector para mostrar los registros. `buscarHabitacion` compara el número solicitado con `getNumero()` hasta encontrarlo o llegar al final. La búsqueda es secuencial porque los datos originales conservan el orden del archivo. La opción 2 permite consultar también una copia ordenada por número.

#### Mecanismos de lectura de archivos para cargar datos

`main.cpp` usa `ifstream` para abrir `habitaciones.txt`. El ciclo `while (archivo >> numero >> tipo >> capacidad >> precio)` lee los cuatro campos de cada registro; después construye una `Habitacion` y la agrega al vector con `push_back`. Al terminar se cierra el archivo. Si no puede abrirse, se muestra un mensaje y se detiene el programa.
