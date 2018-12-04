/******************************************************************************
 * MicroOLED_Demo.ino
 * SFE_MicroOLED Library Demo
 * Jim Lindblom @ SparkFun Electronics
 * Original Creation Date: October 27, 2014
 * 
 * This sketch uses the MicroOLED library to draw bitmaps to the OLED 
 * 
 * This example was modified for the Qwiic Micro OLED
 * Joel Bartlett
 * 04/12/17
 * 
 * Development environment specifics:
 *  Arduino 1.0.5
 *  Arduino Pro 3.3V
 *  Micro OLED Breakout v1.0
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ******************************************************************************/
#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include "bitmaps.h"

//////////////////////////
// MicroOLED Definition //
//////////////////////////
//The library assumes a reset pin is necessary. The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is not being used
#define PIN_RESET 9  
//The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration

void setup()
{
  delay(100);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
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
    oled.drawBitmap(rick);//Display Logo
    oled.display();
}
//---------------------------------------------------------------

void drawMorty()
{
    oled.clear(ALL);
    oled.clear(PAGE);
    oled.drawBitmap(morty);//Display Logo
    oled.display();
}
