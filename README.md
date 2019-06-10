SparkFun Micro OLED Breakout Arduino Library
========================================

<table class="table table-hover table-striped table-bordered">
  <tr align="center">
   <td><a href="https://www.sparkfun.com/products/13003"><img src="https://cdn.sparkfun.com//assets/parts/9/9/5/6/OLED_Action.jpg" alt="SparkFun Micro OLED Breakout"></a></td>
   <td><a href="https://www.sparkfun.com/products/14532"><img src="https://cdn.sparkfun.com//assets/parts/1/2/6/2/1/14532-SparkFun_Micro_OLED_Breakout__Qwiic_-01.jpg" alt="SparkFun Micro OLED Breakout (Qwiic)"></a></td>
  </tr>
  <tr align="center">
    <td><i><a href="https://www.sparkfun.com/products/13003">SparkFun Micro OLED Breakout (LCD-13003)</a></i></td>
    <td><i><a href="https://www.sparkfun.com/products/14532">SparkFun Micro OLED Breakout (Qwiic)</a></i></td>
  </tr>
</table>

An Arduino library that allows you to draw shapes and text on the Micro OLED display and Qwiic micro OLED breakout.

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE.
  * **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE.
* **library.properties** - General library properties for the Arduino package manager.

Documentation
--------------

* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.
* **[Product Repository](https://github.com/sparkfun/Micro_OLED_Breakout)** - Main repository (including hardware files) for the Micro OLED Breakout.
* **[Hookup Guide](https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide)** - Basic hookup guide for the Micro OLED Breakout.

Products that use this Library
---------------------------------

* [Micro OLED Breakout](https://www.sparkfun.com/products/13003)- A breakout for the monochrome 64x48 OLED.
* [Micro OLED Breakout (Qwiic)](https://www.sparkfun.com/products/14532) - Qwiic version of the Micro OLED breakout with jumpers set for I2C

Version History
---------------
* [v 1.2.7](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1.2.7) - Add more comments and Wire.begin() to examples
* [v 1.2.6](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/V_1.2.6) - Removes call of Wire.begin from library
* [v 1.2.5](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1.2.5) - Adding Qwiic Examples for I2C
* [v 1.2.4](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v.1.2.4) - Add colon to 7-segment font, add version history information to README, move and rename swap function to avoid namespace issues, add support for Arduino 101.
* [v 1.2.3](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1.2.3) -- Fix for I2C dcPin not configured
* [v 1.2.0](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/V_1.2.0) - add SAMD21 support, fix PROGMEM and `_BV` errors
* v 1.1.3 (not released)
* [v 1.1.2](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/tree/V_1.1.2) - Added compatibility for ESP8266
* [v 1.1.1](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/tree/V_1.1.1) - Changed to remove register level pin access, for cross-platform compatibility
* [v 1.1.0](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/tree/V_1.1.0) - Matching 1.6 standard
* [V 1.0.0](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/tree/V_1.0.0) - Initial release

License Information
-------------------

This product is _**open source**_!

The **code** is released under the GPL v3 license. See the included LICENSE.md for more information.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
