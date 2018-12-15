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
    void fwdFigureEight();
    void bwdFigureEight();
    void fwdFigureEightAndDock();

    int circleState = 0;
    void lcircleMission();
    void rcircleMission();

    int chaseState = 0;
    void chaseNarwhal();

    // Supporting Functions
    void wallFollow(int Kp, int Jp, int side, int dist_thresh, int front_ir, int back_ir);
};

#endif
