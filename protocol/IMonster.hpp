#pragma once

#include <utility>
#include <stdint.h>
#include <vector>

#include "Protocol.hpp"

class IMonster
{
public:
	virtual ~IMonster(void) {}

	virtual void update(double delta) = 0;
	virtual void takeDamage(uint8_t damage) = 0;

	virtual void setID(uint16_t value) = 0;
	virtual void setPosition(uint16_t y) = 0;

	virtual uint16_t getID(void) const = 0;
	virtual uint16_t getScoreValue(void) const = 0;
	virtual uint8_t getHP(void) const = 0;
	virtual uint8_t getFireRate(void) const = 0;
	virtual uint16_t getVelocity(void) const = 0;
	virtual uint8_t getAngle(void) const = 0;
	virtual std::string getType(void) const = 0;
	virtual uint16_t getPosition(void) const = 0;
	virtual std::vector<std::pair<uint16_t, uint16_t> > const& getCanonRelativePosition(void) const = 0;
	virtual std::vector<float> const& getCanonDegrees(void) const = 0;
};