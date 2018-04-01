#include "..\include\Astar.h"



Astar::Astar()
{
}

Astar::~Astar()
{
}

void Astar::update()// algorithm logic
{
	if (!openSet.empty())
	{
		std::shared_ptr<Node> current = openSet.at(0);
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
			setOpen();
			setClosed();
			setPath();
			return;
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
}

void Astar::render(sf::RenderWindow & window)
{
	window.draw(grid.m_gridDisplay);
	//grid.draw(window);
}

void Astar::init(const bool custom)
{
	//
	//m_Rows = 40;
	//m_Cols = 40;
	
	grid.m_xOffSet = (720 / m_Rows) * 0.95f;
	grid.m_yOffSet = (720 / m_Rows) * 0.95f;

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

	

	//add nodes to closed set.
	for (auto rowit = grid.m_Nodes.begin(); rowit != grid.m_Nodes.end(); rowit++)
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

	grid.setNodeVertices();
	//createGridSquares(m_squareWidth, m_squareHeight);

	m_start->h = heuristic(m_start, m_end);
	m_start->f = m_start->h;
	m_start->g = 0.0;
	m_start->wall = false;
	m_end->wall = false;
	openSet.push_back(m_start);
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
	//Euclidian Distance.
	float d = sqrt(pow(abs(b->x - a->x), 2) + pow(abs(b->y - a->y), 2));
	return(float(pow(2, d)));// returns a value of 2^(d) making the heuristic exponential for better accuracy.



	//Manhattan Distance.
	/*auto dx = abs(b->x - a->x);
	auto dy = abs(b->y - a->y);

	return (dx > dy ? dx : dy);*/
}

//void Astar::createGridSquares(float& w, float& h)
//{
//	std::cout << "Creating grid squares...\n\n";
//	for (int i = 0; i < m_Rows; i++)
//	{
//		//TODO: Find out why only 9 boxes drawing.
//
//		for (int j = 0; j < m_Cols; j++)
//		{
//			auto node = grid.getNode(i, j);
//			float xpos = node->x * w;
//			float ypos = node->y * h;
//
//			sf::RectangleShape gridBox(sf::Vector2f(w, h));
//			//sf::CircleShape gridBox(w / 2);
//			gridBox.setPosition(xpos, ypos);
//			gridBox.move(15.0, 15.0);
//			gridBox.setOutlineColor(sf::Color::Black);
//			gridBox.setOutlineThickness(1.0);
//			node->square = gridBox;
//		}
//	}
//}

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
		//(*nit)->square.setFillColor(sf::Color::Green);
		(*nit)->setColor(sf::Color::Green);
	}
}

void Astar::setClosed()
{
	for (auto nit = closedSet.begin(); nit != closedSet.end(); nit++)
	{
		if ((*nit)->wall)
		{
			(*nit)->setColor(sf::Color::Black);
			//(*nit)->square.setFillColor(sf::Color::Black);
			continue;
		}
		//(*nit)->square.setFillColor(sf::Color::Red);
		(*nit)->setColor(sf::Color::Red);
	}
}

void Astar::setPath()
{
	for (auto nit = path.begin(); nit != path.end(); nit++)
	{
		//(*nit)->square.setFillColor(sf::Color::Blue);
		(*nit)->setColor(sf::Color::Blue);
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
