#include "Arduino.h"
#include "Sonar.h"

Sonar::Sonar()
{
}


void Sonar::init()
{
  pinMode(pin, INPUT); // Sets the echoPin as an Input
}

void Sonar::update()
{
  data = readSensor();
}
void Sonar::print()
{
  Serial.println("Sonar Info:");
  Serial.print("Sonar data: "); Serial.println(data);
}

int Sonar::readSensor()
{
  int distance = pulseIn(pin, HIGH) / 10;
  return distance;
}
