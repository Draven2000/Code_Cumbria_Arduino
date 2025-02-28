#include "arduino_secrets.h"

#include <HC_SR04.h>
/*
HC-SR04 ultrasonic distance meter. Reports distance in mm.
Ultrasonic distance meter is connected on the following pins:
Trigger: D5
Echo: D4 via 1k resistor for protection
*/

// include library for the HC-SR04
// https://github.com/d03n3rfr1tz3/HC-SR04/blob/master/README.md included the github page to see the manual for the library.
#include <HCSR04.h>

// define a macros so the code is easier to understand
#define BUTTON_PIN 2
#define LED_R 9
#define LED_G 10
#define LED_B 11

// global variable to store the button state
int buttonState;  //must be int because digitalRead() function returns an int!
// global variable to store the button state
int newButtonState = 1;  //must be int because digitalRead() function returns an int!
int oldButtonState = 1;
bool measuring = false;


// variable to store LED brightness values
int currentBrightness = 0;
int currentDirection = 0;

// also possible to use variables to name pin numbers --> best practice to use 'const' if you use this method
const byte triggerPin = 5;
const byte echoPin = 4;

void setup() {
  // set up the HC-SR04
  HCSR04.begin(triggerPin, echoPin);

  // set up the LED pins
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

    // initialise the button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // enable the internal pullup resistor for this pin --> press the button to pull the pin to 0V (active low)

  // set up the serial port
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  newButtonState = digitalRead(BUTTON_PIN);  // read and store the current state of the button
  //Serial.print("newButtonState = ");
  //Serial.println(newButtonState);
  
  if(newButtonState != oldButtonState){  // button has changed state
    Serial.println("Button state changed");
    oldButtonState = newButtonState;  // update the button state so the change can be detected next time
  
      if(newButtonState == LOW) // Button pressed, Turn measuring on or off
    {
      measuring ^= true;  // flip measuring
    }
  }

if (measuring == true){
  double* distances = HCSR04.measureDistanceCm();   // declare a variable called 'distances' which points
                                                    // to the array where the measured distance is stored
  Serial.print(distances[0]);   // print the measured distance
  Serial.println(" cm");        // print the units then a new line

  // Make a traffic light system, Visually indicate if object is getting close to sensor by changing colour of LED bulb.
  if (distances[0] <= 10){ //RED
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
    Serial.println("CLOSE");
  }
  else if (distances[0] <= 25){ //GREEN
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 0);
    Serial.println("MID");
  }
  else{ //BLUE
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 255);
    Serial.println("FAR");
  } 

} else{ // measuring == false
    Serial.println("Not measuring");
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
  }

  Serial.println("");
  delay(250);   // delay 250ms
}
