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
// Provides RECIEVE_DATA_STRUCTURE for Arduino comms
#include "ArduinoComms3.h"

SoftwareSerial XBee(2, 3); // RX, TX

#include "Tugboat.h"

#define PROPELLORPIN 9;
#define RUDDERPIN 10;

Tugboat tugboat;

EasyTransfer SENSING; // arduino comms from Arduino 2


// TODO: trim this down if possible
boolean realTimeRunStop = true;   //create a name for real time control loop flag
String command = "stop ";         //create a String object name for operator command string
String loopError = "no error";    //create a String for the real time control loop error system
unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
unsigned long cycleTime = 0;      //create a name for elapsed loop cycle time
const long controlLoopInterval = 1000; //create a name for control loop cycle time in milliseconds
unsigned long timestamp1 = 0; // timestamp from first Arduino
unsigned long timestamp2 = 0; // timestamp from second Arduino
unsigned long timestamp3 = 0; // timestamp for third arduino
unsigned lag1 = 0; //millisecond lag from Arduino1 to Arduino 2
unsigned lag2 = 0; //millisecond lag from Arduino2 to Arduino 3

// creating data structure
RECIEVE_DATA_STRUCTURE sensedata;

void setup() {
  // beloved tugboat object
  tugboat.propellorPin = PROPELLORPIN;
  tugboat.rudderPin = RUDDERPIN;
  tugboat.init();
  XBee.begin(9600); //Xbee comms
  Serial.begin(9600); // Serial comms, might not be needed
  SENSING.begin(details(sensedata), &Serial); //arduino comms
}

void loop() {
  // Get operator input from serial monitor
  command = getOperatorInput();
  tugboat.state = classifyCommand(command);

  if (command == "stop") realTimeRunStop = false;     // skip real time inner loop
  else realTimeRunStop = true;                        // Set loop flag to run = true

  // real-time loop -------------------------------------------------------------
  while (realTimeRunStop == true) {       // if OCU-Stop not commanded, run control loop
    if (checkOperatorInput() == 1) {
      break;
    }
    // ------------------------------------ REAL TIME LOOP CONTROL STARTS HERE ------------------
    if (newLoopTime - oldLoopTime >= controlLoopInterval) { // if true run flight code
      oldLoopTime = newLoopTime;          // reset time stamp

      //SENSE
      // get sensor data from Arduino 2
      XBee.write("Beep! \n");
      if (SENSING.receiveData()) {  // this line updates sensor data
        XBee.write("I got data!");  // boat tells us she received data
        // this code below does some things with timing. Currently not functional
        // because arudino restarts whenever you plug your laptop into it
        //        timestamp3 = millis(); //record when data was recieved
        //        timestamp1 = sensedata.timestamp1;
        //        timestamp2 = sensedata.timestamp2;
        //        lag1 = timestamp2 - timestamp1; // record lag from 1 to 2
        //        lag2 = timestamp3 - timestamp2; //record lag from 2 to 3
        Serial.println(sensedata.ir_0_data);
      }
      tugboat.update(sensedata.ir_0_data, sensedata.ir_1_data, sensedata.ir_2_data,
                     sensedata.ir_3_data, sensedata.ir_4_data, sensedata.ir_5_data,
                     sensedata.sonar_0_data, sensedata.sonar_1_data, sensedata.sonar_2_data);

      // TODO: Put data collection on a different arduino - figure out how this data will come in (thoughts: if pin == -1, use data from serial - else use pin)

      // Sensors is a custom library that defines sensor layout on our particular boat
      //tugboat.velocity = 50;

      tugboat.move();
    } // ----------------------------- REAL TIME CONTROL LOOP ENDS HERE --------------------
  }
}



// TODO: put these functions somewhere else - it's clutter here
String getOperatorInput()
{
  XBee.write("---------------------------\n 0 for stop, 1 for idle, 2 for chase \n");
  while (XBee.available() == 0) {}; // do nothing until operator input typed
  command = XBee.read();      // read command string
  XBee.write("\nCommand Received\n");
  return command;
}

int checkOperatorInput() {
  // Check if operator inputs a command during real-time loop execution
  if (XBee.available() > 0) {         // check to see if operator typed at OCU
    realTimeRunStop = false;            // if OCU input typed, stop control loop
    command = XBee.read();      // read command string to clear buffer
    return 1;                              // break out of real-time loop
  }
  else {
    realTimeRunStop = true; // if no operator input, run real-time loop
  }

  // Real-Time clock control. Check to see if one clock cycle has elapesed before running this control code
  newLoopTime = millis();               // get current Arduino time (50 days till wrap)
  return 0;
}

int checkCycleTime() {
  cycleTime = millis() - newLoopTime;   // calculate loop execution time
  if ( cycleTime > controlLoopInterval) {
    XBee.write("******************************************\n");
    XBee.write("error - real time has failed, stop robot!\n"); // loop took too long to run
    XBee.write(" 1000 ms real-time loop took = \n");
    XBee.write(cycleTime);                                   // print loop time
    XBee.write("******************************************\n");
    return 1;          // break out of real-time inner loop
  }
  else {
    return 0;
  }
}

int classifyCommand(String command) {
  if (command == "0") {
    return 1;
  }
  else if (command == "1") {
    return 2;
  }
  else if (command == "2") {
    return 8;
  }
  else if (command == "search\n") {
    return 9;
  }
  // TODO: add other states
  else {
    //    XBee.write(command);
    return 0;
  }
}
