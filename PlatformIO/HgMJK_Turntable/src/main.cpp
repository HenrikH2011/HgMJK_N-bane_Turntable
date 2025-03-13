/* Project: HgMJK, Turntable for N-scale
Version: alpha 0.0.1
Dev Code: HH
Dev Mechanics: SBC

Library: Accelstepper.h documentation homepage: 
- https://www.airspayce.com/mikem/arduino/AccelStepper/index.html

IDE: VS Code + PlatformIO

Hardware:
MCU: Arduino 328 UNO / NANO, MEGA2560
1x 28BYJ-48 Stepper motor
1x ULN2003 motordriver
1x Potentiometer 10K


ToDo:
1. test analogRead for potMeter_01 = A0
  - test readings: max=1007, min=0, middel:(1007/2=503,5)=503
  - set middel pos (stop stepM movement) > 501 | < 505 : to be adjusted in stepM move test
2. test stepM move according to analogRead potMeter_01
  - TEST: adjusted potmeter values to: > 498 | < 508 :OK - to be adjusted if needed
  - edit code for move speed. slow to faster in both ways CW and CCW


*/

/* ******************** Code start *********************************** */

// Include libraryes
#include <Arduino.h>
#include <AccelStepper.h>


// define variables
/* ------------------- Stepper Motor Control Interface ---------------- */
int speed_CW = 600;   // speed clockwise - NOT IN USE
int speed_CCW = -600; // speed counter clokwise - NOT IN USE
long stepM1_steps_CW = 1000; // steps to move stepM - NOT IN USE

int delay_1 = 50; // delay in milliseconds
int delay_2 = 500;

// define Pin constants
const int potMeter_01 = A0; // Potentiometer Pin

const int LED_01 = 2; // LED Pin
const int LED_02 = 3;

const int stepM1_IN1 = 8;  // StepMotor Pin
const int stepM1_IN2 = 9;
const int stepM1_IN3 = 10;
const int stepM1_IN4 = 11;

// define stepper motor interface type - 4 == FULL4WIRE
#define MotorInterfaceType_1 4 // stepM1 setup

AccelStepper stepM1 = AccelStepper(MotorInterfaceType_1, stepM1_IN1, stepM1_IN3, stepM1_IN2, stepM1_IN4);

// move stepM ClockWise a speed from potentiometer reading
void moveStepM (){
  Serial.println("Move stepM CW or CCW");
  digitalWrite(LED_01, HIGH);
  digitalWrite(LED_02, LOW);
  stepM1.enableOutputs(); // enable all stepM output pins

  stepM1.setCurrentPosition(0);

  while ( (analogRead(potMeter_01) < 498) | (analogRead(potMeter_01) > 508) ) {
    
    if (analogRead(potMeter_01) >508){
      Serial.println("move stepM CW");

      int16_t steps = -508 + (analogRead(potMeter_01));
      Serial.print("steps: ");
      Serial.println(steps);
      stepM1.setSpeed(steps);      
      stepM1.runSpeed();
    } // END if

    if (analogRead(potMeter_01) < 498){
      Serial.println("move stepM CCW");
      int16_t steps = -(498 - analogRead(potMeter_01));
      Serial.print("steps: ");
      Serial.println(steps);
      stepM1.setSpeed(steps);
      stepM1.runSpeed();
    } // END if

 
  } // END while

  stepM1.disableOutputs(); // disable all stepM output pins
  digitalWrite(LED_01, LOW);
  digitalWrite(LED_02, HIGH);
  
} // END void moveStepM

void setup(){
  Serial.begin(9600);

  stepM1.disableOutputs();
  stepM1.setMaxSpeed(500);
  stepM1.setAcceleration(50);
  
  pinMode (LED_01, OUTPUT);
  pinMode (LED_02, OUTPUT);

  pinMode (stepM1_IN1, OUTPUT);
  pinMode (stepM1_IN2, OUTPUT);
  pinMode (stepM1_IN3, OUTPUT);
  pinMode (stepM1_IN4, OUTPUT);

} // END vois setup

void loop(){

  Serial.print("potM value: ");
  Serial.println(analogRead(potMeter_01));
  delay(delay_1);

  while ( (analogRead(potMeter_01) < 495) | (analogRead(potMeter_01) > 510) ) {
    moveStepM();  
  }
  
  delay(delay_2);

} // END void loop

