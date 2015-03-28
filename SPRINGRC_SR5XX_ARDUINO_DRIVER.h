// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_
#define _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_
#include "Arduino.h"
#include "SoftwareSerial.h"

/////////////////////////////////////////////

enum Error
{
	instrErr = 6,
	overloadErr = 5,
	cheksumErr = 4,
	rangeErr = 3,
	highTemper = 2,
	angelLimitErr =1,
	voltErr = 0

};
struct Errors
{
	int count;
	Errors *ers;
};
/////////////////////////////////////////////

class Packet
{

};

/////////////////////////////////////////////

class UpdatedSoftwareSerial : public SoftwareSerial
{

};

/////////////////////////////////////////////
class ServoCascadue
{
private:
	SoftwareSerial *serial;
	int transmitState;

public:
	ServoCascadue(int rx, int tx, int transmitState);
	ServoCascadue(SoftwareSerial &serial);

	Errors ping(int id);
	Errors setServoLimit(int id, int cw_limit, int ccw_limit);
	Errors setServoPosition(int id, int pos, int velocity);
	Errors setServoVelocity(int id, int velocity);

};

/////////////////////////////////////////////



//Do not add code below this line
#endif /* _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_ */
