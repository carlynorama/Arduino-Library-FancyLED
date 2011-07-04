/*
 * FanceyLED Library Example 5
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

//Instantiate Button on digital pin 2
//pressed = ground (i.e. pulled high with external resistor)
Button helloButton = Button(2, LOW);

FancyLED externalLED = FancyLED(9, HIGH);
FancyLED boardLED = FancyLED(13, HIGH); 

void setup()
{

  Serial.begin(9600);
  Serial.print("Default = \t");
  Serial.println(externalLED.getDefaultBrightness(), DEC);
  externalLED.setDefaultBrightness(80);
  Serial.print("New Brightness = \t");
  Serial.println(externalLED.getDefaultBrightness(), DEC);

}

void loop()
{

  helloButton.listen();  


  if (helloButton.isPressed()) {
    //externalLED.turnOnAnalog(); 
    externalLED.turnOnAnalog(2);  //turns on at 2, 
    //leaves default alone                                 
    boardLED.turnOff();
  }


  if (helloButton.isReleased()) {
    externalLED.turnOnAnalog(); //uses default brightness
    boardLED.turnOnAnalog();    //won't work!!!!wrong type of pin!!

  }

}

