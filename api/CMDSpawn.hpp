#pragma once

#include "StaticTools.hpp"

#include "ICommand.hpp"

class CMDSpawn : public ICommand
{
public:
	CMDSpawn(ObjectType object, uint16_t id, uint16_t x, uint16_t y,
		      uint8_t type, uint8_t effect, uint8_t health, bool player);
	CMDSpawn(void);
	virtual ~CMDSpawn(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Spawn *_data;
};

