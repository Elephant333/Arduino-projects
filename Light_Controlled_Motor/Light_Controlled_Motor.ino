// Nathan Li 10/1/2020, Motor controlled by photoresistor, artifical light created by LED and potentiometer

int ledPin = 3;
int motorPin = 5;
const int potPin = A0;
const int resPin = A1;
int resCalibration = 800;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  Serial.print("Potentiometer value: ");
  Serial.print(analogRead(potPin));
  Serial.print("\t");
  Serial.print("Photoresistor value: ");
  Serial.print(analogRead(resPin));
  Serial.println();
  analogWrite(ledPin, map(analogRead(potPin), 0, 1024, 0, 255));
  if (analogRead(resPin) < resCalibration)
  {
    analogWrite(motorPin, 0);
  }
  else
  {
    analogWrite(motorPin, map(analogRead(resPin), resCalibration, 1024, 0, 255));
  }
}
