/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Automata.h
 * Descripción: Contiene la clase Automata
*/

#ifndef AUTOMATA_H_
#define AUTOMATA_H_

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

#include "Alfabeto.h"
#include "Estado.h"
#include "Transicion.h"

class Automata {
 public:
  Automata(const bool& modo_traza = false) : modo_traza_(modo_traza) {}

  void anadirEstado(const std::string& nombre);
  void anadirSimboloEntrada(const char& simbolo);
  void anadirSimboloPila(const char& simbolo);
  void setEstadoInicial(const std::string& estado);
  void setSimboloInicialPila(const char& simbolo);
  void anadirTransicion(const std::string& estado_origen, const Transicion& t);
  bool comprobarCadena(const std::string& cadena);

 private:
  Alfabeto alfabeto_entrada_;
  Alfabeto alfabeto_pila_;
  std::map<std::string, Estado> estados_; 
  
  std::string estado_inicial_ = " ";
  char simbolo_inicial_pila_ = ' ';
  
  bool modo_traza_;
  bool evaluarRecursivo(const std::string& estado_actual, 
                        const std::string& cadena_restante, 
                        std::string pila_actual);
  void imprimirTraza(const std::string& estado, 
                     const std::string& cadena, 
                     const std::string& pila,
                     const std::vector<Transicion>& posibles_transiciones) const;
};

#endif