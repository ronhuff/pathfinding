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

	void populateGrid(const int& rows, const int& cols);

	int m_Rows;
	int m_Cols;
	int m_Size;

	float m_xOffSet = 0;
	float m_yOffSet = 0;

	std::shared_ptr<Node>& getNode(const int& x, const int& y);

	sf::VertexArray m_gridDisplay;
	sf::VertexArray m_lines;

	void setNodeVertices();

	std::vector<std::vector<std::shared_ptr<Node>>> m_Nodes;

	void draw(sf::RenderWindow& window);

};