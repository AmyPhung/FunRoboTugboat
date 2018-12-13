/*
ArduinoComms2.h

Includes data structure for communication between Arduino 1, 2 and 3
*/

#ifndef ArduinoComms2_h
#define ArduinoComms2_h

// Data structure to recieve from Arudino 1 - MUST BE EXACTLY THE SAME ON ARDUINO 1
struct RECEIVE_DATA_STRUCTURE
{
  unsigned long timestamp1;

  int narwhal_pos = 10000;
  int dot_pos = 10000;
};

// Data structure to send to Arudino 3 - MUST BE EXACTLY THE SAME ON ARDUINO 3
struct SEND_DATA_STRUCTURE
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
