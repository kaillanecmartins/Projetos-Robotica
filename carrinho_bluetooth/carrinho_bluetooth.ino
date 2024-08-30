#include "BluetoothSerial.h"

// Saídas que ligam as entradas na ponte H para as rodas direita e esquerda
int IN1 = 12; // Roda direita - sentido horário
int IN2 = 14; // Roda direita - sentido anti-horário
int IN3 = 27; // Roda esquerda - sentido horário
int IN4 = 26; // Roda esquerda - sentido anti-horário

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth não está habilitado! Por favor, entre nas configurações e habilite o Bluetooth.
#endif

BluetoothSerial SerialBT;

void setup() {
  // Declaração dos pinos
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
  SerialBT.begin("novo"); // Nome do dispositivo Bluetooth
}

void loop() {
  char command;
  
  if (SerialBT.available() > 0) {
    command = SerialBT.read();

    // Movimentação do robô diferencial
    if (command == 'F') {
      // Mover para frente
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (command == 'B') {
      // Mover para trás
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (command == 'L') {
      // Virar para a esquerda
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (command == 'R') {
      // Virar para a direita
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (command == 'S') {
      // Parar
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}
