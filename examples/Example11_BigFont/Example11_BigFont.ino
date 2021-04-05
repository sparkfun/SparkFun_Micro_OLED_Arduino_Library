/*
  SFE_MicroOLED Library Demo
  Paul Clark @ SparkFun Electronics
  Original Creation Date: April 3rd, 2021

  This sketch demonstrates how to use the Large Letter 31x48 font.
  This font is disabled by default. To enable it, you need to edit
  SFE_MicroOLED.cpp and change line 85 (or thereabouts) from:
  #define INCLUDE_FONT_LARGELETTER 0
  to:
  #define INCLUDE_FONT_LARGELETTER 1

  Hardware Connections:
    This example assumes you are using Qwiic. See the SPI examples for
    a detailed breakdown of connection info.

  Want to support open source hardware? Buy a board from SparkFun!
  https://www.sparkfun.com/products/13003
  https://www.sparkfun.com/products/14532

  This code is beerware; if you see me (or any other SparkFun employee) at the
  local, and you've found our code helpful, please buy us a round!
  
  Distributed as-is; no warranty is given.
*/

#include <Wire.h>
#include <SFE_MicroOLED.h> //Click here to get the library: http://librarymanager/All#SparkFun_Micro_OLED

#define PIN_RESET 9

// From version v1.3, we can instantiate oled like this (but only for I2C)
MicroOLED oled(PIN_RESET);

void setup()
{
  Serial.begin(115200); // Begin the Serial port
  Serial.println(F("SparkFun MicroOLED Example"));
  
  delay(100);
  Wire.begin();

  // This is the new way of initializing the OLED.
  // We can pass a different I2C address and TwoWire port
  // If 0x3D does not work, try 0x3C
  oled.begin(0x3D, Wire);    // Initialize the OLED

  // Print the total number of fonts loaded into memory
  Serial.print(F("There are "));
  Serial.print(oled.getTotalFonts());
  Serial.println(F(" fonts available"));

  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)

  delay(1000); // Delay 1000 ms

  oled.clear(PAGE); // Clear the buffer.

  if (oled.setFontType(4) == 0)  // Set font to type 4 (fontlargeletter31x48)
  {
    Serial.println(F("Could not enable font 4 (fontlargeletter31x48)!"));
    Serial.println(F("Have you changed the #define INCLUDE_FONT_LARGELETTER to 1 in SFE_MicroOLED.cpp?"));
    Serial.println(F("Freezing..."));
    while (1)
      ; // Do nothing more
  }
}

void loop()
{
  // Demonstrate font 4
  // There are 58 possible characters in the font 4 type: A - z
  // Lets run through all of them and print them out!
  for (int i = 'A'; i <= 'z'; i += 2)
  {
    oled.clear(PAGE);     // Clear the screen
    
    oled.setCursor(0, 0); // Set cursor to top-left
    
    oled.write(i);    // Write a byte out as a character
    oled.write(i+1);  // Write the next byte out as a character
    oled.display();   // Draw on the screen

    delay(500);           // Delay 500 ms
  }
}
