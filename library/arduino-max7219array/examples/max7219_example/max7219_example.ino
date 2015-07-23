/**
 *
 *  max7219array - Library for managing arrays of LED matrix controlled 
 *                 by max7219 8-digits LED display driver.
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


// Include the library and the 4px font

   #include "max7219array.h";
   #include "max7219_font_4px.h"


// Create the array instance in the global scope

   max7219array array;


void setup()
{
  // Set the clock pin to 10 - The clock pin on the Arduino will be connected to the
  // clock pin of any Max7219 controller
  
     array.setClkPin(10);
     
  // Set the data pin to 8 - The data pin on the Arduino will be connected to the
  // data pin of any Max7219 controller
 
     array.setDinPin(8);
 
  // Configure 4 LED matrix modules with their CS pin from left to right - The CS pins
  // on the Arduino will be connected to the CS pin of the proper Max7219 controller
 
     array.addModule(13);
     array.addModule(12);
     array.addModule(11);
     array.addModule(9);

  // Load the matrix buffer with the string M-7219
  
     array.plotstring("M-7219");

  // Flush the matrix buffer to the Max7219 controllers
 
     array.flush();

}

void loop()
{ 
  // Let the matrix buffer rotate by 1 pixel every 1/10 sec. forever
  
     array.rotateleft();
     array.flush();
     delay(100);
}