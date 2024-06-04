#include <LiquidCrystal.h>
#include "Dinosaurio.h"
#include "Cactus.h"
#include "Roca.h"

LiquidCrystal lcd(22, 23, 5, 18, 19, 21);
Dinosaurio dino;
Cactus ca ctus(16);
Roca roca(25);

byte dinoReposo[8] = {
  B00000,
  B00000,
  B00111,
  B00101,
  B10111,
  B10100,
  B01101,
  B01100
};
byte dinoCamina1[8] = {      
  B00000,
  B00111,
  B00101,
  B10111,
  B10100,
  B01110,
  B01100,
  B00010
};  
byte dinoCamina2[8] = {
  B00000,
  B00111,
  B00101,
  B10111,
  B10100,
  B01110,
  B01100,
  B10000
};
byte dinoSalta[8] = {      
  B00111,
  B00101,
  B10111,
  B10100,
  B01101,
  B01100,
  B10000,
  B00000
};
byte cactus1[8] = {      
  B00000,
  B00000,
  B00001,
  B10101,
  B01101,
  B00110,
  B00100,
  B00100
};
byte roca1[8] = {
  B00000,
  B00011,
  B00111,
  B01110,
  B11100,
  B11000,
  B10000,
  B00000
};

struct Button {
  const uint8_t PIN;
  bool pressed;
  unsigned long lastPressed;
};

Button button1 = {4, false, 0};
const int buzzerPin = 13;  // Pin del buzzer

int velocidad = 200;
int puntuacion = 0; // Variable de puntuación

void IRAM_ATTR isr() {  
  unsigned long currentMillis = millis();
  if (currentMillis - button1.lastPressed > 200) { // Debouncing del botón
    button1.pressed = true;  
    button1.lastPressed = currentMillis;
  }
}

void setup() {
  lcd.begin(16, 2); 
  Serial.begin(115200);
  Serial.println("test");

  pinMode(button1.PIN, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);  // Configurar el buzzer como salida
  attachInterrupt(button1.PIN, isr, FALLING);

  lcd.createChar(0, dinoReposo);
  lcd.createChar(1, dinoCamina1);
  lcd.createChar(2, dinoCamina2);
  lcd.createChar(3, dinoSalta);
  lcd.createChar(4, cactus1);
  lcd.createChar(5, roca1);

  lcd.setCursor(0, 1);
  lcd.write(byte(0));  

  delay(4000);  
}

void loop() {
  lcd.clear();

  if (button1.pressed) {      
    dino.saltar();
    tone(buzzerPin, 1000, 200);  // Emitir sonido cuando el dinosaurio salte
    lcd.setCursor(0, 0);
    button1.pressed = false;      
  } else {
    lcd.setCursor(0, 1);
    dino.caminar();      
  }     
  
  lcd.write(byte(dino.obtenerEstado()));  

  cactus.mover();
  lcd.setCursor(cactus.obtenerPosicion(), 1);
  lcd.write(byte(4));  

  roca.mover();
  lcd.setCursor(roca.obtenerPosicion(), 1);
  lcd.write(byte(5));

  // Verificar colisiones
  if (dino.obtenerPosicion() == 0 && (cactus.obtenerPosicion() == 0 || roca.obtenerPosicion() == 0)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Colision!");
    lcd.setCursor(0, 1);
    lcd.print("Puntuacion: ");
    lcd.print(puntuacion); // Mostrar la puntuación obtenida
    Serial.println("Colisión!");
    delay(2000);
    puntuacion = 0; // Reiniciar la puntuación
  } else if (dino.obtenerPosicion() == 1 && (cactus.obtenerPosicion() == 0 || roca.obtenerPosicion() == 0)) {
    puntuacion++; // Incrementar la puntuación si pasa por un obstáculo
  }

  // Mostrar la puntuación en la pantalla LCD
  lcd.setCursor(7, 0);
  lcd.print("Puntos:");
  lcd.setCursor(14, 0);
  lcd.print(puntuacion);

  delay(velocidad);
}
