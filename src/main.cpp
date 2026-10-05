/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: main.cpp
 * Descripción: Contiene la función principal del proyecto
*/

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "../includes/LeerFichero.h"

/** @brief función que muestra como se usa el programa */
void usage(std::ostream& salida) {
  salida << "Modo de uso:\n"
         << "  P1_Automata_pila -config <fichero> -trace <y|n> [-in <fichero>]\n"
         << "  -config <fichero>  Configuracion del automata con pila\n"
         << "  -trace <y|n>       Activar o desactivar la traza\n"
         << "  -in <fichero>      Evaluar las cadenas de un fichero, una por linea\n"
         << "  -h                 Mostrar esta ayuda\n"
         << "Sin -in, introduce cadenas por terminal hasta escribir :q o EOF.\n";
}

void evaluarCadena(Automata& automata, const std::string& cadena) {
  const bool aceptada = automata.comprobarCadena(cadena);
  std::cout << "Cadena \"" << cadena << "\": "
            << (aceptada ? "aceptada" : "rechazada") << '\n';
}

/** @brief función principal del proyecto */
int main(int argc, char* argv[]) {
  std::string fichero_configuracion;
  std::string fichero_entradas;
  bool modo_traza = false;
  bool traza_especificada = false;
  bool entradas_especificadas = false;

  for (int indice = 1; indice < argc; ++indice) {
    const std::string opcion = argv[indice];
    if (opcion == "-h" || opcion == "--help") {
      usage(std::cout);
      return 0;
    }

    if (opcion == "-config" || opcion == "-trace" || opcion == "-in") {
      if (indice + 1 >= argc) {
        std::cerr << "Falta el valor para la opcion " << opcion << ".\n";
        usage(std::cerr);
        return 1;
      }

      const std::string valor = argv[++indice];
      if (opcion == "-config") {
        fichero_configuracion = valor;
      } else if (opcion == "-trace") {
        if (valor != "y" && valor != "n") {
          std::cerr << "El valor de -trace debe ser y o n.\n";
          return 1;
        }
        modo_traza = (valor == "y");
        traza_especificada = true;
      } else {
        if (entradas_especificadas) {
          std::cerr << "La opcion -in solo puede aparecer una vez.\n";
          return 1;
        }
        fichero_entradas = valor;
        entradas_especificadas = true;
      }
    } else {
      std::cerr << "Opcion desconocida: " << opcion << '\n';
      usage(std::cerr);
      return 1;
    }
  }

  if (fichero_configuracion.empty() || !traza_especificada) {
    std::cerr << "Debes indicar -config y -trace.\n";
    usage(std::cerr);
    return 1;
  }

  try {
    LeerFichero lector_configuracion(fichero_configuracion);
    Automata automata = lector_configuracion.parsear(modo_traza);

    if (entradas_especificadas) {
      std::ifstream fichero(fichero_entradas);
      if (!fichero.is_open()) {
        std::cerr << "No se pudo abrir el fichero de cadenas: " << fichero_entradas << '\n';
        return 1;
      }

      std::string cadena;
      while (std::getline(fichero, cadena)) {
        if (!cadena.empty() && cadena.back() == '\r') cadena.pop_back();
        evaluarCadena(automata, cadena);
      }
    } else {
      std::cout << "Introduce cadenas; escribe :q para terminar.\n";
      std::string cadena;
      while (std::cout << "> " && std::cin >> cadena) {
        if (cadena == ":q") break;
        evaluarCadena(automata, cadena);
      }
    }
  } catch (const std::exception& error) {
    std::cerr << "Error al cargar la configuracion: " << error.what() << '\n';
    return 1;
  }

  return 0;
}