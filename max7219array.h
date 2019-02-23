/**
 *
 *  max7219array   - Library for managing arrays of LED matrix controlled 
 *                   by max7219 8-digits LED display driver.
 *
 *  Created by Silvio Marzotto, Jannary 31, 2015.
 *  Copyright (C) 2015 Silvio Marzotto. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  Library version: 1.0
 *  Last update: february 1, 2015
 *  Documentation at: http://www.0ex.it/
 *  Compatible with the Arduino IDE 1.0.6
 *  
 */

#ifndef max7219array_h
#define max7219array_h

#include "Arduino.h"

class max7219array
{
  public:
    /*port definition*/
    byte currentClkPin;
    byte currentDinPin;
    byte currentCsPin;
    byte modulesCount;
    //byte *mudulesCS;
    //byte *matrix;
    byte modulesCS[8];
    byte matrix[64];
    
    max7219array();
    void setClkPin(byte clkPin);
    void setDinPin(byte dinPin);
    
    void addModule(byte moduleCsPin);
    void writeByte(byte module, byte data);
    void write(byte module, byte address, byte data);
    void initModule(byte module);
    
	void test(byte seconds);
	void setBrightness(byte brightness);
	void shutdown();
	void resume();
	
    void plot(byte x,byte y, byte color);
    void plotline(int x1,int y1, int x2, int y2,int color);
    void plotletter(char letter);
    void plotletterat(int x, char letter);
    void plotstring(const char string[]);
    
    void rotateleft();
    void rotateright();
    void shiftleft();
    void shiftright();
    
    void clear();
    void invert();
    
    void flush();
    
  private:
    const static byte font[255][6] PROGMEM;

};
#endif

