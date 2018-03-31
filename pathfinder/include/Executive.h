#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Search.h"
#include "Astar.h"



class Executive
{
public:
	Executive();
	~Executive();


	//Interface details.

	const float m_SCREEN_WIDTH = 1280;
	const float m_SCREEN_HEIGHT = 720;
	
	std::unique_ptr<Search> m_algorithm;
	sf::RenderWindow window;

	bool run();
	void startAstar();
	void validateInteger(std::istream& stream, int& input, const std::string& rangeWarning = "");
	void validateFloat(std::istream& input, float& variable, const std::string& rangeWarning);

	int getRowsFromUser();
	int getColsFromUser();
};

