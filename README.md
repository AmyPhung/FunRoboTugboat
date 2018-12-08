# FunRoboTugboat
Autonomous Tugboat - Final project for Fundamentals of Robotics class, Fall 2018


## Sensor Objects
### IR
##### Methods:
+ `void init()` - initializes an IR sensor, sets pin mode
+ `void update()` - updates IR data and saves it into data attribute
+ `void print()` - prints the data

##### Attributes:
+ `int pin` - analog in pin IR is plugged into
+ `int x_offset` - not yet implemented
+ `int y_offset` - not yet implemented
+ `int heading` - not yet implemented
+ `int data` - IR reading in cm

### Pixycam
+ not yet implemented

### Sonar
##### Methods:
+ `void init()` - initializes an sonar sensor, sets pin mode
+ `void update()` - updates sonar data and saves it into data attribute
+ `void print()` - prints the data

##### Attributes:
+ `int pin` - PWM pin sonar is plugged into
+ `int x_offset` - not yet implemented
+ `int y_offset` - not yet implemented
+ `int heading` - not yet implemented
+ `int data` - IR reading in cm

## Platform-dependent Objects
### Sensors
This object contains all the sensors and pin values for our specific tugboat configuration. This was made to streamline the sensor data flows from the sensors to the tugboat, especially when sensors get put on different arduinos. All pin values for sensors are stored in `Sensors.h`

##### Methods:
+ `void init()` - initializes all sensors, sets all pin modes
+ `void update()` - updates sonar data and saves it into data attribute
+ `void print()` - prints the data

##### Attributes:
+ `IR ir_0` - IR object 0
+ ...
+ `IR ir_5` - IR object 5
+ `Sonar sonar_0` - Sonar object 0
+ ...
+ `Sonar sonar_2` - Sonar object 2
+ `Pixycam pixycam` - Pixycam object


### Tugboat
##### Methods:
+ `void init()` - initializes a boat, also calls init function for sensors
+ `void update()` - calls update function for all sensors
+ `void move()` - moves the boat based on heading 
+ `void print()` - not yet implemented
+ `void stateController()` - sets the state for the boat and calls appropriate function
+ `void stop()`
+ `void idle()`
+ `void avoid()`
+ `void lwall()`
+ `void rwall()`
+ `void lcircle()`
+ `void rcircle()`
+ `void chase()`
+ `void search()`
+ `void setPropSpeed(int speedPercentage)`
+ `void setHeading(int degHeading)`
    
##### Attributes:
+ `Sensors sensors`
+ `int heading` - Heading value in degrees
+ `int velocity` - Velocity value between -100 and 100
+ `int state = 0` - Integer representing state
  + State 1: stop
  + State 2: idle
  + State 3: avoid - use all sensor data to move to a safer position
  + State 4: lwall - follow wall on left of boat
  + State 5: rwall - follow wall on right of boat
  + State 6: lcircle - circumnavigate an object on left of boat
  + State 7: rcircle - circumnavigate an object on right of boat
  + State 8: chase
  + State 9: search
  + State Other: stop

## Now With Arduino Comms:
We're using the EasyTransfer library for inter-Arduino communications. A link to getting this library set up is here -> https://github.com/EverardoG/Arduino-EasyTransfer. 

Arduino 1 passes the `pixydata` object to Arduino 2. Arduino 2 packs the data from `pixydata` and the information collected by its low level sensor suite into `sensedata`. Arduino 2 sends 'sensedata' to Arduino 3. This is all done using the Tx and Rx pins on the Arduinos. This means it uses the same serial channel that you use for the Arduino Serial Monitor. The THINK/ ACT Arduino can print to Serial, but sending it anything through the Serial monitor will confuse it.

### Attributes of pixydata
+ `unsigned long timestamp1` - millisecond timestamp from Arduino 1 when it sent `pixydata` (This was just to test functionality)

We will add more to this once we figure out exactly what pieces of data we want from the pixycam.

### Attributes of sensedata
+ `unsigned long timestamp1` - millisecond timestamp from Arduino 1 when it sent `pixydata` (This was just to test functionality)
+ `unsigned long timestamp2` - millisecond timestamp from Arduino 2 when it sent `sensedata` (This was just to test functionality)

+ `int ir_0_data` - meters measured by IR 0
+ `int ir_1_data` - meters measured by IR 1
+ `int ir_2_data` - meters measured by IR 2
+ `int ir_3_data` - meters measured by IR 3
+ `int ir_4_data` - meters measured by IR 4
+ `int ir_5_data` - meters measured by IR 5

+ `sonar_0_data` - meters measured by sonar 0
+ `sonar_1_data` - meters measured by sonar 1
+ `sonar_2_data` - meters measured by sonar 2

There will be more here once we integrate actual values from the pixycam.

## Now with XBee Comms
We can now communicate with our boat remotely! It's awesome! We use an `Xbee` object on Arduino 3 to communicate via XBee.

For it to work, you need to install the XBee software on your laptop first. Here's a really great walkthrough on that -> https://github.com/olinrobotics/main/wiki/XBee-Radios. Once you have that set up, here's the step-by-step guide to setting up comms.

### Setup
#### Boat Side
1. Upload code to each Arduino. Arduino 1 is the pixy cam arduino. Arduino 2 is the low level sensing arduino. Arduino 3 is the THINK/ACT arduino.
2. Make sure that all arduinos are connected to eachother properly.
Arduino 1 Tx -> Arduino 2 Rx
Arduino 2 Tx -> Arduino 3 Rx
3. Verify that the XBee is indeed plugged into Arduino 3.
4. Turn on the boat.

#### Laptop Side
1. Connect the OCU XBee to your laptop via the adaptor board.
2. Open up the XCTU.desktop software. Remember, you need to use `sudo XCTU ./XCTU.desktop` to make it work. 
3. Click "Add a Radio Module" in the upper left hand corner. Add the OCU XBee. It should show up with "OCU" as its name. 
4. In the upper right, there's a gear icon. Next to it is a computer/ terminal icon. Click it.
5. Now you'll see three icons above the "Console Log". Click "Open". This makes it so that your laptop XBee is now listening to the boat XBee. You can also type into the "Console Log" to send commands to the boat!

### Methods of XBee Comms Object 
+ `void begin(int baudrate)` - sets the data baudrate for XBee transmission
+ `void write(char array)` - the boat will send out this char array to the XBee channel
+ `int available()` - returns the number of bytes avaiable to read from XBee channel
+ `char read()` - returns the character read on the XBee channel (Someone should double check this, but for our purposes, this captures everything that matters)

# To-do:
+ write behavior functions
+ put sensor object functions in separate folder when complete
+ determine if PWM signals alone would be good enough for sonars (will need other pins if sensors have conflict issues) and update code to reflect that
+ determine how Pixycam data is processed

