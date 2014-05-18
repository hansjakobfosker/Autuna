// This firmware is written by hydrobionics, free for all to use and abuse. It's released under creative commons. 


//Libraries:

#include <Wire.h>  // for depth module

#include <Servo.h>  // for servos


Servo finServo, tailServo, rearTorsoServo, bodyServo, pectoralServo;


// globas variables:


// for depth & orientation:
float targetDepth = 0.5, targetIncline;
float depth;
double depthReadingTimeStamp;
int depthReadingInterval = 500;


// for swimming maneuvers:  
int swimServoShift, swimCycleIncrement = 1;
int pecFinAngle = 90;
double obstacleTimeStamp;
int obstacleInterval = 1;
boolean reverse;
boolean glide = false;

// lighting stuff

const int numAmbienceReadings = 10;
int ambienceReadings[numAmbienceReadings];

  



const int numReadings = 30;

int leftReadings[numReadings];         // the readings from the analog input
int rightReadings[numReadings];       // the readings from the analog input
int frontReadings[numReadings];      // the readings from the analog input
int downReadings[numReadings];      // the readings from the analog input    




void setup() {
  // put your setup code here, to run once:
  
  // set pinmodes:
  
  pinMode(A0, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  // "attach servos:
  bodyServo.attach(44);
  rearTorsoServo.attach(42);
  tailServo.attach(41);
  finServo.attach(40);
  pectoralServo.attach(45);
  
  //rangeFinder array initializers
  
        for (int thisReading = 0; thisReading < numReadings; thisReading++){    leftReadings[thisReading] = 0;}
        for (int thisReading = 0; thisReading < numReadings; thisReading++){    rightReadings[thisReading] = 0;}
        for (int thisReading = 0; thisReading < numReadings; thisReading++){    frontReadings[thisReading] = 0;}
        for (int thisReading = 0; thisReading < numReadings; thisReading++){    downReadings[thisReading] = 0;}
  
  Serial.begin(9600);
  
  // pressure module stuff
  
    

  Serial.println("Code is running");
  delay(1000);
  Wire.begin();
  Serial.println("initialized I2C");
  delay(10);
  delay(1000);
  
  initializePressure();
  measureAtmosphere();
  
  // set lighting resolution
  
  //analogWriteResolution(10);
  

}

void loop() {
  

  
  //checkLight();
  
  //checkHeading();  // Check IMU for compass heading.
 
 // checkInclination(); // check IMU for vertical angle in the water.  
  
  // If time has expired, Check the depth module for current depth, and measure it against targetDepth.
  if(millis() - depthReadingTimeStamp > depthReadingInterval){
    checkDepth();  
    depthReadingTimeStamp = millis();
  }
  
    checkMissionStatus(); // check if objective has been met, and if so move on to next and set new behaviour
    
    
  
  //Obstacle check is the last to happen before the swimCycle iteration, so that the range finders will override everything else. 
  
 checkForObstacles(); // check rangefinders for objects in the sensor field. Work out evasive maneuvers, and set parameters for next swimCycle.

 
  
  
  swimCycle(); // iterate swimCycle, stepping all the servos to their next position according to the previous checks.
  
  if(glide){
   
      Glide(); 
    
  }
}
