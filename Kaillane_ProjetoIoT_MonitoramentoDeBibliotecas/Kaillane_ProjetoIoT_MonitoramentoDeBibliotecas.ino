#include <DHT.h>

#define led1 18
#define led2 19

#define DHT_pin 15
#define KY_pin 2
//#define PIR_pin 22
#define IR1_pin 22
#define IR2_pin 4

#define DHTTYPE DHT11

DHT dht(DHT_pin, DHTTYPE);

bool estado = 0; //verifica se teve ruido ou não

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(DHT_pin, INPUT);
  pinMode(IR1_pin, INPUT);
  pinMode(IR2_pin, INPUT);
  pinMode(KY_pin, INPUT);
 // pinMode(LDR_pin, INPUT);
  //pinMode(PIR_pin, INPUT);

  dht.begin();
}

void loop(){

  float temp = dht.readTemperature();
  float umidade = dht.readHumidity();
  int ir1 = digitalRead(IR1_pin);
  int ir2 = digitalRead(IR2_pin);
  int barulho = analogRead(KY_pin);
  //int presenca = digitalRead(PIR_pin);
  
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Umidade: ");
  Serial.println(umidade);
  Serial.print("IR simples: ");
  Serial.println(ir1);
  Serial.print("IR complexo: ");
  Serial.println(ir2);
  Serial.print("Barulho: ");
  Serial.println(barulho);
  /*Serial.print("Presença: ");
  Serial.println(presenca);*/

  //detecção com ir simples
  if(ir1 == 1){
    digitalWrite(led1, HIGH);
  }else{
    digitalWrite(led1, LOW);
  }

  //detecção com ir complexo
  if(ir2 == 1){
    digitalWrite(led2, HIGH);
  }else{
    digitalWrite(led2, LOW);
  }
  delay(500);
}