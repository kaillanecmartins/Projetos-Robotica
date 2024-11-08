#include <AFMotor.h> // Biblioteca do motor shield
#include <Dabble.h> // incluindo biblioteca do app Dabble
#include "SoftwareSerial.h"

//********************Criação dos objetos********************

AF_DCMotor motor1(3); // Motor esquerdo
AF_DCMotor motor2(4); // Motor direito
SoftwareSerial bluetooth(19, 18); //TX, RX (Bluetooth)

void setup() {
  // Configuração de velocidade dos motores
  motor1.setSpeed(255); // Velocidade vai de 0 a 255
  motor2.setSpeed(255);
  //Iniciar monitor serial
  Serial.begin(9600);
  Dabble.begin(9600);
  bluetooth.begin(9600);
}

void loop() {

  Dabble.processInput();

  int c;


  if (bluetooth.available() > 0) {
    
    c = bluetooth.read();
    switch (c) {
      case 'F':
        frente();
        bluetooth.println("F");
        break;
      case 'A':
        frente();
        bluetooth.println("F");
        break;
      case 'L':
        esquerda();
        bluetooth.println("F");
        break;
      case 'R':
        direita();
        bluetooth.println("F");
        break;
      case 'B':
        tras();
        bluetooth.println("F");
        break;
      case 'S':
        para();
        bluetooth.println("F");
        break;
    }
  }
}

//********************Movimenta o robô para frente********************

void frente() {
  motor1.run(FORWARD); // Motor esquerdo
  motor2.run(FORWARD); // Motor direito
}

//********************Movimenta o robô para trás********************

void tras() {
  motor1.run(BACKWARD); // Motor esquerdo
  motor2.run(BACKWARD); // Motor direito
}

//********************Parada dos motores********************

void para() {
  motor1.run(RELEASE); // Motor esquerdo
  motor2.run(RELEASE); // Motor direito
}

//********************Movimenta o robô para esquerda********************

void esquerda() {
  motor1.run(FORWARD); // Motor esquerdo
  motor2.run(BACKWARD); // Motor direito
}

//********************Movimenta o robô para direita********************

void direita() {
  motor1.run(BACKWARD); // Motor esquerdo
  motor2.run(FORWARD); // Motor direito
}
