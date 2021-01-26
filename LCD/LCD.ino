//Nathan Li - LCD - 10/14/2020

#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 9, 6, 5, 4, 3);

void setup() 
{
  lcd.begin(16, 2);
  lcd.print("Seconds elapsed:");
}

void loop() 
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
