#include "..\include\Grid.h"
Grid::Grid()
	:m_gridDisplay(sf::Quads, 0)
{

}

Grid::~Grid()
{
	for (int i = 0; i < m_Rows; i++)
	{
		m_Nodes.pop_back();
	}
}

void Grid::populateGrid(const int& rows, const int& cols)
{
	m_Rows = rows;
	m_Cols = cols;
	m_Size = rows * cols;
	std::cout << "\nCreating Nodes...\n";
	srand(time(0));
	for (int i = 0; i < m_Cols; i++)
	{
		std::vector<std::shared_ptr<Node>> temp;
		m_Nodes.push_back(temp);
		for (int j = 0; j < m_Rows; j++)
		{

			m_Nodes.at(i).push_back(std::make_shared<Node>(i, j));
		}
	}

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
		{
			m_Nodes.at(i).at(j)->addNeighbors(m_Nodes, rows, cols);
		}
	}
}

std::shared_ptr<Node>& Grid::getNode(const int& x, const int& y)
{
	return(m_Nodes.at(x).at(y));
}

void Grid::setNodeVertices()
{
	std::cout << "Setting Node Vertices...\n\n";
	for (int i = 0; i < m_Rows; i++)
	{
		//TODO: Find out why only 9 boxes drawing.

		for (int j = 0; j < m_Cols; j++)
		{
			auto node = getNode(i, j);
			float xpos = node->x * m_xOffSet;
			float ypos = node->y * m_yOffSet;

			//sf::RectangleShape gridBox(sf::Vector2f(w, h));
			//sf::CircleShape gridBox(w / 2);
			//gridBox.setPosition(xpos, ypos);
			//gridBox.move(15.0, 15.0);
			//gridBox.setOutlineColor(sf::Color::Black);
			//gridBox.setOutlineThickness(1.0);
			//node->square = gridBox;
			int index = (j * m_Cols) + i;
			for (int k = 0; k < 4; k++)
			{
				node->m_vArray[k] = &m_gridDisplay[index + k];
			}

			
			node->m_vArray[0]->position = sf::Vector2f(xpos, ypos + m_yOffSet);
			node->m_vArray[1]->position = sf::Vector2f(xpos, ypos);
			node->m_vArray[2]->position = sf::Vector2f(xpos + m_xOffSet, ypos);
			node->m_vArray[3]->position = sf::Vector2f(xpos + m_xOffSet, ypos + m_yOffSet);
			node->setColor(sf::Color::Magenta);
		}
	}
}

void Grid::draw(sf::RenderWindow& window) //draws the current state of the grid.
{
	for (int i = 0; i < m_Cols; i++)
	{
		for (int j = 0; j < m_Rows; j++)
		{
			window.draw(getNode(i, j)->square);
		}
	}
}