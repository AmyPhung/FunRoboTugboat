#ifndef Pixycam_h
#define Pixycam_h

#include "Arduino.h"
#include "Pixy.h"

class Pixycam
{
  public:
    Pixycam();
    void getTargetBearing(int bearing[],int len, Pixy pixy,int blocks, int range, int curvebroadness);
    int getTargetRange(Pixy pixy, int blocks);
  private:
};
    
#endif
