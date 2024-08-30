// C++ code
//
int buzzerpin = 13;
void setup() {
 pinMode(buzzerpin,OUTPUT);
 tone(buzzerpin,500,2000);
}
void loop() {
 tone(buzzerpin,277);
 delay(1000);
 tone(buzzerpin,311);
 delay(1000);
 tone(buzzerpin,350);
 delay(1000);
 tone(buzzerpin,370);
 delay(1000);
 tone(buzzerpin,415);
 delay(1000);
 tone(buzzerpin,466);
 delay(1000);
 tone(buzzerpin,523);
 delay(1000);
 tone(buzzerpin,554);
 delay(1000);
 noTone(buzzerpin);
 delay(500);
  tone(buzzerpin,554);
 delay(1000);
 tone(buzzerpin,523);
 delay(1000);
 tone(buzzerpin,466);
 delay(1000);
 tone(buzzerpin,415);
 delay(1000);
 tone(buzzerpin,370);
 delay(1000);
 tone(buzzerpin,350);
 delay(1000);
 tone(buzzerpin,311);
 delay(1000);
 tone(buzzerpin,277);
 delay(1000);
 noTone(buzzerpin);
 delay(1000);}