/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Transicion.h
 * Descripción: Contiene la clase Transicion
*/

#include <iostream>

#ifndef TRANSICION_H_
#define TRANSICION_H_

class Transicion {
 public:
  Transicion() {}
  Transicion(char simbolo_entrada, char simbolo_pila, std::string estado_siguiente, std::string simbolos_a_insertar)
      : simbolo_entrada_(simbolo_entrada), 
        simbolo_pila_(simbolo_pila), 
        estado_siguiente_(estado_siguiente), 
        simbolos_a_insertar_(simbolos_a_insertar) {}

  bool esAplicable(char entrada_actual, char cima_pila) const;

  // Getters para que el autómata pueda evaluar la transición
  char getSimboloEntrada() const { return simbolo_entrada_; }
  char getSimboloPila() const { return simbolo_pila_; }
  std::string getEstadoSiguiente() const { return estado_siguiente_; }
  std::string getSimbolosAInsertar() const { return simbolos_a_insertar_; }

 private:
  char simbolo_entrada_;
  char simbolo_pila_;
  std::string estado_siguiente_;
  std::string simbolos_a_insertar_;
};

std::ostream& operator<<(const Transicion& trans, std::ostream& os);

#endif