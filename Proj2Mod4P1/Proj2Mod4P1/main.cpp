/**----------------------------------------------------------------------------
 
   \file main.cpp

--                                                                           --
                ECEN 5803 Mastering Embedded System Architecture             
==
                         Project 2 Module 4 Part 2                           
--
                Signal Analyzer Firmware - Harmonic Analysis                 
--
                     		   main.cpp                                      
--
    Designed for:  University of Colorado at Boulder
--               
    Designed by:  Erich Clever & Maitreyee Rao
-- 
   	Version: 1.0
--	
  	Date of current revision:  2021-10-21  
--
   Target Microcontroller: STM23F401RE
--
   Tools used:  
--
-				ARM mbed compiler
-               ARM mbed SDK
-               ST Nucleo-F401RE
-               Analog Discover 2 - Oscilloscope and spectrum analyzer
 
   Functional Description:  
--							
  							A 60 Hz PWM signal is used to generate a 1004 Hz 
  							sawtooth signal by increasing the duty cycle over 
  							60 iterations. This is similar to the program from
							module 2 but with a static frequency.
                           
*/
							
#include "mbed.h"

#define DEBUG   0
#define ONE_SECOND_US 1000000.0
#define TONE_FREQUENCY  1004.0

Ticker timer0;
Ticker timer1;

Timer t;

Serial pc(USBTX, USBRX);

DigitalOut myled(LED1);

PwmOut sawtooth(PB_10);

//Global variables//
static volatile int timerVal;

//Constants
const float steps = 60.0;

/**
 * @brief Function for printing information about the signal to the console
 *		
 * The period of the synthesized signal and the period of the 
 * PWM signal (AKA "Step Size") used to synthesize said signal are displayed over
 * UART at 9600 BAUD. The delay from the main loop execution
 * is also displayed, as this value was used to update the duty
 * cycle more synchronously in the wait_us() function in the 
 * superloop. This function is only turned on in debug mode 
 * ("DEBUG=1").
 * 
 */
void printMainDelay(){

    pc.printf("Period: %.2f us\r\n",((float)ONE_SECOND_US/1004.0)); 
    pc.printf("Step size: %.2f us\r\n",((float)ONE_SECOND_US/66.0));
    pc.printf("Main loop delay: %i us\r\n",timerVal);
        
}

/**
 * @brief Function for toggling the LED value
 * 
 * This function is called by a timer interrupt routine
 * to show that the system is still operating as programmed.
 * 
 */
void heartbeat(){
    
    myled = !myled;
    
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
 /**
 * @brief Main function
 *
 * This function generates a sawtooth signal on PB_10 using the PWM
 * method from module 2. A PWM signal with a frequency 60x that of
 * the target frequency (1004 Hz) varies its PWM in 60 iterations
 * from a duty cycle of 0% to 100%. This results in a sawtooth, especially
 * if a low pass filter is applied.
 * 
 */
int main() {
    
    timer0.attach(&heartbeat,0.5);
    
    if(DEBUG==1) timer1.attach(&printMainDelay,1);
    
    float stepCount = 0;
    const double stepSize = ONE_SECOND_US/(TONE_FREQUENCY*steps);
    
    sawtooth.period_us(stepSize);
    
    while(1){
        
        if(DEBUG==1){
            t.reset();
            t.start();  
        }
    
        stepCount = (stepCount==steps) ? 0 : stepCount+1.0;
        
        sawtooth.write(stepCount/steps);
        
        if(DEBUG==1){
            t.stop();
            timerVal = t.read_us();
        }
        
        wait_us(stepSize-6);
        
    }
    
}
