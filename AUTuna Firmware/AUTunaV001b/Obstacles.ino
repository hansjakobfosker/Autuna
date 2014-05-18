int left = 0, right = 1, front = 2, down = 3;
int leftReading, rightReading, frontReading, downReading;
int leftShift, rightShift, frontShift, downShift;
int sensorMin = 20;
boolean obsLeft, obsRight, obsFront, obsDown; 
int steeringIncrement = 5, depthIncrement = 10;


int threshold = 100;  // lower distance limit for when to execute evasion
// int leftThreshold, rightThreshold, frontThreshold, downThreshold;  // may need these if sensors are weird

// left
int leftIndx = 0;                  // the indx of the current reading
int leftTotal = 0;                  // the running total
int leftAverage = 0;                // the average

// right
int rightIndx = 0;                  // the indx of the current reading
int rightTotal = 0;                  // the running total
int rightAverage = 0;                // the average

// front
int frontIndx = 0;                  // the indx of the current reading
int frontTotal = 0;                  // the running total
int frontAverage = 0;                // the average

// down
int downIndx = 0;                  // the indx of the current reading
int downTotal = 0;                  // the running total
int downAverage = 0;                // the average

void checkForObstacles(){
     swimServoShift = 0;
  

  //Serial.println(leftReading);

  // update sensor image  
    readSensors();
  
      
 
  
  // flush values, to avoid compounding accross loops
     leftShift  = 0;
      rightShift = 0;
       frontShift = 0;
        downShift  = 0;
       
     obsLeft  = false;
      obsRight = false;
       obsFront = false;
        obsDown  = false;     
     
     reverse = false;
     
    // if ranges are below the threshold...
  if(leftReading < threshold) obsLeft = true;
  if(rightReading < threshold) obsRight = true;
  if(frontReading < threshold) obsFront = true;
  if(downReading < threshold) obsDown = true;
  
  // 1-sensor combos:
  
  // obstacle to the left, nowhere else. Steer right.
  if(obsLeft && !obsRight && !obsFront && !obsDown) steerRight();
  
  // obstacle to the right, nowhere else. Steer left. 
  if(!obsLeft && obsRight && !obsFront && !obsDown) steerLeft();
  
  // obstacle to the front, nowhere else. Steer left.
  if(!obsLeft && !obsRight && obsFront && !obsDown) steerLeft();
  
  // obstacle down, nowhere else. Steer up.
  if(!obsLeft && !obsRight && !obsFront && obsDown) climb();
  
  
  // 2 adjacent sensors combos
  
  // obstacle to the right and left. hit reverse.
  if(obsLeft && obsRight && !obsFront && !obsDown) reverse = true;
  
  // obstacle to the front and right. Steer left
  if(!obsLeft && obsRight && obsFront && !obsDown) steerLeft();
  
  // obstacle to the front and down. Steer up & right
  if(!obsLeft && !obsRight && obsFront && obsDown){ steerRight(); climb();}
  
  // obstacle to the left and down. Steer up & right
  if(obsLeft && !obsRight && !obsFront && obsDown){ steerRight(); climb();}
  
  
  // 3 adjacent sensor combos
  
  // obstacle to the front, left, and right. go reverse.
  if(obsLeft && obsRight && obsFront && !obsDown) reverse = true;
  
  // obstacle right, front & down. Steer up & left
  if(!obsLeft && obsRight && obsFront && obsDown){ steerLeft(); climb();}
  
  // obstacle left, front & down. Steer up & right
  if(obsLeft && !obsRight && obsFront && obsDown){ steerRight(); climb();}
  
  // obstacle left, right & down. Hit Reverse
  if(obsLeft && obsRight && !obsFront && obsDown) reverse = true;
  
  
  // all sensors equal
  
  // obstacle to the front, left, right and down. go reverse.
  if(obsLeft && obsRight && obsFront && obsDown) reverse = true;
  
  // All sensors off, no obstacles: smooth sailing = true.. 
   
   
  // 2 opposite sensors combos
  
  // obstacle to the left & front. go right;
  if(obsLeft && !obsRight && obsFront && !obsDown) steerRight();
  
  // obstacle to the right & down. steer up & left;
  if(!obsLeft && obsRight && !obsFront && obsDown){ steerLeft(); climb(); }
  
 
 /*
  Serial.print("rightShift: ");
  Serial.print(rightShift);
  Serial.print(", leftShift: ");
  Serial.println(leftShift);
  */
  
 // flush shiftValue to avoid compounding across loops
 
   // add left & right values
   //swimServoShift = swimServoShift + leftShift - rightShift;
 
 //Serial.println(swimServoShift);
  
}

void steerLeft(){
   
 
   leftShift = rightReading;
   /* 
   Serial.print("leftShift: ");
   Serial.println(leftShift);*/
   leftShift = constrain(leftShift, sensorMin, threshold);
   leftShift = map(leftShift, sensorMin, threshold, 30, 0);
   swimServoShift = swimServoShift + leftShift;
   
}

void steerRight(){
  
  //if(rightReading >= threshold) rightReading = threshold;
   rightShift = leftReading;

   rightShift = constrain(rightShift, sensorMin, threshold);
   rightShift = map(rightShift, sensorMin, threshold, 30, 0);
   /*Serial.print("rightShift: ");
   Serial.println(rightShift);*/
   swimServoShift = swimServoShift - rightShift;
}



void climb(){
  
    //if(rightReading >= threshold) rightReading = threshold;
   pecFinAngle = downReading;

   pecFinAngle = constrain(pecFinAngle, sensorMin, threshold);
   pecFinAngle = map(pecFinAngle, sensorMin, threshold, 150, 90);

  
}


void readSensors(){
  
  // update sensor "image" with fresh readings
   leftReading   = analogRead(left);
  rightReading  = analogRead(right);
  frontReading  = analogRead(front);
  downReading   = analogRead(down);

  // run ranger equation on each reading
  leftReading = ranger(leftReading);
   rightReading = ranger(rightReading);
    frontReading = ranger(frontReading);
     downReading  = ranger(downReading);
  
        // subtract the last reading from each array:
  leftTotal= leftTotal - leftReadings[leftIndx];
   rightTotal= rightTotal - rightReadings[rightIndx];    
    frontTotal= frontTotal - frontReadings[frontIndx];    
     downTotal =  downTotal - downReadings[downIndx];    
  
  // input the sensor readings to the respective arrays:  
  leftReadings[leftIndx] = leftReading;
    rightReadings[rightIndx] = rightReading;
      frontReadings[frontIndx] = frontReading;
        downReadings[downIndx] = downReading;
        
  // add the reading to the total:
  leftTotal= leftTotal + leftReadings[leftIndx];
    rightTotal= rightTotal + rightReadings[rightIndx];
      frontTotal= frontTotal + frontReadings[frontIndx];
        downTotal= downTotal + downReadings[downIndx];  
        
  // advance to the next position in the arrays:  
  leftIndx += 1;
    rightIndx += 1;  
      frontIndx += 1;  
        downIndx += 1;    

  // if we're at the end of the arrays...
  if (leftIndx >= numReadings) leftIndx = 0;   
    if (rightIndx >= numReadings) rightIndx = 0;  
      if (frontIndx >= numReadings) frontIndx = 0;  
        if (downIndx >= numReadings) downIndx = 0;    
    // ...wrap around to the beginning: 
                           

  // calculate the average:
  leftAverage = leftTotal / numReadings;
   rightAverage = rightTotal / numReadings; 
     frontAverage = frontTotal / numReadings;
       downAverage = downTotal / numReadings;      
  // send it to the computer as ASCII digits
  
    
  leftReading = leftAverage;
    rightReading = rightAverage;
      frontReading = frontAverage;
        downReading = downAverage;
        
/*
  Serial.print("leftReading: ");
  Serial.print(leftReading);
  Serial.print(", rightReading: ");
  Serial.print(rightReading);
  Serial.print(", frontReading: ");
  Serial.print(frontReading);
  Serial.print(", downReading: ");
  Serial.println(downReading);
*/

 
  
}
  


int ranger(int value){
    if (value < 10){ 
      value = 10;
    }
    return ((67870.0 / (value - 3.0)) - 40.0);
}



