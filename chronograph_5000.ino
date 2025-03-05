
// improvement :
// - refreshing blinking : put a flag to display every information once, not continously
// - integrate loop mode (for x laps, usage of switch in n mode)


#include <LiquidCrystal_I2C.h>

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int switchPin = 12;  // the number of the pushbutton pin
const int ledPin = 11;    // the number of the LED pin
const int buttonPin = 10;  // the number of the pushbutton pin

int buttonState = 0;  // variable for reading the pushbutton status
int sensorValue = 0;  // value read from the IR sensor
int loop_resolution = 1; // ms
int refresh_rate = 100; // ms
unsigned long startTime = 0;
float endTime = 0;
unsigned long myTime = 0;
float floatTime = 0.0;
int start_trigger = 700;
int flag = 0;
int status = 0;
int counter = 0;

// Format => (ADDRESS,Width,Height )
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(switchPin, INPUT);

  // put your setup code here, to run once:
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  lcd.init();
  // lcd.backlight();

  // Clear the display buffer
  lcd.clear(); 
  // Set cursor (Column, Row)
  lcd.setCursor(0, 0);
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("object");

  analogWrite(ledPin, 0);

}

void loop() 
{

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");

// PWM LED that shows the readaing of IR sensor (conversion of the value !)
  analogWrite(ledPin, sensorValue/4);

  if ((sensorValue < start_trigger) && (status == 0))
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

    if(buttonState == 1)
    {
      status = 0;
      lcd.clear(); 
      // Set cursor (Column, Row)
      lcd.setCursor(0, 0);
      lcd.print("Waiting for");
      lcd.setCursor(0, 1);
      lcd.print("object");
      flag = 0;
    }


  }
  else if(status == 2)
  {
    if(flag == 0)
    {
      startTime = millis();
      flag = 1;
    }

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
        myTime -= startTime;
        floatTime =  myTime / 1000.0;
        lcd.print(floatTime);
        counter = 0;
      }
    }

    if (sensorValue < start_trigger)
    {
      status = 3;
      endTime = floatTime;
    }

    if(buttonState == 1)
    {
      status = 0;
      // Set cursor (Column, Row)
      lcd.setCursor(0, 0);
      lcd.print("Waiting for");
      lcd.setCursor(0, 1);
      lcd.print("object");
      flag = 0;
    }

  }
  else if(status == 3)
  {
    if((loop_resolution * counter) > refresh_rate) // define the LCD refresh rate (50 * 2ms = 100ms)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);       
      lcd.print("Finished :");
      lcd.setCursor(0, 1);       
      lcd.print(endTime);
      counter = 0;
    }

    if(0)
    {
      // reset status and all variables
      status = 0;

    }

    if(buttonState == 1)
    {
      status = 0;
      // Set cursor (Column, Row)
      lcd.setCursor(0, 0);
      lcd.print("Waiting for");
      lcd.setCursor(0, 1);
      lcd.print("object");
      flag = 0;
    }

  }
  else
  {
    // Clear the display buffer
    //lcd.clear(); 

  }

  // resolution of the loop, in ms
  delay(loop_resolution);
  counter++;

}
