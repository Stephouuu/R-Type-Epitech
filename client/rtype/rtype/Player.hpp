#pragma once

#include <string>

#include "APC.hpp"
#include "LevelResource.hpp"
#include "Laser.hpp"
#include "Explosion.hpp"
#include "Powdered.hpp"
#include "LoadedPowdered.hpp"

class IClient;

class Player : public APC
{
private:
	static const uint8_t FRAME_TOP = 0;
	static const uint8_t FRAME_MID = 1;
	static const uint8_t FRAME_BOT = 2;
	static const uint8_t FRAME_EXP = 3;

public:
	Player();
	virtual ~Player(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	virtual void collision(IClient *client, ACollidable *other);
	virtual void input(InputHandler &input);
	virtual void move(float delta);

	virtual void shoot(Fire const& param);

	void setIClient(IClient *client);

	/* ici les getters pour le hud */

private:
	void initFrame(void);
	void updateFrame(void);

	void keyboard(InputHandler &input);
	void joystick(InputHandler &input);

	float _delta;
	float _deltaLastShoot;
	IClient *_client;
	bool _decrease;
	uint8_t _targetFrame;
	uint8_t _currentFrame;

	std::unordered_map<uint8_t, sf::IntRect> _frames;
	uint8_t _currentDirection;
	std::pair<short, short> _resolution;

	Powdered *_powder;
	LoadedPowdered *_loadedPowder;
	bool _loadedShot;
	float _deltaLoadedShot;
};

