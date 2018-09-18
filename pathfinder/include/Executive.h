#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Search.h"
#include "Astar.h"



class Executive
{
public:
	Executive() = default;
	~Executive() = default;


	//Interface details.

	const float SCREEN_WIDTH = 1280;
	const float SCREEN_HEIGHT = 720;
	
	std::unique_ptr<Search> m_algorithm;
	sf::RenderWindow window;

	bool run();
	void runAstar();
	void getUserSpecifications();
	void getSizeAndIndex();
	void validateInteger(std::istream& stream, int& input, const std::string& rangeWarning = "");
	void validateFloat(std::istream& input, float& variable, const std::string& rangeWarning);

	int getRowsFromUser();
	int getColsFromUser();
};

