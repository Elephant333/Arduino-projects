//Nathan Li - Obstacle Avoidance - 11/17/2020
#include <MeMCore.h>

MeUltrasonicSensor ultraSensor(PORT_3); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
MeDCMotor motor1(M1); //Motor1 is Left Motor, diameter = 64.5mm
MeDCMotor motor2(M2); //Motor2 is Right Motor, diameter = 64.3mm
int chooseDirection = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  if (ultraSensor.distanceCm() >= 15)
  {
    motor1.run(-100); //Motor1 (Left)  forward is -negative
    motor2.run(100);  //Motor2 (Right) forward is +positive
  }
  else
  {
    chooseDirection = random(0,2);
    if (chooseDirection == 0) //turn left
    {
      motor1.run(100);
      motor2.run(-100);
      delay(500);
      motor1.run(100);
      motor2.run(100);
      delay(random(500,1000));
    }
    if (chooseDirection == 1) //turn right
    {
      motor1.run(100);
      motor2.run(-100);
      delay(500);
      motor1.run(-100);
      motor2.run(-100);
      delay(random(500,1000));
    }
  }
  delay(100); /* the minimal measure interval is 100 milliseconds */
}
