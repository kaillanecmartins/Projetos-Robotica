#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// Cria uma instância do sensor
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Aguarda a conexão com o monitor serial

  if (!lox.begin()) {
    Serial.println("Não foi possível encontrar o sensor VL53L0X. Verifique a conexão.");
    while (1);
  }
  Serial.println("VL53L0X encontrado!");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);  // false para não usar a calibragem

  Serial.print("Distância: ");
  Serial.print(measure.RangeMilliMeter);
  Serial.println(" mm");

  delay(1000); // Aguarda 1 segundo antes da próxima medição
}

