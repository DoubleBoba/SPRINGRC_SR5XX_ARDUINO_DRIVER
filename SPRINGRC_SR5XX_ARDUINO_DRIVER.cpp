// Do not remove the include below
#include "SPRINGRC_SR5XX_ARDUINO_DRIVER.h"

Packet::Packet(uint8_t *data, uint8_t length)
{
	this->data = data;
	this->length = length;
}
uint8_t& Packet::operator [](const uint8_t index)
{
	return (index >= length) ? 0 : *(data+index);
}

/////////////////////////////////////////////

UpdatedSoftwareSerial::UpdatedSoftwareSerial(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx)
{}
UpdatedSoftwareSerial::SendPacket(const Packet& p)
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
	this->serial->begin(500000); // I find this speed in examples for SR518

}

Errors ServoCascadue::ping(uint8_t id)
{
	/*
	 * TODO maybe it need to get in other method?
	 */
	digitalWrite(this->transmitState, HIGH);
	uint8_t *data = new uint8_t[6];
	*(data) = 0xff;
	*(data+1) = 0xff;
	*(data+2) = id;
	*(data+3) = 0x02;
	*(data+4) = 0x01;
	*(data+5) = ~(id+0x03);
	Packet p(data, 6);
	this->serial->SendPacket(p);
	digitalWrite(this->transmitState, LOW);
}













