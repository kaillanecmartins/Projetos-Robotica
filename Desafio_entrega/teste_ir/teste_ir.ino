int sensorIR = 2;

void setup() {
  pinMode(sensorIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int estado = digitalRead(sensorIR);

  if (estado == LOW) {
    Serial.println("Objeto detectado!");
  } else {
    Serial.println("Nenhum objeto detectado");
  }

  delay(500);
}