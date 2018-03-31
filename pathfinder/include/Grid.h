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
	std::shared_ptr<Node>& getNode(const int& x, const int& y);

	std::vector<sf::Vertex> m_gridDisplay;

	

	std::vector<std::vector<std::shared_ptr<Node>>> m_Nodes;

	void draw(sf::RenderWindow& window);

};