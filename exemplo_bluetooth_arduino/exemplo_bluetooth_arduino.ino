#include <SoftwareSerial.h>

SoftwareSerial btSerial(10,11); //rx e tx

#define led1 8

void setup() {
    btSerial.begin(9600);
    pinMode(led1, OUTPUT);

}

void loop() {

    char c = btSerial.read();
    if(c == 'A'){
      digitalWrite(led1, HIGH);
    }
    if(c == 'a'){
      digitalWrite(led1, LOW);
    }
}
