#pragma once

#include <set>
#include <memory>

#include "ICommand.hpp"

class AConnection;

class ConnectionManager
{
public:
	ConnectionManager(void);
	~ConnectionManager(void);

	void add(std::shared_ptr<AConnection> connexion);
	void leave(std::shared_ptr<AConnection> connexion);
	void broadcast(ICommand *command);
	void closeAll(void);

	size_t getPlayerNumber(void) const;

private:
	std::set<std::shared_ptr<AConnection> > _connections;
};

