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

    sonar_0.pin = SONAR0PIN;
    sonar_1.pin = SONAR1PIN;
    sonar_2.pin = SONAR2PIN;

//    ir_0.init();
//    ir_1.init();
//    ir_2.init();
//    ir_3.init();
//    ir_4.init();
//    ir_5.init();
//
//    sonar_0.init();
//    sonar_1.init();
//    sonar_2.init();    
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
  Serial.println("Sonar Info:");
  Serial.print("Sonar 0 data: "); Serial.println(sonar_0.data);
  Serial.print("Sonar 1 data: "); Serial.println(sonar_1.data);
  Serial.print("Sonar 2 data: "); Serial.println(sonar_2.data);  
}

void Sensors::update(int ir_0_rawdata, int ir_1_rawdata, int ir_2_rawdata, int ir_3_rawdata, int ir_4_rawdata, int ir_5_rawdata, int sonar_0_rawdata, int sonar_1_rawdata, int sonar_2_rawdata) 
{
    ir_0.update(ir_0_rawdata);
    ir_1.update(ir_1_rawdata);
    ir_2.update(ir_2_rawdata);
    ir_3.update(ir_3_rawdata);
    ir_4.update(ir_4_rawdata);
    ir_5.update(ir_5_rawdata);

    sonar_0.update(sonar_0_rawdata);
    sonar_1.update(sonar_1_rawdata);
    sonar_2.update(sonar_2_rawdata); 
}