  #include "SoftwareSerial.h"

//Create a new software  serial
SoftwareSerial bluetooth(2, 3); //TX, RX (Bluetooth)

void setup() {
  //Initialize the hardware serial
  Serial.begin(9600);
  Serial.println(F("Type the AT commands:"));

  //Initialize the software serial
  bluetooth.begin(9600);
}

void loop() {
  //Check received a byte from hardware serial
  if (Serial.available()) {
    char r = Serial.read(); //Read and save the byte
    bluetooth.print(r);  //Send the byte to bluetooth by software serial
    Serial.print(r);  //Echo
  }
  //Check received a byte from bluetooth by software serial
  if (bluetooth.available()) {
    char r = bluetooth.read(); //Read and save the byte
    Serial.print(r); //Print the byte to hardware serial
  }
}