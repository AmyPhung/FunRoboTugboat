#include "Arduino.h"
#include "Missions.h"

Missions::Missions()
{
}

// Main Mission Functions
void Missions::fwdFigureEight()
{
  //TODO: Remove test
  tugboat_state = -1;
  cmd_heading = 45;  // Turn in degrees
  cmd_velocity = 100; // Between -100 and 100
}
void Missions::bwdFigureEight()
{
  //TODO: Remove test
  tugboat_state = 5;
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

}

// Supporting Functions
