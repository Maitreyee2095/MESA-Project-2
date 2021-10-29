
/* This the modified TM102 Library for the Maxim DS1631
Copyright (c) 2010 Donatien Garnier (donatiengar [at] gmail [dot] com)
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef DS1631_H
#define DS1631_H
 
#include "mbed.h"
 
 //!Library for the Maxim DS1631 temperature sensor.
 /*!
 The DS1631 is an I2C digital temperature sensor in a small DIP8 package, with a 0.0625C resolution and 0.5C accuracy.
 */

class DS1631
 {
 public:
   //!Creates an instance of the class.
   /*!
   Connect module at I2C address addr using I2C port pins sda and scl.
   DS1631
   \param addr <table><tr><th>Ax pin connections</th><th>Address</th></tr><tr><td>A0,A1,A2->GND</td><td>0x90</td></tr><tr><td>A0->V+, A1,A2-> GND</td><td>0x92</td></tr><tr><td>A0,A1->V+,A2->GND</td><td>0x96</td></tr><tr><td>A0,A1,A2->GND</td><td>0x9E</td></tr><tr><td>And so on</td><td>8 Addresses</td></tr></table>  
   */
   DS1631(PinName sda, PinName scl, int addr);
   
   /*!
   Destroys instance.
   */ 
   ~DS1631();
   
   //!Reads the current temperature.
   /*!
   Reads the temperature register of the DS1631 and converts it to a useable value.
   */
   float read();
   
 private:
   I2C m_i2c;
   int m_addr;
 
 };
 
 #endif
