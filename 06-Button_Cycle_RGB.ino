#include "arduino_secrets.h"

/*
Cycles through 7 LED colours every time a momentary button is pressed.
RGB LED is external, and is connected to the following pins:
Red: D9
Green: D10
Blue: D11

Button is external, and is connected to pin D2.
*/

// define macros for pin numbers so the code is easier to understand
#define BUTTON_PIN 2
#define LED_R 9
#define LED_G 10
#define LED_B 11

// global variable to store the button state
int newButtonState = 0;  //must be int because digitalRead() function returns an int!
int oldButtonState = 0;

// global variable to store the current colour
int currentColour = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialise the LED pins
  pinMode(LED_R, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // enable the internal pullup resistor for this pin --> press the button to pull the pin to 0V (active low)

  // initialise the serial port
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  newButtonState = digitalRead(BUTTON_PIN);  // read and store the current state of the button
  Serial.print("newButtonState = ");
  Serial.println(newButtonState);

  if(newButtonState != oldButtonState)  // button has changed state
  {
    oldButtonState = newButtonState;  // update the button state so the change can be detected next time

    if(newButtonState == LOW)
    {
      if(currentColour >= 6)
      {
        currentColour = 0;
      }
      else
      {
        currentColour++;
      }
    }
  }

  switch(currentColour)
  {
    case 0: // red
    digitalWrite(LED_R, HIGH);  // turn the red LED on
    digitalWrite(LED_G, LOW);  // turn the green LED off
    digitalWrite(LED_B, LOW);  // turn the blue LED off
    Serial.println("LED Colour: RED");
    break;

    case 1: // yellow
    digitalWrite(LED_R, HIGH);  // turn the red LED on
    digitalWrite(LED_G, LOW);  // turn the green LED off
    digitalWrite(LED_B, LOW);  // turn the blue LED off
    Serial.println("LED Colour: YELLOW");
    break;

    case 2: // green
    digitalWrite(LED_R, LOW);  // turn the red LED off
    digitalWrite(LED_G, HIGH);  // turn the green LED on
    digitalWrite(LED_B, LOW);  // turn the blue LED off
    Serial.println("LED Colour: GREEN");
    break;
    
    case 3: // cyan
    digitalWrite(LED_R, LOW);  // turn the red LED off
    digitalWrite(LED_G, HIGH);  // turn the green LED on
    digitalWrite(LED_B, HIGH);  // turn the blue LED on
    Serial.println("LED Colour: CYAN");
    break;
    
    case 4: // blue
    digitalWrite(LED_R, LOW);  // turn the red LED off
    digitalWrite(LED_G, LOW);  // turn the green LED off
    digitalWrite(LED_B, HIGH);  // turn the blue LED on
    Serial.println("LED Colour: BLUE");
    break;
    
    case 5: // magenta
    digitalWrite(LED_R, HIGH);  // turn the red LED on
    digitalWrite(LED_G, LOW);  // turn the green LED off
    digitalWrite(LED_B, HIGH);  // turn the blue LED on
    Serial.println("LED Colour: MAGENTA");
    break;
    
    case 6: // white
    digitalWrite(LED_R, HIGH);  // turn the red LED on
    digitalWrite(LED_G, HIGH);  // turn the green LED on
    digitalWrite(LED_B, HIGH);  // turn the blue LED on
    Serial.println("LED Colour: WHITE");
    break;
  }

  delay(250);                 // wait for 250ms
}
