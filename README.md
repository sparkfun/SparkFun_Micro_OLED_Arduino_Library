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

Contributing
--------------

If you would like to contribute to this library: please do, we truly appreciate it, but please follow [these guidelines](./CONTRIBUTING.md). Thanks!

MicroOLED: Version 1.3 - A New Hope
---------------

Prior to version 1.3, this library was hard-wired to the ```Wire``` I<sup>2</sup>C and ```SPI``` ports. Version 1.3
allows alternate ports to be used, in a way which is backward-compatible with the previous versions.

We have of course tested the new code, but if you do notice any compatibility issues please
[raise an issue](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/issues).

### I<sup>2</sup>C Example

Prior to v1.3, you would have used:
```
#define DC_JUMPER 1
MicroOLED oled(PIN_RESET, DC_JUMPER); // I2C declaration
```

followed by:
```
oled.begin();    // Initialize the OLED
```

From v1.3.0, you can still do it that way, or can do it like this:
```
MicroOLED oled(PIN_RESET); // The TwoWire I2C port is passed to .begin instead
```

followed by:
```
oled.begin(0x3D, Wire);    // Initialize the OLED using address 0x3D and the Wire port
```

To use a non-standard address or port, you can call:
```
oled.begin(0x3C, Qwiic);    // Initialize the OLED using address 0x3C and the Qwiic port
```

Please see [this example](./examples/Example10_MultiDemo_v13/Example10_MultiDemo_v13.ino) for more details.

### SPI Example

For SPI in v1.3, you still need to instantiate the oled using:
```
MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS); //SPI declaration
```

If you want to use _SPI_ as the SPIClass, then you can continue to call:
```
  oled.begin();    // Initialize the OLED
```

To use a non-standard port, call:
```
  oled.begin(SPI1);    // Initialize the OLED using SPI1
```

Please see [this example](./examples/SPI/MicroOLED_Demo_v13/MicroOLED_Demo_v13.ino) for more details.

Version History
---------------

* [v 1.3.0](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1.3.0) - adding support for non-standard I<sup>2</sup>C and SPI ports
* [v 1.2.10](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1.2.10) - prevent-write-outside-buffer corrections; improved I2C transfer speeds; includes the missing scroll functions; ```line``` corrections; ```enableDebugging```.
* [v 1.2.9](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1.2.9) - drawIcon() correction
* [v 1.2.8](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/releases/tag/v1%2C2.8) - Add drawIcon() and resort examples with Qwiic as default.
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

Please see [LICENSE.md](./LICENSE.md) for more information.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
