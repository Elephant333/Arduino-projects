//Nathan Li - Advanced Obstacle Avoidance - 11/29/2020
#include <MeMCore.h>

MeUltrasonicSensor ultraSensor(PORT_3); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
MePort input(PORT_4);
MeDCMotor motor1(M1); //Motor1 is Left Motor, diameter = 64.5mm
MeDCMotor motor2(M2); //Motor2 is Right Motor, diameter = 64.3mm
float frontDistance;
float leftDistance; //slot 2 of rj25 module
float rightDistance; //slot 1 of rj25 module
int maxFrontDistance = 25;
int maxLeftDistance = 20;
int maxRightDistance = 20;
int motorSpeed = 255;

void setup()
{
  Serial.begin(9600);
}

void loop() //Some logic adapted from https://create.arduino.cc/projecthub/jrance/arduino-obstacle-avoidance-robot-with-ultrasonic-hc-sr04-23035d
{
  checkLeftDistance();
  checkFrontDistance();
  checkRightDistance();
  
  Serial.print("leftDistance:  ");
  Serial.print(leftDistance);
  Serial.print("\t");
  Serial.print("Front distance: ");
  Serial.print(frontDistance);
  Serial.print(" cm");
  Serial.print("\t");
  Serial.print("rightDistance: ");
  Serial.println(rightDistance);

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
