#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <limits>
#include <iostream>
#include <time.h>
#include <stdlib.h>

class Node {
public:
	Node(int& newx, int& newy);
	~Node();

	float x;
	float y;
	
	float f;
	float g;
	float h;

	bool wall;

	sf::RectangleShape square;
	sf::Vertex* m_vArray[4];
	std::vector<std::shared_ptr<Node>> neighbors;

	std::shared_ptr<Node> previous;

	void addNeighbors(std::vector<std::vector<std::shared_ptr<Node>>>& nodes, const int& ROWS, const int& COLS);

	void setColor(sf::Color newColor);
};