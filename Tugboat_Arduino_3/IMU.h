#ifndef IMU_h
#define IMU_h
//Note: conflicts with softwareserial, cannot be on arduino 2


#include "Arduino.h"
#include "NineAxesMotion.h"
//#include <Wire.h>

class IMU
{
  public:
    IMU();
    void init();
    void update();

    NineAxesMotion imu;

    int data = 0; // Boat Heading in degrees

  private:
};

#endif
