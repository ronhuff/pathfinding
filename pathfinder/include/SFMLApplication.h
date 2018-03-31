#pragma once

#include <SFML/Graphics.hpp>

class SFMLApplication
{
public:

	SFMLApplication();
	virtual ~SFMLApplication();

	virtual void update();
	virtual void render(sf::RenderWindow &window);

	virtual bool isDone() const = 0;
	
};
