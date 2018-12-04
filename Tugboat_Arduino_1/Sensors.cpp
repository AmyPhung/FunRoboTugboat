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

    ir_0.init();
    ir_1.init();
    ir_2.init();
    ir_3.init();
    ir_4.init();
    ir_5.init();

    sonar_0.init();
    sonar_1.init();
    sonar_2.init();
}

void Sensors::csvHeader()
{
  Serial.println("IR0,     IR1,     IR2,     IR3,     IR4,     IR5,     Sonar0,     Sonar1,     Sonar2");
}

void Sensors::print(bool csv = false)
{
  if (csv == true) {
    Sensors::p(ir_0.data); Sensors::p(ir_1.data); Sensors::p(ir_2.data);
    Sensors::p(ir_3.data); Sensors::p(ir_4.data); Sensors::p(ir_5.data);
    Sensors::p(sonar_0.data); Sensors::p(sonar_1.data); Sensors::p(sonar_2.data);
    Serial.println();
  }
  else {
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
}

void Sensors::update()
{
    ir_0.update();
    ir_1.update();
    ir_2.update();
    ir_3.update();
    ir_4.update();
    ir_5.update();

    sonar_0.update();
    sonar_1.update();
    sonar_2.update();
}

//Private Functions
void Sensors::p(int var) {
  //CSV-convenient print function; for legibility purposes
  //Used above in "print()" and "csv"
  Serial.print(var);
  Serial.print(",     ");
}
