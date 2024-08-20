#include <Wire.h>
#include <VL53L0X.h>

//Definição dos pinos aos quais o XSHUT está ligado.
#define XSHUT_Sensor1 6

//Definição dos endereços dos sensores VL53L0X. Endereço padrão: 0b0101001 ou 41.
#define Sensor1_endereco 41

VL53L0X Sensor1;

//Constantes:
const int distanciaMin = 0; //Distância mínima de detecção do VL53L0X.
const int distanciaMax = 25; //Distância máxima de detecção do VL53L0X.
const long intervalo = 500; //Delay do buzzer em milisegundos.

// Variáveis de controle:
boolean detectado = false;
byte signalState = LOW;

// Indica a última vez em que o sinal do buzzer foi alterado.
unsigned long previousMillis = 0;

void setup()
{
  //Configura o buzzer como saída.
  
  //Desliga todos os VL53L0X.
  pinMode(XSHUT_Sensor1, OUTPUT);

  //Inicia a comunicação serial.
  Serial.begin(9600);
  Wire.begin();

  //Liga os sensores e altera seus endereços.
  pinMode(XSHUT_Sensor1, INPUT);
  delay(10);
  Sensor1.setAddress(Sensor1_endereco);

  //Inicializa os sensores.
  Sensor1.init();

  //Define timeout para os sensores.
  Sensor1.setTimeout(500);
  
  //Inicia o modo de leitura contínuo dos VL53L0X.
  Sensor1.startContinuous();
}

void loop()
{
  lerSensores(); //Lê os sensores.
}

void lerSensores()
{
  //Lê a distância em centímetros.
  int measure1 = Sensor1.readRangeContinuousMillimeters()*0.1;

  //Mostra o resultado no monitor serial.
  Serial.print(measure1);
  Serial.println("cm");
  Serial.println();

  //Verifica se a leitura está dentro dos parâmetros de detecção.
  if((measure1 > distanciaMin) && (measure1 <= distanciaMax)) {
    Serial.println("Detectou!");
    detectado = true;
  }
  else {
    Serial.println ("Nenhum objeto detectado."); //IMPRIME O TEXTO NO MONITOR SERIAL
  }
}

