/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Automata.cpp
 * Descripción: Contiene la implementación de la clase Automata
*/

#include "../includes/Automata.h"

void Automata::anadirEstado(const std::string& nombre) {
  estados_.emplace(nombre, Estado(nombre));
}

void Automata::anadirSimboloEntrada(const char& simbolo) {
  if (!alfabeto_entrada_.pertenece(simbolo)) {
    alfabeto_entrada_.insertarSimbolo(simbolo);
  }
}

void Automata::anadirSimboloPila(const char& simbolo) {
  if (!alfabeto_pila_.pertenece(simbolo)) {
    alfabeto_pila_.insertarSimbolo(simbolo);
  }
}

void Automata::setEstadoInicial(const std::string& estado) {
  if (estado_inicial_ == " ") {
    estado_inicial_ = estado;
  }
}

void Automata::setSimboloInicialPila(const char& simbolo) {
  if (simbolo_inicial_pila_ == ' ') {
    simbolo_inicial_pila_ = simbolo;
  }
}

void Automata::anadirTransicion(const std::string& estado_origen, const Transicion& t) {
  estados_[estado_origen].anadirTransicion(t);
}

bool Automata::comprobarCadena(const std::string& cadena) {
  Pila pila_inicial{simbolo_inicial_pila_};
  return evaluarRecursivo(estado_inicial_, cadena, pila_inicial);
}

bool Automata::evaluarRecursivo(const std::string& estado_actual, 
                                const std::string& cadena_restante, 
                                Pila pila_actual) {

  if (pila_actual.vacia()) {
    if (modo_traza_) imprimirTraza(estado_actual, cadena_restante, pila_actual, {});
    return cadena_restante.empty();
  }

  char simbolo_entrada = cadena_restante.empty() ? Alfabeto::EPSILON : cadena_restante[0];
  char cima_pila = pila_actual.cima();
  
  std::vector<Transicion> posibilidades = estados_[estado_actual].obtenerTransicionesPosibles(simbolo_entrada, cima_pila);
  if (modo_traza_) imprimirTraza(estado_actual, cadena_restante, pila_actual, posibilidades);

  for (Transicion t : posibilidades) {

    std::string nueva_cadena = cadena_restante;
    if (t.getSimboloEntrada() != Alfabeto::EPSILON && !nueva_cadena.empty()) {
      nueva_cadena.erase(0, 1);
    }

    Pila nueva_pila = pila_actual;
    nueva_pila.desapilar();

    if (t.getSimbolosAInsertar() != std::string{Alfabeto::EPSILON}) {
      nueva_pila.apilar(t.getSimbolosAInsertar());
    }

    if (evaluarRecursivo(t.getEstadoSiguiente(), nueva_cadena, nueva_pila)) {
      return true;
    }
  }
  
  return false;
}

void Automata::imprimirTraza(const std::string& estado, 
                   const std::string& cadena, 
         const Pila& pila,
                   const std::vector<Transicion>& posibles_transiciones) const {
  std::cout << estado << " | "
            << (cadena.empty() ? std::string(1, Alfabeto::EPSILON) : cadena) << " | "
       << (pila.vacia() ? "-" : pila.comoCadena()) << " | ";

  if (posibles_transiciones.empty()) {
    std::cout << "ninguna";
  } else {
    for (std::size_t indice = 0; indice < posibles_transiciones.size(); ++indice) {
      const Transicion& transicion = posibles_transiciones[indice];
      if (indice > 0) std::cout << ", ";
      std::cout << "(" << transicion.getSimboloEntrada() << ", "
                << transicion.getSimboloPila() << ", "
                << transicion.getEstadoSiguiente() << ")";
    }
  }
  std::cout << '\n';
}