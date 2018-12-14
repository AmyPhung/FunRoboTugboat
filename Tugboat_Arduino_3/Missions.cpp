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
      tugboat_state = 2; // turn out of dock to the left
      if ((data.imu_0_data < 285) && (data.imu_0_data > 180)) { // turn only ~75 deg left
        fig8state = 1;
      }
    case 1: // Follow left wall until IMU reads ~0 degrees
      tugboat_state = 4; // Left wall follow
      if ((data.imu_0_data > 350) && (data.imu_0_data < 360) || // Data wraps from 360 to 0
          (data.imu_0_data > 0) && (data.imu_0_data < 10)) {
        fig8state = 2;
      }
      break;
    case 2: // Circle around object on right until IMU reads ~180 degrees
      tugboat_state = 7; // Right ice circumnavigation
      if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
        fig8state = 3;
      }
      break;
    case 3: // Circle around object on left until IMU reads ~180 degrees
      tugboat_state = 6; // Left ice circumnavigation
      if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
        fig8state = 2; // cycle back to circle the other iceberg
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
  // Infinite state loop switching between left and right object circling at 180 deg
  switch(fig8state) {
    case 0: // Undock and turn right
      tugboat_state = 3; // turn out of dock to the right
      if ((data.imu_0_data >  75) && (data.imu_0_data < 180)) { // turn only ~75 deg left
        fig8state = 1;
      }
    case 1: // Follow right wall until IMU reads ~0 degrees
      tugboat_state = 5; // right wall follow
      if ((data.imu_0_data > 350) && (data.imu_0_data < 360) || // Data wraps from 360 to 0
          (data.imu_0_data > 0) && (data.imu_0_data < 10)) {
        fig8state = 2;
      }
      break;
    case 2: // Circle around object on left until IMU reads ~180 degrees
      tugboat_state = 6; // left ice circumnavigation
      if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
        fig8state = 3;
      }
      break;
    case 3: // Circle around object on right until IMU reads ~180 degrees
      tugboat_state = 7; // right ice circumnavigation
      if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
        fig8state = 2; // cycle back to circle the other iceberg
      }
      break;
    default: // Stop robot TODO: remove this, currently here for testing
      tugboat_state = 1;
      break;
  }
}

// void Missions::fwdFigureEightAndDock()
// {
//   break;
  // switch(fig8state) {
  //   //Undock
  //   case 0: // Undock and turn Left
  //     tugboat_state = 2; // turn out of dock to the left
  //     if ((data.imu_0_data >  285) && (data.imu_0_data > 180)) { // turn only ~75 deg left
  //       fig8state = 1;
  //     }
  //   case 1: // Follow left wall until IMU reads ~0 degrees
  //     tugboat_state = 4; // Left wall follow
  //     if ((data.imu_0_data > 350) && (data.imu_0_data < 360) || // Data wraps from 360 to 0
  //         (data.imu_0_data > 0) && (data.imu_0_data < 10)) {
  //       fig8state = 2;
  //     }
  //     break;
  //   case 2: // Circle around object on right until IMU reads ~180 degrees
  //     tugboat_state = 7; // Right ice circumnavigation
  //     if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
  //       fig8state = 3;
  //     }
  //     break;
  //   case 3: // Circle around object on left until IMU reads ~180 degrees
  //     tugboat_state = 6; // Left ice circumnavigation
  //     if ((data.imu_0_data > 170) && (data.imu_0_data < 190)) {
  //       fig8state = 2; // cycle back to circle the other iceberg
  //     }
  //     break;
  //   default: // Stop robot TODO: remove this, currently here for testing
  //     tugboat_state = 1;
  //     break;
  // }
// }

// Supporting Functions
