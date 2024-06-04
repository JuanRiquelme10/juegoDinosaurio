#ifndef Roca_h
#define Roca_h

#include "Arduino.h"

class Roca {
  private:
    int x; // Posición en el eje x

  public:
    Roca(int posicionInicial);
    void mover();
    int obtenerPosicion();
};

#endif