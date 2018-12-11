#include "IMU.h"
#include "NineAxesMotion.h"        //Contains the bridge code between the API and the Arduino Environment

IMU::IMU()
{
}

void IMU::init()
{
  I2C.begin();
  imu.initSensor();          //The I2C Address can be changed here inside this function in the library
  imu.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  imu.setUpdateMode(MANUAL);	//The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions
  //Setting to MANUAL requires fewer reads to the sensor
}

void IMU::update()
{
  imu.updateEuler();        //Update the Euler data into the structure of the object
  imu.updateCalibStatus();  //Update the Calibration Status
  data = imu.readEulerHeading();
}
