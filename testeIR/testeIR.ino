// Teste de Sensor IR - Sensor de Obstáculo/Reflexivo
const int sensorIR = 2;    // Pino digital do sensor IR
const int ledPin = 13;     // LED interno do Arduino

void setup() {
  Serial.begin(9600);      // Inicia comunicação serial
  pinMode(sensorIR, INPUT); // Configura sensor como entrada
  pinMode(ledPin, OUTPUT);  // Configura LED como saída
  
  Serial.println("=== TESTE DE SENSOR IR ===");
  Serial.println("Esperando leitura do sensor...");
  Serial.println("Valor 0 = Obstáculo detectado");
  Serial.println("Valor 1 = Sem obstáculo");
  Serial.println("---------------------------");
}

void loop() {
  int leitura = digitalRead(sensorIR); // Lê o sensor
  
  // Mostra resultado no monitor serial
  Serial.print("Status do Sensor: ");
  Serial.print(leitura);
  
  if (leitura == 0) {
    Serial.println(" - OBSTÁCULO DETECTADO!");
    digitalWrite(ledPin, HIGH); // Acende LED
  } else {
    Serial.println(" - Sem obstáculo");
    digitalWrite(ledPin, LOW);  // Apaga LED
  }
  
  delay(500); // Aguarda 0.5 segundos entre leituras
}