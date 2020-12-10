/*
  SFE_MicroOLED Library Demo
  Paul Clark @ SparkFun Electronics
  Original Creation Date: December 10th, 2020

  This sketch uses the MicroOLED library to show all the functionality built into the library

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

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
}

void loop()
{
  delay(2000);
  oled.scrollRight(0, 7, SCROLL_INTERVAL_2_FRAMES); // Scroll all pages right
  delay(2000);
  oled.scrollVertRight(0, 7, SCROLL_INTERVAL_3_FRAMES); // Scroll all pages vertical right, slower
  delay(2000);
  oled.scrollLeft(0, 7, SCROLL_INTERVAL_4_FRAMES); // Scroll all pages left, slower again
  delay(2000);
  oled.scrollVertLeft(0, 7, SCROLL_INTERVAL_5_FRAMES); // Scroll all pages vertical left, slower still...
}
