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



# To-do:
