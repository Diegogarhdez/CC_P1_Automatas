/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: LeerFichero.cpp
 * Descripción: Contiene la implementación de LeerFichero.cpp
*/

#include "../includes/LeerFichero.h"
#include "../includes/Transicion.h"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>

Automata LeerFichero::parsear(bool modo_traza) {
  const std::filesystem::path ruta_fichero(nombre_fichero_);
  std::ifstream fichero_entrada(ruta_fichero);
  if (!fichero_entrada.is_open() && ruta_fichero.is_relative() &&
      ruta_fichero.parent_path().empty()) {
    fichero_entrada.clear();
    fichero_entrada.open(std::filesystem::path("../tests") / ruta_fichero);
    if (!fichero_entrada.is_open()) {
      fichero_entrada.clear();
      fichero_entrada.open(std::filesystem::path("tests") / ruta_fichero);
    }
  }
  if (!fichero_entrada.is_open()) {
    throw std::runtime_error("Error al abrir el fichero\n");
  }

  Automata automata_configurado(modo_traza);
  std::string linea;
  auto leerLineaValida = [&]() {
    while (std::getline(fichero_entrada, linea)) {
      if (linea.empty()) continue;
      if (linea.starts_with('#')) continue; 
      return true; // Encontramos una línea con datos útiles
    }
    return false;
  };

  // Conjunto de estados
  if (leerLineaValida()) {
    std::stringstream ss(linea);
    std::string estado;
    while (ss >> estado) {
      automata_configurado.anadirEstado(estado);
    }
  }

  // Conjunto de simbolos alfabeto entrada
  if (leerLineaValida()) {
    std::stringstream ss(linea);
    char simbolo;
    while (ss >> simbolo) {
      automata_configurado.anadirSimboloEntrada(simbolo);
    }
  }

  // Conjunto de simbolos alfabeto pila
  if (leerLineaValida()) {
    std::stringstream ss(linea);
    char simbolo;
    while (ss >> simbolo) {
      automata_configurado.anadirSimboloPila(simbolo);
    }
  }

  // Estado inicial
  if (leerLineaValida()) {
    std::stringstream ss(linea);
    std::string estado_inicial;
    ss >> estado_inicial;
    automata_configurado.setEstadoInicial(estado_inicial);
  }

  // Simbolo inicial en la pila
  if (leerLineaValida()) {
    std::stringstream ss(linea);
    char simbolo_pila;
    ss >> simbolo_pila;
    automata_configurado.setSimboloInicialPila(simbolo_pila);
  }

  while (leerLineaValida()) {
    std::stringstream ss(linea);
    std::string estado_origen, estado_destino, inserta_pila;
    char sim_entrada, sim_extrae_pila;
    if (ss >> estado_origen >> sim_entrada >> sim_extrae_pila >> estado_destino >> inserta_pila) {
      Transicion t(sim_entrada, sim_extrae_pila, estado_destino, inserta_pila);
      automata_configurado.anadirTransicion(estado_origen, t);
    }
  }

  return automata_configurado;
}