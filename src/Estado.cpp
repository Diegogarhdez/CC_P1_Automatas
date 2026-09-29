/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Estado.cpp
 * Descripción: Contiene la implementación de la clase Estado
*/

#include "../includes/Estado.h"

std::vector<Transicion> Estado::obtenerTransicionesPosibles(char simbolo_entrada, 
                                                            char simbolo_pila) const {
  std::vector<Transicion> posibilidades;
  for (const Transicion& t : transiciones_) {
    if (t.esAplicable(simbolo_entrada, simbolo_pila)) {
      posibilidades.push_back(t);
    }
  }
  return posibilidades;
}

