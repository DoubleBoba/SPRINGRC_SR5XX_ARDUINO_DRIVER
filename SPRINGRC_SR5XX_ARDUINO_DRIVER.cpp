// Do not remove the include below
#include "SPRINGRC_SR5XX_ARDUINO_DRIVER.h"

Packet::Packet(uint8_t *data, uint8_t length)
{
	int i;
	this->data = (uint8_t*) new uint8_t[length];
	for (i = 0; i < length; i++)
		*(this->data+i) = *(data+i);
	this->length = length;
}
Packet::~Packet() {
	delete [] data;
}
uint8_t& Packet::operator [](const uint8_t index)
{
	return (index >= length) ? 0 : *(data+index);
}


/////////////////////////////////////////////

UpdatedSoftwareSerial::UpdatedSoftwareSerial(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx)
{}
UpdatedSoftwareSerial::sendPacket(const Packet& p)
{
	uint8_t i;
	for (i = 0; i < p.getLength(); i++)
		this->print(p[i]);
}
UpdatedSoftwareSerial::recivePacket(const uint8_t length)
{
	uint8_t *data = (uint8_t *) new uint8_t[length];
	uint8_t i;
	for (i = 0; i <length; i++)
		*(data+i) = this->read();
}

/////////////////////////////////////////////

ServoCascadue::ServoCascadue(uint8_t rx, uint8_t tx, uint8_t transmitState) : transmitState(transmitState)
{
	pinMode(this->transmitState, OUTPUT);
	digitalWrite(this->transmitState,LOW);
	this->serial = (UpdatedSoftwareSerial*) new UpdatedSoftwareSerial(rx, tx);
	this->serial->begin(500000); // I found this speed in examples for SR518,
								 // I don`t now, is it correct.

}

ServoCascadue::~ServoCascadue()
{
	delete serial;
}

ServoCascadue::packetBuildAndSend(uint8_t id, uint8_t instruction,
		uint8_t paramsLen, uint8_t *params)
{
	uint8_t length = paramsLen +6;
	uint8_t *data = (uint8_t*) new uint8_t[length];
	*data = 0xff;
	*(data+1) = 0xff;
	*(data+2) = paramsLen+2;
	*(data+3) = instruction;
	uint8_t i;
	for (i = 0; i < paramsLen; i++)
		*(data+i+4) = *(params+i);
	uint8_t checkSum = 0;
	for (i = 2; i < length -1; i++)
		checkSum += *(data+i);
	checkSum = ~checkSum;
	Packet p(data, length);
	serial->sendPacket(p); // Yeah, bitches!
}
Packet *ServoCascadue::packetRecive() {
	/*
	 * Creating the temporary array.
	 * When i get the data range, i
	 * reallocate memory for this
	 * packet.
	 */
	uint8_t *temp = (uint8_t *) new uint8_t[4];
	while (!serial->available()); // Waiting for data
	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		while (!serial->available()); // Wait for next byte
		*(temp+i) = this->serial->read();
	}
	uint8_t len = (*(temp+3)) + 4; // Calculate new size
	uint8_t *data = (uint8_t *) new uint8_t[len]; //reallocating mem
	for (i = 0; i<4; i++)
		*(data+i) = *(temp+i);
	delete [] temp;
	serial->readBytes(data+4,len-4); //reading other bytes
	return (Packet *)new Packet(data, len);
}
Errors ServoCascadue::ping(uint8_t id)
{

	digitalWrite(this->transmitState, HIGH);
	packetBuildAndSend(id, 0x01, 0x00, 0); // Very simple!
	// In next updates I`ll add method, that will create readable
	// error.

}













