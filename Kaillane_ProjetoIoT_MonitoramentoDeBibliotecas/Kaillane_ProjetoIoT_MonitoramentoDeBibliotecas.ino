#include <DHT.h>

#define R_pin 18
#define G_pin 19
#define B_pin 21

#define DHT_pin 15
#define KY_pin 2
#define LDR_pin 4

#define DHTTYPE DHT11

DHT dht(DHT_pin, DHTTYPE);

bool estado = 0; //verifica se teve ruido ou não

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
  int barulho = analogRead(KY_pin);
  
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Umidade: ");
  Serial.println(umidade);
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);
  Serial.print("Barulho: ");
  Serial.println(barulho);

  if(barulho < 600){
    digitalWrite(R_pin, HIGH);
    digitalWrite(G_pin, LOW);
    digitalWrite(B_pin, LOW);
  }
  else{
    digitalWrite(R_pin, LOW);
    digitalWrite(G_pin, HIGH);
    digitalWrite(B_pin, LOW);
  }
  delay(1000);
}