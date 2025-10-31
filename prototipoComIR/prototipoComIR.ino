#include <AFMotor.h> // Biblioteca do motor shield

// Configuração dos motores
AF_DCMotor motor1(3); // Motor direito
AF_DCMotor motor2(4); // Motor esquerdo

// Definição dos pinos dos sensores IR
// Sensores para seguir linha preta (analógicos)
const int sensorLinhaEsquerda = A0;
const int sensorLinhaDireita = A1;

// Sensores para detectar obstáculos (digitais)
const int sensorObstaculoFrente = 2;
const int sensorObstaculoTras = 3;

// Variáveis para calibração dos sensores de linha
int limiteLinha = 500; // Ajuste este valor conforme necessário
int leituraEsquerda, leituraDireita;

// Variáveis para sensores de obstáculo
int obstaculoFrente, obstaculoTras;

void setup() {
  // Configuração dos motores
  motor1.setSpeed(180); // Velocidade vai de 0 a 255
  motor2.setSpeed(250);
  
  // Configuração dos pinos
  pinMode(sensorLinhaEsquerda, INPUT);
  pinMode(sensorLinhaDireita, INPUT);
  pinMode(sensorObstaculoFrente, INPUT);
  pinMode(sensorObstaculoTras, INPUT);
  
  // Iniciar monitor serial
  Serial.begin(9600);
  
  Serial.println("=== ROBÔ SEGUIDOR DE LINHA COM DETECÇÃO DE OBSTÁCULOS ===");
  Serial.println("Iniciando calibração...");
  delay(2000);
  
  calibrarSensores();
  
  Serial.println("Sistema pronto!");
  Serial.println("----------------------------------------");
}

void loop() {
  // Lê todos os sensores
  lerSensores();
  
  // Mostra leituras no monitor serial
  mostrarLeituras();
  
  // Verifica obstáculos primeiro (prioridade máxima)
  if (obstaculoFrente == LOW) {
    Serial.println("*** OBSTÁCULO À FRENTE - PARANDO ***");
    para();
    delay(1000);
    // Pode adicionar lógica de desvio aqui
    return;
  }
  
  if (obstaculoTras == LOW) {
    Serial.println("*** OBSTÁCULO ATRÁS - PARANDO ***");
    para();
    delay(1000);
    return;
  }
  
  // Lógica de seguimento de linha
  seguirLinha();
  
  delay(50); // Pequeno delay para estabilidade
}

void calibrarSensores() {
  Serial.println("Coloque os sensores sobre a linha preta para calibração...");
  delay(3000);
  
  // Lê valores sobre a linha preta
  int somaEsquerda = 0, somaDireita = 0;
  int leituras = 10;
  
  for (int i = 0; i < leituras; i++) {
    somaEsquerda += analogRead(sensorLinhaEsquerda);
    somaDireita += analogRead(sensorLinhaDireita);
    delay(100);
  }
  
  int mediaEsquerda = somaEsquerda / leituras;
  int mediaDireita = somaDireita / leituras;
  
  // Define o limite como a média dos dois sensores
  limiteLinha = (mediaEsquerda + mediaDireita) / 2;
  
  Serial.print("Calibração concluída - Limite: ");
  Serial.println(limiteLinha);
  Serial.print("Sensor Esquerda: ");
  Serial.println(mediaEsquerda);
  Serial.print("Sensor Direita: ");
  Serial.println(mediaDireita);
}

void lerSensores() {
  // Lê sensores de linha (analógicos)
  leituraEsquerda = analogRead(sensorLinhaEsquerda);
  leituraDireita = analogRead(sensorLinhaDireita);
  
  // Lê sensores de obstáculo (digitais)
  obstaculoFrente = digitalRead(sensorObstaculoFrente);
  obstaculoTras = digitalRead(sensorObstaculoTras);
}

void mostrarLeituras() {
  Serial.print("Linha E: ");
  Serial.print(leituraEsquerda);
  Serial.print(" | Linha D: ");
  Serial.print(leituraDireita);
  Serial.print(" | Obst F: ");
  Serial.print(obstaculoFrente);
  Serial.print(" | Obst T: ");
  Serial.print(obstaculoTras);
  Serial.println();
}

void seguirLinha() {
  // Verifica se ambos os sensores estão na linha preta
  if (leituraEsquerda < limiteLinha && leituraDireita < limiteLinha) {
    Serial.println("Ambos na linha - FRENTE");
    frente();
  }
  // Sensor esquerdo saiu da linha - virar direita
  else if (leituraEsquerda > limiteLinha && leituraDireita < limiteLinha) {
    Serial.println("Esquerda fora - DIREITA");
    direita();
  }
  // Sensor direito saiu da linha - virar esquerda
  else if (leituraEsquerda < limiteLinha && leituraDireita > limiteLinha) {
    Serial.println("Direita fora - ESQUERDA");
    esquerda();
  }
  // Ambos os sensores fora da linha
  else {
    Serial.println("Perdeu a linha - PROCURANDO");
    procurarLinha();
  }
}

void procurarLinha() {
  // Estratégia para encontrar a linha novamente
  // Vira para a esquerda por um curto período
  esquerda();
  delay(200);
  
  // Verifica se encontrou a linha
  lerSensores();
  if (leituraEsquerda < limiteLinha || leituraDireita < limiteLinha) {
    return; // Linha encontrada
  }
  
  // Se não encontrou, vira para direita
  direita();
  delay(400);
  
  // Verifica novamente
  lerSensores();
  if (leituraEsquerda < limiteLinha || leituraDireita < limiteLinha) {
    return; // Linha encontrada
  }
  
  // Se ainda não encontrou, para e espera
  para();
  Serial.println("LINHA NÃO ENCONTRADA - PARADO");
}

//********************Movimenta o robô para frente********************
void frente() {
  motor1.run(FORWARD); // Motor direito
  motor2.run(FORWARD); // Motor esquerdo
}

//********************Movimenta o robô para trás********************
void tras() {
  motor1.run(BACKWARD); // Motor direito
  motor2.run(BACKWARD); // Motor esquerdo
}

//********************Parada dos motores********************
void para() {
  motor1.run(RELEASE); // Motor direito
  motor2.run(RELEASE); // Motor esquerdo
}

//********************Movimenta o robô para esquerda********************
void esquerda() {
  motor1.run(FORWARD);  // Motor direito
  motor2.run(BACKWARD); // Motor esquerdo
}

//********************Movimenta o robô para direita********************
void direita() {
  motor1.run(BACKWARD); // Motor direito
  motor2.run(FORWARD);  // Motor esquerdo
}