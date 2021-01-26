//Nathan Li - 15 May 2020

#include <Servo.h>

   int motorA1  = 3; //Left Forward
   int motorA2  = 5;
   int motorB1  = 6; //Right Forward
   int motorB2  = 9; 
   int light1 = 2;
   int light2 = 4;
   int light3 = 7;
   int light4 = 8;
   int light5 = 10;
   int Servopin = 11;
   int BTled  = A0;
   int state;
   int vSpeed;
   char ch;
   Servo Servo1;

   unsigned long startMillis = 0;
   unsigned long currentMillis = 0;
   int lightPins[] = {2, 4, 7, 8, 10};
   int index = 1;
   int previousIndex = 0;
   int LEDdirection = 1;
   int KITT = 0;

void setup() {

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(light1, OUTPUT); 
    pinMode(light2, OUTPUT);
    pinMode(light3, OUTPUT);
    pinMode(light4, OUTPUT);
    pinMode(light5, OUTPUT);     
    Servo1.attach(Servopin);
    Serial.begin(9600);
    Servo1.write(90);
    
    startMillis = millis();
}

void loop() {

  //Save income data to variable 'state'
    if(Serial.available() > 0){     
      state = Serial.read();
      ch = state;
      Serial.print("state:");Serial.print(state);
      Serial.print(" ch:");Serial.print(ch);
    }
     


    if(state == '0')
     vSpeed = 0;
    if(state == '1')
     vSpeed = 120;
    if(state == '2')
     vSpeed = 140;
    if(state == '3')
     vSpeed = 160;
    if(state == '4')
     vSpeed = 180;
    if(state == '5')
     vSpeed = 200;
    if(state == '6')
     vSpeed = 210;
    if(state == '7')
     vSpeed = 220;
    if(state == '8')
     vSpeed = 230;
    if(state == '9')
     vSpeed = 240;
    if(state == 'q')
     vSpeed = 255;
     

  /***********************Forward****************************/
  //If state is equal with number 'F', car will go forward!
    if (state == 'F') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0);
      Servo1.write(90);      

    }  
  
  /***********************Backward****************************/
  //If state is equal with number 'B', car will go backward
    else if (state == 'B') {
      analogWrite(motorA1, 0); analogWrite(motorA2, vSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
      Servo1.write(90); 

    }

  /***************************Right*****************************/
  //If state is equal with number 'R', wheels will turn right
    else if (state == 'R') {
      analogWrite(motorA1, 0); analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
      Servo1.write(160);    

    }
    
  /***************************Left*****************************/
  //If state is equal with number 'L', wheels will turn left
    else if (state == 'L') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
      analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
      Servo1.write(20);    

    }

  /**********************Forward Right************************/
  //If state is equal with number 'I', car will go forward right
    else if (state == 'I') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
      Servo1.write(160);        

    }
    
  /**********************Forward Left************************/
  //If state is equal with number 'G', car will go forward left
    else if (state == 'G') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0);  
      Servo1.write(20);      

    }
    
  /**********************Backward Right************************/
  //If state is equal with number 'J', car will go backward right
    else if (state == 'J') {
      analogWrite(motorA1, 0); analogWrite(motorA2, vSpeed);
      analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
      Servo1.write(160);   

    }
    
  /**********************Backward Left************************/
  //If state is equal with number 'H', car will go backward left
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
      analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
      Servo1.write(20);   

    }
    
  /***************************Stop*****************************/
  //If state is equal with number 'S', stop the car
    else if (state == 'S') {
      analogWrite(motorA1, 0); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0); analogWrite(motorB2, 0);  
      Servo1.write(90); 
      
    }
    
  /***************************All LED*****************************/
  //If state is equal with letter 'W', light1 turn on
    if (state == 'W' && state != 'U') {
      digitalWrite(light1, HIGH); 
      digitalWrite(light2, HIGH); 
      digitalWrite(light3, HIGH); 
      digitalWrite(light4, HIGH); 
      digitalWrite(light5, HIGH); 
    }
    if (state == 'w') {
      digitalWrite(light1, LOW); 
      digitalWrite(light2, LOW); 
      digitalWrite(light3, LOW); 
      digitalWrite(light4, LOW); 
      digitalWrite(light5, LOW); 
    }

    /***************************KITT Sequence*****************************/
  //If state is equal with letter 'U', light2 turn on
    if (state == 'U' && state != 'W') {
       KITT = 1;
    }
    if (KITT == 1)
    {
      currentMillis = millis();
       if (currentMillis - startMillis >= 100)
       {
         digitalWrite(lightPins[index], HIGH);
         digitalWrite(lightPins[previousIndex], LOW);
         if (LEDdirection == 0)
         {
          index--;
          previousIndex--;
         }
         else
         {
          index++;
          previousIndex++;
         }
         if (index == 5)
         {
          index = index - 2;
          LEDdirection = 0;
         }
         if (index == -1)
         {
          index = index + 2;
          LEDdirection = 1;
         }
         startMillis = currentMillis;
       }
    }
    if (state == 'u') {
      digitalWrite(light1, LOW); 
      digitalWrite(light2, LOW); 
      digitalWrite(light3, LOW); 
      digitalWrite(light4, LOW); 
      digitalWrite(light5, LOW);
      KITT = 0; 
    }
}
