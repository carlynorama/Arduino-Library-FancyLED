/*
	FancyLED.h - - FancyLED library for Wiring/Arduino - Version 0.1
	
	Original library 		(0.1) by Carlyn Maw.
	
 */

// ensure this library description is only included once
#ifndef FancyLED_h
#define FancyLED_h

// include types & constants of Wiring core API
#include "WProgram.h"

// library interface description
class FancyLED {
 
  // user-accessible "public" interface
  public:
  // constructors:
    FancyLED(int myPin, bool myMode);
    FancyLED(int myBit, bool myMode, unsigned char *myRegister);
    
    //char* version(void);			// get the library version
    //unsigned char getRegisterValue(void);

    void setCurrentTime(unsigned long);
    
    bool getState(void);
	void setState(bool);
	bool isOn(void);
	bool isOff(void);
    
    void turnOn(void);
	//void turnOnWithDuration(unsigned int onPeriod);
	
    void turnOff(void);
	
	void toggle(void);
	
	void blinkWithoutDelay(void);
    void blinkWithoutDelay(unsigned int blinkPeriod);

    void delayBlinkWithCount(unsigned int numberOfTimes);
    void delayBlinkWithCount(unsigned int numberOfTimes, unsigned int blinkPeriod);

    void turnOnAnalog(void);
    void turnOnAnalog(byte brightness);
    
    void brighten(void);
    void dim(void);
    
    void brighten(unsigned char);
    void dim(unsigned char increment);


	//void blinkWithAnalog(void);
	//void blinkWithAnalog(byte brightness);
	//void delayBlinkWithCountAndAnalog(unsigned int numberOfTimes, byte brightness);
	//void delayBlinkWithCountAndAnalog(unsigned int numberOfTimes, unsigned int blinkPeriod, byte brightness);	
	
	unsigned int getBlinkPeriod(void);
	void setBlinkPeriod(unsigned int); 
	
	unsigned char getCurrentBrightness(void);
	unsigned char getDefaultBrightness(void);
    void setCurrentBrightness(unsigned char);	
	void setDefaultBrightness(unsigned char); 
	
    unsigned char getBrightnessIncrement(void);
	void setBrightnessIncrement(unsigned char); 




  // library-accessible "private" interface
  private:
    int _myPin;
    int _myBit;
    unsigned char *_myRegister;
    unsigned char _registerValue;
    bool _type;  //direct pin or shift register
    bool _mode;  //HIGH == pressed (1) or LOW == pressed (0)
    
    bool _lastState;
    bool _currentState;
    bool _pinState;
        	
	unsigned int _blinkOnPeriod;  //same as on duration
	//unsigned int _blinkOffPeriod;
	
	byte _dBrightness;
    byte _cBrightness;
    byte _lBrightness;
    unsigned char _brightnessIncrement;
	
	bool _changed;
    bool _justOn;
    bool _justOff;
    //unsigned int _onCount;
    //unsigned int _offCount;
	
    unsigned long int _lastOnTime;
    unsigned long int _currentOnTime;
    unsigned long int _lastOffTime;
    unsigned long int _currentOffTime;
    unsigned long int _blinkFlipTime;
	
	unsigned long int _currentTime;
	
	bool _toggleFlag;
	
	void updatePin(bool);
	void updatePinAnalog(byte);
	void updateBrightness(int, unsigned char);

  
};

#endif

