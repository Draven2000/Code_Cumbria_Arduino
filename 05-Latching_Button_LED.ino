#include "arduino_secrets.h"

/*
Toggles an LED on and off every time a momentary button is pressed.
LED is external, and is connected to pin D9.
Button is external, and is connected to pin D2.
*/
int colors[3] = {0, 1, 2};  // colors = [9,10,11]
int color_pick = 0;


// define macros for pin numbers so the code is easier to understand
#define LED_R 9
#define LED_G 10
#define LED_B 11

#define BUTTON_PIN 2

// global variable to store the button state
int newButtonState = 0;  //must be int because digitalRead() function returns an int!
int oldButtonState = 0;

// global variable to store the Colour state
int newLED_Color = 10;  
int oldLED_Color = 9;

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

    if(newButtonState == LOW && color_pick == 0) // button pressed
    { 
      color_pick++; // RED
      //digitalWrite(LED_R, !digitalRead(LED_R));  // invert the state of the LED pin
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
      Serial.println("LED RED");
    } else if (newButtonState == LOW && color_pick == 1) {
      color_pick++; // Yellow
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      Serial.println("LED YELLOW");
    }
    else if (newButtonState == LOW && color_pick == 2) {
      color_pick++; // GREEN
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      Serial.println("LED GREEN");
    }
        else if (newButtonState == LOW && color_pick == 3) {
      color_pick++; // CYAN
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, HIGH);
      Serial.println("LED CYAN");
    }
        else if (newButtonState == LOW && color_pick == 4) {
      color_pick++; // BLUE
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
      Serial.println("LED BLUE");
    }

        else if (newButtonState == LOW && color_pick == 5) {
      color_pick++; // MAGENTA
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
      Serial.println("LED MAGENTA");
    }
    
    else if (newButtonState == LOW && color_pick == 6) {
      color_pick = 0; // WHITE
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, HIGH);
      Serial.println("LED WHITE");
    }
  }

  delay(250);                 // wait for 250ms
}
