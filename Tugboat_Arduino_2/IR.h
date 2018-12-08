#ifndef IR_h
#define IR_h


#include "Arduino.h"

class IR
{
  public:
    IR();
    void init();
    void update();
    void print();

    int pin = 0; // Set default to 0, 
    int x_offset = 0; // In cm
    int y_offset = 0;
    int heading = 0; // In degrees (0 is front, + is right, - is left)
    int data = 0;
    
  private:
    // define number of sensor readings to use for average filter
    int counts = 20;
    int readSensor();

    int raw_data = 0;
   
};

#endif
