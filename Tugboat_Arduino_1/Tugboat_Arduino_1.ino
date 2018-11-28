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
  */

#include "IR.h"
#include "Sonar.h"
#include "Pixycam.h"


#define IR0PIN 0
#define IR1PIN 1
#define IR2PIN 2
#define IR3PIN 3
#define IR4PIN 4
#define IR5PIN 5

#define SONAR0TRIGPIN 13
#define SONAR0ECHOPIN 0

//IR ir_0;
//IR ir_1;
//IR ir_2;
//IR ir_3;
//IR ir_4;
//IR ir_5;

Sonar sonar_0;


void setup(){
  Serial.begin(9600);
  //ir_0.init();
  //ir_1.init();
  //ir_2.init();
  //ir_3.init();
  //ir_4.init();
  //ir_5.init();

  sonar_0.init();
  sonar_0.trigPin = SONAR0TRIGPIN;
  sonar_0.echoPin = SONAR0ECHOPIN;
}

void loop() {
  //ir_0.update();
  //ir_0.print();

  sonar_0.update();
  sonar_0.print();
}

/*
#define IR1_PIN 0
#define IR2_PIN 1
#define IR3_PIN 2
#define IR4_PIN 3
#define IR5_PIN 4
#define IR5_PIN 4


#include "Tugboat.h"

Tugboat boat;

//========================================================================================
// Create and initialize global variables, objects and constants (containers for all data)
//========================================================================================
boolean realTimeRunStop = true;   //create a name for real time control loop flag
String command = "stop ";         //create a String object name for operator command string
String loopError = "no error";    //create a String for the real time control loop error system
unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
unsigned long cycleTime = 0;      //create a name for elapsed loop cycle time
const long controlLoopInterval = 1000; //create a name for control loop cycle time in milliseconds

//=========================================================================================
// Startup code to configure robot and pretest all robot functionality (to run once)
// and code to setup robot mission for launch.
//=========================================================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  boat.init();

}
//=============================================================================
// Flight code to run continuously until robot is powered down
//=============================================================================
void loop() {
  // Get operator input from serial monitor
  command = getOperatorInput();

  if (command == "stop") realTimeRunStop = false;     // skip real time inner loop
  else realTimeRunStop = true;                        // Set loop flag to run = true

  // real-time loop -------------------------------------------------------------
  while(realTimeRunStop == true) {        // if OCU-Stop not commanded, run control loop
    if (checkOperatorInput() == 1){
      break;
    }
    if (newLoopTime - oldLoopTime >= controlLoopInterval) { // if true run flight code
      oldLoopTime = newLoopTime;          // reset time stamp

      // SENSE-THINK-ACT =============================================================================
      // SENSE -------------------------------------------------------------
      boat.updatePixy(); // Data saved in boat.pixyDataArray (int [NUM_PTS] defined in Tugboat.h)
      boat.updateIR(); // Data saved in boat.irDataArray(int [NUM_PTS] defined in Tugboat.h)
      // THINK -------------------------------------------------------------
      boat.arbiter();
      boat.processData(); // Uses data arrays to update irDecisionArray, pixyDecisionArray
      boat.state = commandState(); // Uses command to update boat state
      boat.stateController(); // Uses decision arrays and current state to run motors
      // ACT ---------------------------------------------------------------
      boat.setPropSpeed(boat.cmd_velocity);
      boat.setHeading(boat.cmd_heading);
      // END SENSE-THINK-ACT ==========================================================================

      // Check to see if all code ran successfully in one real-time increment
      if (checkCycleTime() == 1){
        break;
      }
    } // end flight code
  } // end real-time loop
} // end main loop


//========================================================================================
// Functions for flight code
//========================================================================================
// OPERATOR INPUT FUNCTIONS ------------------------------------------------------------------------------
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

// STATE CONTROLLER FUNCTIONS ------------------------------------------------------------------------------

int commandState(){ // Takes command, returns int for state for switch
  if (command == "stop\n"){
    return 1;
  }
  else if (command == "idle\n"){
    return 2;
  }
  else if (command == "chase\n"){
    return 3;
  }
  else if (command == "search\n"){
    return 4;
  }
  // TODO: add wall follow, figure 8, dock
  else {
    Serial.println(command);
    return 0;
  }
}
*/
