#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int ledPin = 4; // Pino do LED

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Bluetooth"); // Inicializa o Bluetooth com o nome "ESP32Bluetooth"
  Serial.println("O dispositivo foi iniciado!");
  
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
}

void loop() {
  if (SerialBT.available()) { // Verifica se há dados disponíveis via Bluetooth
    char command = SerialBT.read(); // Lê o comando enviado via Bluetooth
    
    // Verifica o comando recebido e controla o LED
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Liga o LED
      SerialBT.println("LED ligado");
    } else if (command == '0') {
      digitalWrite(ledPin, LOW); // Desliga o LED
      SerialBT.println("LED desligado");
    }
  }
  
  delay(50); // Pequeno atraso para estabilidade
}
