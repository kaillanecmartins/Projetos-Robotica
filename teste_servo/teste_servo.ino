#include <Servo.h>

Servo myservo; 

void setup() {
  myservo.attach(6);  // Define o pino do Servo motor como pino 9
}

void loop() {
  myservo.write(180);                  // Define a posição do servo conforme o valor mapeado
  delay(15);                           // Espera para o servo alcançar a posição
}
