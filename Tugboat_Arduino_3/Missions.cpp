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
      if ((sensors.imu.data > 110) && (sensors.imu.data < 130)) { // Near 120 deg
        fig8state = 3;
      }
      break;
    case 3: // Go straight until IRs see an approaching wall
      tugboat_state = -1; // Override
      cmd_heading = 0; // Go straight
      cmd_velocity = 14;
      if ((data.ir_2_data < 70) || (data.ir_3_data < 70)) { // When front wall is close
        fig8state = 4;
      }
      break;
    case 4: // Start left circle until IMU reads ~60 deg (60 away from straight)
      tugboat_state = 6; // Circle on the left
      if ((sensors.imu.data > 50) && (sensors.imu.data < 70)) { // Near 60 deg
        fig8state = 5;
      }
      break;
    case 5: // Wall follow on the right until IMU reads ~0 degrees
      tugboat_state = 5; // Right wall follow
      if ((sensors.imu.data > 0) && (sensors.imu.data < 20)) { // Early near 10 deg, approaching from positive (heading decreasing)
        fig8state = 6;
      }
      break;
    case 6: // Finish the left circle until IMU reads  ~240 deg
      tugboat_state = 6; // Left ice circle
      if ((sensors.imu.data > 230) && (sensors.imu.data < 250)) {
        fig8state = 7;
      }
      break;
    case 7; // Go staight until IRs see a wall approaching
      tugboat_state = -1; // Override
      cmd_heading = 0; // Go straight
      cmd_velocity = 14;
      if ((data.ir_2_data < 70) || (data.ir_3_data < 70)) { // When front wall is close
        fig8state = 8;
      }
      break;
    case 8: // Start right circle until IMU reads ~300 deg (60 away from straight)
      tugboat_state = 7; // Right circle
      if ((sensors.imu.data > 290) && (sensors.imu.data < 310)) {
        fig8state = 1; // cycle back to left wall follow, then circle the other way
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

void Missions::circleMission()
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


// Supporting Functions
