#include "RequestBuilder.hpp"

RequestBuilder::RequestBuilder(void)
{
	_requests[(int)CommandType::Spawn] = std::bind(&RequestBuilder::create_SpawnRequest, this);
	_requests[(int)CommandType::Disconnected] = std::bind(&RequestBuilder::create_DisconnectedRequest, this);
	_requests[(int)CommandType::Move] = std::bind(&RequestBuilder::create_MoveRequest, this);
	_requests[(int)CommandType::Fire] = std::bind(&RequestBuilder::create_FireRequest, this);
	_requests[(int)CommandType::LoadedPowder] = std::bind(&RequestBuilder::create_LoadedPowderRequest, this);
}

RequestBuilder::~RequestBuilder(void)
{
}

std::unique_ptr<IRequest> RequestBuilder::build(CommandType type) const
{
	if (_requests.find((int)type) != _requests.cend()) {
		return (std::move(_requests.at((int)type)()));
	}
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_LoadedPowderRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestPowder));
}

std::unique_ptr<IRequest> RequestBuilder::create_ConnectRequest(void)
{
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_DisconnectedRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestDisconnect));
}

std::unique_ptr<IRequest> RequestBuilder::create_CreatePartyRequest(void)
{
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_SpawnRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestSpawn));
}

std::unique_ptr<IRequest> RequestBuilder::create_MoveRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestMove));
}

std::unique_ptr<IRequest> RequestBuilder::create_CollisionRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_ErrorRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_PingRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_FireRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestFire));
}

std::unique_ptr<IRequest> RequestBuilder::create_GameStatusRequest(void)
{
	return NULL;
}
