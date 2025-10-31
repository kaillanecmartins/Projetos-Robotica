// Teste de Sensor IR Analógico - Maior precisão na detecção
const int sensorIR = A0;   // Pino analógico do sensor IR
int valorLimite = 500;     // Ajuste este valor conforme necessário

void setup() {
  Serial.begin(9600);
  pinMode(sensorIR, INPUT);
  
  Serial.println("=== TESTE DE SENSOR IR ANALÓGICO ===");
  Serial.println("Lendo valores do sensor...");
  Serial.println("Valores baixos = Mais reflexão (obstáculo próximo)");
  Serial.println("Valores altos = Menos reflexão (sem obstáculo)");
  Serial.println("Limite atual: " + String(valorLimite));
  Serial.println("------------------------------------");
}

void loop() {
  int leitura = analogRead(sensorIR); // Lê valor analógico (0-1023)
  
  Serial.print("Valor do Sensor: ");
  Serial.print(leitura);
  Serial.print(" | Status: ");
  
  if (leitura < valorLimite) {
    Serial.println("OBSTÁCULO PRÓXIMO");
  } else {
    Serial.println("LIVRE");
  }
  
  delay(300); // Leitura mais rápida
}