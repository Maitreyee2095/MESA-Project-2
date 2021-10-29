/*!
*\file pindef.h
*\brief Macros for I/O pins for Nucleo-401RE   
*@author Prof. Timothy Scherr  
*@date 10/28/2017
*******************************************************************************/

#ifndef PINDEF_H
#define PINDEF_H
 
/*!
*@brief Macros for digital input pins
*/
#define Din0 PA_10
#define Din1 PB_3
#define Din2 PB_5
#define Din3 PB_4

/*!
*@brief Macros for digital output pins
*/
#define Dout0 PB_10
#define Dout1 PA_8
#define Dout2 PA_9
#define Dout3 PC_7

/*!
*@brief Macros for analog input pins
*/
#define Ain0 PA_0
#define Ain1 PA_1
#define Ain2 PA_4
#define Ain3 PB_0
#define Ain4 PC_1
#define Ain5 PC_0

/*!
*@brief Macros for analog output pins
*/
#define Aout0
#define Aout1
#define Aout2
#define Aout3
#define Aout4
#define Aout5

/*!
*@brief Macros for communication pins
*/
#define I2C_SCL PB_8
#define I2C_SDA PB_9

#define SPI_MOSI PA_7
#define SPI_MISO PA_6
#define SPI_SCLK PA_5
#define SPI_CS PB_6

#define UART_TX PA_2
#define UART_RX PA_3

/*!
*@brief Macros for RGB LED if present on board
*/
#define LED_r PB_10
#define LED_g PA_8
#define LED_b PA_9
#define LED PA_5

#endif
