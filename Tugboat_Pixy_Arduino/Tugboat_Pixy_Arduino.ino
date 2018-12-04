#include <Pixy2.h>

Pixy2 pixy;

void setup()
{
  Serial.begin(9600);
  pixy.init();
}

void loop()
{ 
  int i; 
  // update pixycam readings
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }

    // To access these data points individually, see https://github.com/AmyPhung/FunRoboTugboat/blob/master/Pixy2Info.md
  }  
}
