
// Pinos da ponte H L9110S
const int A_IA = 3;
const int A_IB = 5;
const int B_IA = 10;
const int B_IB = 11;

// Configurações dos motores
int VELOCIDADE = 200;
const unsigned long TEMPO_MOVIMENTO = 1000;

// Controla o motor conforme velocidade e sentido
void motor(int pinIA, int pinIB, int velocidade) {
  velocidade = constrain(velocidade, -255, 255);

  if (velocidade > 0) {
    analogWrite(pinIA, velocidade);
    digitalWrite(pinIB, LOW);
  }
  else if (velocidade < 0) {
    digitalWrite(pinIA, LOW);
    analogWrite(pinIB, -velocidade);
  }
  else {
    digitalWrite(pinIA, LOW);
    digitalWrite(pinIB, LOW);
  }
}

// Controla individualmente os motores
void motorA(int v) {
  motor(A_IA, A_IB, v);
}

void motorB(int v) {
  motor(B_IA, B_IB, v);
}

// Define os movimentos do carrinho
void frente() {
  motorA(VELOCIDADE);
  motorB(VELOCIDADE);
}

void tras() {
  motorA(-VELOCIDADE);
  motorB(-VELOCIDADE);
}

void esquerda() {
  motorA(-VELOCIDADE);
  motorB(VELOCIDADE);
}

void direita() {
  motorA(VELOCIDADE);
  motorB(-VELOCIDADE);
}

// Desliga os dois motores
void parar() {
  motorA(0);
  motorB(0);
}

// Configura os pinos e inicia os motores parados
void setup() {
  pinMode(A_IA, OUTPUT);
  pinMode(A_IB, OUTPUT);
  pinMode(B_IA, OUTPUT);
  pinMode(B_IB, OUTPUT);

  parar();
}

// Executa uma sequência de movimentos
void loop() {

  frente();
  delay(TEMPO_MOVIMENTO);
  parar();
  delay(500);

  tras();
  delay(TEMPO_MOVIMENTO);
  parar();
  delay(500);

  esquerda();
  delay(TEMPO_MOVIMENTO);
  parar();
  delay(500);

  direita();
  delay(TEMPO_MOVIMENTO);
  parar();
  delay(1000);
}
