//#include <Ultrasonic.h>
// portas ultrassonico
#define p_echo 20
#define p_trig 21

//portas display
#define p_scl 18
#define p_sda 19

unsigned long tempo;
double distancia;

void setup() {
  Serial.begin(9600);
  pinMode(p_echo, INPUT);
  pinMode(p_trig, OUTPUT);
  pinMode(p_scl, OUTPUT);
  pinMode(p_sda, OUTPUT);
  digitalWrite(p_trig, LOW);

}

void loop() {
  digitalWrite(p_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(p_trig, LOW);

  tempo = pulseIn(p_echo, HIGH);

  distancia = tempo/58;

  Serial.println(distancia);

  delay(500);  

}
