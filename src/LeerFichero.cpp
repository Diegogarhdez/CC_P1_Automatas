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
#include <set>
#include <stdexcept>

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
  std::size_t numero_linea = 0;
  auto leerLineaValida = [&](std::vector<std::string>& campos) {
    while (std::getline(fichero_entrada, linea)) {
      ++numero_linea;
      std::stringstream ss(linea);
      std::string campo;
      campos.clear();
      while (ss >> campo) {
        campos.push_back(campo);
      }
      if (campos.empty() || campos.front().starts_with('#')) continue;
      return true;
    }
    return false;
  };
  auto errorLinea = [&](const std::string& mensaje) {
    throw std::runtime_error("Error en el fichero de configuracion '" +
                             nombre_fichero_ + "', linea " +
                             std::to_string(numero_linea) + ": " + mensaje);
  };
  auto leerDefinicion = [&](const std::string& descripcion,
                            std::vector<std::string>& campos) {
    if (!leerLineaValida(campos)) {
      errorLinea("falta la definicion de " + descripcion);
    }
  };

  // Conjunto de estados
  std::vector<std::string> campos;
  leerDefinicion("estados", campos);
  std::set<std::string> estados;
  for (const std::string& estado : campos) {
    if (!estados.insert(estado).second) {
      errorLinea("el estado '" + estado + "' esta repetido");
    }
    automata_configurado.anadirEstado(estado);
  }

  // Conjunto de simbolos alfabeto entrada
  leerDefinicion("el alfabeto de entrada", campos);
  std::set<char> simbolos_entrada;
  for (const std::string& token : campos) {
    if (token.size() != 1 || token[0] == Alfabeto::EPSILON) {
      errorLinea("simbolo de entrada invalido '" + token +
                 "' (debe ser un caracter; '.' esta reservado para epsilon)");
    }
    if (!simbolos_entrada.insert(token[0]).second) {
      errorLinea("el simbolo de entrada '" + token + "' esta repetido");
    }
    automata_configurado.anadirSimboloEntrada(token[0]);
  }

  // Conjunto de simbolos alfabeto pila
  leerDefinicion("el alfabeto de pila", campos);
  std::set<char> simbolos_pila;
  for (const std::string& token : campos) {
    if (token.size() != 1 || token[0] == Alfabeto::EPSILON) {
      errorLinea("simbolo de pila invalido '" + token +
                 "' (debe ser un caracter; '.' esta reservado para epsilon)");
    }
    if (!simbolos_pila.insert(token[0]).second) {
      errorLinea("el simbolo de pila '" + token + "' esta repetido");
    }
    automata_configurado.anadirSimboloPila(token[0]);
  }

  // Estado inicial
  leerDefinicion("el estado inicial", campos);
  if (campos.size() != 1) {
    errorLinea("el estado inicial debe contener exactamente un estado");
  }
  if (!estados.contains(campos[0])) {
    errorLinea("el estado inicial '" + campos[0] +
               "' no pertenece al conjunto de estados");
  }
  automata_configurado.setEstadoInicial(campos[0]);

  // Simbolo inicial en la pila
  leerDefinicion("el simbolo inicial de pila", campos);
  if (campos.size() != 1 || campos[0].size() != 1) {
    errorLinea("el simbolo inicial de pila debe ser un unico caracter");
  }
  if (!simbolos_pila.contains(campos[0][0])) {
    errorLinea("el simbolo inicial de pila '" + campos[0] +
               "' no pertenece al alfabeto de pila");
  }
  automata_configurado.setSimboloInicialPila(campos[0][0]);

  while (leerLineaValida(campos)) {
    if (campos.size() != 5) {
      errorLinea("una transicion debe tener exactamente cinco campos: "
                 "estado_origen simbolo_entrada simbolo_pila "
                 "estado_destino simbolos_a_insertar");
    }

    const std::string& estado_origen = campos[0];
    const std::string& entrada = campos[1];
    const std::string& cima_pila = campos[2];
    const std::string& estado_destino = campos[3];
    const std::string& inserta_pila = campos[4];

    if (!estados.contains(estado_origen)) {
      errorLinea("el estado de origen '" + estado_origen +
                 "' no pertenece al conjunto de estados");
    }
    if (entrada.size() != 1 ||
        (entrada[0] != Alfabeto::EPSILON &&
         !simbolos_entrada.contains(entrada[0]))) {
      errorLinea("simbolo de entrada '" + entrada +
                 "' no pertenece al alfabeto de entrada ni es epsilon");
    }
    if (cima_pila.size() != 1 || !simbolos_pila.contains(cima_pila[0])) {
      errorLinea("simbolo de pila '" + cima_pila +
                 "' no pertenece al alfabeto de pila");
    }
    if (!estados.contains(estado_destino)) {
      errorLinea("el estado de destino '" + estado_destino +
                 "' no pertenece al conjunto de estados");
    }
    if (inserta_pila != std::string(1, Alfabeto::EPSILON)) {
      for (char simbolo : inserta_pila) {
        if (!simbolos_pila.contains(simbolo)) {
          errorLinea("simbolo '" + std::string(1, simbolo) +
                     "' a insertar no pertenece al alfabeto de pila");
        }
      }
    }

    Transicion t(entrada[0], cima_pila[0], estado_destino, inserta_pila);
    automata_configurado.anadirTransicion(estado_origen, t);
  }

  return automata_configurado;
}