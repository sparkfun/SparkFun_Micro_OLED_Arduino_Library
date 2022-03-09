/******************************************************************************
SFE_MicroOLED.h
Header file for the MicroOLED Arduino Library

Jim Lindblom @ SparkFun Electronics
October 26, 2014
https://github.com/sparkfun/Micro_OLED_Breakout/tree/master/Firmware/Arduino/libraries/SFE_MicroOLED

Modified by:
Emil Varughese @ Edwin Robotics Pvt. Ltd.
July 27, 2015
https://github.com/emil01/SparkFun_Micro_OLED_Arduino_Library/


This file defines the hardware interface(s) for the Micro OLED Breakout. Those
interfaces include SPI, I2C and a parallel bus.

Development environment specifics:
Arduino 1.0.5
Arduino Pro 3.3V
Micro OLED Breakout v1.0

This code was heavily based around the MicroView library, written by GeekAmmo
(https://github.com/geekammo/MicroView-Arduino-Library), and released under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef SFE_MICROOLED_H
#define SFE_MICROOLED_H

#include <stdio.h>
#include <Arduino.h>

#include <Wire.h> // Needed for TwoWire - even if we are using SPI or Parallel
#include <SPI.h> // Needed for SPIClass - even if we are using I2C or Parallel

#if defined(ARDUINO_ARCH_MBED)
	// ARDUINO_ARCH_MBED (APOLLO3 v2) does not support or require pgmspace.h / PROGMEM
#elif defined(__AVR__) || defined(__arm__) || defined(__ARDUINO_ARC__)
	#include <avr/pgmspace.h>
#else
	#include <pgmspace.h>
#endif

#define I2C_ADDRESS_SA0_0 0b0111100
#define I2C_ADDRESS_SA0_1 0b0111101
#define I2C_ADDRESS_UNDEFINED 0b00000000
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

#define BLACK 0
#define WHITE 1

#define LCDWIDTH 64
#define LCDHEIGHT 48
#define FONTHEADERSIZE 6

#define NORM 0
#define XOR 1

#define PAGE 0
#define ALL 1

#define WIDGETSTYLE0 0
#define WIDGETSTYLE1 1
#define WIDGETSTYLE2 2

#define SETCONTRAST 0x81
#define DISPLAYALLONRESUME 0xA4
#define DISPLAYALLON 0xA5
#define NORMALDISPLAY 0xA6
#define INVERTDISPLAY 0xA7
#define DISPLAYOFF 0xAE
#define DISPLAYON 0xAF
#define SETDISPLAYOFFSET 0xD3
#define SETCOMPINS 0xDA
#define SETVCOMDESELECT 0xDB
#define SETDISPLAYCLOCKDIV 0xD5
#define SETPRECHARGE 0xD9
#define SETMULTIPLEX 0xA8
#define SETLOWCOLUMN 0x00
#define SETHIGHCOLUMN 0x10
#define SETSTARTLINE 0x40
#define MEMORYMODE 0x20
#define COMSCANINC 0xC0
#define COMSCANDEC 0xC8
#define SEGREMAP 0xA0
#define CHARGEPUMP 0x8D
#define EXTERNALVCC 0x01
#define SWITCHCAPVCC 0x02

// Scroll
#define ACTIVATESCROLL 0x2F
#define DEACTIVATESCROLL 0x2E
#define SETVERTICALSCROLLAREA 0xA3
#define RIGHTHORIZONTALSCROLL 0x26
#define LEFT_HORIZONTALSCROLL 0x27
#define VERTICALRIGHTHORIZONTALSCROLL 0x29
#define VERTICALLEFTHORIZONTALSCROLL 0x2A

#define SCROLL_INTERVAL_5_FRAMES 0b000
#define SCROLL_INTERVAL_64_FRAMES 0b001
#define SCROLL_INTERVAL_128_FRAMES 0b010
#define SCROLL_INTERVAL_256_FRAMES 0b011
#define SCROLL_INTERVAL_3_FRAMES 0b100
#define SCROLL_INTERVAL_4_FRAMES 0b101
#define SCROLL_INTERVAL_25_FRAMES 0b110
#define SCROLL_INTERVAL_2_FRAMES 0b111

typedef enum CMD
{
	CMD_CLEAR,		  //0
	CMD_INVERT,		  //1
	CMD_CONTRAST,	  //2
	CMD_DISPLAY,	  //3
	CMD_SETCURSOR,	  //4
	CMD_PIXEL,		  //5
	CMD_LINE,		  //6
	CMD_LINEH,		  //7
	CMD_LINEV,		  //8
	CMD_RECT,		  //9
	CMD_RECTFILL,	  //10
	CMD_CIRCLE,		  //11
	CMD_CIRCLEFILL,	  //12
	CMD_DRAWCHAR,	  //13
	CMD_DRAWBITMAP,	  //14
	CMD_GETLCDWIDTH,  //15
	CMD_GETLCDHEIGHT, //16
	CMD_SETCOLOR,	  //17
	CMD_SETDRAWMODE	  //18
} commCommand_t;

typedef enum COMM_MODE
{
	MOLED_MODE_SPI,
	MOLED_MODE_I2C,
	MOLED_MODE_PARALLEL,
	MOLED_MODE_UNDEFINED
} micro_oled_mode;

class MicroOLED : public Print
{
public:
	// Constructor(s)
	MicroOLED(uint8_t rst = 255); // I2C - leaving the address currently undefined
	MicroOLED(uint8_t rst, uint8_t dc); // I2C
	MicroOLED(uint8_t rst, uint8_t dc, uint8_t cs); // SPI
	MicroOLED(uint8_t rst, uint8_t dc, uint8_t cs, uint8_t wr, uint8_t rd,
			  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7); // Parallel

	boolean begin(void); // Needed for backward-compatibility
	boolean begin(uint8_t deviceAddress, TwoWire &wirePort); // User-defined I2C address and TwoWire
	boolean begin(SPIClass &spiPort); // User-defined SPIClass

	virtual size_t write(uint8_t); // Virtual - for I2C _or_ SPI

	void enableDebugging(Stream &debugPort = Serial); //Turn on debug printing. If user doesn't specify then Serial will be used.

	// RAW LCD functions
	void command(uint8_t c);
	void data(uint8_t c);
	void setColumnAddress(uint8_t add);
	void setPageAddress(uint8_t add);

	// LCD Draw functions
	void clear(uint8_t mode);
	void clear(uint8_t mode, uint8_t c);
	void invert(boolean inv);
	void contrast(uint8_t contrast);
	void display(void);
	void setCursor(uint8_t x, uint8_t y);
	void pixel(uint8_t x, uint8_t y);
	void pixel(uint8_t x, uint8_t y, uint8_t color, uint8_t mode);
	void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t mode);
	void lineH(uint8_t x, uint8_t y, uint8_t width);
	void lineH(uint8_t x, uint8_t y, uint8_t width, uint8_t color, uint8_t mode);
	void lineV(uint8_t x, uint8_t y, uint8_t height);
	void lineV(uint8_t x, uint8_t y, uint8_t height, uint8_t color, uint8_t mode);
	void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode);
	void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
	void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode);
	void circle(uint8_t x, uint8_t y, uint8_t radius);
	void circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color, uint8_t mode);
	void circleFill(uint8_t x0, uint8_t y0, uint8_t radius);
	void circleFill(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color, uint8_t mode);
	void drawChar(uint8_t x, uint8_t y, uint8_t c);
	void drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode);
	void drawBitmap(uint8_t *bitArray);
	void drawIcon(uint8_t locationX, uint8_t locationY, uint8_t iconWidth, uint8_t iconHeight, uint8_t *bitArray, uint8_t arraySizeInBytes, bool overwrite = false);
	uint8_t getLCDWidth(void);
	uint8_t getLCDHeight(void);
	void setColor(uint8_t color);
	void setDrawMode(uint8_t mode);
	uint8_t *getScreenBuffer(void);

	// Font functions
	uint8_t getFontWidth(void);
	uint8_t getFontHeight(void);
	uint8_t getTotalFonts(void);
	uint8_t getFontType(void);
	uint8_t setFontType(uint8_t type);
	uint8_t getFontStartChar(void);
	uint8_t getFontTotalChar(void);

	// LCD Rotate Scroll functions
	// start and stop are PAGE addresses: 0-7
	void scrollRight(uint8_t start, uint8_t stop, uint8_t scrollInterval = SCROLL_INTERVAL_2_FRAMES);
	void scrollLeft(uint8_t start, uint8_t stop, uint8_t scrollInterval = SCROLL_INTERVAL_2_FRAMES);
	void scrollVertRight(uint8_t start, uint8_t stop, uint8_t scrollInterval = SCROLL_INTERVAL_2_FRAMES);
	void scrollVertLeft(uint8_t start, uint8_t stop, uint8_t scrollInterval = SCROLL_INTERVAL_2_FRAMES);
	void scrollStop(void);
	void flipVertical(boolean flip);
	void flipHorizontal(boolean flip);

	//Control the size of the internal I2C transaction amount
	void setI2CTransactionSize(uint8_t bufferSize);
	uint8_t getI2CTransactionSize(void);

	//Set the max number of bytes set in a given I2C transaction
	uint8_t i2cTransactionSize = 32; //Default to ATmega328 limit

	void initDisplay(bool clearDisplay = true); //Set CGRAM settings. Useful if display gets corrupt.

private:
	uint8_t csPin, dcPin, rstPin;
	uint8_t wrPin, rdPin, dPins[8];
	volatile uint8_t *wrport, *wrreg, *rdport, *rdreg;
	uint8_t wrpinmask, rdpinmask;
	micro_oled_mode moled_interface = MOLED_MODE_UNDEFINED;
	byte moled_i2c_address = I2C_ADDRESS_UNDEFINED;
	volatile uint8_t *ssport, *dcport, *ssreg, *dcreg; // use volatile because these are fixed location port address
	uint8_t mosipinmask, sckpinmask, sspinmask, dcpinmask;
	uint8_t foreColor, drawMode, fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar, cursorX, cursorY;
	uint16_t fontMapWidth;
	static const unsigned char *fontsPointer[];
	void swapOLED(uint8_t *x, uint8_t *y);

	//Debug
	Stream *_debugPort;			 //The stream to send debug messages to if enabled. Usually Serial.
	boolean _printDebug = false; //Flag to print debugging variables

	void beginCommon(); // Functionality common to all begin methods

	// Communication
	void spiTransfer(byte data);
	void spiSetup(SPIClass &spiPort = SPI);
	void i2cSetup(uint8_t deviceAddress = I2C_ADDRESS_UNDEFINED, TwoWire &wirePort = Wire);
	void i2cWrite(byte address, byte control, byte data);
	boolean i2cWriteMultiple(byte address, uint8_t *dataBytes, size_t numDataBytes);
	void parallelSetup();
	void parallelWrite(byte data, byte dc);

	TwoWire *_i2cPort;		//The generic connection to user's chosen I2C hardware

	SPIClass *_spiPort;			 //The generic connection to user's chosen SPI hardware
};
#endif
