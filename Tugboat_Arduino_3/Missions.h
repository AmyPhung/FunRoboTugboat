#ifndef Missions_h
#define Missions_h

#include "ArduinoComms3.h"

class Missions
{
  public:
    Missions();
    void fwdFigureEight();
    void bwdFigureEight();

    RECIEVE_DATA_STRUCTURE data;

    int tugboat_state = 0; // Which robot state to be in - for manual control, set to -1
    int cmd_heading = 0;  // Turn in degrees
    int cmd_velocity = 0; // Between -100 and 100

    //int fig8state = 0;
};

#endif
