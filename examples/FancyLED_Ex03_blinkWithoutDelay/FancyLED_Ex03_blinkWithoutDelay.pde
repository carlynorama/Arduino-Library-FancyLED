/*
 * FanceyLED Library Example 3
 * ------------
 *
 * Circuit: 
 *          - Button, pulled up externally with 10k resitor on pin 2
 *          - Extra LED on pin 9
 *
 * Behavior: 
 *
 * Created 4 April 2010
 * Updated 29 October 2010
 * by Carlyn Maw
 *
 */

#include <Button.h> 
#include <FancyLED.h> 

unsigned long  loopCurrentTime = 0;

//Instantiate Button on digital pin 2
//pressed = ground (i.e. pulled high with external resistor)
Button helloButton = Button(2, LOW);

FancyLED externalLED = FancyLED(9, HIGH);
FancyLED boardLED = FancyLED(13, HIGH); 

void setup()
{
  externalLED.turnOff();
  boardLED.turnOff();
  
  Serial.begin(9600);
  Serial.print("Default = \t");
  Serial.println(externalLED.getBlinkPeriod());
  externalLED.setBlinkPeriod(1000);
  Serial.print("New Delay = \t");
  Serial.println(externalLED.getBlinkPeriod());

}

void loop()
{
  loopCurrentTime = millis();
  externalLED.setCurrentTime(loopCurrentTime);
  boardLED.setCurrentTime(loopCurrentTime);
  
  helloButton.listen();  


  if (helloButton.onPress()) {
    externalLED.blinkWithoutDelay();
    boardLED.blinkWithoutDelay(300);
  } else {
    externalLED.turnOn();
    boardLED.turnOff();
  }
}

