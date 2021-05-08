/******************************************************************************
hardware.cpp
MicroOLED Arduino Library Hardware Interface

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

#include "SFE_MicroOLED.h"
//#include <SPI.h> - included in SFE_MicroOLED.h
//#include <Wire.h> - included in SFE_MicroOLED.h

// Configure SPI settings - Max clk frequency for display is 10MHz
SPISettings oledSettings(10000000, MSBFIRST, SPI_MODE0);

/** \brief Set Up SPI Interface

	Sets up the SPI pins, initializes the Arduino's SPI interface.
**/
void MicroOLED::spiSetup(SPIClass &spiPort)
{
	// Initialize the pins:
	pinMode(dcPin, OUTPUT);	   //dc Is used for SPI and parallel interfaces but not I2C
	pinMode(MOSI, OUTPUT);	   // MOSI is an OUTPUT
	pinMode(SCK, OUTPUT);	   // SCK is an OUTPUT
	pinMode(csPin, OUTPUT);	   // CS is an OUTPUT
	digitalWrite(csPin, HIGH); // Start CS High

#if defined(__AVR__)
	pinMode(10, OUTPUT); // Required for setting into Master mode
#endif
	_spiPort = &spiPort;
	_spiPort->begin();
	moled_interface = MOLED_MODE_SPI; // Just in case moled_interface was undefined
}

/** \brief Transfer a byte over SPI

	Use the SPI library to transfer a byte. Only used for data OUTPUT.
	This function does not toggle the CS pin. Do that before and after!
**/
void MicroOLED::spiTransfer(byte data)
{
	_spiPort->beginTransaction(oledSettings);
	digitalWrite(csPin, LOW);
	_spiPort->transfer(data);
	digitalWrite(csPin, HIGH);
	_spiPort->endTransaction();
}

/** \brief Initialize the I2C Interface

	This function initializes the I2C peripheral.
**/
void MicroOLED::i2cSetup(uint8_t deviceAddress, TwoWire &wirePort)
{
	_i2cPort = &wirePort;
	if (deviceAddress != I2C_ADDRESS_UNDEFINED)
		moled_i2c_address = deviceAddress;
	moled_interface = MOLED_MODE_I2C; // Just in case moled_interface was undefined
}

/** \brief  Write a byte over I2C

	Write a byte to I2C device _address_. The DC byte determines whether
	the data being sent is a command or display data. Use either I2C_COMMAND
	or I2C_DATA in that parameter. The data byte can be any 8-bit value.
**/
void MicroOLED::i2cWrite(byte address, byte dc, byte data)
{
	_i2cPort->beginTransmission(address);
	_i2cPort->write(dc); // If data dc = 0, if command dc = 0x40
	_i2cPort->write(data);
	_i2cPort->endTransmission();
}

/** \brief  Write multiple data bytes over I2C

	Write multiple bytes to I2C device _address_.
	Returns true if all numDataBytes were written successfully
**/
boolean MicroOLED::i2cWriteMultiple(uint8_t address, uint8_t *dataBytes, size_t numDataBytes)
{
  // I2C: split the data up into packets of i2cTransactionSize
  size_t bytesLeftToWrite = numDataBytes;
  size_t bytesWrittenTotal = 0;

  while (bytesLeftToWrite > 0)
  {
    size_t bytesToWrite; // Limit bytesToWrite to i2cTransactionSize
    if (bytesLeftToWrite > ((size_t)i2cTransactionSize - 1))
      bytesToWrite = i2cTransactionSize - 1;
    else
      bytesToWrite = bytesLeftToWrite;

    _i2cPort->beginTransmission(address);
		_i2cPort->write(I2C_DATA);
    size_t bytesWritten = _i2cPort->write(dataBytes, bytesToWrite); // Write the bytes

    bytesWrittenTotal += bytesWritten; // Update the totals
    bytesLeftToWrite -= bytesToWrite;
    dataBytes += bytesToWrite; // Point to fresh data

    if (bytesLeftToWrite > 0)
    {
      if (_i2cPort->endTransmission(false) != 0) //Send a restart command. Do not release bus.
        return (false);                          //Sensor did not ACK
    }
    else
    {
      if (_i2cPort->endTransmission() != 0) //We're done. Release bus.
        return (false);                     //Sensor did not ACK
    }
  }

  return (bytesWrittenTotal == numDataBytes);
}

/** \brief Set up Parallel Interface

	This function initializes all of the pins used in the
	parallel interface.
**/
void MicroOLED::parallelSetup()
{
	pinMode(dcPin, OUTPUT); //dc Is used for SPI and parallel interfaces but not I2C

	// Initialize WR, RD, CS and data pins as outputs.
	pinMode(wrPin, OUTPUT);
	digitalWrite(wrPin, HIGH);
	pinMode(rdPin, OUTPUT);
	digitalWrite(rdPin, HIGH);
	pinMode(csPin, OUTPUT);
	digitalWrite(csPin, HIGH);
	for (int i = 0; i < 8; i++)
		pinMode(dPins[i], OUTPUT);

	moled_interface = MOLED_MODE_PARALLEL; // Just in case moled_interface was undefined
}

/** \brief Write a byte over the parallel interface

	This function will both set the DC pin, depending on whether a data or
	command byte is being sent, and it will toggle the WR, RD and data pins
	to send a byte.
**/
void MicroOLED::parallelWrite(byte data, byte dc)
{
	// Initial state: cs high, wr high, rd high
	//digitalWrite(csPin, HIGH);
	//digitalWrite(wrPin, HIGH);
	//digitalWrite(rdPin, HIGH);

	// chip select high->low
	digitalWrite(csPin, LOW);

	// dc high or low
	digitalWrite(dcPin, dc);

	// wr high->low
	digitalWrite(wrPin, LOW);

	// set data pins
	for (int i = 0; i < 8; i++)
	{
		if (data & (1 << i))
			digitalWrite(dPins[i], HIGH);
		else
			digitalWrite(dPins[i], LOW);
	}

	// wr low->high
	digitalWrite(wrPin, HIGH);

	// cs high
	digitalWrite(csPin, HIGH);
}
