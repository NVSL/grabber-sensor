/** ############################# Robot Name ############################## **\
|** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***********~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ **|
|** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/           \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ **|
|** ==========================={ Grabber Sensor }========================== **|
|** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\           /~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ **|
|** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***********~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ **|
\** #############################[[[[[^_^]]]]]############################# **/



/** ======================================================================= **\
|** ------------------------------ Libraries ------------------------------ **|
\** ======================================================================= **/

#include "GadgetManager.h"
#include "ServoMotor.h"
#include "MomentaryButton.h"
#include "PinChangeInt.h"
#include "DistanceSensor.h"
#include "Motor.h"
#include "Pincer.h"
#include "Servo.h"
#include "LED.h"


/** ======================================================================= **\
|** ---------------------------- Pin Constants ---------------------------- **|
\** ======================================================================= **/

#define DISTANCESENSOR1_A A2
#define SERVOMOTOR1_DATA 3
#define PINCER1_DATA 5
#define MOMENTARYBUTTON1_SENSE 4
#define MOTOR1_STBY 8
#define MOTOR1_PWMA 6
#define MOTOR1_AIN1 10
#define MOTOR1_AIN2 11
#define MOTOR1_PWMB 9
#define MOTOR1_BIN1 12
#define MOTOR1_BIN2 13
#define MOMENTARYBUTTON2_SENSE A0
#define MOMENTARYBUTTON3_SENSE A1

/** ======================================================================= **\
|** ------------------------- Object Declarations ------------------------- **|
\** ======================================================================= **/

DistanceSensor distanceSensor(DISTANCESENSOR1_A);
ServoMotor servo(SERVOMOTOR1_DATA);
Pincer pincers(PINCER1_DATA);
MomentaryButton mainButton(MOMENTARYBUTTON1_SENSE);
Motor motors(MOTOR1_STBY, MOTOR1_PWMA, MOTOR1_AIN1, MOTOR1_AIN2, MOTOR1_PWMB, MOTOR1_BIN1, MOTOR1_BIN2);
MomentaryButton bumpSensor1(MOMENTARYBUTTON2_SENSE);
MomentaryButton bumpSensor2(MOMENTARYBUTTON3_SENSE);

// The following constants define what states your robot can be in:
const int STOPPED = 0;
const int DRIVE_FORWARD = 1;
const int SPIN = 2;

// The state variable stores the current state of your robot
int state;
long int start_time;

/** ======================================================================= **\
|** --------------------------- Setup Function ---------------------------- **|
|** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% **|
|** ............................. Description ............................. **|
|** The setup() function runs --ONCE-- when the Arduino boots up. As the    **|
|** name implies, it's useful to add code that 'sets up' your Gadget to     **|
|** run correctly.                                                          **|
|** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% **|
\** ======================================================================= **/

void setup() {
   distanceSensor.setup();
   servo.setup();
   pincers.setup();
   mainButton.setup();
   motors.setup();
   bumpSensor1.setup();
   bumpSensor2.setup();
   // This prepares your code for debugging! Check out our guide on Serial
   // communication to learn more: https://goo.gl/fZadVH
   Serial.begin(9600);
   state = DRIVE_FORWARD;
   start_time = millis();
}



/** ======================================================================= **\
|** ---------------------------- Loop Function ---------------------------- **|
|** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% **|
|** ............................. Description ............................. **|
|** The loop() function runs continuously after the setup() function        **|
|** finishes and while the Arduino is running. In other words, this         **|
|** function is called repeatly over and over again when it reaches the     **|
|** end of the function. This function is where the majority of your        **|
|** program's logic should go.                                              **|
|** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% **|
\** ======================================================================= **/

void loop() {
  // State Transitions
     switch (state) {
     case STOPPED:
	  // Nothing to do.  We never leave the "STOPPED" state.
	  break;
	  
     case DRIVE_FORWARD:
	  if (millis() > start_time + 1000) {
	       // Times up.
	       state = SPIN; // Start spinning.
	       start_time = millis(); // Start timer.
	  } else if (mainButton.isPressed()) {
	       state = STOPPED;
	  }
	  break;
	  
     case SPIN:
	  if (millis() > start_time + 1000) {
	       // Times up.
	       state = DRIVE_FORWARD; // Start driving.
	       start_time = millis(); // Start timer.
	  } else if (mainButton.isPressed()) {
	       state = STOPPED;
	  }
     }

     // Actions
     switch (state) {
     case STOPPED:
	  motors.stop();
	  break;
     case DRIVE_FORWARD:
	  motors.forward();
	  break;
     case SPIN:
	  motors.spinLeft();
	  break;
     }
}
