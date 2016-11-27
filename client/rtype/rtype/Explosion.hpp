#pragma once

#include "AExplosion.hpp"

#include "LevelResource.hpp"

class Explosion : public AExplosion
{
public:
	Explosion();
	virtual ~Explosion(void);

	virtual void init(void);
	virtual void destroy(void);
};
