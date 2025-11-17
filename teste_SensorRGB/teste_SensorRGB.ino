#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pinos para o LED RGB
#define redpin 3
#define greenpin 5
#define bluepin 6

// set to false if using a common cathode LED
#define commonAnode true

// nossa tabela gamma para correção de cor
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 encontrado!");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // para se não encontrar o sensor
  }

  // Configura os pinos do LED RGB
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Tabela gamma para correção de cores
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
  
  Serial.println("Pronto! Movimente o sensor sobre diferentes cores.");
  Serial.println("==================================================");
}

void loop() {
  float red, green, blue;
  
  tcs.setInterrupt(false);  // liga o LED do sensor
  delay(60);  // tempo para leitura
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);  // desliga o LED do sensor

  // Exibe os valores no serial
  Serial.print("R: "); Serial.print(int(red)); 
  Serial.print(" | G: "); Serial.print(int(green)); 
  Serial.print(" | B: "); Serial.print(int(blue));
  
  // Identifica e exibe a cor detectada
  String corDetectada = identificarCor(red, green, blue);
  Serial.print(" | Cor: ");
  Serial.println(corDetectada);

  // Acende o LED RGB com a cor detectada
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);

  delay(500); // Pequena pausa entre leituras
}

// Função para identificar a cor baseada nos valores RGB
String identificarCor(float r, float g, float b) {
  // Normaliza os valores para facilitar a comparação
  float total = r + g + b;
  if (total < 50) return "PRETO";
  
  float redRatio = r / total;
  float greenRatio = g / total;
  float blueRatio = b / total;

  // Detecção de cores principais
  if (redRatio > 0.5 && redRatio > greenRatio && redRatio > blueRatio) {
    if (r > 150) return "VERMELHO";
    if (r > 100) return "VERMELHO ESCURO";
    return "VERMELHO BAIXO";
  }
  
  if (greenRatio > 0.5 && greenRatio > redRatio && greenRatio > blueRatio) {
    if (g > 150) return "VERDE";
    if (g > 100) return "VERDE ESCURO";
    return "VERDE BAIXO";
  }
  
  if (blueRatio > 0.5 && blueRatio > redRatio && blueRatio > greenRatio) {
    if (b > 150) return "AZUL";
    if (b > 100) return "AZUL ESCURO";
    return "AZUL BAIXO";
  }
  
  // Detecção de cores mistas
  if (r > 180 && g > 180 && b < 100) return "AMARELO";
  if (r > 180 && b > 180 && g < 100) return "MAGENTA";
  if (g > 180 && b > 180 && r < 100) return "CIANO";
  
  // Cores neutras
  if (r > 180 && g > 180 && b > 180) return "BRANCO";
  if (r > 100 && g > 100 && b > 100) return "CINZA CLARO";
  if (r > 50 && g > 50 && b > 50) return "CINZA ESCURO";
  
  return "COR DESCONHECIDA";
}