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

#include <EasyTransfer.h> // arduino comms
#include "Sensors.h" //sensors
#include "Xbee2.h" 

Sensors sensors;
EasyTransfer PIXY; // arduino comms from Arrduino 1
EasyTransfer SENSORS; // arduino comms to Arduino 3

//creating data structure
RECEIVE_DATA_STRUCTURE pixydata;

//creating data structure send
SEND_DATA_STRUCTURE sensedata;

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

  // arduino comms
  PIXY.begin(details(pixydata), &Serial);
  SENSORS.begin(details(sensedata), &Serial);

  // for sensing
  sensors.init();
}

void loop() {
  // This is just a sensing arduino so no need for ESTOP

  //------------------------REAL TIME CONTROL LOOP STARTS HERE ---------------------
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval) {
    oldLoopTime = newLoopTime;

    // get Pixydata from Arduino 1
    if (PIXY.receiveData()) {
      // update sensedata with new pixy data
      sensedata.timestamp1 = pixydata.timestamp1;
    }

    sensedata.timestamp2 = millis();

    // THIS IS FOR ACTUALLY COLLECTING DATA AND WON'T BE USED UNTIL ARDUINO COMMS IS SUCCESSFUL
    sensors.update();

    sensedata.ir_0_data =  sensors.ir_0.data;
    sensedata.ir_1_data =  sensors.ir_1.data;
    sensedata.ir_2_data =  sensors.ir_2.data;
    sensedata.ir_3_data =  sensors.ir_3.data;
    sensedata.ir_4_data =  sensors.ir_4.data;
    sensedata.ir_5_data =  sensors.ir_5.data;

    sensedata.sonar_0_data = sensors.sonar_0.data;
    sensedata.sonar_1_data = sensors.sonar_1.data;
    sensedata.sonar_2_data = sensors.sonar_2.data;

//    Serial.println("------------------------------------------------------------------");
//    Serial.print(sensedata.ir_0_data); Serial.print(" - "); Serial.print(sensedata.ir_1_data); Serial.print(" - ");
//    Serial.print(sensedata.ir_2_data); Serial.print(" - "); Serial.print(sensedata.ir_3_data); Serial.print(" - ");
//    Serial.print(sensedata.ir_4_data); Serial.print(" - "); Serial.print(sensedata.ir_5_data); Serial.print(" - ");
//    Serial.print(sensedata.sonar_0_data); Serial.print(" - "); Serial.print(sensedata.sonar_1_data); Serial.print(" - ");
//    Serial.println(sensedata.sonar_2_data);
    // pass data along to next arduino
    SENSORS.sendData();

  } // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
}
