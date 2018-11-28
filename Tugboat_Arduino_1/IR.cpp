#include "IR.h"

IR::IR()
{
}

void IR::init() 
{
  pinMode(pin, INPUT);
}

void IR::print() 
{
  Serial.println("IR Info:");
  Serial.print("IR data: "); Serial.println(data);

}

void IR::update() 
{
  raw_data = readSensor();
  //raw_data = constrain(raw_data, 150, 400);
  data = 19807 * pow(raw_data, -1.0917);
}


// Private Functions:
int IR::readSensor() 
{
  //average sensor reading
  int reading = 0;
  int cumReading = 0;
  int avgReading = 0;

  for (int i = 0; i < counts; i++) {
    reading = analogRead(pin);
    cumReading = reading + cumReading;
    delay(1);
  }

  avgReading = cumReading / counts;
  return avgReading;
};
