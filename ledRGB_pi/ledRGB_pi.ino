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
  //semente do ramdom para maior diversidade de cores
  randomSeed(analogRead(0));
}

void loop() {
  led.white(); 
  led.off();
}
