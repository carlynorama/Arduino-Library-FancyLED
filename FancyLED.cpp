/*
  FancyLED.h - FancyLED for Wiring/Arduino
  (cc) 2007 Carlyn Maw .  Some rights reserved.
  
  Created 29 Oct 2010
  Version 0.1
*/


// include core Wiring API
#include "WProgram.h"

// include this library's description file
#include "FancyLED.h"

   
  
// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

//------------------------------------------------------ Using Arduino Pin Num
FancyLED::FancyLED(int myPin, bool myMode)
{
    // initialize this instance's variables
    this->_myPin = myPin;
    
    pinMode(this->_myPin, OUTPUT);
    
    this->_type = 0;
    this->_myBit = this->_myPin;
    this->_mode = myMode;
    
    _lastState = 0;
    _currentState = 0;
    _pinState= 0;
    
    _blinkOnPeriod = 500;
    _dBrightness = 100;
    _brightnessIncrement = 1;
      
}

//----------------------------------------------------------------- Using Byte
FancyLED::FancyLED(int myBit, bool myMode, unsigned char *myRegister)
{
    // initialize this instance's variables
    this->_type = 1;
    this->_mode = myMode;
    this->_myBit = myBit;
    this->_myPin = this->_myBit;  
    this->_myRegister = myRegister;
    
    this->_registerValue = 255;
    
    _lastState = 0;
    _currentState = 0;
    _pinState= 0;
    
    _blinkOnPeriod = 500;
    _dBrightness = 70;
    _brightnessIncrement = 1;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

//---------////////////////////MAIN LOOP / LISTENER ///////////--------------//

void FancyLED::setCurrentTime(unsigned long newCurrentTime) {
    _currentTime = newCurrentTime;
}

bool FancyLED::getState(void){
    return _currentState;
}

bool FancyLED::isOn(void){
    return _currentState;
}

bool FancyLED::isOff(void){
    return !_currentState;
}



void FancyLED::turnOn(void){
	_pinState = _mode;
	_lastState = _currentState;
	_currentState = _mode;
	_lBrightness  = _cBrightness;
	_cBrightness = 255;
	//_lastOnTime = _currentOnTime;
    //_currentOnTime = _currentTime;
    _blinkFlipTime = _currentTime + _blinkOnPeriod;
    updatePin(_pinState);
}

void FancyLED::turnOff(void){
	_pinState = !_mode;
	_lastState = _currentState;
	_currentState = !_mode;
	_lBrightness  = _cBrightness;
	_cBrightness = 0;
    //_lastOffTime = _currentOffTime;
	//_currentOffTime = _currentTime;
	_blinkFlipTime = _currentTime + _blinkOnPeriod;

    updatePin(_pinState);
}

void FancyLED::toggle(void){
	_lastState = _currentState;
	_currentState ? _currentState=false : _currentState=true;	
	_currentState ? _pinState=_mode : _pinState = !_mode;
	_blinkFlipTime = _currentTime;
	_lBrightness  = _cBrightness;
    _cBrightness = _currentState*255;
    updatePin(_pinState);
}


void FancyLED::setState(bool newState) {
        newState ? turnOn() : turnOff();    
}

void FancyLED::blinkWithoutDelay(void) {
        
    if ((_blinkOnPeriod) < (_currentTime - _blinkFlipTime)) {        
        _currentState ? _currentState=false : _currentState=true;	
        _currentState ? _pinState=_mode : _pinState = !_mode;
        //update the blinkFlipTime with the current time.
        _blinkFlipTime = _currentTime;       
    }
    
    updatePin(_pinState);  //can't use toggle b/c better to have this
                     //value on the outside of the if
}
  
void FancyLED::blinkWithoutDelay(unsigned int myBlinkPeriod) {

   _blinkOnPeriod = myBlinkPeriod;
   blinkWithoutDelay();

}

void FancyLED::delayBlinkWithCount(unsigned int numberOfTimes, unsigned int blinkPeriod) {
    
    _blinkOnPeriod = blinkPeriod;
    delayBlinkWithCount(numberOfTimes);

}

void FancyLED::delayBlinkWithCount(unsigned int numberOfTimes) {
    for (int i=0; i < numberOfTimes; i++) {
        _blinkFlipTime = _currentTime; 
        _currentState=true;
        _lBrightness  = _cBrightness;
        _cBrightness = 255;
        _pinState=_mode;
        updatePin(_pinState); 
        delay(_blinkOnPeriod);
        _blinkFlipTime = _currentTime; 
        _currentState=false;
        _lBrightness  = _cBrightness;
        _cBrightness = 0;
        _pinState= !_mode;
        updatePin(_pinState);
        delay(_blinkOnPeriod);
    }
    //updatePin(_pinState);  //can't use toggle b/c better to have this
                         //value on the outside of the if
}

unsigned int FancyLED::getBlinkPeriod(void) {
    return _blinkOnPeriod;
}
	
void FancyLED::setBlinkPeriod(unsigned int newBlinkPeriod) {
    _blinkOnPeriod = newBlinkPeriod;    
}


void FancyLED::turnOnAnalog(byte myBrightness){
   setCurrentBrightness(myBrightness);
}

void FancyLED::turnOnAnalog(void){
    setCurrentBrightness(_dBrightness);
}

unsigned char FancyLED::getCurrentBrightness(void) {
    return _cBrightness;
}

void FancyLED::setCurrentBrightness(unsigned char myBrightness) {     
        if (myBrightness) {
        _pinState = _mode;
        _lastState = _currentState;
        _currentState = _mode;
        _lBrightness  = _cBrightness;
        _cBrightness = myBrightness;
        //_lastOnTime = _currentOnTime;
        //_currentOnTime = _currentTime;
        _blinkFlipTime = _currentTime + _blinkOnPeriod;        
        updatePinAnalog(_cBrightness);
    } else {
        turnOff();
    }
}

unsigned char FancyLED::getDefaultBrightness(void) {
    return _dBrightness;
}
	
void FancyLED::setDefaultBrightness(unsigned char myBrightness) {
    _dBrightness = myBrightness;  
}


void FancyLED::brighten(void) {
    brighten(_brightnessIncrement);
}
	
void FancyLED::dim(void) {
    dim(_brightnessIncrement);
}

void FancyLED::brighten(unsigned char increment) {
    updateBrightness(1, increment);
}
	
void FancyLED::dim(unsigned char increment) {
    updateBrightness(-1, increment);
}

unsigned char FancyLED::getBrightnessIncrement(void) {
    return _brightnessIncrement;
}
	
void FancyLED::setBrightnessIncrement(unsigned char increment) {
    _brightnessIncrement = increment;  
}
  

// Private Methods //////////////////////////////////////////////////////////////
// Functions available to the library only.


void FancyLED::updatePin(bool pinValue) {
    if (pinValue) {
        digitalWrite(_myPin, HIGH);
    } else {
        digitalWrite(_myPin, LOW);
    }

}

void FancyLED::updateBrightness(int directionMultiplier, unsigned char increment) {
    setCurrentBrightness(constrain((_cBrightness + (directionMultiplier*increment)), 0, 255));
}

void FancyLED::updatePinAnalog(byte brightness) {
    if (_mode) {
        analogWrite(_myPin, brightness);
    } else {
        analogWrite(_myPin, 255-brightness);
    }
}

