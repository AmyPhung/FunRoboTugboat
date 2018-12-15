#ifndef Pixycam_h
#define Pixycam_h

#include "Arduino.h"
#include "Pixy2.h"

class Pixycam
{
  public:
    Pixycam();
    void init();
    void update();
    void print();

    Pixy2 pixy;

    int narwhal_pos;
    int dot_pos;

    int dotLocation();
    int narwhalLocation();
};

#endif
