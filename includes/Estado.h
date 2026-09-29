/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Estado.h
 * Descripción: Contiene la clase Estado
*/

#ifndef ESTADO_H_
#define ESTADO_H_

#include <string>
#include <vector>
#include "Transicion.h"

class Estado {
 public:
  Estado() {}

  // Constructor con nombre
  Estado(const std::string& nombre) : nombre_(nombre) {}

  // Método para añadir una transición saliente a este estado
  void anadirTransicion(const Transicion& transicion) {
    transiciones_.push_back(transicion);
  }

  // Método que devuelve todas las transiciones posibles desde este estado
  std::vector<Transicion> obtenerTransicionesPosibles(char simbolo_entrada, char simbolo_pila) const;
  std::string getNombre() const { return nombre_; }
  const std::vector<Transicion>& getTransiciones() const { return transiciones_; }

 private:
  std::string nombre_;
  std::vector<Transicion> transiciones_;
};

#endif