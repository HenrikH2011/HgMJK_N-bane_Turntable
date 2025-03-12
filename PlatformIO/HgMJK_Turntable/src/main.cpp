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
#include <AccelStepper.h>


// define variables
/* ------------------- Stepper Motor Control Interface ---------------- */
int speed_CW = 500;   // speed clockwise
int speed_CCW = -500; // speed counter clokwise
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
#define MotorInterfaceType_1 4 // stepM1 setup

AccelStepper stepM1 = AccelStepper(MotorInterfaceType_1, stepM1_IN1, stepM1_IN3, stepM1_IN2, stepM1_IN4);

// move stepM ClockWise a speed from potentiometer reading
void moveStepM (){
  Serial.println("Move stepM CW or CCW");
  digitalWrite(LED_01, HIGH);
  digitalWrite(LED_02, LOW);
  stepM1.enableOutputs(); // enable all stepM output pins

  stepM1.setCurrentPosition(0);

  while ( (digitalRead(potMeter_01) < 510) && (digitalRead(potMeter_01) > 514) ) {
    if (digitalRead(potMeter_01) < 510){
      Serial.println("move stepM CCW");
      stepM1.setSpeed(digitalRead(potMeter_01));
      stepM1.runSpeed();
    } // END if

    if (digitalRead(potMeter_01) >514){
      Serial.println("move stepM CW");
      stepM1.setSpeed(digitalRead(potMeter_01));
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
  Serial.println(digitalRead(potMeter_01));
  delay(delay_1);
  

} // END void loop

