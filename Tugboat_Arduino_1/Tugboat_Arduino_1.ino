/*******************************************************************************
Tugboat Arduino 1: Collects Pixycam data and sends it to next Arduino
Created by: Amy Phung, Everardo Gonzalez, Liz Leadley, Robert Wechsler
December 2018
 * ****************************************************************************/

// We'll use SoftwareSerial to communicate with the XBee, since hardware serial is reserved for between-arduino comms
#include <SoftwareSerial.h>
// This is for cross Arduino comms
#include <EasyTransfer.h>
// Provides SEND_DATA_STRUCTURE for Arduino comms
#include "ArduinoComms1.h"

EasyTransfer PIXY; // transfer object for arduino comms

// creating data structure
SEND_DATA_STRUCTURE pixydata;

// TODO: trim this down if possible
boolean realTimeRunStop = true;   //create a name for real time control loop flag
String command = "stop ";         //create a String object name for operator command string
String loopError = "no error";    //create a String for the real time control loop error system
unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
unsigned long cycleTime = 0;      //create a name for elapsed loop cycle time
const long controlLoopInterval = 100; //create a name for control loop cycle time in milliseconds


void setup() {
  Serial.begin(9600);
  PIXY.begin(details(pixydata), &Serial);
}

void loop() {
  // This is just a sensing arduino so no need for ESTOP

  //------------------------REAL TIME CONTROL LOOP STARTS HERE ---------------------
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval) {
    oldLoopTime = newLoopTime;


    //TODO: Code to collect Pixycam data

    // TODO: Code to process Pixycam data to what we want to send

    // TODO: Send actual pixycam data

    //check and see if a data packet has come in.
    pixydata.timestamp1 = millis();
    PIXY.sendData();
  }

  // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
}
