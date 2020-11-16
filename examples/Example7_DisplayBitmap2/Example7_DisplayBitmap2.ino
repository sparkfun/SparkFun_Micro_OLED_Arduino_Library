/*
  MicroOLED_Demo.ino
  SFE_MicroOLED Library Demo
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: October 27, 2014

  This sketch uses the MicroOLED library to draw bitmaps to the OLED

  This example was modified for the Qwiic Micro OLED
  Joel Bartlett
  04/12/17

  Hardware Connections:
    This example assumes you are using Qwiic. See the SPI examples for
    a detailed breakdown of connection info.

  This code is beerware; if you see me (or any other SparkFun employee) at the
  local, and you've found our code helpful, please buy us a round!

  Distributed as-is; no warranty is given.
*/

#include <Wire.h>
#include <SFE_MicroOLED.h> //Click here to get the library: http://librarymanager/All#SparkFun_Micro_OLED

#include "bitmaps.h" //Raw bitmap data

#define DC_JUMPER 1
#define PIN_RESET 9 // Optional - Connect RST on display to pin 9 on Arduino

MicroOLED oled(PIN_RESET, DC_JUMPER); //Example I2C declaration

void setup()
{
    delay(100);   //Give display time to power on
    Wire.begin(); //Setup I2C bus

    oled.begin();     // Initialize the OLED
    oled.clear(ALL);  // Clear the display's internal memory
    oled.display();   // Display what's in the buffer (splashscreen)
    delay(1000);      // Delay 1000 ms
    oled.clear(PAGE); // Clear the buffer.
}
//---------------------------------------------------------------
void loop()
{
    drawRick();
    delay(5000);

    drawMorty();
    delay(5000);
}
//---------------------------------------------------------------
void drawRick()
{
    oled.clear(ALL);
    oled.clear(PAGE);
    oled.drawBitmap(rick); //Display Logo
    oled.display();
}
//---------------------------------------------------------------

void drawMorty()
{
    oled.clear(ALL);
    oled.clear(PAGE);
    oled.drawBitmap(morty); //Display Logo
    oled.display();
}
