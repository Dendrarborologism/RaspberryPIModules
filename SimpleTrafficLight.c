/*  Important Note: 
 *      1. Compile this file using the command: gcc SimpleTrafficLight.c -lwiringPi -lpthread 
-o trafficlight
 *      2. Run the program as a SUDO user: sudo ./trafficlight
 *  
 */
// http://wiringpi.com/reference/core-functions/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <sys/timerfd.h>
#include <time.h>
#include <semaphore.h>
#include <wiringPi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#define RED 2
#define YELLOW 3
#define GREEN 4
#define BUTTON 16
int main(void)
{
    // Step-1
    // ------
    
    // Set-up of GPIO pins using WiringPi library
    wiringPiSetupGpio(); 
    pinMode(RED, OUTPUT); 
    pinMode(YELLOW, OUTPUT); 
    pinMode(GREEN, OUTPUT); 
    pinMode(BUTTON, INPUT); 
    pullUpDnControl(BUTTON, PUD_DOWN); 
    digitalWrite(RED, LOW); 
    digitalWrite(YELLOW, LOW); 
    digitalWrite(GREEN, LOW);
    // Step-2
    // ------
    //Run a infinite while loop and turn on/off one light at a time.
    //Turn on the green light if button 1 is pressed  
    while(1)
    {
        digitalWrite(RED, HIGH); 
        usleep(1000000);
        digitalWrite(RED, LOW); 
        digitalWrite(YELLOW, HIGH); 
        usleep(1000000);
        digitalWrite(YELLOW, LOW);
        if (HIGH == digitalRead(BUTTON))
        {
            digitalWrite(GREEN, HIGH);
            usleep(1000000);
            digitalWrite(GREEN, LOW);
        }
    }  
    return 0;
}