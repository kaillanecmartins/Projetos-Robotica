#include <AFMotor.h> // Biblioteca do motor shield

//********************Criação dos objetos********************

AF_DCMotor motor1(1); // Motor esquerdo
AF_DCMotor motor2(2); // Motor direito

void setup() {
  // Configuração de velocidade dos motores
  motor1.setSpeed(255); // Velocidade vai de 0 a 255
  motor2.setSpeed(255);
  //Iniciar monitor serial
  Serial.begin(9600);
}

void loop() {

  char c = Serial.read();

  switch (c) {
    case 'F':
      frente();
      break;
    case 'A':
      frente();
      break;
    case 'L':
      esquerda();
      break;
    case 'R':
      direita();
      break;
    case 'B':
      tras();
      break;
    case 'S':
      para();
      break;
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
