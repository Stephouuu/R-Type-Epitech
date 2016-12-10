#include "Mate.hpp"

Mate::Mate(void)
{
	_targetFrame = 0;
	_currentFrame = 0;
	setVelocity(0.f);
	_currentDirection = FRAME_MID;
	_resolution = StaticTools::GetResolution();
	_powder = NULL;
	_loadedPowder = NULL;
	_loadedShot = false;
}

Mate::~Mate(void)
{
	if (_loadedPowder) {
		_loadedPowder->recycle();
	}
}

void Mate::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(65, 38));
	setOrigin(32.5f, 19);

	try {
		initFrame();

		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		sf::IntRect const& rect = _frames.at(FRAME_MID);
		getShape()->setTextureRect(rect);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		setDead(true);
	}
}

void Mate::update(float delta)
{
	if (isDead()) {
		if (_powder) {
			_powder->recycle();
			_powder = NULL;
		}
		return;
	}
	_delta += delta;

	if (_powder && _powder->isAnimationFinished()) {
		_powder->recycle();
		_powder = NULL;
	}

	if (_currentDirection != FRAME_EXP) {
		uint8_t direction = getDirection();
		_targetFrame = 0;
		_currentDirection = FRAME_MID;

		if (direction != 0) {
			if (direction == NORTH) {
				_currentDirection = FRAME_TOP;
			}
			else if (direction == SOUTH) {
				_currentDirection = FRAME_BOT;
			}
			else if (direction & NORTH && direction & EAST) {
				_currentDirection = FRAME_TOP;
			}
			else if (direction & SOUTH && direction & EAST) {
				_currentDirection = FRAME_BOT;
			}

			if (direction & WEAST) {
			}
			else if (direction & EAST) {
				_targetFrame = 3;
			}
		}
	}

	updateFrame();
	ANPC::update(delta);
}

void Mate::destroy(void)
{

}

void Mate::collision(IClient *client, AEntity *other)
{
	(void)client;
	if (getCollisionType() != COLLISION_NONE
		&& other->getCollisionType() == COLLISION_FATAL
		&& !hasCollisioned()) {
		
		setCollisioned(true);

		//if (!other->hasCollisioned()) {
		//	other->collision(client, this);
		//}
		setCollisionType(COLLISION_NONE);
	}
}

void Mate::applyCollision(CollisionType type)
{
	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		collisionDestruction();
		break;
	case CollisionType::PowerUP:
		break;
	default:
		break;
	}
}

void Mate::move(float delta)
{
	if (getAngle() != -1) {
		sf::Vector2f const& pos = getPosition();

		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		if (pos.x + x < 0 || pos.x + x > _resolution.first) {
			x = 0;
		}
		if (pos.y + y < 0 || pos.y + y > _resolution.second) {
			y = 0;
		}

		ADrawable::move(x, y);
		if (_powder) {
			_powder->setPosition(pos.x + 35, pos.y + 2);
		}
		if (_loadedPowder) {
			_loadedPowder->setPosition(pos.x + 48, pos.y + 3);
		}
	}
}

void Mate::shoot(Fire const& param)
{
	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}

	std::cout << "spawning shot with id " << (int)param.id << std::endl;

	LevelResource::TheLevelResource.getSoundByKey("shot")->play();

	MissileType type = param.type;
	uint16_t id = param.id;
	uint16_t id_launcher = param.id_launcher;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t velocity = param.velocity;
	uint8_t angle = param.angle;
	uint8_t effect = param.effect;

	StaticTools::DeserializePosition(param.position, x, y);

	Laser *laser = World::spawnEntity<Laser>();
	//Laser *laser = new Laser;
	laser->setID(id);
	laser->setLevel(param.level);
	laser->setPosition(x, y);
	laser->setOwnerID(id_launcher);
	laser->setAngle(angle);
	laser->setVelocity(velocity);
	laser->setColor(id_launcher);
	laser->setReadyForInit(true);
	//World::pushEntity(laser);

	if (!_powder) {
		_powder = World::spawnEntity<Powdered>();
		_powder->setPosition(getPosition().x + 35, y + 2.f);
		_powder->setColor(getID());
		_powder->setReadyForInit(true);
	}
}

void Mate::setPowder(PowderType powderType)
{
	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}

	switch (powderType)
	{
	case PowderType::LoadedPowder:
		_loadedPowder = World::spawnEntity<LoadedPowdered>();
		_loadedPowder->setPosition(getPosition().x + 48, getPosition().y + 3);
		_loadedPowder->setColor(getID());
		_loadedPowder->setReadyForInit(true);
		break;
	default:
		break;
	}
}

void Mate::initFrame(void)
{
	switch (getID())
	{
	case 1:
		_frames[FRAME_TOP] = sf::IntRect(0, 302, 64, 38);
		_frames[FRAME_MID] = sf::IntRect(0, 340, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 377, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 415, 64, 38);
		break;
	case 2:
		_frames[FRAME_TOP] = sf::IntRect(0, 152, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 189, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 226, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 264, 64, 38);
		break;
	case 3:
		_frames[FRAME_TOP] = sf::IntRect(0, 2, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 39, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 76, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 114, 64, 38);
		break;
	case 4:
		_frames[FRAME_TOP] = sf::IntRect(0, 453, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 490, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 527, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 565, 64, 38);
		break;
	default:
		break;
	}
}

void Mate::updateFrame(void)
{
	if (_delta > 0.08f) {

		if (_currentDirection == FRAME_EXP) {
			if (_currentFrame == 5) {
				setDead(true);
				setVisiblity(VISIBILITY_GONE);
				return;
			}
		}

		if (_currentFrame != _targetFrame) {
			if (_currentFrame < _targetFrame) {
				++_currentFrame;
			}
			else if (_currentFrame > _targetFrame) {
				--_currentFrame;
			}
		}

		if (_currentDirection != FRAME_EXP && _currentFrame == 3) {
			if (_decrease) {
				--_currentFrame;
				_decrease = false;
			}
			else {
				_decrease = true;
			}
		}
		else if (_currentDirection != FRAME_EXP && _currentFrame == 0) {
			if (_decrease) {
				++_currentFrame;
				_decrease = false;
			}
			else {
				_decrease = true;
			}
		}
		
		sf::IntRect const& r = _frames.at(_currentDirection);
		getShape()->setTextureRect(sf::IntRect(_currentFrame * r.width, r.top, r.width, r.height));
		_delta = 0.f;
	}
}

void Mate::collisionDestruction(void)
{
	Explosion *explosion = World::spawnEntity<Explosion>();
	explosion->setPosition(getPosition());
	explosion->setReadyForInit(true);

	_currentDirection = FRAME_EXP;
	_currentFrame = 0;
	_targetFrame = 5;

	setAngle(-1);
	setVelocity(0);

	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}
}