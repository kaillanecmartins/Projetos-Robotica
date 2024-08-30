#define echo 52
#define trig 53

unsigned long tempo;
double distancia;

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    Serial.begin(9600);

    digitalWrite(trig, LOW);
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  tempo = pulseIn(echo, HIGH);

  distancia = tempo/58;

  Serial.println(distancia);

  delay(500);  
}
