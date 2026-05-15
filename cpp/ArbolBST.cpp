/**
 * @file ArbolBST.cpp
 * @brief Implementación de la clase ArbolBST
 *
 * Árbol Binario de Búsqueda ordenado por cédula del estudiante.
 * Implementa todas las funciones obligatorias del sistema académico UTA.
 *
 * Universidad Técnica de Ambato - Sistema Académico BST
 */

#include "ArbolBST.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <climits>

// ─────────────────────────────────────────────────────────────────────────────
// Utilidad: imprime los datos de un estudiante con formato
// ─────────────────────────────────────────────────────────────────────────────
static void imprimirEstudiante(const Estudiante& e) {
    std::cout << "┌─────────────────────────────────────────┐\n";
    std::cout << "│ Cédula   : " << std::left << std::setw(29) << e.cedula    << "│\n";
    std::cout << "│ Apellidos: " << std::setw(29) << e.apellidos              << "│\n";
    std::cout << "│ Nombres  : " << std::setw(29) << e.nombres                << "│\n";
    std::cout << "│ Nota     : " << std::setw(29) << std::fixed << std::setprecision(2) << e.notaFinal << "│\n";
    std::cout << "│ Carrera  : " << std::setw(29) << e.carrera                << "│\n";
    std::cout << "│ Nivel    : " << std::setw(29) << e.nivel                  << "│\n";
    std::cout << "│ Estado   : " << std::setw(29)
              << (e.notaFinal >= 7.0f ? "APROBADO" : "REPROBADO")             << "│\n";
    std::cout << "└─────────────────────────────────────────┘\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// Constructor / Destructor
// ─────────────────────────────────────────────────────────────────────────────

ArbolBST::ArbolBST() : raiz(nullptr) {}

ArbolBST::~ArbolBST() {
    destruir(raiz);
}

// Libera memoria post-orden para evitar accesos a punteros colgantes
void ArbolBST::destruir(NodoBST* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->izquierdo);
    destruir(nodo->derecho);
    delete nodo;
}

// ─────────────────────────────────────────────────────────────────────────────
// INSERTAR
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Auxiliar recursiva de inserción.
 *
 * Compara cédulas lexicográficamente:
 *   - Menor  → subárbol izquierdo
 *   - Mayor  → subárbol derecho
 *   - Igual  → cédula duplicada, no se inserta
 *
 * @param nodo      Nodo actual (puede ser nullptr).
 * @param est       Estudiante a insertar.
 * @param insertado Flag que se pone en true si se insertó.
 * @return Puntero al nodo (nuevo o existente).
 */
NodoBST* ArbolBST::insertar(NodoBST* nodo, const Estudiante& est, bool& insertado) {
    // Caso base: posición libre, crear nuevo nodo
    if (nodo == nullptr) {
        insertado = true;
        return new NodoBST(est);
    }

    if (est.cedula < nodo->dato.cedula) {
        // Cédula menor → insertar en subárbol izquierdo
        nodo->izquierdo = insertar(nodo->izquierdo, est, insertado);
    } else if (est.cedula > nodo->dato.cedula) {
        // Cédula mayor → insertar en subárbol derecho
        nodo->derecho = insertar(nodo->derecho, est, insertado);
    } else {
        // Cédula duplicada → rechazar
        insertado = false;
    }

    return nodo;
}

void ArbolBST::insertarEstudiante(const Estudiante& est) {
    bool insertado = false;
    raiz = insertar(raiz, est, insertado);

    if (insertado) {
        std::cout << "\n✔ Estudiante con cédula " << est.cedula
                  << " insertado correctamente.\n";
    } else {
        std::cout << "\n✘ Error: Ya existe un estudiante con cédula "
                  << est.cedula << ". No se puede duplicar.\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// BUSCAR
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Auxiliar recursiva de búsqueda por cédula.
 *
 * @param nodo    Nodo actual.
 * @param cedula  Cédula a buscar.
 * @return Puntero al nodo encontrado o nullptr.
 */
NodoBST* ArbolBST::buscar(NodoBST* nodo, const std::string& cedula) const {
    if (nodo == nullptr)        return nullptr;  // No encontrado
    if (cedula == nodo->dato.cedula) return nodo; // Encontrado
    if (cedula < nodo->dato.cedula)
        return buscar(nodo->izquierdo, cedula);   // Buscar izquierda
    return buscar(nodo->derecho, cedula);          // Buscar derecha
}

void ArbolBST::buscarEstudiante(const std::string& cedula) const {
    NodoBST* resultado = buscar(raiz, cedula);
    if (resultado != nullptr) {
        std::cout << "\n── Estudiante encontrado ──\n";
        imprimirEstudiante(resultado->dato);
    } else {
        std::cout << "\n✘ Estudiante con cédula " << cedula << " no encontrado.\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// ELIMINAR
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Retorna el nodo con el valor mínimo del subárbol (más a la izquierda).
 */
NodoBST* ArbolBST::minimo(NodoBST* nodo) const {
    while (nodo->izquierdo != nullptr)
        nodo = nodo->izquierdo;
    return nodo;
}

/**
 * @brief Auxiliar recursiva de eliminación.
 *
 * Casos:
 *  1. Sin hijos        → eliminar directamente.
 *  2. Un hijo          → reemplazar con el hijo existente.
 *  3. Dos hijos        → reemplazar con el sucesor inorden
 *                        (mínimo del subárbol derecho) y eliminar ese sucesor.
 *
 * @param nodo      Nodo actual.
 * @param cedula    Cédula del estudiante a eliminar.
 * @param eliminado Flag que indica si se realizó la eliminación.
 * @return Nueva raíz del subárbol.
 */
NodoBST* ArbolBST::eliminar(NodoBST* nodo, const std::string& cedula, bool& eliminado) {
    if (nodo == nullptr) {
        eliminado = false;
        return nullptr;
    }

    if (cedula < nodo->dato.cedula) {
        // Buscar en subárbol izquierdo
        nodo->izquierdo = eliminar(nodo->izquierdo, cedula, eliminado);
    } else if (cedula > nodo->dato.cedula) {
        // Buscar en subárbol derecho
        nodo->derecho = eliminar(nodo->derecho, cedula, eliminado);
    } else {
        // Nodo encontrado — aplicar uno de los tres casos
        eliminado = true;

        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            // Caso 1: hoja
            delete nodo;
            return nullptr;
        } else if (nodo->izquierdo == nullptr) {
            // Caso 2: solo hijo derecho
            NodoBST* temp = nodo->derecho;
            delete nodo;
            return temp;
        } else if (nodo->derecho == nullptr) {
            // Caso 2: solo hijo izquierdo
            NodoBST* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        } else {
            // Caso 3: dos hijos → sucesor inorden
            NodoBST* sucesor = minimo(nodo->derecho);
            nodo->dato = sucesor->dato;  // Copiar datos del sucesor
            // Eliminar el sucesor del subárbol derecho
            bool dummy = false;
            nodo->derecho = eliminar(nodo->derecho, sucesor->dato.cedula, dummy);
        }
    }

    return nodo;
}

void ArbolBST::eliminarEstudiante(const std::string& cedula) {
    bool eliminado = false;
    raiz = eliminar(raiz, cedula, eliminado);

    if (eliminado) {
        std::cout << "\n✔ Estudiante con cédula " << cedula
                  << " eliminado correctamente.\n";
    } else {
        std::cout << "\n✘ Estudiante con cédula " << cedula << " no encontrado.\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// RECORRIDOS
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Inorden: izquierdo → raíz → derecho.
 * Produce estudiantes ordenados por cédula de menor a mayor.
 */
void ArbolBST::inorden(NodoBST* nodo) const {
    if (nodo == nullptr) return;
    inorden(nodo->izquierdo);
    imprimirEstudiante(nodo->dato);
    inorden(nodo->derecho);
}

void ArbolBST::recorridoInorden() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    std::cout << "\n══ Recorrido INORDEN (cédulas ascendente) ══\n";
    inorden(raiz);
}

// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Preorden: raíz → izquierdo → derecho.
 */
void ArbolBST::preorden(NodoBST* nodo) const {
    if (nodo == nullptr) return;
    imprimirEstudiante(nodo->dato);
    preorden(nodo->izquierdo);
    preorden(nodo->derecho);
}

void ArbolBST::recorridoPreorden() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    std::cout << "\n══ Recorrido PREORDEN ══\n";
    preorden(raiz);
}

// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Postorden: izquierdo → derecho → raíz.
 */
void ArbolBST::postorden(NodoBST* nodo) const {
    if (nodo == nullptr) return;
    postorden(nodo->izquierdo);
    postorden(nodo->derecho);
    imprimirEstudiante(nodo->dato);
}

void ArbolBST::recorridoPostorden() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    std::cout << "\n══ Recorrido POSTORDEN ══\n";
    postorden(raiz);
}

// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief BFS usando std::queue.
 *
 * Recorre el árbol nivel por nivel, de izquierda a derecha.
 * Muestra el número de nivel antes de cada grupo de nodos.
 */
void ArbolBST::recorridoPorNiveles() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }

    std::cout << "\n══ Recorrido por NIVELES (BFS) ══\n";

    std::queue<NodoBST*> cola;  // Cola de punteros a nodos
    cola.push(raiz);
    int nivel = 0;

    while (!cola.empty()) {
        int tamanoNivel = (int)cola.size();  // Nodos en este nivel
        std::cout << "\n── Nivel " << nivel << " ──\n";

        // Procesar todos los nodos del nivel actual
        for (int i = 0; i < tamanoNivel; ++i) {
            NodoBST* actual = cola.front();
            cola.pop();
            imprimirEstudiante(actual->dato);

            // Encolar hijos para el siguiente nivel
            if (actual->izquierdo != nullptr) cola.push(actual->izquierdo);
            if (actual->derecho   != nullptr) cola.push(actual->derecho);
        }

        ++nivel;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// CONTAR NODOS
// ─────────────────────────────────────────────────────────────────────────────

int ArbolBST::contarNodos(NodoBST* nodo) const {
    if (nodo == nullptr) return 0;
    // Total = 1 (nodo actual) + nodos izquierda + nodos derecha
    return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
}

int ArbolBST::contarNodos() const {
    return contarNodos(raiz);
}

// ─────────────────────────────────────────────────────────────────────────────
// CALCULAR ALTURA
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Calcula altura del árbol recursivamente.
 * Altura = número de aristas en el camino más largo desde la raíz hasta una hoja.
 * Árbol vacío → -1.
 * Árbol con solo raíz → 0.
 */
int ArbolBST::calcularAltura(NodoBST* nodo) const {
    if (nodo == nullptr) return -1;
    int altIzq = calcularAltura(nodo->izquierdo);
    int altDer = calcularAltura(nodo->derecho);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

int ArbolBST::calcularAltura() const {
    return calcularAltura(raiz);
}

// ─────────────────────────────────────────────────────────────────────────────
// MAYOR / MENOR NOTA
// ─────────────────────────────────────────────────────────────────────────────

void ArbolBST::buscarNotaMayor(NodoBST* nodo, NodoBST*& mayor) const {
    if (nodo == nullptr) return;

    // Actualizar si este nodo tiene mayor nota que el actual máximo
    if (mayor == nullptr || nodo->dato.notaFinal > mayor->dato.notaFinal)
        mayor = nodo;

    buscarNotaMayor(nodo->izquierdo, mayor);
    buscarNotaMayor(nodo->derecho, mayor);
}

void ArbolBST::buscarNotaMayor() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    NodoBST* mayor = nullptr;
    buscarNotaMayor(raiz, mayor);
    std::cout << "\n══ Estudiante con MAYOR nota ══\n";
    imprimirEstudiante(mayor->dato);
}

// ─────────────────────────────────────────────────────────────────────────────

void ArbolBST::buscarNotaMenor(NodoBST* nodo, NodoBST*& menor) const {
    if (nodo == nullptr) return;

    // Actualizar si este nodo tiene menor nota que el actual mínimo
    if (menor == nullptr || nodo->dato.notaFinal < menor->dato.notaFinal)
        menor = nodo;

    buscarNotaMenor(nodo->izquierdo, menor);
    buscarNotaMenor(nodo->derecho, menor);
}

void ArbolBST::buscarNotaMenor() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    NodoBST* menor = nullptr;
    buscarNotaMenor(raiz, menor);
    std::cout << "\n══ Estudiante con MENOR nota ══\n";
    imprimirEstudiante(menor->dato);
}

// ─────────────────────────────────────────────────────────────────────────────
// APROBADOS / REPROBADOS
// ─────────────────────────────────────────────────────────────────────────────

void ArbolBST::mostrarAprobados(NodoBST* nodo, int& cont) const {
    if (nodo == nullptr) return;
    mostrarAprobados(nodo->izquierdo, cont);
    if (nodo->dato.notaFinal >= 7.0f) {
        imprimirEstudiante(nodo->dato);
        ++cont;
    }
    mostrarAprobados(nodo->derecho, cont);
}

void ArbolBST::mostrarAprobados() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    int cont = 0;
    std::cout << "\n══ Estudiantes APROBADOS (nota >= 7.0) ══\n";
    mostrarAprobados(raiz, cont);
    std::cout << "Total aprobados: " << cont << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────

void ArbolBST::mostrarReprobados(NodoBST* nodo, int& cont) const {
    if (nodo == nullptr) return;
    mostrarReprobados(nodo->izquierdo, cont);
    if (nodo->dato.notaFinal < 7.0f) {
        imprimirEstudiante(nodo->dato);
        ++cont;
    }
    mostrarReprobados(nodo->derecho, cont);
}

void ArbolBST::mostrarReprobados() const {
    if (estaVacio()) {
        std::cout << "\n⚠ El árbol está vacío.\n";
        return;
    }
    int cont = 0;
    std::cout << "\n══ Estudiantes REPROBADOS (nota < 7.0) ══\n";
    mostrarReprobados(raiz, cont);
    std::cout << "Total reprobados: " << cont << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// UTILIDAD
// ─────────────────────────────────────────────────────────────────────────────

bool ArbolBST::estaVacio() const {
    return raiz == nullptr;
}
