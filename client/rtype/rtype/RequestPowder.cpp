#include "RequestPowder.hpp"
#include "AEntity.hpp"
#include "World.hpp"
#include "ANPC.hpp"

RequestPowder::RequestPowder(void)
{
}

RequestPowder::~RequestPowder(void)
{
}


void RequestPowder::execute(IClient &client, std::shared_ptr<ICommand> data,
								  std::shared_ptr<ICommand> &toSend)
{
	std::cout << "receiving loaded powder" << std::endl;
	(void)client;
	(void)toSend;
	LoadedPowder *powder = (LoadedPowder *)data->getData();

	uint8_t id = powder->id;

	AEntity *entity = World::getEntityByID(id);
	ANPC *anpc = dynamic_cast<ANPC *>(entity);
	if (anpc) {
		anpc->setPowder(powder->type);
	}
}