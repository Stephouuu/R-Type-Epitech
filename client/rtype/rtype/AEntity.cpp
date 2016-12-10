#include "AEntity.hpp"

AEntity::AEntity()
	  : _velocity(0),
		_degrees(0),
		_radians(0),
	   _direction(0)
{
	setAngle(-1);
	setID(0);
}

AEntity::~AEntity(void)
{
}

void AEntity::setID(uint16_t id)
{
	_id = id;
}

uint16_t AEntity::getID(void) const
{
	return (_id);
}

void AEntity::setDirection(uint8_t direction)
{
	setAngle(-1);
	if (direction & NORTH) {
		setAngle(-90.f);
	}
	else if (direction & SOUTH) {
		setAngle(90.f);
	}

	if (direction & EAST) {
		setAngle(getAngle() / 2.f);
	}
	else if (direction & WEAST) {
		setAngle(-180.f - getAngle() / 2.f);
	}
	_direction = direction;
}

uint8_t AEntity::getDirection(void) const
{
	return (_direction);
}

void AEntity::setReadyForInit(bool value)
{
	_readyForInit = value;
}

bool AEntity::isReadyForInit(void) const
{
	return (_readyForInit);
}

void AEntity::setVelocity(float velocity)
{
	_velocity = velocity;
}

float AEntity::getVelocity(void) const
{
	return (_velocity);
}

void AEntity::setAngle(float angle)
{
	_degrees = angle;
	_radians = angle * (2.f * 3.14159265f) / 360.f;
}

float AEntity::getAngle(void) const
{
	return (_degrees);
}

float AEntity::getRadians(void) const
{
	return (_radians);
}