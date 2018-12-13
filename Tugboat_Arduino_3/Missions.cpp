#include "Arduino.h"
#include "Missions.h"

Missions::Missions()
{
}

// Main Mission Functions
void Missions::fwdFigureEight()
{ // TODO: Document angles - currently assumes boat starts facing away from ice
  switch(fig8state) {
    case 0: // Follow left wall until IMU reads ~180 degrees
      tugboat_state = 4; // Left wall follow
      if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
        fig8state = 1;
      }
      break;
    case 1: // Circle around object on right until IMU reads ~0 degrees
      tugboat_state = 7; // Right ice circumnavigation
      if ((data.imu_0_data > 350) && (data.imu_0_data < 360) || // Data wraps from 360 to 0
          (data.imu_0_data > 0) && (data.imu_0_data < 10)) {
        fig8state = 2;
      }
      break;
    case 2: // Circle around object on left until IMU reads ~180
      tugboat_state = 6; // Left ice circumnavigation
      if ((data.imu_0_data > 170) && (data.imu_0_data < 190) || // Data wraps from 360 to 0
          (data.imu_0_data > 0) && (data.imu_0_data < 10)) {
        fig8state = 3;
      }
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }
}
void Missions::bwdFigureEight()
{
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

// Supporting Functions
