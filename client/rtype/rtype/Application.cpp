#include "Application.hpp"

Application::Application(void)
	: _client(&_game, "127.0.0.1", "4242")
{
		//_game(_client, "room1", "pwd1")
	std::pair<short, short> resolution = StaticTools::GetResolution();

	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	_window.create(sf::VideoMode(resolution.first, resolution.second), "R-Type", sf::Style::Default, context);
	_window.setPosition(sf::Vector2i(0, 0));
	_window.setVerticalSyncEnabled(true);

	_state = ApplicationState::AS_MainMenu;
	_inputs[ApplicationState::AS_MainMenu] = std::bind(&Application::inputMenu, this, std::placeholders::_1);
	_inputs[ApplicationState::AS_Game] = std::bind(&Application::inputGame, this, std::placeholders::_1);
	_updates[ApplicationState::AS_MainMenu] = std::bind(&Application::updateMenu, this, std::placeholders::_1);
	_updates[ApplicationState::AS_Game] = std::bind(&Application::updateGame, this, std::placeholders::_1);
	_draws[ApplicationState::AS_MainMenu] = std::bind(&Application::drawMenu, this, std::placeholders::_1);
	_draws[ApplicationState::AS_Game] = std::bind(&Application::drawGame, this, std::placeholders::_1);

	_game = NULL;
	_quit = false;
}

Application::~Application(void)
{
}

//#include <Windows.h> // !
void Application::init(std::string host, std::string pwd)
{
  (void)host;
  (void)pwd;
	try {
		StaticTools::Log.open("client.log" /*+ std::to_string(GetCurrentProcessId()) + ".log"*/, std::ios::out | std::ios::app);
		ProjectResource::TheProjectResource.load();

		initIcon();
		initNetwork();
		
		_fps.init();
		_inputHandler.init();

		_menu.init();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}

	_timer.restart();
}


// les �tats peuvent se changer d'eux m�me => � faire
void Application::loop(void)
{
	sf::Event event;
	float delta = 0;

	while (_window.isOpen())
	{
		delta = _timer.restart();

		while (_window.pollEvent(event))
		{
			_inputHandler.OnEvent(event);
			if (!isRunning()) {
				_client.disconnect();
				_window.close();
			}
		}

		_inputs.at(_state)(_inputHandler);
		_updates.at(_state)(delta);
		_draws.at(_state)(_window);
	}
}

void Application::initIcon(void)
{
	sf::Image image;

	if (!image.loadFromFile("./rsrc/sprites/icon.png")) {
		throw (std::runtime_error("can not load icon"));
	}
	_window.setIcon(128, 128, image.getPixelsPtr());
}

void Application::initNetwork(void)
{
	_client.connect();
	_client.run();
}

void Application::inputMenu(InputHandler &input)
{
	_menu.input(input);
}

void Application::inputGame(InputHandler &input)
{
	_game->input(input);
}

void Application::updateMenu(float delta)
{
	_fps.update(delta);
	_menu.update(delta);
	switch (_menu.pullAction())
	{
	case MainMenuController::SelectedAction::PLAY:
		_state = ApplicationState::AS_Game;
		_game = new GameController(_client);
		_game->init();
		_game->connectToParty("name", "pwd");
		break;
	case MainMenuController::SelectedAction::QUIT:
		_quit = true;
		break;
	default:
		break;
	}
}
void Application::updateGame(float delta)
{
	_fps.update(delta);
	_game->update(delta);
}

void Application::drawMenu(sf::RenderWindow &window)
{
	_window.clear();
	_menu.draw(window);
	_fps.draw(_window);
	_window.display();
}

void Application::drawGame(sf::RenderWindow &window)
{
	_window.clear();
	_game->draw(window);
	_fps.draw(_window);
	_window.display();
}

bool Application::isRunning(void) const
{
	return (!_inputHandler.isExiting() && !_quit && _window.isOpen());
}