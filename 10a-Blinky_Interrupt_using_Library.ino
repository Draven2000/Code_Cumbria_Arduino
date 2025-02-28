#include "arduino_secrets.h"

/*
Turns an LED on for one second, then off for one second, repeatedly.
Code uses Timer1 configured via the TimerOne library to interrupt on overflow.
LED is external, and is connected to pin D9.
*/

// include the TimerOne library
#include <TimerOne.h>

// define a macro for the LED pin number so the code is easier to understand
#define LED_R 9

// Variable to store LED state --> variables used within the ISR must be 'volatile'
volatile bool ledState = false; 

void setup() {
  // initialise LED
  pinMode(LED_R, OUTPUT);

  // initialise Timer1
  //Timer1.initialize(1000000); // configure to overflow Every 1s (specified in microseconds)
  //Timer1.initialize(12e6); //  Scientific notation easier to read, Change to overflow Every 12s
  Timer1.initialize(1e6/12);    // Scientific notation easier to read, Change to flip at a rate of 12HZ
  Timer1.attachInterrupt(Timer1_ISR); // configure to interrupt on overflow and specify the name
                                      // of the function to call when the interrupt occurs
}

void loop() {
  // nothing needed here - everything is controlled from the ISR!
}

// Timer1 Interrupt Service Routine (ISR)
void Timer1_ISR(void)
{
  ledState = !ledState;  // Toggle LED state
  digitalWrite(LED_R, ledState);  // update output pin with new LED state
}