#pragma once

#include "SFML/Graphics.hpp"

#include "InputHandler.hpp"

class MenuSlider : public sf::Drawable {
	static const uint32_t MAX_VALUE;
	static const uint32_t MIN_VALUE;
	static const float VALUE_BAR_WIDTH;
	static const sf::Color DEFAULT_COLOR;

public:
	MenuSlider(uint32_t value = 0u);
	virtual ~MenuSlider();

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool input(InputHandler &input);
	void updateDisplay(void);

public:
	sf::Vector2f const &getPosition(void) const;
	sf::Vector2f const &getSize(void) const;
	uint32_t getValue(void) const;
	sf::Color const &getColor(void) const;

public:
	void setPosition(sf::Vector2f const &position);
	void setSize(sf::Vector2f const &size);
	void setValue(const uint32_t value);
	void setColor(sf::Color const &color);

private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	uint32_t _value;

private:
	sf::RectangleShape _sliderHorizontalBar;
	sf::RectangleShape _sliderValueBar;
};

