#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include "NineAxesMotion.h" // Note: conflicts with SoftwareSerial

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
