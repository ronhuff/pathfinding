#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <math.h>
#include "Search.h"
#include "Grid.h"

class Astar :
	public Search
{
public:
	Astar();
	~Astar();

	virtual void init(const bool custom);
	bool isDone() const;
	bool isSolved() const;

	virtual void update();
	virtual void render(sf::RenderWindow &window);

private:

	virtual void setCustom(const int array[6]);

	int m_Rows = 40;
	int m_Cols = 40;
	int m_beginX = 0;
	int m_beginY = 0;
	int m_endX = m_Rows - 1;
	int m_endY = m_Cols - 1;

	float m_squareWidth;
	float m_squareHeight;

	sf::Clock m_Timer;

	sf::Font m_Font;
	sf::Text m_TimeText;

	Grid grid;
	bool m_isDone = false;
	bool m_isSolved = false;

	std::shared_ptr<Node> m_start;
	std::shared_ptr<Node> m_end;

	std::vector<std::shared_ptr<Node>> openSet;
	std::vector<std::shared_ptr<Node>> closedSet;
	std::vector<std::shared_ptr<Node>> path;

	void removeFromVector(std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node>& element);
	bool vectorContains(std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node>& element);

	float heuristic(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);

	void setOpen();
	void setClosed();
	void setPath();
	void reconstructPath(std::shared_ptr<Node> previous, std::shared_ptr<Node> current);
};

