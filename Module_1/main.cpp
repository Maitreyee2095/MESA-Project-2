#include "mbed.h"

DigitalOut myled(LED1);

Serial pc(USBTX, USBRX);

int main() {
    
    pc.printf("RTC example\r\n"); 
 
    set_time(1633914867); // Set time to Mon, 11 Oct 2021 01:14:27 GMT
                          
    printf("Date and time are set.\r\n");

    while(1) {

        time_t seconds = time(NULL);

        pc.printf("Time as seconds since January 1, 1970 = %d\r\n", seconds);
        
        pc.printf("Time as a basic string = %s\r\n", ctime(&seconds));

        char buffer[32];
        strftime(buffer, 32, "%I:%M:%S %p", localtime(&seconds));
        pc.printf("Time as a custom formatted string = %s\r\n", buffer);

        myled = !myled;      
        wait(1);
    }
}