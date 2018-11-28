#include "Arduino.h"
#include "Tugboat.h"

Tugboat::Tugboat()
{
}

void Tugboat::init() {
  sensors.init();
  
  propellor.attach(propellorPin);
  propellor.writeMicroseconds(1500);
  rudder.attach(rudderPin);
  rudder.writeMicroseconds(1500);
}

void Tugboat::update() {
  //TODO: update state, commands, sensor data etc
  sensors.update();
  //(to get data, sensors.ir1.data
  //              sensors.ir4.heading
}

void Tugboat::move() {
  setPropSpeed(velocity);
  setHeading(heading);
}

void Tugboat::stateController() {
  switch (state) {
      case 1: Serial.println("Robot State: stop");
              stop();
              break;
      case 2: Serial.println("Robot State: idle");
              idle();
              break;
      case 3: Serial.println("Robot State: avoid");
              avoid(); //use all sensor data to move to a safer position
              break;
      case 4: Serial.println("Robot State: lwall");
              lwall(); //follow wall on left of boat
              break;
      case 5: Serial.println("Robot State: rwall");
              rwall(); //follow wall on right of boat
              break;
      case 6: Serial.println("Robot State: lcircle");
              lcircle(); //circumnavigate an object on left of boat
              break;
      case 7: Serial.println("Robot State: rcircle");
              rcircle(); //circumnavigate an object on right of boat
              break;             
      case 8: Serial.println("Robot State: chase");
              chase();
              break;
      case 9: Serial.println("Robot State: search");
              search();
              break;
      default: Serial.println("Robot State: stop *WARNING* Invalid Input");
              stop();
              break;
  }
}

// State Functions -----------------------------------------------------------
// TODO: Each of these functions should modify heading and velocity (and state if necessary for estop)
// TODO: Each of these functions is its own "arbiter" (brain) that thinks with that state goal in mind
void Tugboat::stop()
{
  
}
void Tugboat::idle()
{
  
}
void Tugboat::avoid()
{
  
}
void Tugboat::lwall() // TODO: Each function should start with safetyCheck() function that changes to avoid state if needed
{
  
}
void Tugboat::rwall()
{
  
}
void Tugboat::lcircle()
{
  
}
void Tugboat::rcircle()
{
  
}
void Tugboat::chase()
{
  
}
void Tugboat::search()
{
  
}

// Safety Function -----------------------------------------------------------
int safetyCheck()
{
  //TODO: should return 0 if good, 1 if something is bad with sensor data
}

// Act Functions -------------------------------------------------------------
//function to set propellor speed by percentage
void Tugboat::setPropSpeed(int speedPercentage){
  // Boat speed is between 1000 and 2000 with 1500 = boat stopped
  int microSec;
  if (speedPercentage>=100){ // Limit max speed percentage
    microSec= 2000;        //full speed forward
  }
  else if (speedPercentage<100 && speedPercentage>-100){
    microSec = map(speedPercentage,-100, 100, 1000, 2000);
  }
  else if (speedPercentage<=-100){ // Limit min speed percentage
    microSec=1000;         // back up full speed
  }
  propellor.writeMicroseconds(microSec);
}


void Tugboat::setHeading(int degHeading) // Input heading in degrees
{
  // Boat heading is between -45 degrees (left) and 45 degrees (right), which maps to 1000 to 2000 microseconds with 1500 = 0 degrees
  int microSec;
  if (degHeading>=45){ // Limit max turn right
    microSec= 2000;        // max right turn
  }
  else if (degHeading<45 && degHeading>-45){
    microSec = map(degHeading,-45, 45, 1000, 2000);
  }
  else if (degHeading<=-45){ // Limit max turn left
    microSec=1000;         // max left turn
  }
  rudder.writeMicroseconds(microSec);
}

// move(heading, velocity)
