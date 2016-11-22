#pragma once

#include "Protocol.hpp"

struct ICommand
{
	virtual ~ICommand(void) {}
	virtual void loadFromMemory(char const *data) = 0;
	virtual size_t getSize(void) const = 0;
	virtual CommandType getCommandType(void) const = 0;
	virtual char const* getData(void) const = 0;
};