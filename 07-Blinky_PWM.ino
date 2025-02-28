#include "arduino_secrets.h"

/*
Fades an LED in and out using PWM. Runs forever.
LED is external, and is connected to pin D9.
*/

// define a macros so the code is easier to understand
#define LED_R 9
#define LED_G 10
#define LED_B 11
#define UP 1
#define DOWN 0

// variable to store LED brightness values
int currentBrightness = 0;
int currentDirection = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialise the LED pins
  pinMode(LED_R, OUTPUT);

  // initialise the serial port
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  if (currentDirection == UP)  // increasing brightness
  {

    if (currentBrightness >= 255)  // swap direction when at maximum brightness
    {
      currentDirection = DOWN;
      //currentBrightness = 0; // Sawtooth gradually increase brightness and then drops
      currentBrightness --;
    } else {
      currentBrightness ++;
    }
  } else  // decreasing brightness
  {

    if (currentBrightness <= 0)  // swap direction when at minimum brightness
    {
      currentDirection = UP;
      currentBrightness++;
    } else {
      currentBrightness--;
    }
  }


  analogWrite(LED_R, currentBrightness);  // update PWM latch with current brightness
  analogWrite(LED_B, currentBrightness);
  Serial.print("Brightness value = ");
  Serial.println(currentBrightness);
  delay(10);  // wait for 10ms
}