#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Configuração do sensor
Adafruit_TCS34725 sensor = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

void setup() {
  Serial.begin(9600);

  if (sensor.begin()) {
    Serial.println("Sensor TCS34725 encontrado!");
  } else {
    Serial.println("Erro: sensor nao encontrado!");
    while (1);
  }
}

void loop() {

  uint16_t r, g, b, c;

  // Leitura das cores
  sensor.getRawData(&r, &g, &b, &c);

  Serial.print("Vermelho: ");
  Serial.print(r);

  Serial.print(" | Verde: ");
  Serial.print(g);

  Serial.print(" | Azul: ");
  Serial.print(b);

  Serial.print(" | Intensidade: ");
  Serial.println(c);

  // Identificação aproximada
  if (r > g && r > b) {
    Serial.println("Cor identificada: VERMELHO");
  }
  else if (g > r && g > b) {
    Serial.println("Cor identificada: VERDE");
  }
  else if (b > r && b > g) {
    Serial.println("Cor identificada: AZUL");
  }
  else {
    Serial.println("Cor nao identificada");
  }

  Serial.println("----------------------");

  delay(500);
}