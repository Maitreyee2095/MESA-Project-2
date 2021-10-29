#include "mbed.h"
 
#include "NHD_0216HZ.h"
#include "DS1631.h"
#include "pindef.h"

//#include "rtos.h"

Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;

Mutex lcd_mutex;


/*!
*@brief Definition for LCD unit
*/
NHD_0216HZ mylcd(SPI_CS,SPI_MOSI,SPI_SCLK);


/*!
*@brief Definition for temperature sensor
*/
DS1631 tempsensor(I2C_SDA,I2C_SCL,0x90);


/*!
*@brief Serial communication with PC
*/
Serial pc(USBTX, USBRX);


DigitalOut led1(LED1);

/*!
*@brief Analog input for Potentiometer 1
*/
AnalogIn pot1(Ain0);

/*!
*@brief Analog output for PWM 
*/
PwmOut mypwm(Dout0);

 

#pragma O0
uint16_t count=1;

/*!
*@brief Thread to display temperature on LCD
*/
void temp_thread(){
    float temp;
    //printf("Hello temp\n\r");
    mylcd.set_cursor(0,0);
    mylcd.printf("Temp:");
    wait_ms(1000);
    while (true){
        temp=tempsensor.read();
       // mylcd.clr_lcd();
        char number[24]; 
        sprintf(number, "%2.2f", temp);
        lcd_mutex.lock();   
        mylcd.set_cursor(7,0);
       // wait_ms(50);
        mylcd.printf("%s", number);
        lcd_mutex.unlock();
        pc.printf("Temperature: %s\n",number);
        Thread::wait(4000);
    }
}

/*!
*@brief Thread to adjust brightness of external LED
*/
void adjust_brightness(){
    //printf("Hello bright\n\r");
    while (true){
        double v=pot1.read();
        mypwm=(0.5*v);
        Thread::wait(4000);
        }
}

/*!
*@brief Thread to blink on-board LED LD2
*/
void led1_thread(){
    //printf("Hello led\n\r");
    while (true){
        led1=!led1;
        Thread::wait(4000);
        }
}



/*!
*@brief Thread to display count on LCD
*/
void count_thread(){
    //printf("Hello lcd\n\r");
    mylcd.set_cursor(0,1);
    mylcd.printf("Count:");
    wait_ms(1000);
    while(true){
        lcd_mutex.lock();
        //mylcd.clr_lcd();
       // wait_ms(70);
        mylcd.set_cursor(7,1);
        //wait_ms(50);
        mylcd.printf("%d",count);
        //wait_ms(500);
        lcd_mutex.unlock();
        count++;
        pc.printf("Count is: %d\n",count);    
        Thread::wait(4000);
        }
}
/*!
*@brief Main function to display temperature on lcd using thread
*/
int main() {
    printf("Hello\n\r");
    mylcd.init_lcd();
    mylcd.clr_lcd();
    mylcd.set_cursor(0,0);
    mylcd.printf("Hello LCD");
    wait_ms(1000);
    mylcd.clr_lcd();
    wait_ms(1000);
    printf("Hello mbed!!\n\r");   
    
    thread1.start(led1_thread);
    thread2.start(adjust_brightness);
    thread3.start(temp_thread);
    thread4.start(count_thread);
    while(1) {
        Thread::wait(50000);
    }
}