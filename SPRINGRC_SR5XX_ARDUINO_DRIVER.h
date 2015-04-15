// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_
#define _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "new.h"
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
	Error *ers;
};
/////////////////////////////////////////////

class Packet
{
private:
	uint8_t *data;
	uint8_t length;
public:
	Packet(uint8_t data[], uint8_t length);
	~Packet();
	uint8_t& operator[](uint8_t index);
	uint8_t getLength();
};

/////////////////////////////////////////////

class UpdatedSoftwareSerial : public SoftwareSerial
{
public:
	UpdatedSoftwareSerial(uint8_t rx, uint8_t tx);
	void sendPacket(Packet p);
	Packet recivePacket(uint8_t length);

};

/////////////////////////////////////////////
class ServoCascadue
{
private:
	UpdatedSoftwareSerial *serial;
	uint8_t transmitState;

public:
	ServoCascadue(uint8_t rx, uint8_t tx, uint8_t transmitState);
	~ServoCascadue();
	/**
	 * Method, that generalize process of building
	 * and sending packets to servos.
	 */
	void packetBuildAndSend(uint8_t id,uint8_t instruction, uint8_t paramsLen,
		uint8_t *params);
	/**
	 * Method, that generalize process of getting
	 * packet from servo.
	 */
	Packet *packetRecive();

	/**
	 * Method, that get readable array of
	 * errors.
	 */
	Errors checkForErrors(Packet *p);
	/**
	 * Check the servos status
	 */
	Errors ping(uint8_t id);
	/**
	 * Set maximum and minimum rotation angel
	 */
	Errors setServoLimit(uint8_t id, uint16_t cw_limit, uint16_t ccw_limit);
	/**
	 * Set position of the servo on special velocity
	 */
	Errors setServoPosition(uint8_t id, uint16_t pos, uint16_t velocity);
	/**
	 * Set velocity of the servo
	 */
	Errors setServoVelocity(int id, int velocity);

	/**
	 * Coming soon in next updates...
	 */
};

/////////////////////////////////////////////

uint8_t* splitShort(uint16_t sh);

//Do not add code below this line
#endif /* _SPRINGRC_SR5XX_ARDUINO_DRIVER_H_ */
