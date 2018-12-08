#ifndef WallFollow_h
#define WallFollow_h

class WallFollow
{
  public:
    WallFollow();
    void init();
    void arbiter(int ir_0_data, int ir_1_data, int ir_2_data,
                 int ir_3_data, int ir_4_data, int ir_5_data,
                 int sonar_0_data, int sonar_1_data, int sonar_2_data);

    int heading = 0;  // Turn in degrees
    int velocity = 0; // Between -100 and 100
    
  private:

};

#endif
