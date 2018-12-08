#ifndef Tugboat_h
#define Tugboat_h

#include <Servo.h>
#include "Sensors.h"

class Tugboat
{
  public:
    Tugboat();
    void init();
    void update();
    void move();    
    void stateController();

    Sensors sensors;
    int heading = 0;  // Turn in degrees
    int velocity = 0; // Between -100 and 100
    int state = 0;    // States
                      // 1: stop
                      // 2: idle
                      // 3: avoid //use all sensor data to move to a safer position
                      // 4: lwall //follow wall on left of boat
                      // 5: rwall //follow wall on right of boat
                      // 6: lcircle //circumnavigate an object on left of boat
                      // 7: rcircle //circumnavigate an object on right of boat
                      // 8: chase
                      // 9: search
                      // Other: stop

    // States
    void stop();
    void idle();
    void avoid();
    void lwall();
    void rwall();
    void lcircle();
    void rcircle();
    void chase();
    void search();
    
    // ACT
    void setPropSpeed(int speedPercentage);
    void setHeading(int degHeading);
    Servo propellor;
    Servo rudder;
    int propellorPin;
    int rudderPin;

  private:

};

#endif
