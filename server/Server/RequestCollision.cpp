#include "RequestCollision.hpp"
#include "Party.hpp"

RequestCollision::RequestCollision(void)
{
}

RequestCollision::~RequestCollision(void)
{
}

void RequestCollision::execute(std::shared_ptr<AConnection> owner,
				std::shared_ptr<ICommand> received,
				std::shared_ptr<ICommand> &reply)
{
	(void)received;
	std::shared_ptr<Party> party = owner->getCurrentParty();
	if (party) {
		party->collision(received);
	}
}