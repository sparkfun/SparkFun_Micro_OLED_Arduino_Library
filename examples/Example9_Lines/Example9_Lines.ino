/*
  SFE_MicroOLED Library Demo
  Paul Clark @ SparkFun Electronics
  Original Creation Date: December 10th, 2020

  This sketch uses the MicroOLED library to show all the functionality built into the library -
  specifically the line function. This example is based on Gist by buckle2000
  https://gist.github.com/buckle2000/68dad3f24613d37625e9c2f590dd3f52

  Hardware Connections:
    This example assumes you are using Qwiic. See the SPI examples for
    a detailed breakdown of connection info.

  This code is beerware; if you see me (or any other SparkFun employee) at the
  local, and you've found our code helpful, please buy us a round!
  
  Distributed as-is; no warranty is given.
*/

#include <Wire.h>
#include <SFE_MicroOLED.h> //Click here to get the library: http://librarymanager/All#SparkFun_Micro_OLED

#define PIN_RESET 9
#define DC_JUMPER 1
MicroOLED oled(PIN_RESET, DC_JUMPER); // I2C declaration

void setup()
{
  delay(100);
  Wire.begin();

  Serial.begin(115200);
  Serial.println(F("Micro OLED Example"));

  oled.enableDebugging(); // Uncomment this line to enable debug messages on Serial

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)

  int MIDDLE_X = oled.getLCDWidth() / 2; // Find the centre of the display
  int MIDDLE_Y = oled.getLCDHeight() / 2;

  oled.clear(PAGE);
  oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X, MIDDLE_Y); // Zero length
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X - 10, MIDDLE_Y - 20, MIDDLE_X + 10, MIDDLE_Y + 20); // Steep x0<x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X - 10, MIDDLE_Y - 10, MIDDLE_X + 10, MIDDLE_Y + 10); // 45-degrees x0<x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X - 10, MIDDLE_Y - 5, MIDDLE_X + 10, MIDDLE_Y + 5); // Shallow x0<x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X - 10, MIDDLE_Y, MIDDLE_X + 10, MIDDLE_Y); // Horizontal x0<x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X, MIDDLE_Y - 10, MIDDLE_X, MIDDLE_Y + 10); // Vertical y0<y1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X + 10, MIDDLE_Y - 20, MIDDLE_X - 10, MIDDLE_Y + 20); // Steep x0>x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X + 10, MIDDLE_Y - 10, MIDDLE_X - 10, MIDDLE_Y + 10); // 45-degrees x0>x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X + 10, MIDDLE_Y - 5, MIDDLE_X - 10, MIDDLE_Y + 5); // Shallow x0>x1
  oled.display();
  delay(500);
  
  oled.clear(PAGE);
  oled.line(MIDDLE_X + 10, MIDDLE_Y, MIDDLE_X - 10, MIDDLE_Y); // Horizontal x0>x1
  oled.display();
  delay(500);

  oled.clear(PAGE);
  oled.line(MIDDLE_X, MIDDLE_Y + 10, MIDDLE_X, MIDDLE_Y - 10); // Vertical y0>y1
  oled.display();
}

void loop()
{
  // Nothing to do here...
}
