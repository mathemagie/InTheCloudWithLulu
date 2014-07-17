#include <Process.h>
#include <Bridge.h>
#include <Console.h>
int vitessemotor;
int firsttimea = 1;
int firsttimeb = 1;
int result_tmp = -1;

int motorPin = 3;

void setup() {
  Bridge.begin();   // Initialize the Bridge
  Console.begin();
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  Process p;
  p.runShellCommand("/usr/bin/curl http://mathemagie.net/projects/julien_gps/get_motions.php");
  Serial.println("run curl command");


  while (p.running());

  // Read command output. runShellCommand() should have passed "Signal: xx&":
  while (p.available()) {
    int result = p.parseInt();
    if (result == 1 && result_tmp ==0) firsttimea =1;
    if (result == 2 && result_tmp ==0) firsttimeb =1;
    result_tmp = result;
    
    Serial.println(result);

     if (result == 0) {
        vitessemotor = 0; 
        Serial.println(vitessemotor);
        analogWrite(motorPin, vitessemotor);
        delay(10000);
      
     }  
      
     if (result == 1) {
        vitessemotor = 220; 
        Serial.println(vitessemotor);
        analogWrite(motorPin, vitessemotor);
         if (firsttimea) {
           Serial.println("boucle ajustement");
         
          analogWrite(motorPin, 255);
          delay(3000);
          analogWrite(motorPin, 220);
          firsttimea = 0;

        }
        
        delay(10000);
      
     }  
     
      if (result == 2) {
        vitessemotor = 240; 
        Serial.println(vitessemotor);
        analogWrite(motorPin, vitessemotor);
         if (firsttimeb) {
           Serial.println("boucle ajustement");
          analogWrite(motorPin, 255);
          delay(3000);
          analogWrite(motorPin, 240);
          firsttimeb = 0;
        }
        delay(10000);
      
     }  
    
     if (result == 3) {
        vitessemotor = 255; 
        Serial.println(vitessemotor);
        analogWrite(motorPin, vitessemotor);
        delay(10000);
      
     }  
    
     
   }
}
