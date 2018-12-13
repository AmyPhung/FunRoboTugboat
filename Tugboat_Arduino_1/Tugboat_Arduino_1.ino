/**
  * Tugboat Arduino 1: Collects Pixycam data and sends it to next Arduino
  * @author Amy Phung, Everardo Gonzalez, Liz Leadley, Robert Wechsler
  * @date December 2018
  */

// We'll use SoftwareSerial to communicate with the XBee, since hardware serial is reserved for between-arduino comms
#include <SoftwareSerial.h>
// This is for cross Arduino comms
#include <EasyTransfer.h>
// Provides SEND_DATA_STRUCTURE for Arduino comms
#include "ArduinoComms1.h"
// Custom library for detecting narwhal and dot
#include "Pixycam.h"

Pixycam pixycam; // Pixycam object for detecting narwhal

EasyTransfer PIXY; // transfer object for arduino comms
SEND_DATA_STRUCTURE pixydata; // creating data structure

unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
const long controlLoopInterval = 100; //create a name for control loop cycle time in milliseconds

void setup() {
  Serial.begin(9600);
  pixycam.init();
  PIXY.begin(details(pixydata), &Serial);
}

void loop() {
  // This is just a sensing arduino so no need for ESTOP

  //------------------------REAL TIME CONTROL LOOP STARTS HERE ---------------------
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval) {
    oldLoopTime = newLoopTime;

    pixydata.narwhal_pos = pixycam.narwhal_pos;
    pixydata.dot_pos = pixycam.dot_pos;

    //check and see if a data packet has come in.
    pixydata.timestamp1 = millis();
    PIXY.sendData();
  }
  // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
}
