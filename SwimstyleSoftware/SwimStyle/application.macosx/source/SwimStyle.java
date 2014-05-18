import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import processing.serial.*; 
import processing.serial.*; 
import cc.arduino.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class HJFish01 extends PApplet {




    
    



ControlP5 cp5;

int numSegments = 4; // front torso, rear torso, tail, fin
float[] x = new float[numSegments];
float[] y = new float[numSegments];
float[] angle = new float[numSegments];
float fishYPosition = 300;
float fishXPosition = 300;
int speed;
int framecount;

int centerShift;
float sensorShift;

float bodyLength = 130;
float torsoSegLength = 90;
float rearTorsoSegLength;
float tailSegLength = 60;
float finSegLength = 45;
float ang = 135, ang1 = 90,  ang2 = 0, ang3 = 340;  // for thunniform, set ang2 to 45, for a more carangiform style, set ang2 to 0
//float ang = 180, ang1 = 90, ang2 = 0, ang3 = 270;
long time; 
int centerFrontTorso = 90;
int centerRearTorso = 90;
int centerTail = 90;
int centerFin = 90;
int bodyDeflection,  bodyServo  = 40,    bodyServoOffset  = -10;
int torsoDeflection, torsoServo = 41,   torsoServoOffset = -5;
int tailDeflection,  tailServo  = 42,   tailServoOffset  = -10;
int finDeflection,   finServo   = 44,   finServoOffset   = -10;
int deflection = 30;
float px, py;
boolean up = true;
int timer;

Arduino arduino;

//float targetX, targetY;

public void setup(){
 
  size(displayWidth, displayHeight);
  strokeWeight(20.0f);
  stroke(255, 100);
  fishXPosition = width/2;
  fishYPosition = height/3;
   // println(Arduino.list());  
   // arduino = new Arduino(this, Arduino.list()[7], 57600);
    //println("arduino port: " + Arduino.list()[7]);
  /*  arduino.pinMode(bodyServo, Arduino.SERVO);
    arduino.pinMode(torsoServo, Arduino.SERVO);
    arduino.pinMode(tailServo, Arduino.SERVO);
    arduino.pinMode(finServo, Arduino.SERVO);*/

  cp5 = new ControlP5(this);
     
  // add a vertical slider
  cp5.addSlider("fishYPosition")
     .setPosition(10,100)
     .setSize(200,20)
     .setRange(100,550)
     .setValue(450)
     ;
     
       cp5.addSlider("bodyLength")
     .setPosition(10,150)
     .setSize(200,20)
     .setRange(0,500)
     .setValue(285)
     ;
     
       cp5.addSlider("torsoSegLength")
     .setPosition(10,200)
     .setSize(200,20)
     .setRange(0,200)
     .setValue(60)
     ;
     
       cp5.addSlider("rearTorsoSegLength")
     .setPosition(10,250)
     .setSize(200,20)
     .setRange(0,200)
     .setValue(38)
     ;
     
       cp5.addSlider("tailSegLength")
     .setPosition(10,300)
     .setSize(200,20)
     .setRange(0,200)
     .setValue(37)
     ;
     
       cp5.addSlider("finSegLength")
     .setPosition(10,350)
     .setSize(200,20)
     .setRange(0,200)
     .setValue(29)
     ;
     
       cp5.addSlider("speed")
     .setPosition(width-300,100)
     .setSize(200,20)
     .setRange(-10,30)
     .setValue(8)
     ;
     
       cp5.addSlider("bodyDeflection")
     .setPosition(width-300,150)
     .setSize(200,20)
     .setRange(0,180)
     .setValue(20)
     ;
     
       cp5.addSlider("torsoDeflection")
     .setPosition(width-300,200)
     .setSize(200,20)
     .setRange(0,180)
     .setValue(30)
     ;
     
       cp5.addSlider("tailDeflection")
     .setPosition(width-300,250)
     .setSize(200,20)
     .setRange(0,180)
     .setValue(35)
     ;
     
       cp5.addSlider("finDeflection")
     .setPosition(width-300,300)
     .setSize(200,20)
     .setRange(0,180)
     .setValue(50)
     ;
  
       cp5.addSlider("centerShift")
     .setPosition(width/2-200,50)
     .setSize(400,10)
     .setRange(-45,45)
     .setValue(0)
     .setNumberOfTickMarks(62)
     .setSliderMode(Slider.FLEXIBLE)
     ;
  



  
  
}

public void draw(){
/*  if(framecount < 150){
  
 saveFrame("fish-####.png");
  framecount++; 
  
}*/
  
 background(0);
 fill(255);
 
 timer = 0;
 

  
  sensorShift = map(sensorShift, 0, 1000, 0, 30);
 
noStroke();
 
 bodySegment(fishXPosition, fishYPosition, ang, ang1, ang2, ang3, 5);
 

 
   ang += speed;
   ang1 += speed;
   ang2 += speed;
   ang3 += speed;
   

   

   if(ang > 360) ang = 0;
   if(ang1 > 360) ang1 = 0;
   if(ang2 > 360) ang2 = 0;
   if(ang3 > 360) ang3 = 0;
   
   if(ang < 0) ang = 360;
   if(ang1 < 0) ang1 = 360;
   if(ang2 < 0) ang2 = 360;
   if(ang3 < 0) ang3 = 360;
   


 
}


public void bodySegment(float x, float y, float a, float b, float c, float d, float sw) {
  //int angle2;
  
  strokeWeight(9);
 float servoA = a;
  pushMatrix();
  translate(x, y);
  ellipseMode(CENTER);
   line(0, 0, 0, -bodyLength);
   rect(-30,0,60,-(bodyLength/3)*2);
   ellipse(0,-(bodyLength/3)*2,60, (bodyLength/3)*2);
   
  a = sin(radians(a));
  a = map(a, radians(0), radians(115), radians(0), radians(bodyDeflection));
  
  
  
//  servoA = sin(radians(servoA));
//  servoA = map(servoA, radians(0), radians(115), radians(bodyDeflection), radians(0));
  servoA = degrees(a + radians(90-centerShift-sensorShift+bodyServoOffset));
  
  servoA = map(servoA, 0, 180, 180, 0);
  
 // arduino.servoWrite(bodyServo, int(servoA));
  println(degrees(a + radians(90-centerShift-sensorShift)));
  rotate(a + radians(90-centerShift-sensorShift));
    line(0, 0, torsoSegLength, 0);
    quad(0,-30,0,30,torsoSegLength,20,torsoSegLength, -20);
    ellipse(0,0,60,60);
  
  //ellipse(segLength, 0, 30, 30);
  torsoSegment(torsoSegLength, 0, b, c, d, sw);
  
 
  popMatrix();
}

public void torsoSegment(float x, float y, float a, float b, float c, float sw) {
  //int angle2;
   float servoA = a;
  strokeWeight(6);
  pushMatrix();
  translate(x, y);
  a = sin(radians(a + 45));
  
  a = map(a, radians(0), radians(115), radians(0), radians(torsoDeflection));
  
  servoA = degrees(a + radians(90-centerShift-sensorShift+torsoServoOffset));
  
  servoA = map(servoA, 0, 180, 180, 0);
  
 // arduino.servoWrite(torsoServo, int(servoA));
  rotate(a-radians(centerShift));
    line(0, 0, rearTorsoSegLength, 0);
    quad(0,-20,0,20,rearTorsoSegLength,10,rearTorsoSegLength, -10);
    ellipse(0,0,40,40);
  ellipseMode(CENTER);
  //ellipse(segLength, 0, 30, 30);
  tailSegment(rearTorsoSegLength, 0, b, c, sw);
 
  popMatrix();
}
public void tailSegment(float x, float y, float a, float b, float sw) {
  //int angle2;
    float servoA = a;
  strokeWeight(6);
  pushMatrix();
  translate(x, y);
  a = sin(radians(a + 45));
  a = map(a, radians(0), radians(115), radians(0), radians(tailDeflection));
  

   servoA = degrees(a + radians(90-centerShift-sensorShift+tailServoOffset));
  
  servoA = map(servoA, 0, 180, 180, 0);
  
//  arduino.servoWrite(tailServo, int(servoA));

  rotate(a-radians(centerShift));
    line(0, 0, tailSegLength, 0);
    quad(0,-10,0,10,tailSegLength,5,tailSegLength, -5);
    ellipse(0,0,20,20);
  ellipseMode(CENTER);
  //ellipse(segLength, 0, 30, 30);
  finSegment(tailSegLength, 0, b, sw);
 
  popMatrix();
}

public void finSegment(float x, float y, float a, float sw) {
  //int angle2;
    float servoA = a;
  fill(255,0,0);
  strokeWeight(6);
  pushMatrix();
  translate(x, y);
  a = sin(radians(a + 45));
  a = map(a, radians(0), radians(115), radians(0), radians(finDeflection));
  

  servoA = degrees(a + radians(90-centerShift-sensorShift-finServoOffset));
  
  //servoA = map(servoA, 0, 180, 180, 0);
  
//  arduino.servoWrite(finServo, int(servoA));
  
  rotate(a-radians(centerShift));
    line(0, 0, finSegLength, 0);
    quad(-(finSegLength/2),-5,  -(finSegLength/2), 5,   finSegLength, 1,   finSegLength,-1);   // "-(finSegLength/2)" sets the pivot point
    ellipse(0,0,10,10);
  ellipseMode(CENTER);
  //ellipse(segLength, 0, 30, 30);
 
  popMatrix();
}



public boolean sketchFullScreen() {
  return true;
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--stop-color=#cccccc", "HJFish01" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
