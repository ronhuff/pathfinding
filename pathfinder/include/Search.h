#pragma once

#include "SFMLApplication.h"
class Search :
	public SFMLApplication
{
public:
	Search() = default;
	virtual ~Search() = default;

	virtual void init(bool custom) = 0;

	virtual bool update() = 0;
	virtual void render(sf::RenderWindow &window);
	virtual bool isDone() const = 0;
	virtual bool isSolved() const = 0;

	virtual void setCustom(const int array[6]) = 0;
	virtual void setHeuristicFlag(bool newFlag) = 0;
};

