//#include <Ultrasonic.h>

// portas ultrassonico
#define p_echo 20
#define p_trig 21

//portas display
#define p_scl 18
#define p_sda 19

unsigned long tempo;
double distancia;

#define LedR 17
#define LedG 16
#define LedB 15

//biblioteca Github: https://github.com/samueldesaa/Robotic-Projects/blob/main/Arduino/ledPWM-Ultrasonic-Classes.ino

class ledRGB {
  int R, G, B;

public:
  //Construtor do LED
  ledRGB(int r, int g, int b) {
    R = r;
    G = g;
    B = b;
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
  }
  //Função de cor aleatória
  void randColor() {
    analogWrite(R, random(256));
    analogWrite(G, random(256));
    analogWrite(B, random(256));
  }
  //Função de escolher cor específica
  void color(int r, int g, int b) {
    analogWrite(R, r);
    analogWrite(G, g);
    analogWrite(B, b);
  }
  void color(int r, int g, int b, int del) {
    analogWrite(R, r);
    analogWrite(G, g);
    analogWrite(B, b);
    delay(del);
  }
  //Função de ligar todas as cores
  void white() {
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }
  //Led vermelho
  void red() {
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
  //Led verde
  void green() {
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
  }
  //Led azul
  void blue() {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
  }
  //Desligar
  void off() {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
};

//Determinado as portas do led
ledRGB led(LedR, LedG, LedB);

void setup() {
  Serial.begin(9600);
  pinMode(p_echo, INPUT);
  pinMode(p_trig, OUTPUT);
  pinMode(p_scl, OUTPUT);
  pinMode(p_sda, OUTPUT);
  digitalWrite(p_trig, LOW);
  randomSeed(analogRead(0));
}

void loop() {
  digitalWrite(p_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(p_trig, LOW);

  tempo = pulseIn(p_echo, HIGH);

  distancia = tempo/58;

  //Serial.println(distancia);

  if(distancia < 5){
    led.red();
  }else if(distancia < 15){
    led.blue();
  }else if(distancia < 20){
    led.green();
  }else if(distancia >= 20){
    led.white();                            
  }
  delay(500);  

}
