#include "Arduino.h"
#include "Tugboat.h"

#define STOPPEDMICRO 1450 //Typically 1500 - sometimes changes, unsure why

Tugboat::Tugboat()
{
}

void Tugboat::init() {
  propellor.attach(propellorPin);
  propellor.writeMicroseconds(STOPPEDMICRO);
  rudder.attach(rudderPin);
  rudder.writeMicroseconds(STOPPEDMICRO);
}

void Tugboat::update(int ir_0_data, int ir_1_data, int ir_2_data,
                     int ir_3_data, int ir_4_data, int ir_5_data,
                     int sonar_0_data, int sonar_1_data, int sonar_2_data) {
  ir_0 = ir_0_data;
  ir_1 = ir_1_data;
  ir_2 = ir_2_data;
  ir_3 = ir_3_data;
  ir_4 = ir_4_data;
  ir_5 = ir_5_data;

  //TODO: update state, commands, sensor data etc
  stateController();
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
              lwall(64, 30, 0.125, true); //follow wall on left of boat
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

      //TELEOP COMMANDS
      case 10: break;
      case 11: break;
      case 12: break;
      case 13: break;

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
  velocity = 0;
  heading = 0;
}
void Tugboat::idle()
{

}
void Tugboat::avoid()
{

}
void Tugboat::lwall(int Kp, int full_cycle, float pulse_ratio, bool mtr_pulse) // TODO: Each function should start with safetyCheck() function that changes to avoid state if needed
{
  /*
  Inputs:
  Kp - proportional control constant
  ctr_count - initialize at zero, keeps track of where we are in control loop
  full_cycle - cycle for motor pulse in 1/10 seconds
  pulse_ratio - fraction of time motors are on (put a decimal, doesn't like fractions)
  mtr_pulse - initalize at false, determines whether motors are on or off
  */
int newHeading = Kp * (ir_0 - ir_1);

// dealing with that god damn edge case
if (newHeading>45) {
  newHeading = 45;
}
// don't let the boat turn right
else if (newHeading<0){
  newHeading = 0;
}

heading = newHeading;

//switch motor pulse on and off
Serial.println("----------------------------------");
Serial.print("ctr_count"); Serial.println(ctr_count);
Serial.print("pulse_ratio"); Serial.println(pulse_ratio);
Serial.print("full_cycle"); Serial.println(full_cycle);


if (ctr_count <= pulse_ratio*full_cycle)
{mtr_pulse = true;
//XBee.write("pulsing motors");
Serial.println("pulsing motors");
}
else {mtr_pulse = false;}

//reset pulse counter
if (ctr_count >= full_cycle){
  ctr_count = 0;
}

// set motor speed
if (mtr_pulse == true) {
        velocity = 20;
      }
      else {
        velocity = 0;
      }

ctr_count += 1;
Serial.print("ctr_count: "); Serial.println(ctr_count);
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
  //TODO: Get rid of speed limit
  //int tempLimit = 0;

  // Boat speed is between 1000 and 2000 with 1500 = boat stopped
  int microSec;
  if (speedPercentage>=100){ // Limit max speed percentage
    microSec= STOPPEDMICRO+500;//2000-tempLimit;        //full speed forward
  }
  else if (speedPercentage<100 && speedPercentage>-100){
    microSec = map(speedPercentage,-100, 100, STOPPEDMICRO-500, STOPPEDMICRO+500);
  }
  else if (speedPercentage<=-100){ // Limit min speed percentage
    microSec= STOPPEDMICRO-500;//1000+tempLimit;         // back up full speed
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
