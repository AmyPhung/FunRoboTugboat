/**
  * Tugboat Arduino 2: Collects Sonar and IR data and sends it to next Arduino
  * @author Amy Phung, Everardo Gonzalez, Liz Leadley, Robert Wechsler
  * @date December 2018
  */

// This is for cross Arduino comms
#include <EasyTransfer.h>
// Provides RECEIVE_DATA_STRUCTURE and SEND_DATA_STRUCTURE for Arduino comms
#include "ArduinoComms2.h"
// Provides Sensors object to collect and process sensor data
#include "Sensors.h"

Sensors sensors;
EasyTransfer PIXY; // arduino comms from Arrduino 1
EasyTransfer SENSORS; // arduino comms to Arduino 3

//creating data structure
RECEIVE_DATA_STRUCTURE pixydata;

//creating data structure send
SEND_DATA_STRUCTURE sensedata;

unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
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
    sensors.print();

    sensedata.ir_0_data =  sensors.ir_0.data;
    sensedata.ir_1_data =  sensors.ir_1.data;
    sensedata.ir_2_data =  sensors.ir_2.data;
    sensedata.ir_3_data =  sensors.ir_3.data;
    sensedata.ir_4_data =  sensors.ir_4.data;
    sensedata.ir_5_data =  sensors.ir_5.data;

    sensedata.sonar_0_data = sensors.sonar_0.data;
    sensedata.sonar_1_data = sensors.sonar_1.data;
    sensedata.sonar_2_data = sensors.sonar_2.data;

    //sensedata.imu_0_data = sensors.imu_0.data;

//    Serial.println("------------------------------------------------------------------");
//    Serial.print(sensedata.ir_0_data); Serial.print(" - "); Serial.print(sensedata.ir_1_data); Serial.print(" - ");
//    Serial.print(sensedata.ir_2_data); Serial.print(" - "); Serial.print(sensedata.ir_3_data); Serial.print(" - ");
//    Serial.print(sensedata.ir_4_data); Serial.print(" - "); Serial.print(sensedata.ir_5_data); Serial.print(" - ");
//    Serial.print(sensedata.sonar_0_data); Serial.print(" - "); Serial.print(sensedata.sonar_1_data); Serial.print(" - ");
//    Serial.println(sensedata.sonar_2_data);
    // pass data along to next arduino
    //Serial.println(sensedata.ir_5_data);
    //Serial.println(sensedata.imu_0_data);
    SENSORS.sendData();

  } // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
}
