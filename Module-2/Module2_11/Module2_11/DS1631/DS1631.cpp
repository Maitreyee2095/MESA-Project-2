
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
#include "DS1631.h"

#define TEMP_CONV_CMD 0x51
#define TEMP_READ_CMD 0xAA

DS1631::DS1631(PinName sda, PinName scl, int addr) : m_i2c(sda, scl), m_addr(addr)
{

}

DS1631::~DS1631()
{

}

float DS1631::read()
{
  I2C temperatureIn(PB_9, PB_8);
  
  const char tempConvCmd = TEMP_CONV_CMD;
  const char tempReadCmd = TEMP_READ_CMD;

  m_i2c.write(m_addr, &tempConvCmd, 1); //This command begins a temperature conversion
   wait(0.76); //12bit resolution needs 750ms
  m_i2c.write(m_addr, &tempReadCmd, 1); //This command reads the last temperature conversion result
    wait(0.1);
  char reg[2] = {0,0};
  m_i2c.read((m_addr + 1), reg, 2); //Rea
  
  unsigned short res = (reg[0] << 4) | (reg[1] >> 4);
  
  float temp =  (float) ((float)res * 0.0625);
   
  return temp;
}