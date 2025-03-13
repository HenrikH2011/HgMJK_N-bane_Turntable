/* Project: HgMJK, Turntable for N-scale
Version: RC 1.1.2
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
1. OK - test analogRead for potMeter_01 = A0
  OK - test readings: max=1007, min=0, middel:(1007/2=503,5)=503
  OK - set middel pos (stop stepM movement) > 501 | < 505 : to be adjusted in stepM move test
2. OK - test stepM move according to analogRead potMeter_01
  OK - TEST: adjusted potmeter values to: > 498 | < 508 :OK - to be adjusted if needed
  OK - edit code for move speed. slow to faster in both ways CW and CCW
3. test with turntable

4. in-prograss: cleanup code and comments
*/

/* ******************** Code start *********************************** */

// Include libraryes
#include <Arduino.h>
#include <AccelStepper.h>

// define variables
int delay_1 = 50; // delay in milliseconds
int delay_2 = 500;

// define Pin constants
const int potMeter_01 = A0; // Potentiometer Pin

const int LED_01 = 2; // Green LED Pin - stepM moving
const int LED_02 = 3; // Red LED Pin - stepM not moving

const int stepM1_IN1 = 8;  // StepMotor Pin
const int stepM1_IN2 = 9;
const int stepM1_IN3 = 10;
const int stepM1_IN4 = 11;

// define stepper motor interface type - 4 == FULL4WIRE
#define MotorInterfaceType_1 4 // stepM1 setup

AccelStepper stepM1 = AccelStepper(MotorInterfaceType_1, stepM1_IN1, stepM1_IN3, stepM1_IN2, stepM1_IN4);

// move stepM ClockWise / CounterClockWise at speed from potentiometer reading
void moveStepM (){
  Serial.println("Move stepM CW or CCW");
  digitalWrite(LED_01, HIGH); // Green LED - stepM moving
  digitalWrite(LED_02, LOW); // Red LED - stepM not moving
  stepM1.enableOutputs(); // enable all stepM output pins

  stepM1.setCurrentPosition(0);

  while ( (analogRead(potMeter_01) < 498) | (analogRead(potMeter_01) > 508) ) {
    
    if (analogRead(potMeter_01) >508){
      Serial.println("move stepM CW");
      
      // read potmeter value and calculate steps
      int16_t steps = -508 + (analogRead(potMeter_01));
      Serial.print("steps: ");
      Serial.println(steps);
      stepM1.setSpeed(steps);      
      stepM1.runSpeed();
    } // END if

    if (analogRead(potMeter_01) < 498){
      Serial.println("move stepM CCW");

      // read potmeter value and calculate steps
      int16_t steps = -(498 - analogRead(potMeter_01));
      Serial.print("steps: ");
      Serial.println(steps);
      stepM1.setSpeed(steps);
      stepM1.runSpeed();
    } // END if

 
  } // END while

  stepM1.disableOutputs(); // disable all stepM output pins
  digitalWrite(LED_01, LOW); // Green LED
  digitalWrite(LED_02, HIGH); // Red LED
  
} // END void moveStepM

void setup(){
  Serial.begin(9600);

  pinMode (LED_01, OUTPUT);
  pinMode (LED_02, OUTPUT);

  pinMode (stepM1_IN1, OUTPUT);
  pinMode (stepM1_IN2, OUTPUT);
  pinMode (stepM1_IN3, OUTPUT);
  pinMode (stepM1_IN4, OUTPUT);

  stepM1.disableOutputs();
  stepM1.setMaxSpeed(500);
  stepM1.setAcceleration(50);
  
  digitalWrite(LED_01, LOW); // Green LED
  digitalWrite(LED_02, HIGH); // Red LED

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

