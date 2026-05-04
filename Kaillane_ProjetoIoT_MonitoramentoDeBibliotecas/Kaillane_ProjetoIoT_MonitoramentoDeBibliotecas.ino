#include <DHT.h>

#define R_pin 18
#define G_pin 19
#define B_pin 21

#define DHT_pin 15
#define KY_pin 23
#define LDR_pin 4

#define DHTTYPE DHT22

DHT dht(DHT_pin, DHTTYPE);

void setup(){
  Serial.begin(9600);
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);

  pinMode(DHT_pin, INPUT);
  pinMode(KY_pin, INPUT);
  pinMode(LDR_pin, INPUT);

  dht.begin();
}

void loop(){

  float temp = dht.readTemperature();
  float umidade = dht.readHumidity();
  int luminosidade = analogRead(LDR_pin);
  
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Umidade: ");
  Serial.println(umidade);
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);

  delay(1000);
}