/**
  * @description Tugboat Arduino 3: Uses collected data from other arduinos
  to control tugboat
  * @author Amy Phung, Everardo Gonzalez, Liz Leadley, Robert Wechsler
  * @date December 2018
  */

// We'll use SoftwareSerial to communicate with the XBee, since hardware serial is reserved for between-arduino comms
// #include <SoftwareSerial.h>
// This is for cross Arduino comms
#include <EasyTransfer.h>
// Provides RECIEVE_DATA_STRUCTURE for Arduino comms
#include "ArduinoComms3.h"

// SoftwareSerial XBee(2, 3); // RX, TX

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
const long controlLoopInterval = 50; //create a name for control loop cycle time in milliseconds
unsigned long timestamp1 = 0; // timestamp from first Arduino
unsigned long timestamp2 = 0; // timestamp from second Arduino
unsigned long timestamp3 = 0; // timestamp for third arduino
unsigned lag1 = 0; //millisecond lag from Arduino1 to Arduino 2
unsigned lag2 = 0; //millisecond lag from Arduino2 to Arduino 3

// controller stuff
int ctr_count = 0;
int full_cycle = 30; // full motor pulse cycle - 3 seconds
float pulse_ratio = 0.125; // fraction of time motors are on (put a decimal, doesn't like fractions)
bool mtr_pulse = false;


// creating data structure
RECIEVE_DATA_STRUCTURE sensedata;

void setup() {
  // beloved tugboat object
  tugboat.propellorPin = PROPELLORPIN;
  tugboat.rudderPin = RUDDERPIN;
  tugboat.init();
  Serial1.begin(9600); //Xbee comms
  Serial.begin(9600); // Serial comms for printing to monitor when offshore
  SENSING.begin(details(sensedata), &Serial); //arduino comms
}

void loop() {

  tugboat.velocity = 0;
  // Get operator input from serial monitor
  Serial1.write("Input Command\n");
  command = getOperatorInput();
  tugboat.state = classifyCommand(command);
  if (tugboat.state == 0) { // For missions, need a second command to indicate which
    Serial1.write("Input Mission\n");
    String mission_cmd = getOperatorInput(); // Get string representing mission command
    tugboat.mission_state = tugboat.classifyMission(mission_cmd); // Convert string to int representation
  }

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
      SENSING.receiveData();

      // Update heading and velocity based on sensors and state
      tugboat.update(sensedata);
      // Print sensor data for debugging
      tugboat.sensors.print();
      // Moves boat based on current heading and velocity cmd
      tugboat.move();
    } // ----------------------------- REAL TIME CONTROL LOOP ENDS HERE --------------------
  }
}


// TODO: put these functions somewhere else - it's clutter here
String getOperatorInput()
{
  while (Serial1.available() == 0) {}; // do nothing until operator input typed
  command = Serial1.read();      // read command string
  Serial.println(command);
  Serial1.write("Command Received\n");
  return command;
}

int checkOperatorInput() {
  // Check if operator inputs a command during real-time loop execution
  if (Serial1.available() > 0) {         // check to see if operator typed at OCU
    realTimeRunStop = false;            // if OCU input typed, stop control loop
    command = Serial1.read();      // read command string to clear buffer
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
    Serial1.write("******************************************\n");
    Serial1.write("error - real time has failed, stop robot!\n"); // loop took too long to run
    Serial1.write(" 1000 ms real-time loop took = \n");
    Serial1.write(cycleTime);                                   // print loop time
    Serial1.write("******************************************\n");
    return 1;          // break out of real-time inner loop
  }
  else {
    return 0;
  }
}

int classifyCommand(String command) {
  // Since command is a string, we compare it to the ASCII code, not the int value
  // e.g. ASCII for "1" is 49
  if (command == "48") { //0
    return 0;
  }
  else if (command == "49") { //1
    return 1; //stopped
  }
  else if (command == "50") { //2
    return 2; //idling
  }
  else if (command == "51") { //3
    return 3; // obstacle avoidance
  }
  else if (command == "52") { //4
    return 4; //left wall follow
  }
  else if (command == "53") { //5
    return 5; // right wall follow
  }
  else if (command == "54") { //6
    return 6; // left circle
  }
  else if (command == "55") {
    return 7; // right circle
  }
  else if (command == "56") {
    return 8; //chase
  }
  else if (command == "57") {
    return 9; // search
  }

  // TELEOPERATED CONTROL
  else if (command == "119") { // Keypress: W
    Serial1.write("w");
    tugboat.velocity = 20;
    return 10;
  }
  else if (command == "97") { // Keypress: A
    Serial1.write("a");
    tugboat.heading += -10;
    return 11;
  }
  else if (command == "115") { // Keypress: S
    Serial1.write("s");
    tugboat.velocity = 0;
    return 12;
  }
  else if (command == "100") { // Keypress: D
    Serial1.write("d");
    tugboat.heading += +10;
    return 13;
  }
  else if (command = "120") { // Keypress: X
    Serial1.write("x");
    tugboat.velocity = -25;
    return 14;
  }
  // TODO: add other states
  else {
    //    Serial1.write(command);
    return 1;
  }
}
