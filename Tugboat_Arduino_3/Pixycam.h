#ifndef Pixycam_h
#define Pixycam_h

#include "Arduino.h"
#include "Pixy2.h"

class Pixycam
{
  public:
    Pixycam();
    void init();
    void update(); // TODO: actually collect data from pixycam
    void print();

    Pixy2 pixy;

    int narwhal_pos;
    int dot_pos;

    int dotLocation();
    int narwhalLocation();
};

#endif
