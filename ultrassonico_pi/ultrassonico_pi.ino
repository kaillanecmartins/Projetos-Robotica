#include <Ultrasonic.h>
// portas ultrassonico
#define p_echo 20
#define p_trig 21

//portas display
#define p_scl 18
#define p_sda 19

void setup() {
  Serial.begin(9600);
  pinMode(p_echo, INPUT);
  pinMode(p_trig, INPUT);
  pinMode(p_scl, OUTPUT);
  pinMode(p_sda, OUTPUT);

}

void loop() {
  

}
