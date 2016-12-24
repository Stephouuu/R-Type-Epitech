#include "GameOverController.hpp"

GameOverController::GameOverController(void)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
	_string = "Game Over !";
	_color = sf::Color(0, 0, 0, 0);
	_finished = false;
	_started = false;
}

GameOverController::~GameOverController(void)
{
}

void GameOverController::init(void)
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey("font_state"));

		_text.setCharacterSize(26);
		_text.setFillColor(sf::Color::Yellow);
		_text.setString(_string);

		_shape.setSize(sf::Vector2f(_resolution.first, _resolution.second));
		_shape.setPosition(0, 0);
		_shape.setFillColor(_color);

		sf::FloatRect textRect = _text.getLocalBounds();
		_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));
	}
	catch (std::exception const& e) {
		StaticTools::Log << "GameOverController: " << e.what() << std::endl;
	}
}

bool GameOverController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void GameOverController::update(float delta)
{
	_delta += delta;

	if (!_started) {
		ProjectResource::TheProjectResource.getMusicByKey("game_over").play();

		_started = true;
	}
	if (_delta < 8.f) {
		if (_delta < 6.f) {
			_color.a = static_cast<uint8_t>((_delta / 6.f) * 255.f);
			_shape.setFillColor(_color);
		}
	}
	else {
		_finished = true;
	}
}

void GameOverController::draw(sf::RenderWindow &window)
{
	window.draw(_shape);
	window.draw(_text);
}

void GameOverController::recycle(void)
{
}

bool GameOverController::hasFinished(void) const
{
	return (_finished);
}