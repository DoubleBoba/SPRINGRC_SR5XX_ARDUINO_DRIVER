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
private:
	uint8_t *data;
	uint8_t length;
public:
	Packet(uint8_t data[], uint8_t length);

	uint8_t& operator[](int index);

};

/////////////////////////////////////////////

class UpdatedSoftwareSerial : public SoftwareSerial
{
public:
	UpdatedSoftwareSerial(uint8_t rx, uint8_t tx);
	void SendPacket(Packet p);
	Packet recivePacket(uint8_t length);

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

	/**
	 * Check the servos status
	 */
	Errors ping(int id);
	/**
	 * Set maximum and minimum rotation angel
	 */
	Errors setServoLimit(int id, int cw_limit, int ccw_limit);
	/**
	 * Set position of the servo on special velocity
	 */
	Errors setServoPosition(int id, int pos, int velocity);
	/**
	 * Set velocity of the servo
	 */
	Errors setServoVelocity(int id, int velocity);
	/**
	 * Coming soon in next updates...
	 */
};

/////////////////////////////////////////////



//Do not add code below this line
#endif /* _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_ */
