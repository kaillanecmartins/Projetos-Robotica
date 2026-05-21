#include <DHT.h>

#define R_pin1 4
#define G_pin1 18
#define R_pin2 19
#define G_pin2 21

#define DHT_pin 15
//#define KY_pin 2
//#define LDR_pin 4
//#define PIR_pin 22
#define IR1_pin 22
#define IR2_pin 15

#define DHTTYPE DHT11

DHT dht(DHT_pin, DHTTYPE);

bool estado = 0; //verifica se teve ruido ou não

void setup(){
  Serial.begin(9600);
  pinMode(R_pin1, OUTPUT);
  pinMode(G_pin1, OUTPUT);
  pinMode(R_pin2, OUTPUT);
  pinMode(G_pin2, OUTPUT);

  pinMode(DHT_pin, INPUT);
  pinMode(IR1_pin, INPUT);
  pinMode(IR2_pin, INPUT);
  //pinMode(KY_pin, INPUT);
 // pinMode(LDR_pin, INPUT);
  //pinMode(PIR_pin, INPUT);

  dht.begin();
}

void loop(){

  float temp = dht.readTemperature();
  float umidade = dht.readHumidity();
  int ir1 = digitalRead(IR1_pin);
  int ir2 = digitalRead(IR2_pin);
  //int luminosidade = analogRead(LDR_pin);
  //int barulho = analogRead(KY_pin);
  //int presenca = digitalRead(PIR_pin);
  
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Umidade: ");
  Serial.println(umidade);
  Serial.print("IR simples: ");
  Serial.println(ir1);
  Serial.print("IR complexo: ");
  Serial.println(ir2);
  /*Serial.print("Luminosidade: ");
  Serial.println(luminosidade);*/
  /*Serial.print("Barulho: ");
  Serial.println(barulho);
  Serial.print("Presença: ");
  Serial.println(presenca);*/

  /*if(barulho > 700){
    LED_RG1(0,1);
  }else{
    LED_RG1(1,0);
  }*/

/* if(!presenca){
    LED_RG2(1,0);
  }else{
    LED_RG2(0,1);
  }*/

  //detecção com ir simples
  if(ir1){
    LED_RG1(1, 0);
  }else{
    LED_RG1(0,1);
  }

  //detecção com ir complexo
  if(ir2){
    LED_RG2(1, 0);
  }else{
    LED_RG2(0,1);
  }

  delay(500);
}

void LED_RG1(int modeR, int modeG){
    digitalWrite(R_pin1, modeR);
    digitalWrite(G_pin1, modeG);
}
void LED_RG2(int modeR, int modeG){
    digitalWrite(R_pin2, modeR);
    digitalWrite(G_pin2, modeG);
}