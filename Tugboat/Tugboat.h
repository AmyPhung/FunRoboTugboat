#ifndef Tugboat_h
#define Tugboat_h

#include <Arduino.h>
#include <Servo.h>
#include "IMU.h" // Not on sense arduino since needs I2C, conflicts with IR
#include "Missions.h" // Provides complex behaviors

class Tugboat
{
  public:
    Tugboat();
    void init();
    void update();
    void move();
    void stateController(int state);

    // Sensor data storage
    Sensors sensors;


    int heading = 0;  // Turn in degrees
    int velocity = 0; // Between -100 and 100
    int state = 1;    // States
                      // 0: mission
                      // 1: stop
                      // 2: lundock //undock boat to left
                      // 3: rundock //undock boat to right
                      // 4: lwall //follow wall on left of boat
                      // 5: rwall //follow wall on right of boat
                      // 6: lcircle //circumnavigate an object on left of boat
                      // 7: rcircle //circumnavigate an object on right of boat
                      // 8: placeholder
                      // 9: search
                      // Other: stop

    // Mission Controller
    Missions missions;
    int mission_state = 0; // Missions
                           // 1: fwdFigureEight
                           // 2: bwdFigureEight
                           // Other: stop
    int classifyMission(String mission_cmd);
    void missionTugboat();

    //Controller Variables
    int ctr_count = 0; // counter for ime based control loops TODO: remove this

    // States
    void mission(int mission_num);
    void stop();
    void lundock();
    void rundock();
    void wallFollow(int Kp, int Jp, int side, int dist_thresh);
    void circleIce(int side);
    void dock();
    void placeholder2();

    // ACT
    void setPropSpeed(int speedPercentage);
    void setHeading(int degHeading);
    Servo propellor;
    Servo rudder;
    int propellorPin;
    int rudderPin;

  private:
    float computeWallDistance(int front_ir, int back_ir, int sensor_dist);


};

#endif
