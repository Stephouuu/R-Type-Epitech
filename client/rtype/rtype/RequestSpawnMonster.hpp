#pragma once

#include "IRequest.hpp"
#include "StaticTools.hpp"
#include "World.hpp"
#include "Mate.hpp"

class RequestSpawnMonster : public IRequest
{
public:
	RequestSpawnMonster(void);
	virtual ~RequestSpawnMonster(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};