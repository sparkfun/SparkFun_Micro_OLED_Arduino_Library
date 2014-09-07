#include "SFE_MicroOLED.h"
#include <SPI.h>
#include <Wire.h>

#define I2C_FREQ 400000L

void MicroView::spiSetup()
{
	ssport		= portOutputRegister(digitalPinToPort(csPin));
	sspinmask	= digitalPinToBitMask(csPin);
	ssreg		= portModeRegister(digitalPinToPort(csPin));
	
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
	
	pinMode(csPin, OUTPUT);
	digitalWrite(csPin, HIGH);
		
	SPI.setClockDivider(SPI_CLOCK_DIV2); 
	//SPI.setDataMode(SPI_MODE0);
	pinMode(csPin, OUTPUT);
	pinMode(10, OUTPUT); // Required for setting into Master mode
	digitalWrite(csPin, HIGH);
	SPI.begin();
	pinMode(SCK, OUTPUT);
	pinMode(MOSI, OUTPUT);
}

void MicroView::spiTransfer(byte data)
{
	SPI.transfer(data);
}

void MicroView::i2cSetup()
{
	Wire.begin();
	
	// SCL frequency = (F_CPU) / (16 + 2(TWBR) * (prescalar))
	TWBR = ((F_CPU / I2C_FREQ) - 16) / 2;
}

void MicroView::i2cWrite(byte address, byte dc, byte data)
{
	Wire.beginTransmission(address);
	Wire.write(dc); // If data = 0, if command = 0x40
	Wire.write(data);
	Wire.endTransmission();
}

void MicroView::parallelSetup()
{
}

void MicroView::parallelWrite(byte data, byte dc)
{
	// Initial state: cs high, wr high, rd high
	/*digitalWrite(csPin, HIGH);
	digitalWrite(wrPin, HIGH);
	digitalWrite(rdPin, HIGH);*/
	
	// chip select high->low
	//digitalWrite(csPin, LOW);
	*ssport &= ~sspinmask;		// SS LOW
	
	// dc high or low
	//digitalWrite(dcPin, dc);
	if (dc)
		*dcport |= dcpinmask;	// DC HIGH
	else
		*dcport &= ~dcpinmask;		// DC pin LOW
	
	// wr high->low
	//digitalWrite(wrPin, LOW);
	*wrport &= ~wrpinmask;		// SS LOW
	
	// set data pins
	/*for (int i=0; i<8; i++)
	{
		if (data & (1<<i))
			digitalWrite(dPins[i], HIGH);
		else
			digitalWrite(dPins[i], LOW);
	}*/
	PORTD = data;
	
	// wr low->high
	*wrport |= wrpinmask;	// SS HIGH
	//digitalWrite(wrPin, HIGH);
	
	// cs high
	//digitalWrite(csPin, HIGH);
	*ssport |= sspinmask;	// SS HIGH
}