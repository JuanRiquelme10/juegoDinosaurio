#include "Cactus.h"

Cactus::Cactus(int posicionInicial) {  
  x = posicionInicial;  
}

void Cactus::mover() {   
  if(x > 0) {
    x = x - 1;
  }
  else {
    x = 16;
  }  
}

int Cactus::obtenerPosicion() {
  return x;
}

