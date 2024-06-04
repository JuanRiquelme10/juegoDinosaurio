#include "Roca.h"

Roca::Roca(int posicionInicial) {
  x = posicionInicial;
}

void Roca::mover() {
  if (x > 0) {
    x = x - 1;
  } else {
    x = 16; // Si la roca llega al borde izquierdo de la pantalla, vuelve al lado derecho
  }
}

int Roca::obtenerPosicion() {
  return x;
}