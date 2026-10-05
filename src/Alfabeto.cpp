/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Alfabeto.cpp
 * Descripción: Contiene la implementación clase Alfabeto
*/

#include "../includes/Alfabeto.h"

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  os << "{ ";
  for (const auto& a : alfabeto.getAlfabeto()) {
    os << a << " ";
  }
  os << "}";
  return os;
}