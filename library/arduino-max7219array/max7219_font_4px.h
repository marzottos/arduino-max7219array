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
 
#ifndef max7219array_font_4px_h
#define max7219array_font_4px_h

#include "Arduino.h"

byte max7219array::font[100][6] = {
  {5,0,0,0,0,0},           // ' '   32
  {2,95,15},               // '!'
  {0,0,0,0,0,0},    // '"'
  {0,0,0,0,0,0},    // '#'   35
  {5,36,42,127,42,18},    // '$'
  {5,35,19,8,100,98},     // '%'
  {0,0,0,0,0,0},    // '&'
  {0,0,0,0,0,0},    // '''
  {3,28,34,65},           // '('   40
  {3,65,34,28},           // ')'
  {0,0,0,0,0,0},    // '*'
  {3,8,28,8},              // '+'
  {3,128,224,96},          // ','
  {3,8,8,8},               // '-'   45
  {2,96,96},               // '.'
  {0,0,0,0,0,0},    // '/'
  {4,62,65,65,62},      // '0'   48
  {2,2,127},            // '1'
  {4,98,81,73,70},      // '2'   50
  {4,34,65,73,54},      // '3'
  {4,28,18,127,16},     // '4'
  {4,39,69,69,57},      // '5'
  {4,62,73,73,50},      // '6'
  {4,3,97,25,7},        // '7'   55
  {4,54,73,73,54},      // '8'
  {4,38,73,73,62},      // '9'
  {1,36},             // ':'   58
  {3,128,230,102},         // ';'
  {3,8,20,34},             // '<'   60
  {3,20,20,20},            // '='
  {3,34,20,8},             // '>'
  {0,0,0,0,0,0},           // '?'
  {5,62,65,93,81,94},      // '@'
  {5,124,18,17,18,124},    // 'A'   65
  {5,65,127,73,73,54},     // 'B'
  {5,62,65,65,65,34},      // 'C'
  {5,65,127,65,65,62},     // 'D'
  {5,127,73,73,73,65},     // 'E'
  {5,127,9,9,9,1},         // 'F'
  {5,62,65,73,73,58},      // 'G'
  {5,127,8,8,8,127},       // 'H'
  {3,65,127,65},           // 'I'
  {5,32,64,65,63,1},       // 'J'
  {5,127,8,8,20,99},       // 'K'
  {5,127,64,64,64,64},     // 'L'
  {5,127,2,4,2,127},       // 'M'
  {5,127,2,4,8,127},       // 'N'
  {5,62,65,65,65,62},      // 'O'
  {5,65,127,73,9,6},       // 'P'
  {5,62,65,97,65,190},     // 'Q'
  {5,65,127,9,25,102},     // 'R'
  {5,38,73,73,73,50},      // 'S'
  {5,1,1,127,1,1},         // 'T'
  {5,63,64,64,64,63},      // 'U'
  {5,31,32,64,32,31},      // 'V'
  {5,127,32,16,32,127},    // 'W'
  {5,99,20,8,20,99},       // 'X'
  {5,3,68,120,68,3},       // 'Y'
  {5,99,81,73,69,99},      // 'Z'


  
};
#endif
