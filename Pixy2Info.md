# Pixy2 Setup Instructions

Following: https://pixycam.com/downloads-pixy2/

### Notes:
If after `cd ../../../build/pixymon/bin/` you get the error `bash: cd: ../../../build/pixymon/bin/: No such file or directory` try using 
`cd ~/pixy2/build/pixymon` instead.

Arduino Setup: https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29

After you extract the files, you will have a Pixy2 folder in your downloads. Move this folder to the Arduino/libraries folder.

# Pixy2 Library usage
+ Include: `#include <Pixy2.h>`
+ Object Declaration: `Pixy2 pixy;`
+ Updating pixy: `pixy.ccc.getBlocks();`
+ Number of detected objects: `pixy.ccc.numBlocks`
+ Printing info: `pixy.ccc.blocks[i].print()`
+ Accessing data: `pixy.ccc.blocks[i].<attribute>` (ex: `pixy.ccc.blocks[i].m_x`)
  + Attributes Include:
    + `uint16_t m_signature` - signature number -  If we have red registered as 1 and blue registered as 2, then these will be printed accordingly
    + `uint16_t m_x`
    + `uint16_t m_y`
    + `uint16_t m_width`
    + `uint16_t m_height`
    + `int16_t m_angle`
    + `uint8_t m_index`
    + `uint8_t m_age`
