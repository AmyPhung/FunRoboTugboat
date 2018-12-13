#include "Tugboat.h"

#define STOPPEDMICRO 1450 //Typically 1500 - sometimes changes, unsure why

Tugboat::Tugboat()
{
}

void Tugboat::init() {
  imu.init();

  propellor.attach(propellorPin);
  propellor.writeMicroseconds(STOPPEDMICRO);
  rudder.attach(rudderPin);
  rudder.writeMicroseconds(STOPPEDMICRO);
}

void Tugboat::update(RECIEVE_DATA_STRUCTURE recieved_data) {
  data = recieved_data;

  imu.update();
  data.imu_0_data = imu.data; // Comes onboard, not from Serial

  //TODO: update state, commands, sensor data etc
  stateController(state);
}

void Tugboat::move() {
  setPropSpeed(velocity);
  setHeading(heading);
}

void Tugboat::stateController(int cmd_state) {
  switch (cmd_state) {
      case 0: Serial.println("Robot State: mission"); // Uses custom mission code based on second input
              mission(mission_state); // Run mission code with selected mission
              break;
      case 1: Serial.println("Robot State: stop");
              stop();
              break;
      case 2: Serial.println("Robot State: lundock"); // Undocks robot to the left of dock
              lundock();
              break;
      case 3: Serial.println("Robot State: rundock"); // Undocks robot to right of dock
              rundock();
              break;
      case 4: Serial.println("Robot State: lwall");
              wallFollow(8, 8, 0); //Kp, Jp, side
              break;
      case 5: Serial.println("Robot State: rwall");
              wallFollow(8, 8, 1); //Kp, Jp, side
              break;
      case 6: Serial.println("Robot State: leftIce");
              circleIce(0); //circumnavigate an object on left of boat
              break;
      case 7: Serial.println("Robot State: rightIce");
              circleIce(1); //circumnavigate an object on right of boat
              break;
      case 8: Serial.println("Robot State: placeholder1");
              placeholder1();
              break;
      case 9: Serial.println("Robot State: placeholder2");
              placeholder2();
              break;

      //TELEOP COMMANDS
      case 10: break;
      case 11: break;
      case 12: break;
      case 13: break;
      case 14: break;

      default: Serial.println("Robot State: stop *WARNING* Invalid Input");
              stop();
              break;
  }
}

// State Functions -----------------------------------------------------------
// TODO: Each of these functions should modify heading and velocity (and state if necessary for estop)
// TODO: Each of these functions is its own "arbiter" (brain) that thinks with that state goal in mind
void Tugboat::mission(int mission_num)
{
  missions.data = data; // Update mission data based tugboat data
  switch (mission_num) {
    case 1:
      missions.fwdFigureEight();
      Tugboat::missionTugboat();
      break;
    case 2:
      missions.bwdFigureEight();
      Tugboat::missionTugboat();
      break;
    default:
      Tugboat::stop();
      break;
  }
}

void Tugboat::stop()
{
  velocity = 0;
  heading = 0;
}
void Tugboat::lundock()
{
  //TODO: insert undock code here
  velocity = -30;  // 7 seconds
  heading = 45;
  Tugboat::move();
  delay(7000);
}
void Tugboat::rundock()
{
  //TODO: insert undock code here
  velocity = -30;  // 7 seconds
  heading = -45;
  Tugboat::move();
  delay(7000);
}
void Tugboat::wallFollow(int Kp, int Jp, int side)
{
  /*
  Inputs:
  Kp - proportional control constant for heading
  Jp - proportional control constant for distance
  side - which side to wall follow on. 0 For left, 1 for right
  */
  int dist_thresh = 30; // Desired distance to stay away from wall

  int front_ir, back_ir;

  if (side == 0) { // Use left sensors for left wall follow
    front_ir = data.ir_1_data;
    back_ir = data.ir_0_data;
  } else if (side == 1) { // Use right sensors for right wall follow
    front_ir = data.ir_4_data;
    back_ir = data.ir_5_data;
  }

  int ir_dist = front_ir - dist_thresh;
  int ir_diff = (back_ir-front_ir);
  int dist_heading, diff_heading;

  if (side == 0) { // Use logic to avoid left wall
    dist_heading = - Jp * ir_dist;
    diff_heading = Kp * ir_diff;
    if (dist_heading < 0) {dist_heading = 0;} // Prevent robot from turning left
    if (diff_heading < 0) {diff_heading = 0;} // Prevent robot from turning left
  } else if (side == 1) { // Use logic to avoid right wall
    dist_heading = Jp * ir_dist;
    diff_heading = - Kp * ir_diff;
    if (dist_heading > 0) {dist_heading = 0;} // Prevent robot from turning right
    if (diff_heading > 0) {diff_heading = 0;} // Prevent robot from turning right
  }

  heading = dist_heading + diff_heading;
  velocity = 14;
}

void Tugboat::circleIce(int side) // circle iceberg
{
  /*
  Inputs:
  side - which side obstacle is on follow on. 0 For left, 1 for right
  */
  int default_heading = 30; // Heading that allows perfect circumnavigation
  int threshold = 50; // IR reading that constitutes an iceberg

  int front_ir, back_ir;
  int s = 0; // Used for changing sign of constants for left/right use

  if (side == 0) { // Use left sensors for left wall follow
    front_ir = data.ir_1_data;
    back_ir = data.ir_0_data;
    s = -1;
  } else if (side == 1) { // Use right sensors for right wall follow
    front_ir = data.ir_4_data;
    back_ir = data.ir_5_data;
    s = 1;
  }

  // Front IR, Back IR, Sonar
  //int dist_thresh = 30; // Desired distance to stay away from iceberg

  if (back_ir < threshold) {
    heading = s*default_heading + s*20;
  } else if (front_ir < threshold) {
    heading = s*default_heading - s*10;
  } else {
    heading = s*default_heading;
  }
  velocity = 15;
  /*

  if back ir is triggered then need to turn sharper too far back
  if front ir is triggered then need to turn less sharp
  */
}
void Tugboat::placeholder1()
{

}
void Tugboat::placeholder2()
{

}

// Mission Functions ---------------------------------------------------------
int Tugboat::classifyMission(String mission_cmd)
{
  if (mission_cmd == "49") { //1
    missions.fig8state = 0; // Reset figure 8 progress
    return 1; // fwdFigureEight
  }
  else if (mission_cmd == "50") { //2
    missions.fig8state = 0; // Reset figure 8 progress
    return 2; // bwdFigureEight
  }
  else {
    return 0; // stop
  }
}

void Tugboat::missionTugboat(){ // Allows mission to set boat state
  if (missions.tugboat_state == -1) { // If mission declares manual control, use specified values
    velocity = missions.cmd_velocity;
    heading = missions.cmd_heading;
  } else {
    stateController(missions.tugboat_state); // Run desired robot state based on mission cmd
  }
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
