/*****************************************************************************************
   Title: 2018 Fun-Robo Narwhal chasing tugboat (ENGR3390 Think Lab)
   Description:
     Original:This structure template contains a SENSE-THINK-ACT flow to allow a robotic
      tugboat to perform a sequence of meta-behaviors in soft-real-time based on direct text
       commands from a human operator.
     This Version:
      Introduces functions to make code eaiser to read, created a Tugboat library for ease
      of controlling boat
   Robot Name: Moby Pix (Team 4)
   What does code do:
     sense: Detect range and bearing of target and obstacles with the Pixycam and IR sensors
     think: Combine bearing arrays for target and obstacles to optimize bearing of the tugboat.
            If unobstructed on set bearing, calculate propellor speed proportional to range
     act:   Set rudder bearing, propellor speed
   Hardware warnings: Do not wire the Pixycam ICSP arduino I/O pin the wrong way around.
   Created by Moby Pix (Team 4) November 2018
 * ***************************************************************************************
*/

/*
   TODO

   test libraries

   update documentation for all things (docstrings + actual documentation)
   wire everything (solder stuff)

   put IR, Pixycam, Sonar into separate folder (separate libraries for each sensor, not platform-specific)
   This folder should only have this file, tugboat, and sensors (all platform-specific)

*/

// We'll use SoftwareSerial to communicate with the XBee, since hardware serial is reserved for between-arduino comms
#include <SoftwareSerial.h>

// This is for cross Arduino comms
#include <EasyTransfer.h>

#include "Sensors.h"

EasyTransfer PIXY; // transfer object for arduino comms

// creating data structure to send to Arudino 2
struct SEND_DATA_STRUCTURE
{
  // variable definitions go here
  // MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  unsigned long timestamp1;
//  Sensors sensors;
};

// creating data structure
struct SEND_DATA_STRUCTURE pixydata;

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

