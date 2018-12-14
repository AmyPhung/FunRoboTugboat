#ifndef Missions_h
#define Missions_h

#include "Sensors.h"

class Missions
{
  public:
    Missions();

    Sensors sensors;

    int tugboat_state = 0; // Which robot state to be in - for manual control, set to -1
    int cmd_heading = 0;  // Turn in degrees
    int cmd_velocity = 0; // Between -100 and 100

    // Figure 8
    int fig8state = 0; // Used for keeping track of current progress in figure 8
    int circleState = 0; // Used for keeping track of current progress in circle
    void fwdFigureEight();
    void bwdFigureEight();

    int circleState = 0;
    void circleMission();
};

#endif
