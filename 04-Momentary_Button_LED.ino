#include "arduino_secrets.h"

/*
Turns an LED on while a momentary button is pressed.
LED is external, and is connected to pin D9.
Button is external, and is connected to pin D2.
*/

// define macros for pin numbers so the code is easier to understand
#define LED_R 11 //blue
#define BUTTON_PIN 2

// global variable to store the button state
int buttonState;  //must be int because digitalRead() function returns an int!

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
  
  buttonState = digitalRead(BUTTON_PIN);  // read and store the current state of the button
  Serial.print("buttonState=");
  Serial.println(buttonState);

  if(buttonState == LOW && OUTPUT == LOW)  // low state means button has been pressed
  {
    digitalWrite(LED_R, HIGH);  // turn the red LED on
    Serial.println("Button is pressed: LED ON");
  }
  
  else if(buttonState == LOW && OUTPUT == HIGH )  // low state means button has been pressed
  {
    digitalWrite(LED_R, LOW);  // turn the red LED off
    Serial.println("Button is pressed: LED OFF");
  }

  //else  // button has not been pressed --> default state
  //{
    //digitalWrite(LED_R, LOW);  // turn the red LED off
    //Serial.println("Button is not pressed: LED OFF");
  //}

  delay(250);                 // wait for 250ms
}
