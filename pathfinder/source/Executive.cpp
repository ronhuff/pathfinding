#include "..\include\Executive.h"

bool Executive::run()
{
	std::cout << "-== Algorithms! ==-\n\n";
	std::cout << "Please select an algorithm to execute.\n";
	std::cout << "1) A* Pathfinding Algorithm.\n";
	std::cout << "2) Exit application.\n";
	std::cout << "Selection: ";
	int input;
	validateInteger(std::cin, input);
	while (input > 2 || input < 1)
	{
		validateInteger(std::cin, input);
	}
	if (input == 1)
	{
		getUserSpecifications();
		runAstar();
	}
	else if (input == 2)
	{
		return(false);
	}
	return(true);
}

void Executive::runAstar()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "A* Pathfinding Algorithm", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	bool closed = false;
	bool wait = false;

	while (!closed)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				closed = true;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (wait == true)
				{
					closed = true;
				}
				wait = false;
			}
		}

		if (m_algorithm->isDone() && m_algorithm->isSolved() && !closed)
		{
			window.clear(sf::Color(30, 255, 30));
			m_algorithm->render(window);
			window.display();
			wait = true;
		}
		else if (m_algorithm->isDone() && !closed)
		{
			window.clear(sf::Color(255, 255, 30));
			m_algorithm->render(window);
			window.display();
			wait = true;
		}
		else
		{
			window.clear(sf::Color(245, 245, 255));
		}
		if (!wait)
		{
			m_algorithm->update();
			m_algorithm->render(window);
			window.display();
		}
	}
	window.close();	
}

void Executive::getUserSpecifications()
{
	std::cout << "\nDo you wish to specify your own parameters or choose the default?(50x50, top left -> bottom right)\n";
	std::cout << "1) Default.\n";
	std::cout << "2) Specify my own.\n";
	int input;
	validateInteger(std::cin, input);
	while (input > 2 || input < 1)
	{
		validateInteger(std::cin, input);
	}
	m_algorithm = std::make_unique<Astar>();
	if (input == 2)
	{
		getSizeAndIndex();//grid size, starting/ending index
	}
	else if (input == 1)
	{
		m_algorithm->init(false);
		std::cout << "Finding shortest route from position (1, 1) to position (50, 50)...\n";
	}
}

void Executive::getSizeAndIndex()
{
	std::cout << "\n-== Define grid specifications ==-\n";
	int userRows = getRowsFromUser();
	int userCols = userRows;

	std::cout << "\nPlease enter beginning index values(e.g. x = 1, y = 1).\nNote: The first index is (1, 1) and the final is (" << userRows << ", " << userCols << ").\n";
	std::cout << "\nBeginning Index:\nx = ";
	int userX;
	int userY;
	validateInteger(std::cin, userX);
	while (userX > userRows || userX < 1)
	{
		validateInteger(std::cin, userX, "Value for x must be between 1 and " + std::to_string(userRows) + ".");
	}
	std::cout << "\nBeginning Index:\ny = ";
	validateInteger(std::cin, userY);
	while (userY > userCols || userY < 1)
	{
		validateInteger(std::cin, userY, "Value for y must be between 1 and " + std::to_string(userCols) + ".");
	}

	int userEndX = 0;
	int userEndY = 0;

	std::cout << "\nPlease enter ending index values(e.g. x = 1, y = 1).\nNote: The first index is (1, 1) and the final is (" << userRows << ", " << userCols << ").\n";
	std::cout << "\nEnding Index:\nx = ";

	//set end cell.
	validateInteger(std::cin, userEndX);
	while (userEndX > userRows || userEndX < 1)
	{
		validateInteger(std::cin, userEndX, "Value for x must be between 1 and " + std::to_string(userRows) + ".");
	}

	std::cout << "\nEnding Index:\ny = ";
	validateInteger(std::cin, userEndY);
	while (userEndY > userCols || userEndY < 1)
	{
		validateInteger(std::cin, userEndY, "Value for y must be between 1 and " + std::to_string(userCols) + ".");
	}
	const int pointIndexes[6] = { userRows, userCols, userX - 1, userY - 1, userEndX - 1, userEndY - 1 };
	
	std::cout << "\nPlease choose a heuristic for distance.\n";
	std::cout << "1) Euclidian Distance.\n";
	std::cout << "2) Manhattan Distance.\n";
	int hChoice;
	validateInteger(std::cin, hChoice);
	if (hChoice == 1)
	{
		m_algorithm->setHeuristicFlag(true);
	}
	else
	{
		m_algorithm->setHeuristicFlag(false);
	}
	m_algorithm->setCustom(pointIndexes);
	m_algorithm->init(true);
	std::cout << "Finding shortest route from position (" << userX << ", " << userY << ") to position (" << userEndX << ", " << userEndY << ").\n";
}

void Executive::validateInteger(std::istream& input, int& variable, const std::string& rangeWarning)
{
	if (rangeWarning != "")
	{
		std::cout << rangeWarning;

	}
	while (!(input >> variable))
	{
		std::cout << "\nPlease enter a number: \n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
}

void Executive::validateFloat(std::istream& input, float& variable, const std::string& rangeWarning)
{
	if (rangeWarning != "")
	{
		std::cout << rangeWarning;
	}
	while (!(input >> variable))
	{
		std::cout << "\nPlease enter a number: \n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
}

int Executive::getRowsFromUser()
{
	std::cout << "We are currently only able to support square grids (e.g. 10 x 10, 50 x 50, etc.)\n";
	std::cout << "Enter grid size(225 max): ";
	int userRows;
	validateInteger(std::cin, userRows);
	while (userRows > 225 || userRows < 4)
	{
		validateInteger(std::cin, userRows, "Please keep the size between 4 & 100\n");
	}
	return(userRows);
}

int Executive::getColsFromUser()
{
	std::cout << "Columns: ";
	int userCols;
	validateInteger(std::cin, userCols);
	while (userCols > 60 || userCols < 4)
	{
		validateInteger(std::cin, userCols, "Please keep the size between 4 & 60 columns.\n");
	}
	return (userCols);
}