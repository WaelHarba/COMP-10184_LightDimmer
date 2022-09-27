#include <Arduino.h>

/*
  I, Wael Harba, student number 000787960, certify that what I am submitting is my own work;
  that I have not copied it from any other source. I also certify that I have not allowed my work to be copied by others.
*/

int lastButtonState = 0; // Global variable that will hold the last state/value of the button
int lightStatus = 1;     // Global variable for the last state of the LED light. Set it to high by default to have the light off at first

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure pin D5 as digital input - this is the pushbutton
  pinMode(D5, INPUT_PULLUP);

  // configure pin D4 as a digital output - this is the LED
  pinMode(D4, OUTPUT);

  digitalWrite(D4, lightStatus); // Set light to off at first
}

void loop()
{
  int currentButtonState = digitalRead(D5); // Get the state of the button pressed
  int analogValue = analogRead(A0);         // Read the analog value from the variable resistor

  // Check if the new button state is different than last state from previous cycle in the loop
  if (currentButtonState != lastButtonState)
  {
    lastButtonState = currentButtonState; // Save the new button state into the global varaible

    // Check if the current state of the button is pressed
    if (currentButtonState == 0)
    {
      // Check if the light status was HIGH
      if (lightStatus == 1)
      {
        lightStatus = 0; // Change the global value to light is LOW since it was HIGH
      }
      // In the case of the light status being LOW
      else
      {
        lightStatus = 1; // Change the global value to HIGH since light was LOW
      }
      digitalWrite(D4, lightStatus); // Set the LED light to be on or off based on the value of the global variable of the light state
    }
  }

  // Check the light status to allow the variable resistor to control it
  if (lightStatus == 0)
  {
    analogWrite(D4, analogValue); // Change the LED light to be based on the value from the variable resistor
  }

  delay(1);
}