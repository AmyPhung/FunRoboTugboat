#include "Pixycam.h"

Pixycam::Pixycam()
{
}

void Pixycam::init()
{
  pixy.init();
}

void Pixycam::print()
{
  Serial.print("Red Dot Location: ");
  Serial.println(dot_pos);

  Serial.print("Narwhal Location: ");
  Serial.println(narwhal_pos);
}

void Pixycam::update()
{
  dot_pos = dotLocation();
  narwhal_pos = narwhalLocation();
}

// Other Functions
int Pixycam::dotLocation()
{
  int i;
  int reddot = 0;

  pixy.ccc.getBlocks(); // grab blocks

  if (pixy.ccc.numBlocks) {// If there are detect blocks
   for (i=0; i<pixy.ccc.numBlocks; i++) {
      if (pixy.ccc.blocks[i].m_signature == 1) {
        reddot = map((pixy.ccc.blocks[i].m_x),0,319,-100,100); // maps pixy view onto more useful scale
      }
    }
  }
  // Serial.println(reddot);
  return reddot;
}

int Pixycam::narwhalLocation()
{
  int i;
  int narwhal = 0;

  pixy.ccc.getBlocks(); // grab blocks!

  if (pixy.ccc.numBlocks) { // If there are detect blocks, print them!
    for (i=0; i<pixy.ccc.numBlocks; i++) {
      if (pixy.ccc.blocks[i].m_signature == 2) {
        narwhal = map((pixy.ccc.blocks[i].m_x),0,319,-100,100); // maps pixy view onto more useful scale
      }
    }
  }
  return narwhal;
}
