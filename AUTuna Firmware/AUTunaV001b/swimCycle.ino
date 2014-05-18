// set up servo ranges

// hi-Tech large servo: 755ms -2255ms
// hit-tec small servo: -----
// Savöx badass-servo: 790ms - 2290ms (center: 1460ms)

int swimStrokeInterval = 4; 
double swimStrokeTimeStamp;

int cycleNumber, cycleSize = 360;
int bodyPhase = 135, rearTorsoPhase = 90, tailPhase = 45, finPhase = 180;
int bodyPos, rearTorsoPos, tailPos, finPos, pectoralPos;



int bodyCenter       = 90; 
int rearTorsoCenter  = 92;
int tailCenter       = 100;
int finCenter        = 65; 
int pectoralCenter   = 90;

int bodyDeflection = 15;
int rearTorsoDeflection = 20;
int tailDeflection = 20;
int finDeflection  = 25;

int bodyLow = bodyCenter - bodyDeflection, bodyHigh = bodyCenter + bodyDeflection;
int rearTorsoLow = rearTorsoCenter - rearTorsoDeflection, rearTorsoHigh = rearTorsoCenter + rearTorsoDeflection;
int tailLow = tailCenter - tailDeflection, tailHigh = tailCenter + tailDeflection;
int finLow  = finCenter  - finDeflection,  finHigh  = finCenter  + finDeflection;

                
 //Sin table values
int Vector[] = {180, 183, 186, 189, 192, 195, 198, 201, 204, 208, 211, 214, 217, 220, 223, 226, 229, 232, 235, 238, 241, 244, 247, 250, 253, 255, 258, 261, 
                264, 267, 269, 272, 275, 277, 280, 282, 285, 288, 290, 292, 295, 297, 300, 302, 304, 306, 309, 311, 313, 315, 317, 319, 321, 323, 325, 327, 
                328, 330, 332, 333, 335, 336, 338, 339, 341, 342, 343, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 354, 355, 356, 356, 357, 357, 358, 
                358, 358, 359, 359, 359, 359, 359, 359, 359, 359, 359, 358, 358, 358, 357, 357, 356, 356, 355, 354, 354, 353, 352, 351, 350, 349, 348, 347, 
                346, 345, 343, 342, 341, 339, 338, 336, 335, 333, 332, 330, 328, 327, 325, 323, 321, 319, 317, 315, 313, 311, 309, 306, 304, 302, 300, 297, 
                295, 292, 290, 288, 285, 282, 280, 277, 275, 272, 269, 267, 264, 261, 258, 255, 253, 250, 247, 244, 241, 238, 235, 232, 229, 226, 223, 220, 
                217, 214, 211, 208, 204, 201, 198, 195, 192, 189, 186, 183, 180, 176, 173, 170, 167, 164, 161, 158, 155, 151, 148, 145, 142, 139, 136, 133, 
                130, 127, 124, 121, 118, 115, 112, 109, 106, 104, 101, 98, 95, 92, 90, 87, 84, 82, 79, 77, 74, 71, 69, 67, 64, 62, 59, 57, 55, 53, 50, 48, 
                46, 44, 42, 40, 38, 36, 34, 32, 31, 29, 27, 26, 24, 23, 21, 20, 18, 17, 16, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 5, 4, 3, 3, 2, 2, 1, 1, 1, 
                0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 20, 21, 23, 24, 26, 27, 29, 31, 32, 
                34, 36, 38, 40, 42, 44, 46, 48, 50, 53, 55, 57, 59, 62, 64, 67, 69, 71, 74, 77, 79, 82, 84, 87, 90, 92, 95, 98, 101, 104, 106, 109, 112, 
                115, 118, 121, 124, 127, 130, 133, 136, 139, 142, 145, 148, 151, 155, 158, 161, 164, 167, 170, 173, 176 };               
        


void swimCycle(){
  

if(millis() - swimStrokeTimeStamp > swimStrokeInterval){
  
     // increment servoPhases, according to reverse condition 
     phaseIncrement(reverse); 
     
     // wrap around between 0 - 359
     wrapAround();   
      

    // run sineWaves, set new positions
      
      bodyPos       = sineStroke(bodyPhase,      bodyLow,      bodyHigh);
      rearTorsoPos  = sineStroke(rearTorsoPhase, rearTorsoLow, rearTorsoHigh);
      tailPos       = sineStroke(tailPhase,      tailLow,      tailHigh);
      finPos        = sineStroke(finPhase,       finLow,       finHigh);
      
    //  and write them to the servos
      bodyServo.write(bodyPos - swimServoShift);
      rearTorsoServo.write(rearTorsoPos - swimServoShift);
      tailServo.write(tailPos - swimServoShift);
      finServo.write(finPos);
          
     
        
     
            swimStrokeTimeStamp = millis();

   }     
      
}

 //Sin table values

        
// function:

int sineStroke(int phase, int low, int high){
    
    int pos;
    pos = Vector[phase];      // get angle
    pos = map(pos, 0, 359, low, high); // map it to range low-high
    
    return pos;    // spit out value for rest of program

}

void phaseIncrement(boolean reverse){
       if(!reverse){
        
              bodyPhase      += swimCycleIncrement;
              rearTorsoPhase += swimCycleIncrement;
              tailPhase      += swimCycleIncrement;
              finPhase       += swimCycleIncrement;
        
       }

       if(reverse){
   
              bodyPhase      -= swimCycleIncrement;
              rearTorsoPhase -= swimCycleIncrement;
              tailPhase      -= swimCycleIncrement;
              finPhase       -= swimCycleIncrement;
  
        } 
  
}

void wrapAround(){
  
  
        // when phases exceed 359, wrap around to 0
    if (bodyPhase      > 359) bodyPhase      = 0;
    if (rearTorsoPhase > 359) rearTorsoPhase = 0;
    if (tailPhase      > 359) tailPhase      = 0;
    if (finPhase       > 359) finPhase       = 0;
    
    
     // if phases go below 0, reset to 0
    if(bodyPhase < 0) bodyPhase = 359;
    if(rearTorsoPhase < 0) rearTorsoPhase = 359;
    if(tailPhase < 0) tailPhase = 359;
    if(finPhase < 0) finPhase = 359;
    
  
  
}
void Glide(){
  
    
  
  
   if(bodyPos != bodyCenter){
      
     if(bodyPos < bodyCenter) bodyPos += swimCycleIncrement;
     if(bodyPos > bodyCenter) bodyPos -= swimCycleIncrement;  
     
    
   }
   
   if(rearTorsoPos != rearTorsoCenter){
      
     if(rearTorsoPos < rearTorsoCenter) rearTorsoPos += swimCycleIncrement;
     if(rearTorsoPos > rearTorsoCenter) rearTorsoPos -= swimCycleIncrement;  
     
    
   }
   
  
   if(tailPos != tailCenter){
    
     if(tailPos < tailCenter) tailPos += swimCycleIncrement;
     if(tailPos > tailCenter) tailPos -= swimCycleIncrement;  
    
   }
  
    if(bodyPos != tailCenter){
    
     if(finPos < finCenter) finPos += swimCycleIncrement;
     if(finPos > finCenter) finPos -= swimCycleIncrement;    
    
   }
  
  bodyServo.write(bodyPos);
  rearTorsoServo.write(bodyPos);
  tailServo.write(tailPos);
  finServo.write(finPos);
  pectoralServo.write(pecFinAngle); 
  
  
}
