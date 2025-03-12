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
1. 


*/

/* ******************** Code start *********************************** */

// Include libraryes
#include <Arduino.h>
#include <accelstepper.h>


// define variables
/* ------------------- Stepper Motor Control Interface ---------------- */
int speed_CW = 500;   // speed clockwise
int speed CCW = -500; // speed counter clokwise
long stepM1_steps_CW = 1000; // steps to move stepM 

int delay_1 = 1000; // delay in milliseconds
int delay_2 = 2000;




// define Pin constants
const int potMeter_01 = A0; // Potentiometer Pin

const int LED_01 = 2; // LED Pin
const int LED_02 = 3;

const int stepM1_IN1 = 8;  // StepMotor Pin
const int stepM1_IN2 = 9;
const int stepM1_IN3 = 10;
const int stepM1_IN4 = 11;

// define stepper motor interface type - 4 == FULL4WIRE
#define motorInterfaceType_1 4 // stepM1 setup

Accelstepper stepM1 = Accelstepper(MotorInterfaceType_1, stepM1_IN1, stepM1_IN3, stepM1_IN2, stepM1_IN4);

// move stepM ClockWise a speed from potentiometer reading
void moveStepM_CW (){
  Serial.println("Move CW");
  digitalWrite(LED_01, HIGH);
  digitalWrite(LED_02, LOW);
  stepM1.enableOutputs(); // enable all stepM output pins

  
}

