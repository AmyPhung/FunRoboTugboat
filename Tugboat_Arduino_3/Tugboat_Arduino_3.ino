/**
  * @description Tugboat Arduino 3: Uses collected data from other arduinos
  to control tugboat
  * @author Amy Phung, Everardo Gonzalez, Liz Leadley, Robert Wechsler
  * @date December 2018
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
  XBee.begin(9600); //Xbee comms
  Serial.begin(9600); // Serial comms for printing to monitor when offshore
  SENSING.begin(details(sensedata), &Serial); //arduino comms
}

void loop() {

  tugboat.velocity = 0;
  // Get operator input from serial monitor
  XBee.write("Input Command\n");
  command = getOperatorInput();
  tugboat.state = classifyCommand(command);
  if (tugboat.state == 0) { // For missions, need a second command to indicate which
    XBee.write("Input Mission\n");
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


      // Serial.println("-------------");
      // Serial.println(tugboat.velocity);
      // Serial.println(tugboat.heading);
      if (tugboat.heading == 45) {XBee.write("Bang!\n");}
      //int ir_diff = tugboat.ir_0-tugboat.ir_1;
//      int ir_avg = (tugboat.ir_0+tugboat.ir_1)/2;
//      Serial.print("ir_avg: "); Serial.println(ir_avg);

//      if (ir_diff < 0){XBee.write("<0\n");}
//      else if (ir_diff == 0){XBee.write("0\n");}
//      else if (ir_diff == 1){XBee.write("1\n");}
//      else if (ir_diff == 2){XBee.write("2\n");}
//      else if (ir_diff == 3){XBee.write("3\n");}
//      else if (ir_diff == 4){XBee.write("4\n");}
//      else if (ir_diff == 5){XBee.write("5\n");}
//      else if (ir_diff == 6){XBee.write("6\n");}
//      else if (ir_diff == 7){XBee.write("7\n");}


//      Serial.print("ir diff: ");Serial.println(ir_diff);

      tugboat.move(); // Moves boat based on current heading and velocity cmd
    } // ----------------------------- REAL TIME CONTROL LOOP ENDS HERE --------------------
  }
}



// TODO: put these functions somewhere else - it's clutter here
String getOperatorInput()
{
  while (XBee.available() == 0) {}; // do nothing until operator input typed
  command = XBee.read();      // read command string
  Serial.println(command);
  XBee.write("Command Received\n");
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
    XBee.write("w");
    tugboat.velocity = 20;
    return 10;
  }
  else if (command == "97") { // Keypress: A
    XBee.write("a");
    tugboat.heading += -10;
    return 11;
  }
  else if (command == "115") { // Keypress: S
    XBee.write("s");
    tugboat.velocity = 0;
    return 12;
  }
  else if (command == "100") { // Keypress: D
    XBee.write("d");
    tugboat.heading += +10;
    return 13;
  }
  else if (command = "120") { // Keypress: X
    XBee.write("x");
    tugboat.velocity = -25;
    return 14;
  }
  // TODO: add other states
  else {
    //    XBee.write(command);
    return 1;
  }
}
