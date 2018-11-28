#ifndef Sonar_h
#define Sonar_h

#include "Arduino.h"

class Sonar
{
  public:
    Sonar();
    void init();
    void update();
    void print();

    //int trigPin = 0; // Set default to 0  For now, we won't use this - may need if interference becomes an issue
    int echoPin = 0;
    int x_offset = 0; // In cm
    int y_offset = 0;
    int heading = 0; // In degrees (0 is front, + is right, - is left)
    int data = 0;
    
  private:
    long duration;
    int distance;
    int counts = 1;     // define number of sensor readings to use for average filter
    int readSensor();
};

#endif
