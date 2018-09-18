#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <math.h>
#include <iomanip>
#include "Search.h"
#include "Grid.h"

class Astar :
	public Search
{
private:
	int m_Rows = 50;
	int m_Cols = 50;
	int m_beginX = 0;
	int m_beginY = 0;
	int m_endX = m_Rows - 1;
	int m_endY = m_Cols - 1;

	float m_squareWidth;
	float m_squareHeight;

	sf::Clock m_Timer;
	sf::Font m_Font;
	sf::Text m_TimeText;
	int m_cellsVisited = 0;

	std::shared_ptr<Node> m_start;
	std::shared_ptr<Node> m_end;

	std::vector<std::shared_ptr<Node>> openSet;
	std::vector<std::shared_ptr<Node>> closedSet;
	std::vector<std::shared_ptr<Node>> path;

	bool m_isDone = false;
	bool m_isSolved = false;
	bool m_heuristicFlag = true;

public:
	Astar();
	~Astar() = default;

	virtual void init(const bool custom);
	bool isDone() const;
	bool isSolved() const;

	virtual bool update();
	virtual void render(sf::RenderWindow &window);

	void setHeuristicFlag(bool newFlag);
	Grid grid;

private:
	virtual void setCustom(const int array[6]);

	float heuristic(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);

	void setOpen();
	void setClosed();
	void setPath();
	void reconstructPath(std::shared_ptr<Node> previous, std::shared_ptr<Node> current);

	void removeFromVector(std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node>& element);
	bool vectorContains(std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node>& element);
};

