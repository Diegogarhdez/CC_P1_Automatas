/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: LeerFichero.h
 * Descripción: Contiene la clase LeerFichero
*/

#ifndef LEERFICHERO_H_
#define LEERFICHERO_H_

#include <string>
#include <fstream>
#include "Automata.h"

class LeerFichero {
 public:
  // El constructor recibe la ruta del fichero (ej. de la opción -config)
  LeerFichero(const std::string& nombre_fichero) : nombre_fichero_(nombre_fichero) {}

  // Método principal que orquesta toda la lectura y construye el autómata
  Automata parsear(bool modo_traza = false);

 private:
  std::string nombre_fichero_;
  // Limpia la línea de espacios iniciales/finales y recorta si hay un '#'
  void procesarLinea(std::string& linea) const;
  // Lee las transiciones y las añade al autómata
  void parsearTransicion(const std::string& linea, Automata& automata) const;
};

#endif