/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Alfabeto.h
 * Descripción: Contiene la declaración clase Alfabeto
*/

#include <iostream>
#include <set>

#ifndef ALFABETO_H_
#define ALFABETO_H_

class Alfabeto {
 public:
  static const char EPSILON = '.';

  Alfabeto() {}
  Alfabeto(const std::set<char>& alfabeto) {
    alfabeto_ = alfabeto;
  }

  bool pertenece(char c) const {
    return c == EPSILON || alfabeto_.find(c) != alfabeto_.end();
  }

  void insertarSimbolo(char c) {
    alfabeto_.insert(c);
  }

 private:
  std::set<char> alfabeto_;
};

#endif