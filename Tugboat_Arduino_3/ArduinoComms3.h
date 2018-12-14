/*
ArduinoComms3.h

Includes data structure for communication between Arduino 2 and 3
*/

#ifndef ArduinoComms3_h
#define ArduinoComms3_h

// Data structure to recieve from Arudino 2 - MUST BE EXACTLY THE SAME ON ARDUINO 2
struct RECIEVE_DATA_STRUCTURE
{
  unsigned long timestamp1;
  unsigned long timestamp2;

  int sonar_0_data = 0;
  int sonar_1_data = 0;
  int sonar_2_data = 0;

  int narwhal_pos = 10000;
  int dot_pos = 10000;
};

#endif
