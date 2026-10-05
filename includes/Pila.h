#ifndef PILA_H_
#define PILA_H_

#include <stdexcept>
#include <string>
#include <vector>

class Pila {
 public:
  Pila() = default;
  explicit Pila(char simbolo_inicial) { apilar(simbolo_inicial); }

  bool vacia() const { return elementos_.empty(); }

  char cima() const {
    if (vacia()) throw std::out_of_range("No se puede consultar una pila vacia");
    return elementos_.back();
  }

  void apilar(char simbolo) { elementos_.push_back(simbolo); }

  void apilar(const std::string& simbolos) {
    for (auto iterador = simbolos.rbegin(); iterador != simbolos.rend(); ++iterador) {
      elementos_.push_back(*iterador);
    }
  }

  void desapilar() {
    if (vacia()) throw std::out_of_range("No se puede desapilar una pila vacia");
    elementos_.pop_back();
  }

  std::string comoCadena() const {
    std::string representacion;
    for (auto iterador = elementos_.rbegin(); iterador != elementos_.rend(); ++iterador) {
      representacion.push_back(*iterador);
    }
    return representacion;
  }

 private:
  std::vector<char> elementos_;
};

#endif