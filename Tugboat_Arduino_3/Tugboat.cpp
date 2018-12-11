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
                     int sonar_0_data, int sonar_1_data, int sonar_2_data){//,
//                     int imu_0_data) {
  ir_0 = ir_0_data;
  ir_1 = ir_1_data;
  ir_2 = ir_2_data;
  ir_3 = ir_3_data;
  ir_4 = ir_4_data;
  ir_5 = ir_5_data;

  sonar_0 = sonar_0_data;
  sonar_1 = sonar_1_data;
  sonar_2 = sonar_2_data;

//  imu_0 = imu_0_data;

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
      case 2: Serial.println("Robot State: idle"); // Undocks robot to the left of dock
              velocity = -30;  // 7 seconds
              heading = 45;
              Tugboat::move();
              delay(7000);
              break;
      case 3: Serial.println("Robot State: avoid"); // Undocks robot to right of dock
              //TESTING
              velocity = -30;
              heading = 0;
              Tugboat::move();
              delay(7000);
              //avoid(); //use all sensor data to move to a safer position
              break;
      case 4: Serial.println("Robot State: lwall");
              lwall(4, 2, 20, 40, 20);//64, 30, 0.125, true); //follow wall on left of boat
              break;
      case 5: Serial.println("Robot State: rwall");
              // Kp, Jp, des_heading, des_dist, vel
              rwall(4, 2, 20, 40, 20); //follow wall on right of boat
              break;
      case 6: Serial.println("Robot State: leftIce");
              fig8state = 1;
              leftIce(); //circumnavigate an object on left of boat
              break;
      case 7: Serial.println("Robot State: rightIce");
              fig8state = 1;
              rightIce(); //circumnavigate an object on right of boat
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
void Tugboat::lwall(int Kp, int Jp, int des_heading, int des_dist, int vel)//TODO: combine with other function//int Kp, int full_cycle, float pulse_ratio, bool mtr_pulse) // TODO: Each function should start with safetyCheck() function that changes to avoid state if needed
{
  float wall_dist = computeWallDistance(ir_1, ir_0, 10); //10 represents distance between IRs - TODO: put in more reasonable location

  heading = Kp*(ir_0 - ir_1) + Jp*(des_dist-wall_dist) + des_heading; //Controller designed for maintaining 0 value, adding des_heading makes "default" state the turn it takes to achieve pool navigation

  if (heading < (-10)) {//(des_heading)) {
    heading = -10;//(des_heading-15);
  }

  velocity = vel;  /*
  Inputs:
  Kp - proportional control constant
  ctr_count - initialize at zero, keeps track of where we are in control loop
  full_cycle - cycle for motor pulse in 1/10 seconds
  pulse_ratio - fraction of time motors are on (put a decimal, doesn't like fractions)
  mtr_pulse - initalize at false, determines whether motors are on or off
  */
  /*
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
        velocity = 30;
      }
      else {
        velocity = 0;
      }

ctr_count += 1;
Serial.print("ctr_count: "); Serial.println(ctr_count);*/
}
void Tugboat::rwall(int Kp, int Jp, int des_heading, int des_dist, int vel)
{ float wall_dist = computeWallDistance(ir_4, ir_5, 10); //10 represents distance between IRs - TODO: put in more reasonable location

  heading = -Kp*(ir_5 - ir_4) + -Jp*(des_dist-wall_dist) - des_heading; //Controller designed for maintaining 0 value, adding des_heading makes "default" state the turn it takes to achieve pool navigation

  if (heading > 10) {
    heading = 10;
  }

  velocity = vel;
}

void Tugboat::rightIce()
{
  heading = 0;
  velocity = 0;
}

void Tugboat::leftIce() // pass iceberg on left
{ // Uses fig8state - attribute of Tugboat
  switch (fig8state) {
      case 1: // Follow right wall until iceberg passed on left
        fig8state = 2;

        // if (ir_0 < 90) {// determine if iceberg was passed FRONTIR-BACKIR
        //   fig8state = 2;
        //   break;
        // }
        // Tugboat::rwall(4, 2, 20, 40, 20); //TODO: add parameters
        // //XBee.write("state 1");
        break;
      case 2:
        // XBee.write("state 2"); // Hard turn left until iceberg spotted on right
        velocity = 20;
        heading = -45; //Hard turn left
        //delay(1000);
        //if (abs(ir_1-ir_0) > 20) {
        //  fig8state = 3;
        //}
        break;
      // case 3: // Hard turn right until boat is close to wall
      //   // XBee.write("state 3");
      //   velocity = 20;
      //   heading = 45; //Hard turn right
      //   delay(1000); //TODO: determine if this is necessary
      //   if ((ir_1+ir_0)/2 < 40) {  // Check if boat is close to wall
      //     fig8state = 0;
      //     state = 7;// Switch to rightIce
      //   }
        break;
      default:
        fig8state = 0;
        break;
   }
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




// PRIVATE FUNCTIONS
float Tugboat::computeWallDistance(int front_ir, int back_ir, int sensor_dist) {
  int z = (front_ir + back_ir)/2; // Average distance between IRs
  // float theta;
  //
  // if (front_ir - back_ir == 0){
  //   theta = 0;
  // }
  // else {
  //   theta = PI/2 - atan(sensor_dist/abs(front_ir-back_ir)); // In Radians
  // }
  //
  // float distance = z*cos(theta);
  return z;
}
