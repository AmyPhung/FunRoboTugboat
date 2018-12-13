#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"
#include "IR.h"
#include "IMU.h"
// #include "Sonar.h"

#define IR0PIN 4
#define IR1PIN 4
#define IR2PIN 4
#define IR3PIN 4
// #define IR4PIN 4
// #define IR5PIN 5

// #define SONAR0PIN 11
// #define SONAR1PIN 12
// #define SONAR2PIN 13


class Sensors
{
  public:
    Sensors();
    void init();
    void update();
    void print();

    IR ir_0;
    IR ir_1;
    IR ir_2;
    IR ir_3;
    // IR ir_4;
    // IR ir_5;

    IMU imu;

    // Sonar sonar_0;
    // Sonar sonar_1;
    // Sonar sonar_2;

  private:
};

#endif
