#include "Arduino.h"
#include "Missions.h"

Missions::Missions()
{
}

// Main Mission Functions
void Missions::fwdFigureEight()
{
  // Undocks, follows left wall to 0 deg heading, then enter 8 loop.
  // Infinite state loop switching between right and left object circling at 180 deg
  switch(fig8state) {
    case 0: // Undock and turn Left
      tugboat_state = 2; // Turn out of dock to the left
      if ((sensors.imu.data < 285) && (sensors.imu.data > 180)) { // turn only ~75 deg left
        fig8state = 1;
      }
      break;
    case 1: // Follow left wall until IMU reads ~0 degrees
      tugboat_state = 4; // Left wall follow
      if ((sensors.imu.data > 340) && (sensors.imu.data < 360)) { // Early along approach to 360 deg from negative (heading increasing)
        fig8state = 2;
      }
      break;
    case 2: // Finish the right circle until IMU reads ~30 deg off straight
      tugboat_state = 7; // Right ice circle
      if ((sensors.imu.data > 130) && (sensors.imu.data < 150)) { // Near 140 deg
        fig8state = 3;
      }
      break;
    case 3: // Go straight until IRs see an approaching wall
      tugboat_state = -1; // Override
      cmd_heading = -5; // Go slight angle left
      cmd_velocity = 14;
      if ((sensors.ir_2.data < 140) || (sensors.ir_3.data < 140)) { // When front wall is close
        fig8state = 4;
      }
      break;
    case 4: // Start left circle until IMU reads ~60 deg (60 away from straight)
      tugboat_state = 6; // Circle on the left
      if ((sensors.imu.data > 20) && (sensors.imu.data < 30)) { // Near 60 deg
        fig8state = 5;
      }
      break;
    case 5: // Wall follow on the right until IMU reads ~0 degrees
      tugboat_state = 5; // Right wall follow
      if ((sensors.imu.data > 340) && (sensors.imu.data < 360)){ // Early near 0 deg, approaching from positive (heading decreasing)
        fig8state = 6;
      }
      break;
    case 6: // Finish the left circle until IMU reads  ~220 deg
      tugboat_state = 6; // Left ice circle
      if ((sensors.imu.data > 210) && (sensors.imu.data < 230)) { //Near 220 deg
        fig8state = 7;
      }
      break;
    case 7: // Go staight until IRs see a wall approaching
      tugboat_state = -1; // Override
      cmd_heading = 5; // Go slight angle right
      cmd_velocity = 14;
      if ((sensors.ir_2.data < 140) || (sensors.ir_3.data < 140)) { // When front wall is close
        fig8state = 8;
      }
      break;
    case 8: // Start right circle until IMU reads ~300 deg (60 away from straight)
      tugboat_state = 7; // Right circle
      if ((sensors.imu.data > 320) && (sensors.imu.data < 340)) {
        fig8state = 1; // cycle back to left wall follow, then circle the other way
      }
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }

}
void Missions::bwdFigureEight()
{
  // Undocks, follows right wall to 0 deg heading, then enter 8 loop.
  // Infinite state loop switching between right and left object circling at 180 deg
  // Identical to fwdFigureEight except for case 0.
  switch(fig8state) {
    case 0: // Undock and turn Left
      tugboat_state = 3; // Turn out of dock to the right
      if ((sensors.imu.data > 75) && (sensors.imu.data < 180)) { // turn only ~75 deg right
        fig8state = 5; // skip to right wall following
      }
      break;
    case 1: // Follow left wall until IMU reads ~0 degrees
      tugboat_state = 4; // Left wall follow
      if ((sensors.imu.data > 340) && (sensors.imu.data < 360)) { // Early along approach to 360 deg from negative (heading increasing)
        fig8state = 2;
      }
      break;
    case 2: // Finish the right circle until IMU reads ~30 deg off straight
      tugboat_state = 7; // Right ice circle
      if ((sensors.imu.data > 130) && (sensors.imu.data < 150)) { // Near 140 deg
        fig8state = 3;
      }
      break;
    case 3: // Go straight until IRs see an approaching wall
      tugboat_state = -1; // Override
      cmd_heading = -5; // Go slight angle left
      cmd_velocity = 14;
      if ((sensors.ir_2.data < 140) || (sensors.ir_3.data < 140)) { // When front wall is close
        fig8state = 4;
      }
      break;
    case 4: // Start left circle until IMU reads ~60 deg (60 away from straight)
      tugboat_state = 6; // Circle on the left
      if ((sensors.imu.data > 20) && (sensors.imu.data < 30)) { // Near 60 deg
        fig8state = 5;
      }
      break;
    case 5: // Wall follow on the right until IMU reads ~0 degrees
      tugboat_state = 5; // Right wall follow
      if ((sensors.imu.data > 340) && (sensors.imu.data < 360)){ // Early near 0 deg, approaching from positive (heading decreasing)
        fig8state = 6;
      }
      break;
    case 6: // Finish the left circle until IMU reads  ~220 deg
      tugboat_state = 6; // Left ice circle
      if ((sensors.imu.data > 210) && (sensors.imu.data < 230)) { //Near 220 deg
        fig8state = 7;
      }
      break;
    case 7: // Go staight until IRs see a wall approaching
      tugboat_state = -1; // Override
      cmd_heading = 5; // Go slight angle right
      cmd_velocity = 14;
      if ((sensors.ir_2.data < 140) || (sensors.ir_3.data < 140)) { // When front wall is close
        fig8state = 8;
      }
      break;
    case 8: // Start right circle until IMU reads ~300 deg (60 away from straight)
      tugboat_state = 7; // Right circle
      if ((sensors.imu.data > 320) && (sensors.imu.data < 340)) {
        fig8state = 1; // cycle back to left wall follow, then circle the other way
      }
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }
}

void Missions::fwdFigureEightAndDock()
{
  // Undocks, follows left wall to 0 deg heading, then enter 8 loop.
  // Infinite state loop switching between right and left object circling at 180 deg
  // Identical to fwdFigureEight except case 7 is dock, and no case 8
  switch(fig8state) {
    case 0: // Undock and turn Left
      tugboat_state = 2; // Turn out of dock to the left
      if ((sensors.imu.data < 285) && (sensors.imu.data > 180)) { // turn only ~75 deg left
        fig8state = 1;
      }
      break;
    case 1: // Follow left wall until IMU reads ~0 degrees
      tugboat_state = 4; // Left wall follow
      if ((sensors.imu.data > 340) && (sensors.imu.data < 360)) { // Early along approach to 360 deg from negative (heading increasing)
        fig8state = 2;
      }
      break;
    case 2: // Finish the right circle until IMU reads ~30 deg off straight
      tugboat_state = 7; // Right ice circle
      if ((sensors.imu.data > 130) && (sensors.imu.data < 150)) { // Near 140 deg
        fig8state = 3;
      }
      break;
    case 3: // Go straight until IRs see an approaching wall
      tugboat_state = -1; // Override
      cmd_heading = -5; // Go slight angle left
      cmd_velocity = 14;
      if ((sensors.ir_2.data < 140) || (sensors.ir_3.data < 140)) { // When front wall is close
        fig8state = 4;
      }
      break;
    case 4: // Start left circle until IMU reads ~60 deg (60 away from straight)
      tugboat_state = 6; // Circle on the left
      if ((sensors.imu.data > 20) && (sensors.imu.data < 30)) { // Near 60 deg
        fig8state = 5;
      }
      break;
    case 5: // Wall follow on the right until IMU reads ~0 degrees
      tugboat_state = 5; // Right wall follow
      if ((sensors.imu.data > 340) && (sensors.imu.data < 360)){ // Early near 0 deg, approaching from positive (heading decreasing)
        fig8state = 6;
      }
      break;
    case 6: // Finish the left circle until IMU reads  ~220 deg
      tugboat_state = 6; // Left ice circle
      if ((sensors.imu.data > 170) && (sensors.imu.data < 190)) { //Near 180 deg
        fig8state = 7;
      }
      break;
    case 7: // Dock
      tugboat_state = 8; // Docking
      if ((sensors.ir_2.data < 30) || (sensors.ir_3.data < 30)) { // When front wall is close
        tugboat_state = 1; //  Stop, mission is complete
      }
      break;
    default: // Stop robot
      tugboat_state = 1;
      break;
  }
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
  //int obj_thresh = 50; // For obstacle avoidance
  int dist_thresh = 70; // For wall following

  int l_ir = sensors.ir_2.data;
  int r_ir = sensors.ir_3.data;

  if (sensors.pixycam.dot_pos != 0) { // We assume the narwhal is never truly centered
    tugboat_state = -1;
    cmd_heading = sensors.pixycam.dot_pos;
    cmd_velocity = 14;
  }
  else {
    tugboat_state = -1;
    int l_avg = (sensors.ir_1.data + sensors.ir_0.data)/2;
    int r_avg = (sensors.ir_4.data + sensors.ir_5.data)/2;

    if (l_avg < r_avg) {
      wallFollow(8,8,0,dist_thresh,sensors.ir_1.data,sensors.ir_0.data); // Kp, Jp, side, dist_thresh, front_ir, back_ir
    } else {
      wallFollow(8,8,1,dist_thresh,sensors.ir_4.data,sensors.ir_5.data); // Kp, Jp, side, dist_thresh, front_ir, back_ir
    };



    // if ((l_ir < obj_thresh) || (r_ir < obj_thresh)){
    //   if (r_ir < l_ir) {
    //     cmd_heading = -45;
    //   } else if (r_ir > l_ir) {
    //     cmd_heading = 45;
    //   } else { // Unlikely case of facing something head-on - pick one at random
    //     cmd_heading = 45;
    //   }
    // }
    // cmd_velocity = 14;

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
