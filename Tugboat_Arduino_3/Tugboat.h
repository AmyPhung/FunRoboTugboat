#ifndef Tugboat_h
#define Tugboat_h

#include <Servo.h>

class Tugboat
{
  public:
    Tugboat();
    void init();
    void update(int ir_0_data, int ir_1_data, int ir_2_data,
                int ir_3_data, int ir_4_data, int ir_5_data,
                int sonar_0_data, int sonar_1_data, int sonar_2_data,
                int imu_0_data);
    void move();
    void stateController();

    int ir_0, ir_1, ir_2, ir_3, ir_4, ir_5;
    int sonar_0, sonar_1, sonar_2;
    int imu_0;

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

    //Controller Variables
    int ctr_count = 0; // counter for ime based control loops

    // States
    void stop();
    void idle();
    void avoid();
    void lwall(int Kp, int Jp, int des_heading, int des_dist, int vel);//int Kp, int full_cycle, float pulse_ratio, bool mtr_pulse);
    void rwall(int Kp, int Jp, int des_heading, int des_dist, int vel);
    void leftIce();
    void rightIce();
    void chase();
    void search();

    // ACT
    void setPropSpeed(int speedPercentage);
    void setHeading(int degHeading);
    Servo propellor;
    Servo rudder;
    int propellorPin;
    int rudderPin;

    int fig8state = 1; //TODO: Make this private, here for debug

  private:
    float computeWallDistance(int front_ir, int back_ir, int sensor_dist);


};

#endif
