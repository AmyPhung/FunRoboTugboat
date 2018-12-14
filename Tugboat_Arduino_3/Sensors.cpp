#include "Sensors.h"

Sensors::Sensors()
{
}

void Sensors::init()
{
    ir_0.pin = IR0PIN;
    ir_1.pin = IR1PIN;
    ir_2.pin = IR2PIN;
    ir_3.pin = IR3PIN;
    ir_4.pin = IR4PIN;
    ir_5.pin = IR5PIN;

    ir_0.init();
    ir_1.init();
    ir_2.init();
    ir_3.init();
    ir_4.init();
    ir_5.init();

    imu.init();

    pixycam.init();
}

void Sensors::print()
{
  Serial.println("IR Info:");
  Serial.print("IR 0 data: "); Serial.println(ir_0.data);
  Serial.print("IR 1 data: "); Serial.println(ir_1.data);
  Serial.print("IR 2 data: "); Serial.println(ir_2.data);
  Serial.print("IR 3 data: "); Serial.println(ir_3.data);
  Serial.print("IR 4 data: "); Serial.println(ir_4.data);
  Serial.print("IR 5 data: "); Serial.println(ir_5.data);
  Serial.println("");
  Serial.println("IMU Info:");
  Serial.print("IMU data: "); Serial.println(imu.data);
  Serial.println("");
  Serial.println("Pixy Data:");
  Serial.print("Narwhal Position: "); Serial.println(pixycam.narwhal_pos);
  Serial.print("Dot Position: "); Serial.println(pixycam.dot_pos);
  // Serial.print("Sonar 0 data: "); Serial.println(sonar_0_data);
  // Serial.print("Sonar 1 data: "); Serial.println(sonar_1_data);
  // Serial.print("Sonar 2 data: "); Serial.println(sonar_2_data);
}

void Sensors::update(RECIEVE_DATA_STRUCTURE sensedata)
{
    ir_0.update();
    ir_1.update();
    ir_2.update();
    ir_3.update();
    ir_4.update();
    ir_5.update();

    imu.update();

    pixycam.update();

    // sonar_0_data = sensedata.sonar_0_data;
    // sonar_1_data = sensedata.sonar_1_data;
    // sonar_2_data = sensedata.sonar_2_data;
}
