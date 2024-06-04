#include "Dinosaurio.h"

Dinosaurio::Dinosaurio() {
  estado = 0;  
  y = 0;    
}

void Dinosaurio::caminar() {    
    y = 0;
    if(estado == 1) {
      estado = 2;
    } 
    else {
      estado = 1;
    } 
}

void Dinosaurio::saltar() {
  y = 1;
  estado = 3;
}

int Dinosaurio::obtenerEstado() {
  return estado;
}

int Dinosaurio::obtenerPosicion() {
  return y;
}
