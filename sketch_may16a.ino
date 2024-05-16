#include <Servo.h>

// Define pins for ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;

// Define pins for IR sensors
const int irLeftPin = 4;
const int irRightPin = 5;

// Define pins for servo motor
const int servoPin = 9;  // Pin for the servo


// Define pins for L298N motor driver
const int motorLeftForward = 7;
const int motorLeftBackward = 8;
const int motorRightForward = 9;
const int motorRightBackward = 10;

// Define variables for distance and servo angle
int distance = 0;
int servoAngle = 0;

void setup() {
  // Initialize pins as outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irLeftPin, INPUT);
  pinMode(irRightPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);




}

void loop() {
  // Read distance from ultrasonic sensor
  distance = readDistance();

  // Read IR sensor values
  int irLeftValue = digitalRead(irLeftPin);
  int irRightValue = digitalRead(irRightPin);

  // Calculate servo angle based on IR sensor values
  if (irLeftValue == HIGH && irRightValue == LOW) {
    servoAngle = 30; // Turn right
  } else if (irLeftValue == LOW && irRightValue == HIGH) {
    servoAngle = 150; // Turn left
  } else {
    servoAngle = 90; // Move forward
  }

  // Update servo motor angle
  

  // Control DC gear motors based on distance and servo angle
  if (distance < 20) {
    // Stop motors if distance is too close
    stopMotors();
  } else if (servoAngle == 30) {
    // Turn right
    MotorRightForward();
    MotorLeftBackward();
  } else if (servoAngle == 150) {
    // Turn left
    MotorLeftForward();
    MotorRightBackward();
  } else {
    // Move forward
    MotorLeftForward();
    MotorRightForward();
  }

  delay(50);
}

// Function to read distance from ultrasonic sensor
int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Function to stop DC gear motors
void stopMotors() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

// Function to move DC gear motor forward
void MotorLeftForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
}

void MotorRightForward() {
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

// Function to move DC gear motor backward
void MotorLeftBackward() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
}

void MotorRightBackward() {
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
}