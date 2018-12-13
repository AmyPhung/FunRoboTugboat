/**
  * Tugboat Arduino 2: Collects Sonar and IR data and sends it to next Arduino
  * @author Amy Phung, Everardo Gonzalez, Liz Leadley, Robert Wechsler
  * @date December 2018
  */

// This is for cross Arduino comms
#include <EasyTransfer.h>
// Provides RECEIVE_DATA_STRUCTURE and SEND_DATA_STRUCTURE for Arduino comms
#include "ArduinoComms2.h"
// Library for interfacing with Sonars
#include "Sonar.h"

#define SONAR0PIN 11
#define SONAR1PIN 12
#define SONAR2PIN 13

Sonar sonar_0;
Sonar sonar_1;
Sonar sonar_2;

EasyTransfer PIXY; // arduino comms from Arduino 1
EasyTransfer SENSORS; // arduino comms to Arduino 3

//creating data structure
RECEIVE_DATA_STRUCTURE pixydata;

//creating data structure send
SEND_DATA_STRUCTURE sensedata;

unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
const long controlLoopInterval = 50; //create a name for control loop cycle time in milliseconds

void setup() {
  Serial.begin(9600);

  // Sonar initialization
  sonar_0.pin = SONAR0PIN;
  sonar_1.pin = SONAR1PIN;
  sonar_2.pin = SONAR2PIN;
  sonar_0.init();
  sonar_1.init();
  sonar_2.init();

  // arduino comms
  PIXY.begin(details(pixydata), &Serial);
  SENSORS.begin(details(sensedata), &Serial);
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

    // Update sonar data
    sonar_0.update();
    sonar_1.update();
    sonar_2.update();

    sonar_0.print();
    sonar_0.print();
    sonar_0.print();

    sensedata.timestamp2 = millis();
    sensedata.sonar_0_data = sonar_0.data;
    sensedata.sonar_1_data = sonar_1.data;
    sensedata.sonar_2_data = sonar_2.data;

    SENSORS.sendData();

  } // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
}
