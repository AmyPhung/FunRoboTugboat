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

    int pin = 0;
    int x_offset = 0; // In cm
    int y_offset = 0;
    int heading = 0; // In degrees (0 is front, + is right, - is left)
    int data = 0;
    
  private:
    int readSensor();
};

#endif
