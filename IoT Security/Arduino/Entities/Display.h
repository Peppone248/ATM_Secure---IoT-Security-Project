#include <math.h>
#include <LiquidCrystal.h>

const int LCD_PIN1 = 8;
const int LCD_PIN2 = 9;
const int LCD_PIN3 = 10;
const int LCD_PIN4 = 11;
const int LCD_PIN5 = 12;
const int LCD_PIN6 = 13;
const int BATTERY_PIN = A13;

LiquidCrystal lcd(LCD_PIN1, LCD_PIN2, LCD_PIN3, LCD_PIN4, LCD_PIN5, LCD_PIN6);

class Display
{
  public:

    void printLogo()
    {
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print(F("I.o.T. for C.S."));
      lcd.setCursor(1, 1);
      lcd.print(F("    Group 3"));
    }

    void printAlarm(char * message)
    {
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      // Print a message to the LCD.
      //lcd.write(byte(0));
      //lcd.write(byte(1));
      lcd.print("     ");
      lcd.print(message);
      lcd.setCursor(1, 1);
      lcd.print(F("  triggered!"));
      //lcd.write(byte(2));
      //lcd.write(byte(3));
    }

    void printBatteryStatus()
    {
      lcd.begin(16, 2);
      int sensorValue = analogRead(BATTERY_PIN);
      float voltage = (sensorValue * 8.4) / 5.4;
      voltage = voltage / 100;
      voltage = floorf(voltage * 100) / 100;
      lcd.setCursor(0,0);
      lcd.print("voltage = ");
      lcd.print(voltage); //print the voltage to LCD
      lcd.print(" V");
      //analogRead : 5v = x : 8.4v
    }
};
