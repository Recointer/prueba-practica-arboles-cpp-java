/**
 * @file ArbolBST.h
 * @brief Declaración de la clase ArbolBST (Árbol Binario de Búsqueda)
 *
 * Contiene todas las funciones obligatorias del sistema académico:
 * insertar, buscar, eliminar, recorridos, estadísticas y filtros.
 *
 * Universidad Técnica de Ambato - Sistema Académico BST
 */

#ifndef ARBÓLBST_H
#define ARBÓLBST_H

#include "NodoBST.h"
#include <queue>

/**
 * @class ArbolBST
 * @brief Árbol Binario de Búsqueda de estudiantes, ordenado por cédula.
 */
class ArbolBST {
private:
    NodoBST* raiz;  ///< Puntero a la raíz del árbol

    // ── Auxiliares privadas (recursivas) ──────────────────────────────────

    /** Inserta un estudiante recursivamente. Retorna nuevo nodo/subárbol. */
    NodoBST* insertar(NodoBST* nodo, const Estudiante& est, bool& insertado);

    /** Busca por cédula; retorna puntero al nodo o nullptr. */
    NodoBST* buscar(NodoBST* nodo, const std::string& cedula) const;

    /** Elimina el nodo con la cédula dada; retorna nueva raíz del subárbol. */
    NodoBST* eliminar(NodoBST* nodo, const std::string& cedula, bool& eliminado);

    /** Retorna el nodo con el valor mínimo (más a la izquierda). */
    NodoBST* minimo(NodoBST* nodo) const;

    /** Recorrido inorden (izq → raíz → der). */
    void inorden(NodoBST* nodo) const;

    /** Recorrido preorden (raíz → izq → der). */
    void preorden(NodoBST* nodo) const;

    /** Recorrido postorden (izq → der → raíz). */
    void postorden(NodoBST* nodo) const;

    /** Cuenta nodos recursivamente. */
    int contarNodos(NodoBST* nodo) const;

    /** Calcula altura del árbol recursivamente. */
    int calcularAltura(NodoBST* nodo) const;

    /** Busca nodo con mayor nota final. */
    void buscarNotaMayor(NodoBST* nodo, NodoBST*& mayor) const;

    /** Busca nodo con menor nota final. */
    void buscarNotaMenor(NodoBST* nodo, NodoBST*& menor) const;

    /** Muestra aprobados (nota >= 7.0) recursivamente. */
    void mostrarAprobados(NodoBST* nodo, int& cont) const;

    /** Muestra reprobados (nota < 7.0) recursivamente. */
    void mostrarReprobados(NodoBST* nodo, int& cont) const;

    /** Libera toda la memoria del árbol. */
    void destruir(NodoBST* nodo);

public:
    // ── Constructor / Destructor ──────────────────────────────────────────

    /** Inicializa árbol vacío. */
    ArbolBST();

    /** Destructor: libera toda la memoria. */
    ~ArbolBST();

    // ── Interfaz pública ─────────────────────────────────────────────────

    /** Inserta un estudiante en el árbol. */
    void insertarEstudiante(const Estudiante& est);

    /** Busca y muestra un estudiante por cédula. */
    void buscarEstudiante(const std::string& cedula) const;

    /** Elimina un estudiante por cédula. */
    void eliminarEstudiante(const std::string& cedula);

    /** Recorrido inorden: muestra estudiantes en orden de cédula. */
    void recorridoInorden() const;

    /** Recorrido preorden. */
    void recorridoPreorden() const;

    /** Recorrido postorden. */
    void recorridoPostorden() const;

    /** Recorrido por niveles BFS usando std::queue. */
    void recorridoPorNiveles() const;

    /** Retorna cantidad total de estudiantes en el árbol. */
    int contarNodos() const;

    /** Retorna la altura del árbol (-1 si vacío). */
    int calcularAltura() const;

    /** Muestra el estudiante con la mayor nota final. */
    void buscarNotaMayor() const;

    /** Muestra el estudiante con la menor nota final. */
    void buscarNotaMenor() const;

    /** Muestra todos los estudiantes aprobados (nota >= 7.0). */
    void mostrarAprobados() const;

    /** Muestra todos los estudiantes reprobados (nota < 7.0). */
    void mostrarReprobados() const;

    /** Retorna true si el árbol está vacío. */
    bool estaVacio() const;
};

#endif // ARBÓLBST_H
