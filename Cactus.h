#ifndef Cactus_h
#define Cactus_h
#include "Arduino.h"

class Cactus {
  private:    
    int x;         

  public:
    Cactus(int posicionInicial);
    void mover();
    int obtenerPosicion();    
};

#endif

