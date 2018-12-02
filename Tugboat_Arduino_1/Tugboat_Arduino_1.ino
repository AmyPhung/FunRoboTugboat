/*****************************************************************************************
 * Title: 2018 Fun-Robo Narwhal chasing tugboat (ENGR3390 Think Lab)
 * Description:
   * Original:This structure template contains a SENSE-THINK-ACT flow to allow a robotic
    * tugboat to perform a sequence of meta-behaviors in soft-real-time based on direct text
     * commands from a human operator.
   * This Version:
    * Introduces functions to make code eaiser to read, created a Tugboat library for ease
    * of controlling boat
 * Robot Name: Moby Pix (Team 4)
 * What does code do:
   * sense: Detect range and bearing of target and obstacles with the Pixycam and IR sensors
   * think: Combine bearing arrays for target and obstacles to optimize bearing of the tugboat.
   *        If unobstructed on set bearing, calculate propellor speed proportional to range
   * act:   Set rudder bearing, propellor speed
 * Hardware warnings: Do not wire the Pixycam ICSP arduino I/O pin the wrong way around.
 * Created by Moby Pix (Team 4) November 2018
 * ***************************************************************************************
 */

 /*
  * TODO
  * 
  * test libraries
  * 
  * update documentation for all things (docstrings + actual documentation)
  * wire everything (solder stuff)
  * 
  * put IR, Pixycam, Sonar into separate folder (separate libraries for each sensor, not platform-specific)
  * This folder should only have this file, tugboat, and sensors (all platform-specific)
  * 
  */

// We'll use SoftwareSerial to communicate with the XBee, since hardware serial is reserved for between-arduino comms
#include <SoftwareSerial.h>

#include "Tugboat.h"
#include "Sensors.h"

#define PROPELLORPIN 9;
#define RUDDERPIN 10;

Tugboat tugboat;


// TODO: trim this down if possible
boolean realTimeRunStop = true;   //create a name for real time control loop flag
String command = "stop ";         //create a String object name for operator command string
String loopError = "no error";    //create a String for the real time control loop error system
unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
unsigned long cycleTime = 0;      //create a name for elapsed loop cycle time
const long controlLoopInterval = 1000; //create a name for control loop cycle time in milliseconds


void setup(){
  Serial.begin(9600);
  tugboat.propellorPin = PROPELLORPIN;
  tugboat.rudderPin = RUDDERPIN;
  tugboat.init();
}

void loop() {
  // Get operator input from serial monitor
  command = getOperatorInput();
  tugboat.state = classifyCommand(command);

  if (command == "stop") realTimeRunStop = false;     // skip real time inner loop
  else realTimeRunStop = true;                        // Set loop flag to run = true

  // real-time loop -------------------------------------------------------------
  while(realTimeRunStop == true) {        // if OCU-Stop not commanded, run control loop
    if (checkOperatorInput() == 1){
      break;
    }
    if (newLoopTime - oldLoopTime >= controlLoopInterval) { // if true run flight code
      oldLoopTime = newLoopTime;          // reset time stamp

      tugboat.update(); // also updates sensors
      tugboat.sensors.print();
      // TODO: Put data collection on a different arduino - figure out how this data will come in (thoughts: if pin == -1, use data from serial - else use pin)
      
      // Sensors is a custom library that defines sensor layout on our particular boat
      
      tugboat.move();    
    }
  }
}



// TODO: put these functions somewhere else - it's clutter here
String getOperatorInput()
{
  Serial.println(F("======================================================================================"));
  Serial.println(F("|Robot Behavior-Commands: chase(moves robot), stop(e-stops motors), idle(robot idles)|"));
  Serial.println(F("|                                                                                    |"));
  Serial.println(F("| Please type desired robot behavior in command line at top of this window           |"));
  Serial.println(F("| and then press SEND button.                                                        |"));
  Serial.println(F("======================================================================================"));
  while (Serial.available()==0) {};   // do nothing until operator input typed
  command = Serial.readString();      // read command string
  //command.trim();
  Serial.print(F("| New robot behavior command is: "));    // give command feedback to operator
  Serial.println(command);
  Serial.println(F("| Type 'stop' to stop control loop and wait for new command                          |"));
  Serial.println(F("======================================================================================"));
  return command;
}

int checkOperatorInput() {
  // Check if operator inputs a command during real-time loop execution
  if (Serial.available() > 0) {         // check to see if operator typed at OCU
    realTimeRunStop = false;            // if OCU input typed, stop control loop
    command = Serial.readString();      // read command string to clear buffer
    return 1;                              // break out of real-time loop
  }
  else {realTimeRunStop = true;}        // if no operator input, run real-time loop

  // Real-Time clock control. Check to see if one clock cycle has elapesed before running this control code
  newLoopTime = millis();               // get current Arduino time (50 days till wrap)
  return 0;
}

int checkCycleTime() {
  cycleTime = millis()-newLoopTime;     // calculate loop execution time
  if( cycleTime > controlLoopInterval){
    Serial.println("******************************************");
    Serial.println("error - real time has failed, stop robot!"); // loop took too long to run
    Serial.print(" 1000 ms real-time loop took = ");
    Serial.println(cycleTime);                                   // print loop time
    Serial.println("******************************************");
    return 1;          // break out of real-time inner loop
    }
  else {
    return 0;
  }
}

int classifyCommand(String command) {
  if (command == "stop\n"){
    return 1;
  }
  else if (command == "idle\n"){
    return 2;
  }
  else if (command == "chase\n"){
    return 8;
  }
  else if (command == "search\n"){
    return 9;
  }
  // TODO: add other states
  else {
    Serial.println(command);
    return 0;
  }
}
