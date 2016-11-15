#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Timer.hpp"
#include "SplashScreen.hpp"
#include "FPSCounter.hpp"

#include "StaticTools.h"
#include "ProjectResource.h"


class Application
{
public:
	Application(void);
	~Application(void);

	/* Initialise l'application */
	void init(void);

	/* Boucle principale */
	void loop(void);

private:
	void draw(void);

	Timer _timer;
	sf::RenderWindow _window;

	MusicBox _music;
	SplashScreen _splash;
	FPSCounter _fps;
};

