#include <Ultrasonic.h>
#define echo 2
#define trig 3
#define led1 8
#define led2 9
#define led3 10

double distancia2; 
double distancia;
 Ultrasonic ultra(3,2);
 Ultrasonic ultra2(5,4);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);

  //digitalWrite(trig, LOW);
  /*digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(trig, HIGH);
  //delayMicroseconds(1000);
  //digitalWrite(trig, LOW);
  distancia = ultra.read();
  distancia2 = ultra2.read();
  Serial.println(distancia);
  Serial.println("---------------");
  Serial.println(distancia2);

  if(distancia <= 6){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else if(distancia <= 10){
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);
  } else if(distancia <= 14){
    digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
    delay(500);

}
