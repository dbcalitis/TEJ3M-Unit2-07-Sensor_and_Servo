// ------------------------------------------ //
// Arduino Ultrasonic Sensor HC-SR04 and Servo
// It moves the servo if the sensor detects a distance less than 50cm 
// Created by: Daria Bernice Calitis
// Created on: April 2022
// ------------------------------------------ //

#include <Servo.h>

Servo servo;

int trigPin = 3;
int echoPin = 2;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int angle; // variable for the angle of the servo
bool clockwise = true; // determines the direction of servo's movement
int maxAngle = 180;
int maxDistance = 50;
int interval = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  
  servo.attach(4);
  servo.write(0); // changes the angle to zero
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // if it reaches the maximum angle it will rotate backwards 
  if (angle == maxAngle) {
    clockwise = false;
  // if it reaches the minimum angle it will rotate the other way
  } else if (angle == 0) {
    clockwise = true;
  }
  // The servo will only rotate if the distance is below 50cm
  if (distance < maxDistance) {
    if (clockwise) {
      	angle++;
    	servo.write(angle);
    	delay(interval);
  	} else {
      angle--;
      servo.write(angle);
  	  delay(interval);
  	}
  }
  Serial.print("Angle: ");
  Serial.println(angle);
}
