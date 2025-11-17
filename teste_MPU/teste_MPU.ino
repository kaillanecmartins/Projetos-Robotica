#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial.println("Teste do Sensor MPU6050");
  
  if (!mpu.begin()) {
    Serial.println("ERRO: Sensor MPU6050 não encontrado!");
    while (1);
  }
  
  Serial.println("Sensor MPU6050 inicializado com sucesso!");
  
  // Configurações do sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  Serial.println("Acelerômetro  |  Giroscópio");
  Serial.println("X\tY\tZ\t|\tX\tY\tZ");
  Serial.println("---------------------------------------------");
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Acelerômetro (m/s²)
  Serial.print(a.acceleration.x);
  Serial.print("\t");
  Serial.print(a.acceleration.y);
  Serial.print("\t");
  Serial.print(a.acceleration.z);
  Serial.print("\t|\t");
  
  // Giroscópio (rad/s)
  Serial.print(g.gyro.x);
  Serial.print("\t");
  Serial.print(g.gyro.y);
  Serial.print("\t");
  Serial.println(g.gyro.z);
  
  // Detecção de movimento simples
  float accelTotal = sqrt(a.acceleration.x*a.acceleration.x + 
                         a.acceleration.y*a.acceleration.y + 
                         a.acceleration.z*a.acceleration.z);
  
  if (accelTotal > 15) {
    Serial.println("*** MOVIMENTO BRUSCO DETECTADO! ***");
  }
  
  delay(500);
}