#include "AEntity.hpp"

AEntity::AEntity()
	  : _waitingForRecycle(false),
	    _init(false)
{
}

AEntity::~AEntity(void)
{
}

void AEntity::recycle(void)
{
	_waitingForRecycle = true;
}

bool AEntity::isWaitingForRecycle(void) const
{
	return (_waitingForRecycle);
}

bool AEntity::isInitialized(void) const
{
	return (_init);
}