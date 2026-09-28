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

/** @brief función que muestra como se usa el programa */
void usage() {
  std::cout << "Modo de uso:\n"
            << "./P1_Automata_pila -config <nombre fichero> -trace [y|n]\n"
            << "[-in <nombre_fichero>] leer cadenas por fichero\n"
            << "[-h] mostrar este texto\n";
}

/** @brief función principal del proyecto */
int main(int argc, char* argv[]) {
  if (argc < 3) {
    usage();
    return 1;
  }

  return 0;
}