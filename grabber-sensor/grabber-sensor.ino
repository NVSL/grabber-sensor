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
LED led(13);

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
   Serial.begin(9600);
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
  if( bumpSensor1.isPressed() || bumpSensor2.isPressed()) 
    led.turnOn();
  else
    led.turnOff();
  if( mainButton.isPressed() ) {
    servo.rotate(0);
    //motors.forward();
    pincers.open();
  }
  else {
    servo.rotate(180);
    //motors.stop();
    pincers.close();
  }
  Serial.print("Distance Sensor Readings: ");
  Serial.print( distanceSensor.get_distance() );
  Serial.println("cm");
}
