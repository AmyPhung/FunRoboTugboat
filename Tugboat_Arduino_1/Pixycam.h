#ifndef Pixycam_h
#define Pixycam_h

#include "Arduino.h"
#include "Pixy.h"

class Pixycam
{
  public:
    Pixycam();
    void init();
    void update(); // TODO: actually collect data from pixycam
    void print();

    Pixy pixy;
    int x_offset = 0; // In cm
    int y_offset = 0;
    int heading = 0; // In degrees (0 is front, + is right, - is left)
    int data = 0; // TODO: make this not an int once data is aquired
    
  private:
};
    
#endif
