#include "..\include\Grid.h"
Grid::Grid()
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
