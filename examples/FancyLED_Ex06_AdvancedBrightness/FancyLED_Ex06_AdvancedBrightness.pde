/*
 * FancyLED Library Example 6, combines w/ AnalogIn SerialOut example included
 * in Arduino 21
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

bool runFlag = 0;
const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup()
{

  Serial.begin(9600);
  Serial.print("Default = \t");
  Serial.println(externalLED.getBrightnessIncrement(), DEC);
  externalLED.setBrightnessIncrement(2);
  Serial.print("New Brightness Increment = \t");
  Serial.println(externalLED.getBrightnessIncrement(), DEC);
  externalLED.setDefaultBrightness(178);
}

void loop()
{

  helloButton.listen();  
  
   // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  externalLED.setDefaultBrightness(outputValue);   

   if (helloButton.onPress()) {
        helloButton.listen();
        runFlag = true;
   }

  if (runFlag) {
    externalLED.turnOff();  
    for(int i = 0; i < (externalLED.getDefaultBrightness()/externalLED.getBrightnessIncrement()); i++){ //goes through each speed from 0 to 255
      //externalLED.brighten();     //brightens by 
      //externalLED.brighten(20);
      //externalLED.dim(); 
      //externalLED.dim(20);
      externalLED.brighten(); 
      delay(20);
      }
    Serial.println(externalLED.getCurrentBrightness(), DEC);
    runFlag = false;
  }

}

