//Nathan Li - Advanced Obstacle/Edge Avoidance - 12/3/2020
#include <MeMCore.h>

MeUltrasonicSensor ultraSensor(PORT_3); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
MeLineFollower lineFinder(PORT_2); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MePort input(PORT_4);
MeDCMotor motor1(M1); //Motor1 is Left Motor, diameter = 64.5mm
MeDCMotor motor2(M2); //Motor2 is Right Motor, diameter = 64.3mm
float frontDistance;
float leftDistance; //slot 2 of rj25 module
float rightDistance; //slot 1 of rj25 module
int maxFrontDistance = 25;
int maxLeftDistance = 20;
int maxRightDistance = 20;
int motorSpeed = 150;
int sensorState;

void setup()
{
  Serial.begin(9600);
}

void loop() //Some logic adapted from https://create.arduino.cc/projecthub/jrance/arduino-obstacle-avoidance-robot-with-ultrasonic-hc-sr04-23035d
{
  checkFrontDistance();
  if (frontDistance < maxFrontDistance)
  {
    motor1.run(motorSpeed);
    motor2.run(-motorSpeed);
    delay(500); // move backwards 0.5 seconds
    checkLeftDistance();
    checkRightDistance();
    if (leftDistance < rightDistance) //turn right
    {
      motor1.run(-motorSpeed);
      motor2.run(-motorSpeed);
    }
    else
    {
      if (leftDistance > rightDistance) //turn left
      {
        motor1.run(motorSpeed);
        motor2.run(motorSpeed);
      }
    }
  }
  else
  {
    motor1.run(-motorSpeed); //Motor1 (Left)  forward is -negative
    motor2.run(motorSpeed);  //Motor2 (Right) forward is +positive
  }

  checkLeftDistance();
  if (leftDistance < maxLeftDistance)
  {
    checkLeftDistance();
    checkRightDistance();
    if (leftDistance > rightDistance) //move forward
    {
      motor1.run(-motorSpeed);
      motor2.run(motorSpeed);
    }
    else
    {
      if (leftDistance < rightDistance) //turn right
      {
        motor1.run(-motorSpeed);
        motor2.run(-motorSpeed);
      }
    }
  }

  checkRightDistance();
  if (rightDistance < maxRightDistance)
  {
    checkLeftDistance();
    checkRightDistance();
    if (rightDistance > leftDistance) //move forward
    {
      motor1.run(-motorSpeed);
      motor2.run(motorSpeed);
    }
    else
    {
      if (rightDistance < leftDistance) //turn left
      {
        motor1.run(motorSpeed);
        motor2.run(motorSpeed);
      }
    }
  }

  checkEdge();

  checkLeftDistance();
  checkFrontDistance();
  checkRightDistance();

  Serial.print("leftDistance: ");
  Serial.print(leftDistance);
  Serial.print("\t");
  Serial.print("Front distance: ");
  Serial.print(frontDistance);
  Serial.print(" cm");
  Serial.print("\t");
  Serial.print("rightDistance: ");
  Serial.println(rightDistance);
  
  delay(100); /* the minimal measure interval is 100 milliseconds */
}

void checkLeftDistance()
{
  leftDistance = (float)65398*pow(input.aRead2(),-1.45); //output is in cm
}

void checkFrontDistance()
{
  frontDistance = ultraSensor.distanceCm();
}

void checkRightDistance()
{
  rightDistance = (float)65398*pow(input.aRead1(),-1.45); //output is in cm
}

void checkEdge()
{
  sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: 
      Serial.println("Sensor 1 and 2 are inside of black line"); //front is near an edge
      motor1.run(motorSpeed);
      motor2.run(-motorSpeed);
      delay(500); // move backwards 0.5 seconds
      checkLeftDistance();
      checkRightDistance();
      if (leftDistance < rightDistance) //turn right 1 seconds
      {
        motor1.run(-motorSpeed);
        motor2.run(-motorSpeed);
        delay(1000);
      }
      else
      {
        if (leftDistance > rightDistance) //turn left 1 seconds
        {
          motor1.run(motorSpeed);
          motor2.run(motorSpeed);
          delay(1000);
        }
      }
      break;
    case S1_IN_S2_OUT: 
      Serial.println("Sensor 2 is outside of black line"); //left side is near an edge
      motor1.run(motorSpeed);
      motor2.run(-motorSpeed);
      delay(500); // move backwards 0.5 seconds
      motor1.run(-motorSpeed);
      motor2.run(-motorSpeed);
      delay(500); //turn right 0.5 seconds
      break;
    case S1_OUT_S2_IN: 
      Serial.println("Sensor 1 is outside of black line"); //right side is near an edge
      motor1.run(motorSpeed);
      motor2.run(-motorSpeed);
      delay(500); // move backwards 0.5 seconds
      motor1.run(motorSpeed);
      motor2.run(motorSpeed);
      delay(500); //turn left 0.5 seconds
      break;
    case S1_OUT_S2_OUT: 
      Serial.println("Sensor 1 and 2 are outside of black line"); //all is good
      break;
    default:
      break;
  }
}
