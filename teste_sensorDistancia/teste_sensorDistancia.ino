#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X vl = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  Serial.println("Teste do Sensor VL53L0X");
  
  if (!vl.begin()) {
    Serial.println("ERRO: Sensor VL53L0X não encontrado!");
    while (1);
  }
  
  Serial.println("Sensor VL53L0X inicializado com sucesso!");
  Serial.println("Distância (mm) | Status | Interpretação");
  Serial.println("----------------------------------------");
}

void loop() {
  VL53L0X_RangingMeasurementData_t medida;
  
  // Faz a leitura
  vl.rangingTest(&medida, false);
  
  Serial.print(medida.RangeMilliMeter);
  Serial.print(" mm\t\t");
  
  // Mostra o status da medição
  switch (medida.RangeStatus) {
    case 0:
      Serial.print("OK\t\t");
      break;
    case 1:
      Serial.print("SIGMA\t\t");
      break;
    case 2:
      Serial.print("SINAL\t\t");
      break;
    case 4:
      Serial.print("FORA\t\t");
      break;
    default:
      Serial.print("ERRO\t\t");
      break;
  }
  
  // Interpretação da distância
  if (medida.RangeStatus == 0) {
    if (medida.RangeMilliMeter < 100) {
      Serial.println("MUITO PERTO");
    } else if (medida.RangeMilliMeter < 500) {
      Serial.println("PERTO");
    } else if (medida.RangeMilliMeter < 1000) {
      Serial.println("MÉDIA");
    } else {
      Serial.println("LONGE");
    }
  } else {
    Serial.println("MEDIÇÃO INVÁLIDA");
  }
  
  delay(500);
}