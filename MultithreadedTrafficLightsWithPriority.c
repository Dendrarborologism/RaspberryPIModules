/*  Important Note: 
 *      1. Compile this file using the command: gcc MultithreadedTrafficLightsWithPriority -lwiringPi -lpthread 
-o modded_traffic_light
 *      2. Run the program as a SUDO user: sudo ./modded_traffic_light
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
#define MY_PRIORITY 49
#define NUM_THREADS 3
sem_t sem;
void *Light1(void *data)
{
    struct sched_param param;
    param.sched_priority = MY_PRIORITY; 
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) 
    {
        printf("Run the program as a sudo user\n");
      perror("sched_setscheduler failed, thread 1");
     exit(20);
    }
    while (1)
    {
        sem_wait(&sem); 
        digitalWrite(RED, HIGH); 
        usleep(1000000);
        digitalWrite(RED, LOW);
        printf("Red cycle"); 
        sem_post(&sem); 
        usleep(300); 
    }
}
void *Light2(void *data)
{
    struct sched_param param;
    param.sched_priority = MY_PRIORITY-1; 
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) 
    {
        printf("Run the program as a sudo user\n");
      perror("sched_setscheduler failed, thread 2");
     exit(20);
    }
    while (1)
    {
        sem_wait(&sem); 
        digitalWrite(YELLOW, HIGH); 
        usleep(1000000);
        digitalWrite(YELLOW, LOW);
        sem_post(&sem); 
        usleep(300); 
    }
}
void *Light3(void *data)
{
    struct sched_param param;
    param.sched_priority = MY_PRIORITY-1; 
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) 
    {
        printf("Run the program as a sudo user\n");
      perror("sched_setscheduler failed, thread 3");
     exit(20);
    }
    while(1)
    {
        if(HIGH == digitalRead(BUTTON))
        {
            sem_wait(&sem); 
            digitalWrite(GREEN, HIGH);
            usleep(1000000);
            digitalWrite(GREEN, LOW);
            printf("Green cycle"); 
            sem_post(&sem); 
            //usleep(300); 
        }
    }
    
}
int main(void)
{
    sem_init(&sem, 0, 1); 
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
    
    //initialize thread ids 
    pthread_t thread1, thread2, thread3;
    //run then join the threads
    if (pthread_create(&thread1, NULL, Light1, NULL))
    {
        return 1; 
    }
    if (pthread_create(&thread2, NULL, Light2, NULL))
    {
        return 1; 
    }
    if (pthread_create(&thread3, NULL, Light3, NULL))
    {
        return 1; 
    }
    while (1)
    {
    }
    
    return 0;
}
