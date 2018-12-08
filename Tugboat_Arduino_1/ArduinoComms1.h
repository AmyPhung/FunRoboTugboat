/*
ArduinoComms1.h

Includes data structure for communication between Arduino 1 and 2
*/

#ifndef ArduinoComms1_h
#define ArduinoComms1_h

// Data structure to send to Arudino 2 - MUST BE EXACTLY THE SAME ON ARDUINO 2
struct SEND_DATA_STRUCTURE
{
  unsigned long timestamp1;
};

#endif
