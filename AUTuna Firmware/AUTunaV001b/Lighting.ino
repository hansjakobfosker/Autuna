int leftLight = 4, rightLight = 5;
int leftLighting, rightLighting;
int ledPin = 13;

int indx = 0;                  // the indx of the current reading
int total = 0;                  // the running total
//int average = 0;                // the average

int inputPin = A0;
int padding = 10;
int ambience, target = 600, ledVal;

void checkLight(){
 
  
  ambience = (analogRead(leftLight) + analogRead(rightLight))/2;
  
  /*
  total= total - ambienceReadings[indx];         
  // read from the sensor:  
  ambienceReadings[indx] = analogRead(inputPin); 
  // add the reading to the total:
  total= total + ambienceReadings[indx];       
  // advance to the next position in the array:  
  indx = indx + 1;  
  
  if (indx >= numAmbienceReadings)              
    // ...wrap around to the beginning: 
  indx = 0;                           

  // calculate the average:
  ambience = total / numAmbienceReadings;  
  */
 
  
  if((ambience - target) > padding) ledVal++;
    if((ambience - target) > 100) ledVal += 10;
  
  if((ambience - target) < -padding) ledVal--;
    if((ambience - target) < -100) ledVal -= 10;
  

  
  
  ledVal = constrain(ledVal, 0, 255);
  analogWrite(ledPin, ledVal); 
  /*
    Serial.print("ambience: ");
  Serial.print(ambience);
  Serial.print(", ledVal: ");
  Serial.println(ledVal); 
  */
  
}
