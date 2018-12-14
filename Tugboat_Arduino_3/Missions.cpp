#include "Arduino.h"
#include "Missions.h"

Missions::Missions()
{
}

// Main Mission Functions
void Missions::fwdFigureEight()
{ // TODO: Document angles - currently assumes boat starts facing away from ice
  // Undocks, follows left wall to 0 deg heading, then enter 8 loop.
  // Infinite state loop switching between right and left object circling at 180 deg
  switch(fig8state) {
    case 0: // Undock and turn Left
      tugboat_state = 2; // turn out of dock to the left
      if ((sensors.imu.data < 285) && (sensors.imu.data > 180)) { // turn only ~75 deg left
        fig8state = 1;
      }
    case 1: // Follow left wall until IMU reads ~0 degrees
      tugboat_state = 4; // Left wall follow
      if ((sensors.imu.data > 350) && (sensors.imu.data < 360) || // Data wraps from 360 to 0
          (sensors.imu.data > 0) && (sensors.imu.data < 10)) {
        fig8state = 2;
      }
      break;
    case 2: // Circle around object on right until IMU reads ~180 degrees
      tugboat_state = 7; // Right ice circumnavigation
      if ((sensors.imu.data > 170) && (sensors.imu.data < 190)) {
        fig8state = 3;
      }
      break;
    case 3: // Circle around object on left until IMU reads ~180 degrees
      tugboat_state = 6; // Left ice circumnavigation
      if ((sensors.imu.data > 170) && (sensors.imu.data < 190)) {
        fig8state = 2; // cycle back to circle the other iceberg
      }
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }






  // switch(fig8state) {
  //   case 0: // Follow left wall until IMU reads ~180 degrees
  //     tugboat_state = 4; // Left wall follow
  //     if ((sensors.imu.data > 170) && (sensors.imu.data < 190)) {
  //       fig8state = 1;
  //     }
  //     break;
  //   case 1: // Circle around object on right until IMU reads ~0 degrees
  //     tugboat_state = 7; // Right ice circumnavigation
  //     if ((sensors.imu.data > 350) && (sensors.imu.data < 360) || // Data wraps from 360 to 0
  //         (sensors.imu.data > 0) && (sensors.imu.data < 10)) {
  //       fig8state = 2;
  //     }
  //     break;
  //   case 2: // Circle around object on left until IMU reads ~180
  //     tugboat_state = 6; // Left ice circumnavigation
  //     if ((sensors.imu.data > 170) && (sensors.imu.data < 190) || // Data wraps from 360 to 0
  //         (sensors.imu.data > 0) && (sensors.imu.data < 10)) {
  //       fig8state = 3;
  //     }
  //     break;
  //   default: // Stop robot TODO: remove this, currently here for testing
  //     tugboat_state = 1;
  //     break;
  // }
}
void Missions::bwdFigureEight()
{

  // Undocks, follows right wall to 0 deg heading, then enter 8 loop.
  // Infinite state loop switching between left and right object circling at 180 deg
  switch(fig8state) {
    case 0: // Undock and turn right
      tugboat_state = 3; // turn out of dock to the right
      if ((sensors.imu.data >  75) && (sensors.imu.data < 180)) { // turn only ~75 deg left
        fig8state = 1;
      }
    case 1: // Follow right wall until IMU reads ~0 degrees
      tugboat_state = 5; // right wall follow
      if ((sensors.imu.data > 350) && (sensors.imu.data < 360) || // Data wraps from 360 to 0
          (sensors.imu.data > 0) && (sensors.imu.data < 10)) {
        fig8state = 2;
      }
      break;
    case 2: // Circle around object on left until IMU reads ~180 degrees
      tugboat_state = 6; // left ice circumnavigation
      if ((sensors.imu.data > 170) && (sensors.imu.data < 190)) {
        fig8state = 3;
      }
      break;
    case 3: // Circle around object on right until IMU reads ~180 degrees
      tugboat_state = 7; // right ice circumnavigation
      if ((sensors.imu.data > 170) && (sensors.imu.data < 190)) {
        fig8state = 2; // cycle back to circle the other iceberg
      }
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }

  //TODO: Remove test
  //tugboat_state = 5;
  /*
switch(fig8state) {
  case 0:
    tugboat_state = 4; // For semi-auto control
    if (data.ir_0_data < 30) {
      fig8state = 1;
    }
    break;
  case 1:
    tugboat_state = -1; // For manual control
    // Because you want manual control, you need to specify heading and velocity
    cmd_heading = 45;
    cmd_velocity = 100;
  default: // need to define to prevent errors - this is your error case
    tugboat_state = -1;
    cmd_heading = 0;
    cmd_velocity = 0;

}
  */
  //if switch state goes here
     //tugboat_state = 9

     // Uses fig8state - attribute of Tugboat

      // TODO: Move this code over to mission
      // switch (fig8state) {
      //     case 1: // Follow right wall until iceberg passed on left
      //       Serial.println("case1");
      //       Tugboat::rwall(4, 2, 20, 40, 20); //TODO: add parameters
      //
      //       if (imu_0 > 260 && imu_0 < 280) { //TODO: add parameters // determine if iceberg was passed FRONTIR-BACKIR
      //          fig8state = 2;
      //          break;
      //       }
      //       //
      //       // //XBee.write("state 1");
      //       break;
      //     case 2:
      //       Serial.println("case2");
      //       // XBee.write("state 2"); // Hard turn left until iceberg spotted on right
      //       velocity = 20;
      //       heading = -45; //Hard turn left
      //
      //       if (imu_0 > 80 && imu_0 < 100) {
      //         fig8state = 3;
      //         break;
      //       }
      //       break;
      //     case 3: // Hard turn right until boat is close to wall
      //       Serial.println("case3");
      //       velocity = 20;
      //       heading = 45; //Hard turn right
      //
      //       if (imu_0 > 260 && imu_0 < 280) {
      //         fig8state = 4;
      //         break;
      //       }
      //       break;
      //
      //     case 4: // Hard turn right until boat is close to wall
      //       Serial.println("case4");
      //       velocity = 0;
      //       heading = 0; //Hard turn right
      //
      //
      //     //   // XBee.write("state 3");
      //     //   velocity = 20;
      //     //   heading = 45; //Hard turn right
      //     //   delay(1000); //TODO: determine if this is necessary
      //     //   if ((ir_1+ir_0)/2 < 40) {  // Check if boat is close to wall
      //     //     fig8state = 0;
      //     //     state = 7;// Switch to rightIce
      //     //   }
      //       break;
      //     default:
      //       fig8state = 0;
      //       break;
      //  }

}

void Missions::lcircleMission()
{ // TODO: Document angles - currently assumes boat starts facing away from ice
  switch(circleState) {
    case 0: // Follow left wall until IMU reads ~180 degrees
      tugboat_state = 2; // turn out of dock
      if ((sensors.imu.data < 285)
           && (sensors.imu.data > 180)) // if you've turned 75 degrees left
      {
        circleState = 1; //switch to next state
      }
      break;
    case 1: // Circle around object on right until IMU reads ~0 degrees
      tugboat_state = 4; //left wall follow
      if ((sensors.imu.data < 200) //check to see we've turned far enough
           && (sensors.imu.data > 180))
      {
        circleState = 2; //switch to next state
      }
      break;
    case 2: // Circle around object on left until IMU reads ~180
      tugboat_state = 7; // circle iceberg on right
      if ((sensors.imu.data > 260) && (sensors.imu.data < 290))
      {
        circleState = 3;
      }
      break;
    case 3:
      tugboat_state = -1; // straighten out cross finish line
      cmd_heading = 0;
      cmd_velocity = 14;
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }
}

void Missions::rcircleMission()
{ // TODO: Document angles - currently assumes boat starts facing away from ice
  switch(circleState) {
    case 0: // Follow left wall until IMU reads ~180 degrees
      tugboat_state = 3; // turn out of dock
      if ((sensors.imu.data < 360-180)
           && (sensors.imu.data > 360-285)) // if you've turned 75 degrees left
      {
        circleState = 1; //switch to next state
      }
      break;
    case 1: // Circle around object on right until IMU reads ~0 degrees
      tugboat_state = 5; //left wall follow
      if ((sensors.imu.data < 360-180) //check to see we've turned far enough
           && (sensors.imu.data > 360-200))
      {
        circleState = 2; //switch to next state
      }
      break;
    case 2: // Circle around object on left until IMU reads ~180
      tugboat_state = 6; // circle iceberg on right
      if ((sensors.imu.data > 360-290)
           && (sensors.imu.data < 360-260))
      {
        circleState = 3;
      }
      break;
    case 3:
      tugboat_state = -1; // straighten out cross finish line
      cmd_heading = 0;
      cmd_velocity = 14;
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }
}

void Missions::chaseNarwhal()
{
  int obj_thresh = 50; // For obstacle avoidance
  int dist_thresh = 50; // For wall following
  if (sensors.pixycam.narwhal_pos != 0) { // We assume the narwhal is never truly centered
    tugboat_state = -1;
    cmd_heading = sensors.pixycam.narwhal_pos;
    cmd_velocity = 14;
  } else {
    tugboat_state = -1;
    int l_avg = (sensors.ir_1.data + sensors.ir_0.data)/2;
    int r_avg = (sensors.ir_4.data + sensors.ir_5.data)/2;

    if (l_avg < r_avg) {
      wallFollow(8,8,0,dist_thresh,sensors.ir_1.data,sensors.ir_0.data); // Kp, Jp, side, dist_thresh, front_ir, back_ir
    } else {
      wallFollow(8,8,1,dist_thresh,sensors.ir_4.data,sensors.ir_5.data); // Kp, Jp, side, dist_thresh, front_ir, back_ir
    };

    int l_ir = sensors.ir_2.data;
    int r_ir = sensors.ir_3.data;

    if ((l_ir < obj_thresh) || (r_ir < obj_thresh)){
      if (r_ir < l_ir) {
        cmd_heading = -45;
      } else if (r_ir > l_ir) {
        cmd_heading = 45;
      } else { // Unlikely case of facing something head-on - pick one at random
        cmd_heading = 45;
      }
    }
    cmd_velocity = 14;

  };
}


// Supporting Functions
void Missions::wallFollow(int Kp, int Jp, int side, int dist_thresh, int front_ir, int back_ir)
{
  /*
  Inputs:
  Kp - proportional control constant for heading
  Jp - proportional control constant for distance
  side - which side to wall follow on. 0 For left, 1 for right
  dist_thresh - desired distance to stay away from wall in cm
  front_ir - front IR data
  back_ir - back IR data
  */

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

  cmd_heading = dist_heading + diff_heading;
  cmd_velocity = 14;
}
