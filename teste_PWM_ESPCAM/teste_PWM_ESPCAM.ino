#include <Arduino.h>

// =============================
// PINOS DO MOTOR
// =============================

// Motor esquerdo
#define LEFT_IN1 12
#define LEFT_IN2 13
#define LEFT_PWM 4   // ENA

// Motor direito
#define RIGHT_IN1 14
#define RIGHT_IN2 15
#define RIGHT_PWM 2  // ENB

// Velocidade inicial (0 a 255)
int leftSpeed = 100;
int rightSpeed = 100;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("=== TESTE DE MOTORES L298N + ESP32-CAM ===");

  // Configura pinos como saída
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);

  Serial.println("Configuração concluída!");
}

// =============================
// FUNÇÕES DE CONTROLE DE MOTOR
// =============================

// Motor esquerdo
void left_forward() {
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(LEFT_PWM, leftSpeed);
}

void left_backward() {
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  analogWrite(LEFT_PWM, leftSpeed);
}

// Motor direito
void right_forward() {
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
  analogWrite(RIGHT_PWM, rightSpeed);
}

void right_backward() {
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, HIGH);
  analogWrite(RIGHT_PWM, rightSpeed);
}

// =============================
// MOVIMENTOS COMPLETOS
// =============================

void forward() {
  left_forward();
  right_forward();
}

void backward() {
  left_backward();
  right_backward();
}

void leftTurn() {
  left_backward();
  right_forward();
}

void rightTurn() {
  left_forward();
  right_backward();
}

void stopMotors() {
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}

// =============================
// LOOP PRINCIPAL DE TESTE
// =============================

void loop() {
  Serial.println("➡ Indo para FRENTE");
  forward();
  delay(1500);

  Serial.println("⬅ Indo para TRÁS");
  backward();
  delay(1500);

  Serial.println("↪ Virando DIREITA");
  rightTurn();
  delay(1200);

  Serial.println("↩ Virando ESQUERDA");
  leftTurn();
  delay(1200);

  Serial.println("⛔ PARADO");
  stopMotors();
  delay(2000);
}
