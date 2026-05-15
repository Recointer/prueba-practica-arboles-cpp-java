/**
 * @file NodoBST.h
 * @brief Definición del nodo del Árbol Binario de Búsqueda
 *
 * Cada nodo almacena un Estudiante y punteros al hijo
 * izquierdo y derecho del árbol.
 *
 * Universidad Técnica de Ambato - Sistema Académico BST
 */

#ifndef NODOBST_H
#define NODOBST_H

#include "Estudiante.h"

/**
 * @struct NodoBST
 * @brief Nodo del árbol binario de búsqueda.
 *
 * La clave de comparación es el campo `cedula` del Estudiante.
 */
struct NodoBST {
    Estudiante  dato;       ///< Datos del estudiante almacenado en el nodo
    NodoBST*    izquierdo;  ///< Puntero al hijo izquierdo (cédula menor)
    NodoBST*    derecho;    ///< Puntero al hijo derecho (cédula mayor)

    /**
     * @brief Constructor: inicializa con un estudiante y punteros nulos.
     * @param est Estudiante a almacenar en el nodo.
     */
    explicit NodoBST(const Estudiante& est)
        : dato(est), izquierdo(nullptr), derecho(nullptr) {}
};

#endif // NODOBST_H
