//Nathan Li - Black Line Follower - 11/10/2020
#include <MeMCore.h>

MeLineFollower lineFinder(PORT_2); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MeDCMotor motor1(M1); //Motor1 is Left Motor
MeDCMotor motor2(M2); //Motor2 is Right Motor

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: 
      Serial.println("Sensor 1 and 2 are inside of black line"); 
      motor1.run(-75); //Motor1 (Left)  forward is -negative
      motor2.run(75); //Motor2 (Right) forward is +positive
      break;
    case S1_IN_S2_OUT: 
      Serial.println("Sensor 2 is outside of black line"); //straying to the right of line
      motor1.run(75);
      motor2.run(75); 
      break;
    case S1_OUT_S2_IN: 
      Serial.println("Sensor 1 is outside of black line"); //straying to the left of line
      motor1.run(-75);
      motor2.run(-75);
      break;
    case S1_OUT_S2_OUT: 
      Serial.println("Sensor 1 and 2 are outside of black line");
      motor1.run(75);
      motor2.run(-75);
      break;
    default:
      break;
  }
}
