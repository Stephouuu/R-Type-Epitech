#include "ConnectionManager.hpp"
#include "AConnection.hpp"

ConnectionManager::ConnectionManager(void)
{
}

ConnectionManager::~ConnectionManager(void)
{
}

void ConnectionManager::add(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_connections.insert(connection);
}

void ConnectionManager::leave(std::shared_ptr<AConnection> connection)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_connections.erase(connection);
}

void ConnectionManager::broadcast(std::shared_ptr<AConnection> connection, std::shared_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		if (it->getID() != connection->getID()) {
			it->sync_write(command);
		}
	}
}

void ConnectionManager::broadcast(std::shared_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		std::cout << "sending to " << (int)it->getID() << std::endl;
		it->sync_write(command);
	}
}

void ConnectionManager::closeAll(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_connections.clear();
}

void ConnectionManager::reset(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		it->setLife(3);
	}
}

void ConnectionManager::distributeShipID(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		ObjectType object = ObjectType::Ship;
		uint16_t id = it->getID();
		uint16_t x = it->getPosition().first;
		uint16_t y = it->getPosition().second;
		uint8_t type = (uint8_t)ShipType::Standard;
		uint8_t effect = 0;
		uint8_t health = it->getLife();
		bool player = true;

		it->sync_write(std::make_shared<CMDSpawn>(object, id, x, y, type, effect, health, player));
	}
}

void ConnectionManager::sendSpawnedShip(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (auto &it : _connections) {
		for (auto &it2 : _connections) {
			if (it->getID() != it2->getID()) {
				ObjectType object = ObjectType::Ship;
				uint16_t id = it2->getID();
				uint16_t x = it2->getPosition().first;
				uint16_t y = it2->getPosition().second;
				uint8_t type = (uint8_t)ShipType::Standard;
				uint8_t effect = 0;
				uint8_t health = it2->getLife();
				bool player = false;

				it->sync_write(std::make_shared<CMDSpawn>(object, id, x, y, type, effect, health, player));
			}
		}
	}
}


uint8_t ConnectionManager::getPlayerNumber(void) const
{
	return (static_cast<uint8_t>(_connections.size()));
}

bool ConnectionManager::isPlayersAlive(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	uint8_t nb = 0;

	for (auto &it : _connections) {
		if (it->getLife() > 0) {
			++nb;
		}
	}
	return (nb > 0);
}