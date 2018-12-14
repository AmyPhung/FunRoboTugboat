#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"
#include "IR.h"
#include "IMU.h"
#include "ArduinoComms3.h" // Needed for RECEIVE_DATA_STRUCTURE

#define IR0PIN 6
#define IR1PIN 7
#define IR2PIN 8
#define IR3PIN 9
#define IR4PIN 10
#define IR5PIN 11

class Sensors
{
  public:
    Sensors();
    void init();
    void update(RECIEVE_DATA_STRUCTURE sensedata);
    void print();

    IR ir_0;
    IR ir_1;
    IR ir_2;
    IR ir_3;
    IR ir_4;
    IR ir_5;

    IMU imu;

    // Store data from other arduinos
    int narwhal_pos = 0;
    int dot_pos = 0;
    int sonar_0_data = 0;
    int sonar_1_data = 0;
    int sonar_2_data = 0;

  private:
};

#endif
