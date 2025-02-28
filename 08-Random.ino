#include "arduino_secrets.h"

/*
Generates a random number when a momentary button is pressed.
Random number is displayed in the Serial Monitor.
Button is external, and is connected to pin D2.
*/

// define macros for pin numbers so the code is easier to understand
#define BUTTON_PIN 2
// define a macros so the code is easier to understand
#define LED_R 9
#define LED_G 10
#define LED_B 11


// global variable to store the button state
int buttonState;  //must be int because digitalRead() function returns an int!

// global variable to store the button state
int newButtonState = 0;  //must be int because digitalRead() function returns an int!
int oldButtonState = 0;

// global variable to store the randomly generated number
int randNumber;
int randNumberR;
int randNumberG;
int randNumberB;


// the setup function runs once when you press reset or power the board
void setup() {


  // initialise the button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);         // enable the internal pullup resistor for this pin --> press the button to pull the pin to 0V (active low)
  newButtonState = digitalRead(BUTTON_PIN);  // read and store the current state of the button
  Serial.print("newButtonState = ");
  Serial.println(newButtonState);

  if (newButtonState != oldButtonState)  // button has changed state
  {
    oldButtonState = newButtonState;  // update the button state so the change can be detected next time
    // seed the random number generator
    randomSeed(analogRead(0));

    // initialise the serial port
    Serial.begin(9600);
  }
}

// the loop function runs over and over again forever
void loop() {

  newButtonState = digitalRead(BUTTON_PIN);  // read and store the current state of the button
  //Serial.print("newButtonState = ");
  //Serial.println(newButtonState);

  if (newButtonState != oldButtonState)  // button has changed state
  {
    oldButtonState = newButtonState;        // update the button state so the change can be detected next time
    buttonState = digitalRead(BUTTON_PIN);  // read and store the current state of the button
    //Serial.print("buttonState=");
    //Serial.println(buttonState);

    if (buttonState == LOW)  // low state means button has been pressed
    {
      randNumberR = random(256);  // generate a random number from 0 - 255
      randNumberG = random(256);
      randNumberB = random(256);

      Serial.print("Button is pressed! Random Colour: R");  // print the random number
      // If the Button is pressed comment is printed out, the code can plot the random numbers using Serial Plotte
  
      Serial.print(randNumberR);
      Serial.print(", G");
      Serial.print(randNumberG);
      Serial.print(", B");
      Serial.println(randNumberB);

      // Attempted to manually convert RGB to HEX using maths 
      //int divide = floor(244/16);
      //int remainder = 244%16;
      
      //Serial.print(divide);
      //Serial.print(",");
      //Serial.println(remainder);

      // Discovered Arduino has a built in HEX representation.
      // Print out random Colour in Hex representation.
      
      /* LEADING ZEROS ERROR: 
      If one of the RGB values is less than 16 the HEX representation only displays a single digit
      This leads to the full HEX value being 1 character less then expected */
      
      /*Serial.println(String("Hello") + " " + "World");  // Can concatenate strings like this
      Serial.println("R"+ String(randNumberR) + ", G" + String(randNumberG) + ", B"+ String(randNumberB));
      Serial.println(""+ String(randNumberR, HEX) + ", " + String(randNumberG, HEX) + ", "+ String(randNumberB, HEX));*/       
      Serial.print('#'); 
      if (randNumberR < 16){
        Serial.print("0" + String(randNumberR, HEX));
      } 
      else {
        Serial.print(randNumberR, HEX);
      }
      if (randNumberG < 16){
        Serial.print("0" + String(randNumberG, HEX));
      } 
      else {
        Serial.print(randNumberG, HEX);
      }
      if (randNumberB < 16){
        Serial.print("0" + String(randNumberB, HEX));
      } 
      else {
        Serial.print(randNumberB, HEX);
      }
      

      analogWrite(LED_R, randNumberR);
      analogWrite(LED_G, randNumberG);
      analogWrite(LED_B, randNumberB);
      
      Serial.println("");

    } else  // button has not been pressed --> default state
    {
      //Serial.println("Button is not pressed.");
    }
  }
  delay(10);  // wait for 500ms
}
