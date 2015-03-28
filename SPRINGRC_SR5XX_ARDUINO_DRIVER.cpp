// Do not remove the include below
#include "SPRINGRC_SR5XX_ARDUINO_DRIVER.h"


ServoCascadue::ServoCascadue(int rx, int tx, int transmitState)
{

	this->serial = new SoftwareSerial(rx,tx);
	this->transmitState = transmitState;

}
ServoCascadue::ServoCascadue(SoftwareSerial &serial)
