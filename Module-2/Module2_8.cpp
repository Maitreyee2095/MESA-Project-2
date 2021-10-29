#include "mbed.h"

//#include "rtos.h"
//BusIn My_Bus_In(PA_10, PB_3,PB_5,PB_4);

BusOut My_Bus_Out(PB_10);

DigitalOut led1(LED2);

InterruptIn button_1_press(PA_10);
InterruptIn button_2_press(PB_3);
InterruptIn button_3_press(PB_5);
InterruptIn button_4_press(PB_4);
void button_1_handler(){
    led1=1;
}

/*!
*@brief Interrupt routine for switch 2
*/
void button_2_handler(){
    led1=0;
}

/*!
*@brief Interrupt routine for switch 3
*/
void button_3_handler(){
    My_Bus_Out=1;
}

/*!
*@brief Interrupt routine for switch 4
*/
void button_4_handler(){
    My_Bus_Out=0;
}


/*!
*@brief Main function to control LEDs with external switches by interrupts
*/
int main(){
    
    __enable_irq();         
    
    led1=0;
    My_Bus_Out=0;
    
        
    button_1_press.fall(&button_1_handler);
    button_2_press.fall(&button_2_handler);
    button_3_press.fall(&button_3_handler);
    button_4_press.fall(&button_4_handler);
    
    while(1);
        
    
}

//int main() {
//   My_Bus_Out=1;
//   led1=1;
//   
//   while(1)
//   {
//    if(My_Bus_In== 0x0E)
//        {
//            led1=1;
//        }
//        
//        if(My_Bus_In==0x0D)
//        {
//            led1=0;
//        }
//        
//        if(My_Bus_In==0x0B)
//        {
//            My_Bus_Out=1;
//        }
//        
//        if(My_Bus_In==0x07)
//        {
//            My_Bus_Out=0;
//        }
//        
//    
//    }
//   
//}