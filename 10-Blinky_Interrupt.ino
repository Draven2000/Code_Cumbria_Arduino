#include "arduino_secrets.h"

/*
Turns an LED on for one second, then off for one second, repeatedly.
Code uses Timer1 configured to interrupt on overflow.
LED is external, and is connected to pin D9.
*/

// define a macro for the LED pin number so the code is easier to understand
#define LED_R 9

// Variable to store LED state --> variables used within the ISR must be 'volatile'
volatile bool ledState = false; 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_R, OUTPUT);

  // configure Timer1
  configTimer1();
}

// the loop function runs over and over again forever
void loop() {

  // nothing needed here - everything is controlled from the ISR!
}

// Timer1 Interrupt Service Routine (ISR)
ISR(TIMER1_COMPA_vect) {

    ledState = !ledState;  // Toggle LED state
    digitalWrite(LED_R, ledState);  // update output pin with new LED state
}

// Function to configure Timer1
void configTimer1() {
    cli();  // Disable global interrupts

    TCCR1A = 0;  // Set entire Timer1 control register A to 0
    TCCR1B = 0;  // Set entire Timer1 control register B to 0

    TCCR1B |= (1 << WGM12);  // Set CTC (Clear Timer on Compare Match) mode

    TCCR1B |= (1 << CS12) | (1 << CS10);  // Set prescaler to 1024

    // Calculate OCR1A for 1Hz (1 sec)
    // Formula: OCR1A = (16MHz / (Prescaler * Frequency)) - 1
    //          OCR1A = (16,000,000 / (1024 * 1)) - 1 = 15624
    OCR1A = 15624;

    TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 Compare Match A interrupt

    sei();  // Enable global interrupts
}

