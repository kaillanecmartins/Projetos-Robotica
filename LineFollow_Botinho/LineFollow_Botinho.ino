#include <BnrOneAPlus.h>
#include <SPI.h>
#include <Servo.h>
#include <Ultrasonic.h>

BnrOneAPlus one;

// ================= CONFIG =================
#define SSPIN 2
#define MINIMUM_BATTERY_V 10.5

#define BW_THRESHOLD 300
#define DIST_OBJ 10   // distância em cm para detectar objeto

// ================= OBJETOS =================
Servo servoA;
Ultrasonic ult1(A0, A1);

// ================= CONTROLE =================
int speed = 6;

// Servo
int angAberto = 0;
int angFechado = 120;

// Controle de estado
String estado = "SEGUIR";

// Controle de leitura do ultrassônico (economia)
unsigned long lastRead = 0;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  servoA.attach(6);
  servoA.write(angAberto);

  one.spiConnect(SSPIN);
  one.stop();
  one.setMinBatteryV(MINIMUM_BATTERY_V);

  one.lcd1("Bot'n Roll");
  one.lcd2("Pressione...");
  one.move(10, 10);
  while (one.readButton() == 0);

  one.lcd2("Rodando...");
  
}

// ================= FUNÇÃO SEGUIR LINHA =================
void seguirLinha() {

  int s2 = one.readAdc(2);
  int s3 = one.readAdc(3);
  int s4 = one.readAdc(4);
  int s5 = one.readAdc(5);

  // linha central
  if (s3 > BW_THRESHOLD && s4 > BW_THRESHOLD) {
    one.move(speed, speed);
  }

  // leve esquerda
  else if (s2 > BW_THRESHOLD) {
    one.move(3, speed);
  }

  // leve direita
  else if (s5 > BW_THRESHOLD) {
    one.move(speed, 3);
  }

  // correção mais forte
  else if (s3 > BW_THRESHOLD) {
    one.move(2, speed);
  }
  else if (s4 > BW_THRESHOLD) {
    one.move(speed, 2);
  }

  // perdeu linha
  else {
    one.move(4, -4);
  }
}

// ================= PEGAR OBJETO =================
void pegarObjeto() {

  one.stop();
  delay(200);

  // aproxima mais um pouco
  one.move(5,5);
  delay(400);

  one.stop();

  // fecha garra
  servoA.write(angFechado);
  delay(800);

  // economia: desliga servo
  servoA.detach();
}

// ================= LOOP =================
void loop() {

  if (estado == "SEGUIR") {

    seguirLinha();

    // leitura do ultrassônico com intervalo (economia)
    if (millis() - lastRead > 150) {

      lastRead = millis();

      int d = ult1.read();

      Serial.print("Dist: ");
      Serial.println(d);

      if (d > 0 && d < DIST_OBJ) {
        estado = "PEGAR";
      }
    }
  }

  else if (estado == "PEGAR") {

    pegarObjeto();
    estado = "PARAR";
  }

  else if (estado == "PARAR") {

    one.stop();
  }

  delay(20);
}