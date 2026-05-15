/**
 * @file Estudiante.h
 * @brief Definición del struct Estudiante para el sistema académico UTA
 *
 * Contiene los datos de cada estudiante:
 * cédula, apellidos, nombres, nota final, carrera y nivel.
 *
 * Universidad Técnica de Ambato - Sistema Académico BST
 */

#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

/**
 * @struct Estudiante
 * @brief Representa los datos académicos de un estudiante.
 */
struct Estudiante {
    std::string cedula;     ///< Cédula de identidad (10 dígitos) — clave del BST
    std::string apellidos;  ///< Apellidos del estudiante
    std::string nombres;    ///< Nombres del estudiante
    float       notaFinal;  ///< Nota final en escala 0.0 a 10.0
    std::string carrera;    ///< Carrera universitaria
    std::string nivel;      ///< Nivel o semestre cursado

    /**
     * @brief Constructor por defecto.
     */
    Estudiante()
        : cedula(""), apellidos(""), nombres(""),
          notaFinal(0.0f), carrera(""), nivel("") {}

    /**
     * @brief Constructor con todos los campos.
     */
    Estudiante(const std::string& ced,
               const std::string& ape,
               const std::string& nom,
               float              nota,
               const std::string& car,
               const std::string& niv)
        : cedula(ced), apellidos(ape), nombres(nom),
          notaFinal(nota), carrera(car), nivel(niv) {}
};

#endif // ESTUDIANTE_H
