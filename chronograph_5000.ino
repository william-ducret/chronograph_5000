

#include <LiquidCrystal_I2C.h>


const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;  // value read from the pot
int loop_resolution = 2; // ms
int refresh_rate = 100; // ms
unsigned long myTime = 0;
int start_trigger = 800;
int edge_flag = 0;
int status = 0;
int counter = 0;

// Format => (ADDRESS,Width,Height )
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() 
{
  // put your setup code here, to run once:
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  // Clear the display buffer
  lcd.clear(); 
  // Set cursor (Column, Row)
  lcd.setCursor(0, 0);
  lcd.print("Waiting for object");

}

void loop() 
{

  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");

  if (sensorValue < start_trigger)
  {
    status = 1;
  }


  if(status == 1)
  {
    if((loop_resolution * counter) > refresh_rate) // define the LCD refresh rate (50 * 2ms = 100ms)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);       
      lcd.print("Ready...");
      counter = 0;
    }

    if (sensorValue > start_trigger)
    {
      status = 2;

    }

  }
  else if(status == 2)
  {

    if((loop_resolution * counter) > refresh_rate) // define the LCD refresh rate (50 * 2ms = 100ms)
    {
      if((loop_resolution * counter) > refresh_rate) // define the LCD refresh rate (50 * 2ms = 100ms)
      {
        // Clear the display buffer
        lcd.clear(); 
        // Set cursor (Column, Row)
        lcd.setCursor(0, 0);       
        lcd.print("Go !"); 
        lcd.setCursor(0,1);
        myTime = millis();
        myTime /= 1000.0;
        lcd.print(myTime);
        counter = 0;
      }
    }

  }
  else if(status == 3)
  {
    if((loop_resolution * counter) > refresh_rate) // define the LCD refresh rate (50 * 2ms = 100ms)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);       
      lcd.print("Finished :");
      counter = 0;
    }
  }
  else
  {
    // Clear the display buffer
    lcd.clear(); 

  }

  // resolution of the loop, in ms
  delay(loop_resolution);
  counter++;

}
