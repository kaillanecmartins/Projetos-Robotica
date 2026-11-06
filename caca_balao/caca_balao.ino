#include <SoftwareSerial.h>

SoftwareSerial SerialBT(10, 11); // RX = 10, TX = 11 do Arduino (HC-05)

const int A_IA = 5;  // Motor direito
const int A_IB = 6;

const int B_IA = 9;  // Motor esquerdo
const int B_IB = 3;

int velocidade = 250; // Velocidade dos motores (0 a 255)

void setup() {
  Serial.begin(9600);
  SerialBT.begin(9600); // Comunicação com HC-05

  pinMode(A_IA, OUTPUT);
  pinMode(A_IB, OUTPUT);
  pinMode(B_IA, OUTPUT);
  pinMode(B_IB, OUTPUT);

  parar();

  Serial.println("Carrinho Bluetooth iniciado");
  Serial.println("Comandos: F, B, L, R, S");
}

void loop() {
  char comando = '\0';

  while (SerialBT.available()) {
    char c = SerialBT.read();

    if (c != '\n' && c != '\r' && c != ' ' && c != '\t') {
      comando = c;
    }
  }

  if (comando != '\0') {
    comando = toupper(comando);

    Serial.print("Comando recebido: ");
    Serial.println(comando);

    switch (comando) {
      case 'F': frente(); break;
      case 'B': re(); break;
      case 'L': girarEsquerda(); break;
      case 'R': girarDireita(); break;
      case 'S': parar(); break;

      default:
        SerialBT.println("Comando invalido");
        break;
    }
  }
}

void motorDireito(int velocidade) {
  velocidade = constrain(velocidade, -255, 255);

  if (velocidade > 0) {
    analogWrite(A_IA, velocidade);
    analogWrite(A_IB, 0);
  } 
  else if (velocidade < 0) {
    analogWrite(A_IA, 0);
    analogWrite(A_IB, -velocidade);
  } 
  else {
    analogWrite(A_IA, 0);
    analogWrite(A_IB, 0);
  }
}

void motorEsquerdo(int velocidade) {
  velocidade = constrain(velocidade, -255, 255);

  if (velocidade > 0) {
    analogWrite(B_IA, velocidade);
    analogWrite(B_IB, 0);
  } 
  else if (velocidade < 0) {
    analogWrite(B_IA, 0);
    analogWrite(B_IB, -velocidade);
  } 
  else {
    analogWrite(B_IA, 0);
    analogWrite(B_IB, 0);
  }
}

void frente() {
  motorDireito(velocidade);
  motorEsquerdo(velocidade);

  Serial.println("Frente");
  SerialBT.println("Frente");
}

void re() {
  motorDireito(-velocidade);
  motorEsquerdo(-velocidade);

  Serial.println("Re");
  SerialBT.println("Re");
}

void girarDireita() {
  motorDireito(-velocidade);
  motorEsquerdo(velocidade);

  Serial.println("Girar direita");
  SerialBT.println("Girar direita");
}

void girarEsquerda() {
  motorDireito(velocidade);
  motorEsquerdo(-velocidade);

  Serial.println("Girar esquerda");
  SerialBT.println("Girar esquerda");
}

void parar() {
  motorDireito(0);
  motorEsquerdo(0);

  Serial.println("Parado");
  SerialBT.println("Parado");
}