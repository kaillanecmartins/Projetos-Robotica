#define LedR 16
#define LedG 17
#define LedB 15

void setup() {
  // put your setup code here, to run once:
  pinMode(LedR, OUTPUT);
  pinMode(LedR, OUTPUT);
  pinMode(LedR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LedR, HIGH);
  delay(1000);
  digitalWrite(LedG, HIGH);
  delay(1000);
  digitalWrite(LedB, HIGH);
  delay(1000);
  digitalWrite(LedR, HIGH);
  delay(1000);
}
