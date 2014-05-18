// lots of objectives...
int objective = 0;
boolean complete;
float buf = 0.1;

void checkMissionStatus(){
  
  switch(objective){
   
   case 0:
   
      // set some behavior here
      targetDepth = 0.4;
        
          
          
          
          
        
      
      // set some success condition, and if true, set complete to true:
      if(complete == true){
          objective++;
          complete = false;
      }
      
      
    break;
    
    
   case 1:
   
     // set some other behavior here
     
          if(complete == true){
          objective++;
          complete = false;
      }
     
     
      
    break; 
    
  }
  
 
  
}
