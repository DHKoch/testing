/* ECE3220 Lab9_example.c
 * Author: Luis Rivera
 * 
 * This program shows how to use wiringPi on the Raspberri Pi 3 to turn on and off
 * an LED on the auxiliary board.

  Compile using -lwiringPi
	gcc Lab9_example.c -o Lab9_example -lwiringPi
		or
	add wiringPi to the linker (-l), if using Eclipse
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// standard symbolic constants and types (e.g. NULL); usleep
#include <wiringPi.h>	// needed for the wiringPi functions

#define LED1  8		// wiringPi number corresponding to GPIO2.
#define LED2  9		//Check Figures 2 and 3 in the Lab9 guide.
#define LED3  7	
#define LED4  21

# define Button 27

int main(int argc, char **argv)
{       int i = 0;
	wiringPiSetup();	// wiringPiSetupGpio() could be used. The numbers for the ports would
						// need to match the RPi GPIO pinout.
	
	pinMode(LED1, OUTPUT);	// Configure GPIO2, which is the one connected to the red LED.
	pinMode(LED2, OUTPUT);
        pinMode(LED3, OUTPUT);
        pinMode(LED4, OUTPUT);
        
        pinMode(Button,INPUT);
        while(digitalRead(Button) ==0){}
	// The program will turn off the red LED, sleep for a while, then on, sleep, off, on and off.
	while(i!=10){
            digitalWrite(LED1, LOW);
            sleep(1);	// How can you sleep for less than a second?
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);
            sleep(1);	// How can you sleep for less than a second?
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, LOW);
            sleep(1);	// How can you sleep for less than a second?
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, LOW);
            sleep(1);	// How can you sleep for less than a second?
            digitalWrite(LED4, HIGH);
            i++;
        }
        
    return 0;
}