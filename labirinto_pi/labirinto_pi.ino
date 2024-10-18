int IN1 = 12; // Roda direita - sentido horário
int IN2 = 14; // Roda direita - sentido anti-horário
int IN3 = 27; // Roda esquerda - sentido horário
int IN4 = 26; // Roda esquerda - sentido anti-horário

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
