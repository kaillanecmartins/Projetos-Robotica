#include <LiquidCrystal.h>
// Define as conexões e cria o objeto para acesso
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int backLight = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define echo 52
#define trig 53
#define ledVermelho 46
#define ledVerde 3
#define ledAmarelo 4

unsigned long tempo; 
double distancia;
// Limites para detecção das teclas, em ordem crescente
 
// Iniciação
void setup() {
  //Progama o pino de backlight como saída
  pinMode(backLight, OUTPUT);
  // Inicia o display e coloca uma mensagem
  lcd.begin(16, 2);
  lcd.print("Distancia:");
  // Acende o backlight
  digitalWrite(backLight, HIGH);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  Serial.begin(9600);

  digitalWrite(trig, LOW);
}
 
// Laço principal
void loop() {
  static int teclaAnt = -1;   // última tecla detectada
 
  // Lê a tensão no pino A0
  int leitura = analogRead(A0);
 
  // Identifica a tecla apertada pela tensão lida
  /*int teclaNova;
  for (teclaNova = 0; ; teclaNova++) {
    if (leitura < teclas[teclaNova].limite) {
      break;
    }
  }*/
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  tempo = pulseIn(echo, HIGH);
  //digitalWrite(ledVerde, HIGH);
  distancia = tempo/58;
  digitalWrite(ledVermelho, HIGH);
  lcd.setCursor(0,1);
  lcd.print(distancia);
  Serial.println(distancia);
  if(distancia <= 4.0){
    digitalWrite(ledVermelho, HIGH);
  }else if(distancia <= 6.0){
    digitalWrite(ledAmarelo, HIGH);
  }else if(distancia <= 10.0){
    digitalWrite(ledVerde, HIGH);
    delay(100);
    digitalWrite(ledVerde, LOW);
    delay(500);
  }else{
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
  }
  // Atualiza a tela se pressionou uma nova tecla
  /*if (teclaNova != teclaAnt) {
    lcd.setCursor(0,1);
    lcd.print(distancia);
    //teclaAnt = teclaNova;
  }*/
 
  // Dá um tempo antes do próximo teste
  delay (100);
}
