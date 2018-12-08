#ifndef Xbee3_h
#define Xbee3_h

struct RECIEVE_DATA_STRUCTURE
{
  // variable definitions go here
  // MUST BE EXACTLY THE SAME ON ARDUINO 3
  unsigned long timestamp1;
  unsigned long timestamp2;

  //This code goes into the data structure
  int ir_0_data =  0;
  int ir_1_data =  0;
  int ir_2_data =  0;
  int ir_3_data =  0;
  int ir_4_data =  0;
  int ir_5_data =  0;

  int sonar_0_data = 0;
  int sonar_1_data = 0;
  int sonar_2_data = 0;

};

#endif
