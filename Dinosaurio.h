#ifndef Dinosaurio_h
#define Dinosaurio_h
#include "Arduino.h"

class Dinosaurio {
  private:
    int estado;
    int x, y;
    
    

  public:
    Dinosaurio();
    int obtenerEstado();
    void caminar();
    void saltar();   
    int obtenerPosicion(); 
};

#endif