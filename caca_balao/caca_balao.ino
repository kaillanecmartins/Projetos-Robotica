#include <SoftwareSerial.h>

// Comunicação Bluetooth HC-05
SoftwareSerial serialdobluetooth(8, 9);

// Pinos da ponte H L9110S
const int A_IA = 3;
const int A_IB = 5;
const int B_IA = 10;
const int B_IB = 11;

// Configurações
int VELOCIDADE = 200;
const unsigned long TEMPO_MOVIMENTO = 500;

int valordobluetooth = 0;

unsigned long tempoInicio = 0;
bool movimentoAtivo = false;


void motor(int pinIA, int pinIB, int velocidade) {

  velocidade = constrain(velocidade, -255, 255);

  if (velocidade > 0) {
    analogWrite(pinIA, velocidade);
    digitalWrite(pinIB, LOW);
  }

  else if (velocidade < 0) {
    digitalWrite(pinIA, LOW);
    analogWrite(pinIB, -velocidade);
  }

  else {
    digitalWrite(pinIA, LOW);
    digitalWrite(pinIB, LOW);
  }
}

void motorA(int v) {
  motor(A_IA, A_IB, v);
}

void motorB(int v) {
  motor(B_IA, B_IB, v);
}


void frente() {
  motorA(VELOCIDADE);
  motorB(VELOCIDADE);
}

void tras() {
  motorA(-VELOCIDADE);
  motorB(-VELOCIDADE);
}

void esquerda() {
  motorA(-VELOCIDADE);
  motorB(VELOCIDADE);
}

void direita() {
  motorA(VELOCIDADE);
  motorB(-VELOCIDADE);
}

void parar() {
  motorA(0);
  motorB(0);
  movimentoAtivo = false;
}

void freiar() {

  digitalWrite(A_IA, HIGH);
  digitalWrite(A_IB, HIGH);

  digitalWrite(B_IA, HIGH);
  digitalWrite(B_IB, HIGH);

  movimentoAtivo = false;
}


void iniciarMovimento(void (*funcaoMovimento)()) {

  funcaoMovimento();

  tempoInicio = millis();
  movimentoAtivo = true;
}

void setup() {

  serialdobluetooth.begin(9600);
  Serial.begin(9600);

  pinMode(A_IA, OUTPUT);
  pinMode(A_IB, OUTPUT);
  pinMode(B_IA, OUTPUT);
  pinMode(B_IB, OUTPUT);

  parar();

  Serial.println("Carrinho Bluetooth iniciado!");
  Serial.println("F = Frente");
  Serial.println("B = Tras");
  Serial.println("L = Esquerda");
  Serial.println("R = Direita");
  Serial.println("S = Parar");
  Serial.println("X = Freio");
}

void loop() {

  // RECEBER COMANDO BLUETOOTH
  if (serialdobluetooth.available()) {

    valordobluetooth = serialdobluetooth.read();

    Serial.print("Comando recebido: ");
    Serial.println((char)valordobluetooth);

    if (valordobluetooth == 'F' || valordobluetooth == 'f') {
      iniciarMovimento(frente);
    }

    else if (valordobluetooth == 'B' || valordobluetooth == 'b') {
      iniciarMovimento(tras);
    }

    else if (valordobluetooth == 'L' || valordobluetooth == 'l') {
      iniciarMovimento(esquerda);
    }

    else if (valordobluetooth == 'R' || valordobluetooth == 'r') {
      iniciarMovimento(direita);
    }

    else if (valordobluetooth == 'S' || valordobluetooth == 's') {
      parar();
      Serial.println("Parada imediata");
    }

    else if (valordobluetooth == 'X' || valordobluetooth == 'x') {
      freiar();
      Serial.println("Freio acionado");
    }
  }

  if (movimentoAtivo &&
      millis() - tempoInicio >= TEMPO_MOVIMENTO) {

    parar();

    Serial.println("Tempo encerrado - Carrinho parado");
  }
}
