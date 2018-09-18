#include "..\include\Astar.h"

Astar::Astar()
{
	m_Font.loadFromFile("arial.ttf");
	m_TimeText.setCharacterSize(36);
	m_TimeText.setFillColor(sf::Color::Black);
	m_TimeText.setFont(m_Font);
	m_TimeText.setPosition(sf::Vector2f(900, 200));
}

bool Astar::update()// algorithm logic
{
	if (!openSet.empty())
	{
		std::shared_ptr<Node> current = openSet.at(0);
		m_cellsVisited++;
		for (auto openit = openSet.begin(); openit != openSet.end(); openit++)
		{
			if (((*openit)->f >= current->f))
			{
				continue;
			}
			else
			{
				current = (*openit);
			}
		}
		if (current == m_end)
		{
			std::cout << "...Solved\n";
			//find path.
			m_isSolved = true;
			m_isDone = true;
			//current->square.setFillColor(sf::Color::Blue);
			current->setColor(sf::Color::Blue);
			
			reconstructPath(current->previous, current);
			std::cout << "\nManhattan distance: " << abs(m_end->x - m_start->x) + abs(m_end->y - m_start->y) + 2 << " steps.\n";
			std::cout << "Approximate Euclidian distance: " << floor(sqrt(pow(abs(m_end->x - m_start->x + 1), 2) + pow(abs(m_end->y - m_start->y + 1), 2))) << " steps.\n";
			std::cout << "The shortest path takes " << path.size() << " steps.\n";
			std::cout << "Visited " << m_cellsVisited << " locations out of " << m_Rows * m_Rows - grid.numWalls<< " total.(";
			std::cout << std::fixed << std::setprecision(2) << (((double)m_cellsVisited / (double)(m_Rows * m_Rows - grid.numWalls)) * 100) << "%)\n";
			setOpen();
			setClosed();
			setPath();
			return(true);
		}
		removeFromVector(openSet, current);
		closedSet.push_back(current);

		for (auto neighborit = current->neighbors.begin(); neighborit != current->neighbors.end(); neighborit++)
		{
			if (vectorContains(closedSet, (*neighborit)))
			{
				// Ignore the neighbor which is already evaluated.
				//std::cout << "Ignoring neighbor in closed set. Astar.cpp: 87 ** DEBUG **\n";
				continue;
			}

			if (!vectorContains(openSet, (*neighborit)))
			{
				// Discover a new node.
				openSet.push_back((*neighborit));
				//std::cout << "Added neighbor at " << (*neighborit)->x << ", " << (*neighborit)->y << ". To the closed set Astar.cpp: 96 ** DEBUG **\n";
			}

			float tempg = current->g + 1.0f;//in this system, dist must be 1.
			if (tempg >= (*neighborit)->g)
			{
				// This is not a better path.
				continue;
			}

			// This path is the best until now, Record it.
			(*neighborit)->previous = current;
			(*neighborit)->g = tempg;
			(*neighborit)->f = (*neighborit)->g + heuristic((*neighborit), m_end);
		}
		setOpen();
		setClosed();
		reconstructPath(current->previous, current);
		setPath();
	}
	else
	{
		std::cout << "No solution.\n";
		m_isSolved = false;
		m_isDone = true;
	}
	return(false);
}

void Astar::render(sf::RenderWindow & window)
{
	m_Timer.restart();
	window.draw(grid.gridDisplay);	
	window.draw(grid.lines);

	//The below commented block can be used to display render calls per second.
	//Uncomment the block, comment out lines 116, 117 & pass fstring to setString()
	//on line 118

	//auto elapsed = m_Timer.getElapsedTime();
	//float milliseconds = elapsed.asSeconds();
	//std::string fstring = std::to_string(std::floor(1.0f / milliseconds));
	//fstring.erase(fstring.find_last_not_of('0') + 1, std::string::npos);
	//fstring.pop_back();*/
	//fstring += "\nRenders per second.\n";
	std::string cellString = std::to_string(m_cellsVisited);
	cellString += "\nCells visited.\n";
	m_TimeText.setString(cellString);

	window.draw(m_TimeText);
}

void Astar::setHeuristicFlag(bool newFlag)
{
	m_heuristicFlag = newFlag;
}

void Astar::init(const bool custom)
{
	if (!custom)
	{
		grid.populateGrid(m_Rows, m_Cols);//create nodes.
		const int BEGIN_X = 0;
		const int BEGIN_Y = 0;
		const int END_X = m_Rows - 1;
		const int END_Y = m_Cols - 1;
		m_start = grid.getNode(BEGIN_X, BEGIN_Y);
		m_end = grid.getNode(END_X, END_Y);
	}

	grid.m_xOffSet = (720.0f / float(m_Rows)) * 0.95f;
	grid.m_yOffSet = (720.0f / float(m_Rows)) * 0.95f;
	grid.setNodeVertices();
	//add nodes to closed set.
	for (auto rowit = grid.nodes.begin(); rowit != grid.nodes.end(); rowit++)
	{
		for (auto nodeit = rowit->begin(); nodeit != rowit->end(); nodeit++)
		{
			if ((*nodeit) == m_end)
			{
				continue;
			}
			if ((*nodeit)->wall)
			{
				closedSet.push_back((*nodeit));
			}
		}
	}

	m_start->h = heuristic(m_start, m_end);
	m_start->f = m_start->h;
	m_start->g = 0.0;
	//if start or end were randomly set to be walls, this fixes that.
	m_start->wall = false;
	m_end->wall = false;
	openSet.push_back(m_start);
	int count = 0;
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
		{
			if (grid.getNode(i, j)->wall)
			{
				count++;
			}
		}
	}
	grid.numWalls = count;
	std::cout << "Number of walls: " << count << " Percentage: " << (float(count) / (float(m_Rows) * float(m_Cols))) * 100.0f << "%\n";
}

void Astar::setCustom(const int array[6])
{
	m_Rows = array[0];
	m_Cols = array[1];
	grid.populateGrid(m_Rows, m_Cols);
	m_start = grid.getNode(array[2], array[3]);
	m_end = grid.getNode(array[4], array[5]);	
}

void Astar::removeFromVector(std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node>& element)
{
	for (auto it = vector.begin(); it != vector.end(); it++)
	{
		if ((*it) == element)
		{
			vector.erase((it));
			return;
		}
	}
}

bool Astar::vectorContains(std::vector<std::shared_ptr<Node>>& vector, std::shared_ptr<Node>& element)
{
	for (auto it = vector.begin(); it != vector.end(); it++)
	{
		if ((*it) == element)
		{
			return(true);
		}
	}
	return(false);
}

float Astar::heuristic(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b)
{
	if (m_heuristicFlag)
	{
		//Euclidian Distance.
		float d = sqrt(float(pow(abs(b->x - a->x), 2.0f)) + float(pow(abs(b->y - a->y), 2.0f)));
		//return(float(pow(d + 1.0f, 2.0f)));// returns a value of (d + 1)^2 adding additional accuracy to the heuristic
		return(d);
	}
	else
	{
		//Manhattan Distance.
		auto dx = abs(b->x - a->x);
		auto dy = abs(b->y - a->y);
		//return (pow(dx + dy, 2));//returns (dx + dy)^2
		return(dx + dy);
	}

}

void Astar::reconstructPath(std::shared_ptr<Node> previous, std::shared_ptr<Node> current)
{
	path.clear();
	path.push_back(current);
	while (current->previous)
	{
		current = current->previous;
		path.push_back(current);
	}
}

void Astar::setOpen()
{
	for (auto nit = openSet.begin(); nit != openSet.end(); nit++)
	{
		(*nit)->setColor(sf::Color(30, 255, 30));
	}
}

void Astar::setClosed()
{
	for (auto nit = closedSet.begin(); nit != closedSet.end(); nit++)
	{
		if ((*nit)->wall)
		{
			(*nit)->setColor(sf::Color(15, 15, 15));
			continue;
		}
		(*nit)->setColor(sf::Color(255, 30, 30));
	}
}

void Astar::setPath()
{
	for (auto nit = path.begin(); nit != path.end(); nit++)
	{
		(*nit)->setColor(sf::Color(30, 30, 255));
	}
}

bool Astar::isDone() const
{
	return(m_isDone);
}

bool Astar::isSolved() const
{
	return (m_isSolved);
}