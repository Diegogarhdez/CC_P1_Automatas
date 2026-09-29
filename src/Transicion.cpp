/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Transicion.cpp
 * Descripción: Contiene la definición de los metodos de la clase Transicion
*/

#include "../includes/Transicion.h"
#include "../includes/Alfabeto.h"

bool Transicion::esAplicable(char entrada_actual, char cima_pila) const {
  // Coincide si la cima de la pila es la que pide la transición
  bool coincide_pila = (simbolo_pila_ == cima_pila);
  // Coincide si leemos el carácter exacto O si esta transición es una transición épsilon (.)
  bool coincide_entrada = (simbolo_entrada_ == entrada_actual || simbolo_entrada_ == Alfabeto::EPSILON); 
  return coincide_pila && coincide_entrada;
}