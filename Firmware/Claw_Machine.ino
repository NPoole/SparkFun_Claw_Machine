/**************************************
        Actobotics Crane Game

            Nick P 2015
            
        SparkFun Electronics
**************************************/

#include <Servo.h>

Servo claw; // Initialize Servo object for claw

boolean clawState = 0; // Boolean to store claw position (open/close)

void setup() {
  
  // DEBUGGING
  Serial.begin(9600);

  // Attach claw servo
  claw.attach(4);

  // Setup outputs
  for(int i=0; i<12; i++){   
    pinMode(i, OUTPUT);}

  // Setup inputs with pull-up resistors    
  pinMode(A5, INPUT); digitalWrite(A5, HIGH); // button 
  pinMode(A1, INPUT); digitalWrite(A1, HIGH); // jstick 
  pinMode(A2, INPUT); digitalWrite(A2, HIGH); // jstick   
  pinMode(A3, INPUT); digitalWrite(A3, HIGH); // jstick   
  pinMode(A4, INPUT); digitalWrite(A4, HIGH); // jstick   
  pinMode(9, INPUT);  //digitalWrite(9, HIGH);  // xlimit
  pinMode(10, INPUT); //digitalWrite(10, HIGH); // ylimit  
  pinMode(12, INPUT); //digitalWrite(12, HIGH); // zlimit
  
  claw.write(120);
  
} 

void loop() {
// Read joystick inputs sequentially and
// actuate the appropriate motor
  
  while(digitalRead(A1)==LOW){moveX(0);}
  while(digitalRead(A3)==LOW){moveX(1);} 
  while(digitalRead(A2)==LOW){moveY(0);} 
  while(digitalRead(A4)==LOW){moveY(1);}
  if(digitalRead(A5)==LOW){grab(); setHome();}
  stopAll();
  
  // DEBUGGING
  //if(!digitalRead(9)){Serial.println("X LIMIT");}
  //if(!digitalRead(10)){Serial.println("Y LIMIT");}
  
}

void moveX(boolean dir){ 
// Pass this function a 0 to go right, a 1 to go left

  // Choose direction of travel
  if(dir){digitalWrite(6, LOW); //Serial.println("X1"); 
  }else{digitalWrite(6, HIGH); /*Serial.println("X0");*/ }
  
  // Turn up the go-juice 
  analogWrite(3, 255);
  
}

void moveY(boolean dir){ 
// Pass this function a 0 to go back, a 1 to go forward  

  // Choose direction of travel
  if(dir){digitalWrite(7, LOW); //Serial.println("Y1"); 
  }else{digitalWrite(7, HIGH); /*Serial.println("Y0");*/ }
  
  // Turn up the go-juice 
  analogWrite(5, 255);
  
}

void grab(){
// Classic crane game behavior:
// Down, actuate claw, up, home, actuate claw 
  
  // Bounce appears problematic
  delay(100); 
  
  digitalWrite(8, 0);
  
  analogWrite(11, 100);
  delay(800);
  analogWrite(11, 0);
  
  delay(3000);
  
  claw.write(35);
  
  delay(2000);
  
  // TESTING ONLY: Flip claw state
  //if(clawState){claw.write(140); clawState=0;
  //}else{claw.write(60); clawState=1;}
  
  digitalWrite(8, 1);
  
  while(digitalRead(12)){analogWrite(11, 200);}
  analogWrite(11, 20);

  // Bounce appears problematic
  delay(100); 
  
}

void setHome(){
// Bring the crane to the home position over the prize chute  
  
  // Prepare to move back and to te left
  digitalWrite(6, HIGH); digitalWrite(7, LOW);
 
  // Move left until XLimit is reached
  while(digitalRead(9)){analogWrite(3, 255);}
  analogWrite(3, 0);
  
  // Move back until YLimit is reached
  while(digitalRead(10)){analogWrite(5, 255);}
  analogWrite(5, 0);
  
  claw.write(120);
  analogWrite(11, 0);
  
  delay(2000);
  
  digitalWrite(8, 1);
  
  while(digitalRead(12)){analogWrite(11, 200);}
  analogWrite(11, 80);
 
}

void stopAll(){
// STOP EVERYTHING

    analogWrite(3 ,0); // moveX OFF
    analogWrite(5 ,0); // moveY OFF
    analogWrite(11 ,0); // cranePulley OFF
  
}
