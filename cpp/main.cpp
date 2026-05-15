/**
 * @file main.cpp
 * @brief Sistema Académico UTA - Menú principal
 *
 * Punto de entrada del sistema. Gestiona el menú interactivo de 14 opciones
 * y valida todos los datos ingresados por el usuario.
 *
 * Compilación:
 *   g++ -o sistema main.cpp ArbolBST.cpp -std=c++17
 *
 * Ejecución:
 *   ./sistema       (Linux/Mac)
 *   sistema.exe     (Windows)
 *
 * Universidad Técnica de Ambato - Sistema Académico BST
 */

#include "ArbolBST.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>

// ─────────────────────────────────────────────────────────────────────────────
// Utilidades de validación
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Limpia el buffer de entrada para evitar lecturas basura.
 */
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Valida que una cédula tenga exactamente 10 dígitos numéricos.
 * @param cedula Cadena a validar.
 * @return true si es válida.
 */
bool cedulaValida(const std::string& cedula) {
    if (cedula.size() != 10) return false;
    return std::all_of(cedula.begin(), cedula.end(), ::isdigit);
}

/**
 * @brief Valida que una nota esté en el rango [0.0, 10.0].
 * @param nota Valor a validar.
 * @return true si es válida.
 */
bool notaValida(float nota) {
    return nota >= 0.0f && nota <= 10.0f;
}

/**
 * @brief Lee un string no vacío del usuario.
 * @param prompt Mensaje a mostrar.
 * @return String ingresado (sin espacios extremos).
 */
std::string leerString(const std::string& prompt) {
    std::string valor;
    do {
        std::cout << prompt;
        std::getline(std::cin, valor);
        if (valor.empty())
            std::cout << "  ⚠ El campo no puede estar vacío. Intente de nuevo.\n";
    } while (valor.empty());
    return valor;
}

/**
 * @brief Lee una cédula válida del usuario.
 * @return Cédula de 10 dígitos.
 */
std::string leerCedula() {
    std::string cedula;
    do {
        std::cout << "  Cédula (10 dígitos): ";
        std::getline(std::cin, cedula);
        if (!cedulaValida(cedula))
            std::cout << "  ⚠ Cédula inválida. Debe tener exactamente 10 dígitos numéricos.\n";
    } while (!cedulaValida(cedula));
    return cedula;
}

/**
 * @brief Lee una nota válida en [0.0, 10.0].
 * @return Nota ingresada.
 */
float leerNota() {
    float nota;
    bool valido = false;
    do {
        std::cout << "  Nota final (0.0 - 10.0): ";
        if (std::cin >> nota) {
            limpiarBuffer();
            if (notaValida(nota))
                valido = true;
            else
                std::cout << "  ⚠ La nota debe estar entre 0.0 y 10.0.\n";
        } else {
            limpiarBuffer();
            std::cout << "  ⚠ Ingrese un número válido.\n";
        }
    } while (!valido);
    return nota;
}

/**
 * @brief Lee la opción del menú principal.
 * @return Opción elegida (1-14).
 */
int leerOpcion() {
    int opcion;
    while (!(std::cin >> opcion) || opcion < 1 || opcion > 14) {
        limpiarBuffer();
        std::cout << "  ⚠ Opción inválida. Ingrese un número entre 1 y 14: ";
    }
    limpiarBuffer();
    return opcion;
}

// ─────────────────────────────────────────────────────────────────────────────
// Menú
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Muestra el menú principal del sistema.
 */
void mostrarMenu() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║   SISTEMA ACADÉMICO UTA - ÁRBOL BST C++      ║\n";
    std::cout << "║      Universidad Técnica de Ambato            ║\n";
    std::cout << "╠══════════════════════════════════════════════╣\n";
    std::cout << "║  1.  Insertar estudiante                     ║\n";
    std::cout << "║  2.  Buscar estudiante por cédula            ║\n";
    std::cout << "║  3.  Eliminar estudiante                     ║\n";
    std::cout << "║  4.  Recorrido Inorden                       ║\n";
    std::cout << "║  5.  Recorrido Preorden                      ║\n";
    std::cout << "║  6.  Recorrido Postorden                     ║\n";
    std::cout << "║  7.  Recorrido por niveles (BFS)             ║\n";
    std::cout << "║  8.  Contar estudiantes                      ║\n";
    std::cout << "║  9.  Calcular altura del árbol               ║\n";
    std::cout << "║ 10.  Mostrar estudiante con mayor nota       ║\n";
    std::cout << "║ 11.  Mostrar estudiante con menor nota       ║\n";
    std::cout << "║ 12.  Mostrar estudiantes aprobados           ║\n";
    std::cout << "║ 13.  Mostrar estudiantes reprobados          ║\n";
    std::cout << "║ 14.  Salir                                   ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n";
    std::cout << "  Seleccione una opción: ";
}

// ─────────────────────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────────────────────

int main() {
    ArbolBST arbol;
    int opcion = 0;

    std::cout << "\n  Bienvenido al Sistema Académico UTA\n";
    std::cout << "  Gestión de Estudiantes con Árbol Binario de Búsqueda\n";

    do {
        mostrarMenu();
        opcion = leerOpcion();

        switch (opcion) {

        // ── 1. Insertar ───────────────────────────────────────────────────
        case 1: {
            std::cout << "\n── Insertar Estudiante ──\n";
            std::string cedula   = leerCedula();
            std::string apellidos = leerString("  Apellidos: ");
            std::string nombres   = leerString("  Nombres  : ");
            float       nota      = leerNota();
            std::string carrera   = leerString("  Carrera  : ");
            std::string nivel     = leerString("  Nivel    : ");

            Estudiante est(cedula, apellidos, nombres, nota, carrera, nivel);
            arbol.insertarEstudiante(est);
            break;
        }

        // ── 2. Buscar ─────────────────────────────────────────────────────
        case 2: {
            std::cout << "\n── Buscar Estudiante ──\n";
            std::string cedula = leerCedula();
            arbol.buscarEstudiante(cedula);
            break;
        }

        // ── 3. Eliminar ───────────────────────────────────────────────────
        case 3: {
            std::cout << "\n── Eliminar Estudiante ──\n";
            std::string cedula = leerCedula();
            arbol.eliminarEstudiante(cedula);
            break;
        }

        // ── 4. Inorden ────────────────────────────────────────────────────
        case 4:
            arbol.recorridoInorden();
            break;

        // ── 5. Preorden ───────────────────────────────────────────────────
        case 5:
            arbol.recorridoPreorden();
            break;

        // ── 6. Postorden ──────────────────────────────────────────────────
        case 6:
            arbol.recorridoPostorden();
            break;

        // ── 7. BFS ────────────────────────────────────────────────────────
        case 7:
            arbol.recorridoPorNiveles();
            break;

        // ── 8. Contar ─────────────────────────────────────────────────────
        case 8:
            std::cout << "\n── Total de estudiantes en el árbol: "
                      << arbol.contarNodos() << " ──\n";
            break;

        // ── 9. Altura ─────────────────────────────────────────────────────
        case 9:
            std::cout << "\n── Altura del árbol: "
                      << arbol.calcularAltura() << " ──\n";
            break;

        // ── 10. Mayor nota ────────────────────────────────────────────────
        case 10:
            arbol.buscarNotaMayor();
            break;

        // ── 11. Menor nota ────────────────────────────────────────────────
        case 11:
            arbol.buscarNotaMenor();
            break;

        // ── 12. Aprobados ─────────────────────────────────────────────────
        case 12:
            arbol.mostrarAprobados();
            break;

        // ── 13. Reprobados ────────────────────────────────────────────────
        case 13:
            arbol.mostrarReprobados();
            break;

        // ── 14. Salir ─────────────────────────────────────────────────────
        case 14:
            std::cout << "\n  Hasta luego. Sistema cerrado correctamente.\n\n";
            break;

        default:
            std::cout << "\n  ⚠ Opción no válida.\n";
        }

    } while (opcion != 14);

    return 0;
}
