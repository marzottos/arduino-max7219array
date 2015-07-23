/**
 *
 *  max7219array  - Library for managing arrays of LED matrix controlled 
 *                  by max7219 8-digits LED display driver.
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

#include "Arduino.h"
#include "max7219array.h"


max7219array::max7219array()
{
    currentClkPin = 0;
    currentDinPin = 0;
    currentCsPin  = 0;  
    modulesCount  = 0;
    //modulesCS     = NULL;
    //matrix        = NULL;
    for(int i=0;i<64;i++)
      matrix[i]=0;

}

void max7219array::setClkPin(byte clkPin)
{
  currentClkPin = clkPin;
  pinMode(clkPin,OUTPUT);
}

void max7219array::setDinPin(byte dinPin)
{
  currentDinPin = dinPin;
  pinMode(dinPin,OUTPUT);
}

void max7219array::addModule(byte moduleCsPin)
{
  pinMode(moduleCsPin,OUTPUT);
  digitalWrite(moduleCsPin,HIGH);
  modulesCS[modulesCount] = moduleCsPin;
  initModule(modulesCount);
  modulesCount++;
}

void max7219array::writeByte(byte module, byte data) 
{   
  for(byte i=0;i<8;i++)
  {		  
    digitalWrite(currentClkPin,LOW);
    digitalWrite(currentDinPin,data&0x80);  //Obtain the MSB of the data
    data = data<<1;
    digitalWrite(currentClkPin,HIGH);
  }
}

void max7219array::write(byte module, byte address, byte data)
{
        digitalWrite(modulesCS[module],LOW);
        writeByte(module,address);
        writeByte(module,data);
        digitalWrite(modulesCS[module],HIGH);
}

void max7219array::initModule(byte module)
{
  /*
  Serial.println("init module");
  Serial.print("Module:");
  Serial.print(module);
  Serial.print(" CS:");
  Serial.print(modulesCS[module]);
  Serial.print(" CLK:");
  Serial.print(currentClkPin);
  Serial.print(" DTA:");
  Serial.println(currentDinPin);
  */

 write(module, 0x09, 0x00);       //decode (always no decode)
 write(module, 0x0a, 0x03);       //Brightness (0..15)
 write(module, 0x0b, 0x07);       //Display digits (always 7, digit = column)
 write(module, 0x0c, 0x01);       //Shutdown (0x01 Normal | 0x00 Shutdown)
 write(module, 0x0f, 0x00);       //Display test (0x01 Test | 0x00 Normal)
 
 write(module, 0x01, 0x00);       // digit 0 -> first column
 write(module, 0x02, 0x00);       // digit 1
 write(module, 0x03, 0x00);       // digit 2
 write(module, 0x04, 0x00);       // digit 3
 write(module, 0x05, 0x00);       // digit 4
 write(module, 0x06, 0x00);       // digit 5
 write(module, 0x07, 0x00);       // digit 6
 write(module, 0x08, 0x00);       // digit 7 -> last column
}

void max7219array::setBrightness(byte brightness)
{
	for(byte module=0;module<modulesCount;module++)
		write(module, 0x0a, brightness);
}

void max7219array::shutdown()
{
	for(byte module=0;module<modulesCount;module++)
		write(module, 0x0c, 0x00);
}

void max7219array::resume()
{
	for(byte module=0;module<modulesCount;module++)
		write(module, 0x0c, 0x01);
}

void max7219array::test(byte seconds)
{
	for(byte module=0;module<modulesCount;module++)
		write(module, 0x0f, 0x01);
		
	delay(1000*seconds);
	
	for(byte module=0;module<modulesCount;module++)
		write(module, 0x0f, 0x00);
}


void max7219array::plot(byte x,byte y, byte color=1)
{
  if(color==1)
    matrix[x]=matrix[x]|(1<<y);
  
  if(color==0)
    matrix[x]=matrix[x]&(0xff-(1<<y));
}

void max7219array::plotline(int x1,int y1, int x2, int y2,int color=1)
{
  int x,y;
  int a,b;
  int tmp;
  int d,q,k,s;
  int swap = 0;
  int DX = x2 - x1;
  int DY = y2 - y1;

  //siccome scambio DY e DX ho sempre DX>=DY allora per sapere quale coordinata occorre cambiare uso una variabile
  if (abs(DX) < abs(DY)) 
  {
     tmp = DX;
     DX  = DY;
     DY  = tmp;

     swap = 1;
  }

  //per non scrivere sempre i valori assoluti cambio DY e DX con altre variabili
  a = abs(DY);
  b = -abs(DX);

  //assegna le coordinate iniziali
  x = x1;
  y = y1;

  //il nostro valore d0
  d = 2 * a + b;

  //s e q sono gli incrementi/decrementi di x e y
  q = 1;
  s = 1;
  
  if (x1 > x2) q = -1;
  if (y1 > y2) s = -1;

  plot(x, y, color);
  plot(x2, y2, color);
  
  for (k = 0; k < -b; k+=1) 
  {
   if (d > 0) {
       x= x + q; y= y + s;
       d= d + 2 * (a + b);
   }
   else {
       x = x + q;
       if (swap==1) { y = y + s; x = x - q; }
       d = d + 2 * a;
   }

   plot(x, y, color);
  }
}

void max7219array::plotletter(char letter)
{
  int letterLen = font[letter-32][0];
  
  for(int p=1;p<=letterLen;p++)
  {
    matrix[p] = font[letter-32][p];
  }
}

void max7219array::plotletterat(int x, char letter)
{
  int letterLen = font[letter-32][0];
  
  for(int p=0;p<letterLen;p++)
  {
    matrix[p+x] = font[letter-32][p+1];
  }
}

void max7219array::plotstring(char string[])
{
  int letter=0;
  int pos=0;
  
  while(string[letter]!=0)
  {
    plotletterat(pos,string[letter]);
    pos+=font[string[letter]-32][0];
    pos+=1;
    letter++;
  }
}

void max7219array::rotateleft()
{
  byte first;
  
  first = matrix[0];
  for(int i=0; i<(8*modulesCount)-1; i++)
  {
    matrix[i]=matrix[i+1];
  }
  matrix[(8*modulesCount)-1]=first;
}

void max7219array::rotateright()
{
  byte last;
  
  last = matrix[(8*modulesCount)-1];
  for(int i=(8*modulesCount)-1; i>0; i--)
  {
    matrix[i]=matrix[i-1];
  }
  matrix[0]=last;
}

void max7219array::shiftleft()
{
  for(int i=0; i<(8*modulesCount)-1; i++)
  {
    matrix[i]=matrix[i+1];
  }
  matrix[(8*modulesCount)-1]=0;
}

void max7219array::shiftright()
{
  for(int i=(8*modulesCount)-1; i>0; i--)
  {
    matrix[i]=matrix[i-1];
  }
  matrix[0]=0;
}

void max7219array::clear()
{
    for(int i=0;i<64;i++)
      matrix[i]=0;
}

void max7219array::invert()
{
  for(int i=0; i<8*modulesCount; i++)
  {
  	matrix[i] = 255-matrix[i];
  }
}

void max7219array::flush()
{
  byte module;
  byte row;

  for(int i=0; i<8*modulesCount; i++)
  {
    module = i>>3;
    row = i % 8;
    write(module,row+1,matrix[i]);   //NB: Le righe della matrice partono dall'indirizzo 1
  }
}

