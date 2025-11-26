#include <BnrOneAPlus.h>  // Bot'n Roll ONE A+ library
#include <SPI.h>          // SPI communication library required by BnrOneAPlus.cpp
//#include <Wire.h>
//#include <VL53L0X.h>
#include <Ultrasonic.h>

BnrOneAPlus one;  // object to control the Bot'n Roll ONE A
//VL53L0X sensor;

// Constants definition
#define SSPIN 2                 // Slave Select (SS) pin for SPI communication
#define MINIMUM_BATTERY_V 10.5  // safety voltage for discharging the battery
#define OBSTACLE_DISTANCE_CM 15 // Minimum distance to consider an obstacle
#define BLACK_LINE_THRESHOLD 870 // Threshold for detecting black line
#define BLACK_LINE_THRESHOLD_C 950 // Threshold for detecting black line

// Configuração do sensor
#define TRIGGER_PIN A2
#define ECHO_PIN    A3

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

// Pin definitions
const int RIGHT_IR_PIN = A0;
const int LEFT_IR_PIN = A1;
const int CENTER_IR_PIN = A4;

// ==========================================================================
// Movement Functions
// ==========================================================================

void moveForward(const int speedR, const int speedL, const int time) {
  one.lcd2("    Forward   ");
  int r = -1 * speedR;
  int l = -1 * speedL;
  one.move(l, r);
  delay(time);
}

void moveBackward(const int speed, const int time) {
  one.lcd2("   Backwards  ");
  one.move(speed, speed);
  delay(time);
}

void rotateLeft(const int speed, const int time) {
  one.lcd2("  Rotate Left ");
  one.move(speed, -speed);
  delay(time);
}

void rotateRight(const int speed, const int time) {
  one.lcd2(" Rotate Right ");
  one.move(-speed, speed);
  delay(time);
}

void stopRobot(const int time) {
  one.lcd2("     Stop     ");
  one.stop();
  delay(time);
}

void brake(const int torque, const int time) {
  one.lcd2("     Brake    ");
  one.brake(torque, torque);
  delay(time);
}

int readRightIRSensor() {
  return analogRead(RIGHT_IR_PIN);
}

int readLeftIRSensor() {
  return analogRead(LEFT_IR_PIN);
}

int readCenterIRSensor() {
  return analogRead(CENTER_IR_PIN);
}

/*float readLaserDistance() {
  return sensor.readRangeContinuousMillimeters() / 10.0; // Convert to cm
}*/

float readUltrasonicDistance(){
  return ultrasonic.read();
}

bool isWhiteLine(int sensorValue) {
  return sensorValue < BLACK_LINE_THRESHOLD;
}

bool isWhiteLineC(int sensorValue) {
  return sensorValue < BLACK_LINE_THRESHOLD_C;
}

bool isPathClear(float distance) {
  // LÓGICA INVERSA: retorna true quando NÃO há obstáculo próximo
  return distance >= OBSTACLE_DISTANCE_CM;
}

void followLineBackwards(int rightValue, int leftValue, int centerValue) {
  if(isWhiteLineC(centerValue)){
    moveBackward(30, 400);
  }
  else if (isWhiteLine(rightValue)) {
    // Right sensor detected black line - adjust left
    moveForward(-40, 40, 70); // Turn slightly left
  } else if (isWhiteLine(leftValue)) {
    // Left sensor detected black line - adjust right
    moveForward(40, -40, 70); // Turn slightly right
  } else {
    // Both sensors on white - move straight backwards
    moveForward(30, 30, 100);
  }
}

bool avoidLeft = true;
void avoidObstacleLeft() {
  one.lcd2("AVOID LEFT!!");

  // Back up first
  moveBackward(30, 400);
  //moveBackward(30, 200);

  // Turn LEFT to avoid obstacle (lógica inversa)
  //moveForward(30, 50, 100);
  if (avoidLeft) {
    rotateLeft(30, 100);
  } else {
    rotateRight(30, 100);
  }
  avoidLeft = !avoidLeft;
  // rotateRight(50, 200);
  // Slight right correction
  //moveForward(50, 10, 100);
}

void moveWhenClear() {
  one.lcd2("PATH CLEAR - MOVE");
  // Move forward when path is clear
  moveForward(30, 30, 100);
}

void lineFollowingRoutine() {
  int rightValue = readRightIRSensor();
  int leftValue = readLeftIRSensor();
  int centerValue = readCenterIRSensor();
  //float distance = readLaserDistance();
  float distance = readUltrasonicDistance();

  // Debug information
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(", Right: ");
  Serial.print(rightValue);
  Serial.print(", Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LÓGICA INVERSA: Robô só se move quando NÃO detecta obstáculo
  if (isPathClear(distance)) {
    // Caminho livre - robô pode se mover
    moveWhenClear();
  } else {
    // Obstáculo detectado - executar manobra de evasão para ESQUERDA
    avoidObstacleLeft();
  }

  // Sempre executa o seguimento de linha (ajuste fino)
  followLineBackwards(rightValue, leftValue, centerValue);
}

void setup() {
  one.spiConnect(SSPIN);  // Start SPI communication
  one.stop();             // Stop motors initially

  pinMode(RIGHT_IR_PIN, INPUT);
  pinMode(LEFT_IR_PIN, INPUT);

  Serial.begin(9600);     // Serial communication with Raspberry Pi

  /*Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous(); // Start continuous measurement*/

  //delay(1000); // Initialization delay

  one.lcd1("Line Follower");
  one.lcd2("   TEAM TWO   ");
  /*while(1){
    //int rightValue = readRightIRSensor();
    int centerValue = readCenterIRSensor();
    //float distance = readLaserDistance();
    if(one.readButton() == 1){
      break;
    }else{
      one.lcd1(centerValue);
      //one.lcd2(rightValue);
      delay(100);
    }
  }*/
  // moveForward(30, 30, 1000);
  /*moveForward(-40,40,80);
  one.stop();*/
  // delay(500);
  one.lcd1(one.readBattery());
  // delay(500);
  // delay(2000);
  moveForward(30, 30, 1000);
}

void loop() {
  lineFollowingRoutine();
  stopRobot(50); // Brief stop between cycles for stability
}