#include "Arduino.h"
#include "Sonar.h"

Sonar::Sonar()
{ 
}


void Sonar::init()
{
  //pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void Sonar::update()
{
  //average sensor reading
  int reading = 0;
  int cumReading = 0;
  int avgReading = 0;

  for (int i = 0; i < counts; i++) {
    reading = readSensor();
    cumReading = reading + cumReading;
    delay(1);
  }
  data = cumReading; // in mm
}
void Sonar::print()
{
  Serial.println("Sonar Info:");
  Serial.print("Sonar data: "); Serial.println(data);
}

int Sonar::readSensor()
{
  // Clears the trigPin
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;
  return distance;
}
