#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Node.h"

class Grid
{
public:
	Grid();
	~Grid();

	const int WALL_CHANCE = 25;

	int m_Rows;
	int m_Cols;
	int m_Size;

	float m_xOffSet = 0;
	float m_yOffSet = 0;

	void populateGrid(const int& rows, const int& cols);


	std::shared_ptr<Node>& getNode(const int& x, const int& y);

	void setNodeVertices();
	sf::VertexArray gridDisplay;
	sf::VertexArray lines;

	std::vector<std::vector<std::shared_ptr<Node>>> nodes;

	int numWalls = 0;

private:


};