#include <Servo.h>

Servo meuServo;

void setup() {
  meuServo.attach(9);
}

void loop() {
  meuServo.write(0);
  delay(1000);

  meuServo.write(90);
  delay(1000);

  meuServo.write(180);
  delay(1000);
}