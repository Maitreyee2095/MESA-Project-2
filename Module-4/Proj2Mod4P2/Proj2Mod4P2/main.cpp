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
-               ARM CMSIS DSP API
-               ST Nucleo-F401RE
-               Analog Discover 2 - Oscilloscope and function generation
 
   Functional Description:  
--							
  							Samples of an analog signal are read using the 12-bit
                            ADC included in the microcontroller, then harmonic
  							analysis is performed to determine the fundamental
  							frequency of this signal. An FFT algorithm included
  							in the CMSIS DSP library is used to do this. The
  							User LED (LD2) blinks at a rate proportional to the 
  							measured fundamental frequency.
*/

#include "mbed.h"
#include "arm_math.h"

#include "arm_common_tables.h"
#include "arm_const_structs.h"
#include "math_helper.h"

#include <time.h>

#define BUFFER_SIZE (4096)
#define SAMPLE_RATE (44100)

#define ONE_SECOND_US 1000000.0

Serial pc(USBTX, USBRX);

AnalogIn signal(PA_0);

PwmOut myLED(PA_5);

//Global variables//
//uint16_t buffer[BUFFER_SIZE];
static float signalSamples[BUFFER_SIZE*2];
static float fftOutput[BUFFER_SIZE];

/**
 * @brief Function for sampling the ADC input "signal"
 *
 * This function creates a buffer of sample data for input
 * into a complex FFT function.
 *
 */
void sample()
{
    for(int i = 0; i<(BUFFER_SIZE*2); i+=2){
    
        signalSamples[i] = (signal * 2.0f) - 1.0f;
        signalSamples[i+1] = 0;
        
        //The wait time was adjusted to acheive a more accuracte measurement
        wait_us((ONE_SECOND_US/SAMPLE_RATE)-5);
    
    }
}

/**
 * @brief Function obtaining the fundamental frequency from the sample
 * buffer.
 *
 * This function determiens the fundamental frequency of the measured 
 * signal by performing complex FFT algorithms on the data buffer
 * then finding the bin with the largest magnitude.
 *
 * @return
 *  The fundamental frequency of the signal
 */
uint32_t getFundamentalFreq()
{
    //Declare variable for holding the index of the bin with the maximum
    //intensity and the frequency of that bin
    uint32_t maxFreqIndex;
    float32_t  maxVal;
    
    //Perform FFT on acquired samples. This function is a part of 
    //the CMSIS DSP library and was created by ARM ltd.
    arm_cfft_f32(&arm_cfft_sR_f32_len4096, signalSamples, 0, 1);
    
    //Calculate the magnitude of the complex results. This function is a part of 
    //the CMSIS DSP library and was created by ARM ltd.
    arm_cmplx_mag_f32(signalSamples, fftOutput, BUFFER_SIZE);
    
    fftOutput[0] = 0;       //Ignore DC bias

    //Find the bin with the largest value among the resulting magnitude array. 
    //This function is a part of the CMSIS DSP library and was created by ARM ltd.
    arm_max_f32(fftOutput, BUFFER_SIZE, &maxVal, &maxFreqIndex);
    
    pc.printf("Bin with max value @ %i \r\n",maxFreqIndex);
    pc.printf("Max value = %f \r\n",maxVal);
    
    uint32_t fundFreq = (maxFreqIndex*SAMPLE_RATE)/(BUFFER_SIZE);
    
    pc.printf("Fundamental frequency = %i Hz\r\n",fundFreq);

    return fundFreq;
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
 /**
 * @brief Main function
 *
 * This function executes the firmware for a signal analyzer by executing the
 * following steps in a loop:
 *				-ADC sampling into a data buffer
 *				-FFT on data buffer to determine the fundamental frequency
 *				-Display over UART of determined fundamental frequency and 
 *					blinking of User LED at that frequency
 *
 * 
 */
int main() {

    while(1){

        //Acquire samples of input signal using ADC
        sample();
        
        //Extract fundamental frequency from the measured signal using
        //FFT algorithms
        uint32_t fundFreq = getFundamentalFreq();
        
        //Blink User LED (LD2) at rate proportional to the measure
        //fundamental frequency.
        myLED.period_us(ONE_SECOND_US/fundFreq);
        myLED = .5;     //Set PWM duty cycle to 50%
   
        wait(1);

    }
    
}
