#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"
#include "IR.h"
#include "Sonar.h"
#include "Pixycam.h"

#define IR0PIN 0
#define IR1PIN 1
#define IR2PIN 2
#define IR3PIN 3
#define IR4PIN 4
#define IR5PIN 5

#define SONAR0PIN 11
#define SONAR1PIN 12
#define SONAR2PIN 13


class Sensors
{
  public:
    Sensors();
    void init();
    void update(int ir_0_rawdata, int ir_1_rawdata, int ir_2_rawdata, int ir_3_rawdata, int ir_4_rawdata, int ir_5_rawdata, int sonar_0_rawdata, int sonar_1_rawdata, int sonar_2_rawdata);
    void print();

    IR ir_0;
    IR ir_1;
    IR ir_2;
    IR ir_3;
    IR ir_4;
    IR ir_5;

    Sonar sonar_0;
    Sonar sonar_1;
    Sonar sonar_2;

    Pixycam pixycam;
  
  private:
};
    
#endif
