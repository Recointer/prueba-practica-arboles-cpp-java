# Sistema Academico UTA - Arbol Binario de Busqueda en C++

> Universidad Tecnica de Ambato  
> Estructura de Datos - Prueba Practica  
> Implementacion en **C++** usando Arbol Binario de Busqueda (BST)

---

## Descripcion del Proyecto

Sistema de gestion de estudiantes universitarios implementado con un **Arbol Binario de Busqueda (BST)** en C++. Cada nodo del arbol almacena la informacion academica de un estudiante, ordenada por **cedula de identidad** como clave primaria.

### Datos de cada estudiante

| Campo      | Tipo     | Descripcion                   |
|------------|----------|-------------------------------|
| Cedula     | `string` | 10 digitos - clave del BST    |
| Apellidos  | `string` | Apellidos del estudiante      |
| Nombres    | `string` | Nombres del estudiante        |
| Nota Final | `float`  | Escala 0.0 a 10.0             |
| Carrera    | `string` | Carrera universitaria         |
| Nivel      | `string` | Nivel o semestre              |

**Nota minima de aprobacion:** 7.0 / 10.0

---

## Estructura del Proyecto

```
prueba-practica-arboles-cpp-java/
└── cpp/
    ├── Estudiante.h    # Struct con los datos del estudiante
    ├── NodoBST.h       # Struct del nodo del arbol (punteros izq/der)
    ├── ArbolBST.h      # Declaracion de la clase ArbolBST
    ├── ArbolBST.cpp    # Implementacion de todas las operaciones BST
    └── main.cpp        # Menu principal + validacion de entrada
```

---

## Compilacion y Ejecucion

### Requisitos

- Compilador: `g++` con soporte C++17 o superior
- Sistema operativo: Windows, Linux o macOS

### Compilar

```bash
# Desde la carpeta cpp/
g++ -o sistema main.cpp ArbolBST.cpp -std=c++17
```

### Ejecutar

```bash
# Linux / macOS
./sistema

# Windows
sistema.exe
```

---

## Funciones Implementadas

| N | Funcion                  | Descripcion                                          |
|---|--------------------------|------------------------------------------------------|
| 1 | `insertarEstudiante()`   | Inserta un estudiante (rechaza cedulas duplicadas)   |
| 2 | `buscarEstudiante()`     | Busca por cedula en O(log n)                         |
| 3 | `eliminarEstudiante()`   | Elimina por cedula (sucesor inorden si tiene 2 hijos)|
| 4 | `recorridoInorden()`     | Cedulas en orden ascendente (izq - raiz - der)       |
| 5 | `recorridoPreorden()`    | Raiz - izquierdo - derecho                           |
| 6 | `recorridoPostorden()`   | Izquierdo - derecho - raiz                           |
| 7 | `recorridoPorNiveles()`  | BFS nivel por nivel con std::queue                   |
| 8 | `contarNodos()`          | Cuenta total de estudiantes en el arbol              |
| 9 | `calcularAltura()`       | Altura del arbol (-1 si vacio, 0 si solo raiz)       |
|10 | `buscarNotaMayor()`      | Muestra el estudiante con la nota mas alta           |
|11 | `buscarNotaMenor()`      | Muestra el estudiante con la nota mas baja           |
|12 | `mostrarAprobados()`     | Lista estudiantes con nota >= 7.0                    |
|13 | `mostrarReprobados()`    | Lista estudiantes con nota < 7.0                     |

---

## Menu del Sistema

```
╔══════════════════════════════════════════════╗
║   SISTEMA ACADEMICO UTA - ARBOL BST C++      ║
║      Universidad Tecnica de Ambato            ║
╠══════════════════════════════════════════════╣
║  1.  Insertar estudiante                     ║
║  2.  Buscar estudiante por cedula            ║
║  3.  Eliminar estudiante                     ║
║  4.  Recorrido Inorden                       ║
║  5.  Recorrido Preorden                      ║
║  6.  Recorrido Postorden                     ║
║  7.  Recorrido por niveles (BFS)             ║
║  8.  Contar estudiantes                      ║
║  9.  Calcular altura del arbol               ║
║ 10.  Mostrar estudiante con mayor nota       ║
║ 11.  Mostrar estudiante con menor nota       ║
║ 12.  Mostrar estudiantes aprobados           ║
║ 13.  Mostrar estudiantes reprobados          ║
║ 14.  Salir                                   ║
╚══════════════════════════════════════════════╝
```

---

## Conceptos Tecnicos Aplicados

- **Arbol Binario de Busqueda (BST):** Clave = cedula, comparacion lexicografica de strings
- **Recursividad:** Insercion, busqueda, eliminacion, todos los recorridos, contar y altura
- **Punteros en C++:** `NodoBST*` para enlaces entre nodos, memoria con `new` y `delete`
- **Gestion de memoria:** Destructor libera toda la memoria en postorden evitando memory leaks
- **Cola BFS:** `std::queue<NodoBST*>` para recorrido por niveles
- **Clases y objetos:** Clase `ArbolBST` con metodos publicos y auxiliares privadas recursivas
- **Modularidad:** 4 archivos separados por responsabilidad
- **Validacion de datos:** Cedula (10 digitos), nota (0.0-10.0), campos no vacios

---

## Reglas de Validacion

- **Cedula:** Exactamente 10 caracteres numericos. No se permiten duplicados.
- **Nota:** Numero decimal entre 0.0 y 10.0. Se rechaza cualquier valor fuera del rango.
- **Campos de texto:** Ninguno puede estar vacio.
- **Arbol vacio:** Todas las operaciones notifican si el arbol no tiene datos.

---

## Instrucciones de Compilacion Detalladas

### Windows (MinGW / g++)

```bash
cd cpp
g++ -o sistema.exe main.cpp ArbolBST.cpp -std=c++17
sistema.exe
```

### Linux / macOS

```bash
cd cpp
g++ -o sistema main.cpp ArbolBST.cpp -std=c++17
./sistema
```

---

## Ejemplo de Ejecucion

### Insertar dos estudiantes y consultar el arbol

```
  Bienvenido al Sistema Academico UTA
  Gestion de Estudiantes con Arbol Binario de Busqueda

╔══════════════════════════════════════════════╗
║   SISTEMA ACADEMICO UTA - ARBOL BST C++      ║
║      Universidad Tecnica de Ambato            ║
╠══════════════════════════════════════════════╣
║  1.  Insertar estudiante                     ║
   ...
╚══════════════════════════════════════════════╝
  Seleccione una opcion: 1

── Insertar Estudiante ──
  Cedula (10 digitos): 1804567890
  Apellidos: Garcia Lopez
  Nombres  : Juan Carlos
  Nota final (0.0 - 10.0): 9.5
  Carrera  : Sistemas
  Nivel    : Segundo

 Estudiante con cedula 1804567890 insertado correctamente.

  Seleccione una opcion: 1

── Insertar Estudiante ──
  Cedula (10 digitos): 0502345678
  Apellidos: Mendoza Torres
  Nombres  : Ana Maria
  Nota final (0.0 - 10.0): 5.0
  Carrera  : Civil
  Nivel    : Tercero

Estudiante con cedula 0502345678 insertado correctamente.
```

### Recorrido Inorden (cedulas de menor a mayor)

```
  Seleccione una opcion: 4

══ Recorrido INORDEN (cedulas ascendente) ══
┌─────────────────────────────────────────┐
│ Cedula   : 0502345678                   │
│ Apellidos: Mendoza Torres               │
│ Nombres  : Ana Maria                    │
│ Nota     : 5.00                         │
│ Carrera  : Civil                        │
│ Nivel    : Tercero                      │
│ Estado   : REPROBADO                    │
└─────────────────────────────────────────┘
┌─────────────────────────────────────────┐
│ Cedula   : 1804567890                   │
│ Apellidos: Garcia Lopez                 │
│ Nombres  : Juan Carlos                  │
│ Nota     : 9.50                         │
│ Carrera  : Sistemas                     │
│ Nivel    : Segundo                      │
│ Estado   : APROBADO                     │
└─────────────────────────────────────────┘
```

### Contar estudiantes y calcular altura

```
  Seleccione una opcion: 8
── Total de estudiantes en el arbol: 2 ──

  Seleccione una opcion: 9
── Altura del arbol: 1 ──
```

### Estudiantes aprobados y reprobados

```
  Seleccione una opcion: 12

══ Estudiantes APROBADOS (nota >= 7.0) ══
┌─────────────────────────────────────────┐
│ Cedula   : 1804567890                   │
│ Nombres  : Juan Carlos                  │
│ Nota     : 9.50                         │
│ Estado   : APROBADO                     │
└─────────────────────────────────────────┘
Total aprobados: 1

  Seleccione una opcion: 13

══ Estudiantes REPROBADOS (nota < 7.0) ══
┌─────────────────────────────────────────┐
│ Cedula   : 0502345678                   │
│ Nombres  : Ana Maria                    │
│ Nota     : 5.00                         │
│ Estado   : REPROBADO                    │
└─────────────────────────────────────────┘
Total reprobados: 1
```

---

## Autor

Desarrollado por: Jonathan Valle  
Materia: Estructura de Datos  
Universidad Tecnica de Ambato - 2026
