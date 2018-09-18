#include "..\include\Grid.h"
Grid::Grid()
	:gridDisplay(sf::Quads, 0), lines(sf::Lines, 0)
{
}

Grid::~Grid()
{
	for (int i = 0; i < m_Rows; i++)
	{
		nodes.pop_back();
	}
}

void Grid::populateGrid(const int& rows, const int& cols)
{
	m_Rows = rows;
	m_Cols = cols;
	m_Size = rows * cols;
	std::cout << "\nCreating Nodes...\n";
	srand(time(0));
	int count = 0;
	for (int i = 0; i < m_Cols; i++)
	{
		std::vector<std::shared_ptr<Node>> tempVec;
		nodes.push_back(tempVec);
		for (int j = 0; j < m_Rows; j++)
		{

			
			for (int k = 0; k < 4; k++)
			{
				//add vertices
				sf::Vertex temp(sf::Vector2f(0.0f, 0.0f), sf::Color(245, 245, 255));
				gridDisplay.append(temp);
				if (k == 0)
				{

				}
				if (k == 3)
				{


					//std::cout << "i = " << i << '\n';
					//std::cout << "j = " << j << '\n';
					//std::cout << "One dimensional index: " << m_Nodes.at(i).back()->m_1DIndex << '\n';
				}
			}
			nodes.at(i).push_back(std::make_shared<Node>(i, j, gridDisplay));
			int randNum = rand() % 100;
			//std::cout << randNum << '\n';
			if (randNum < WALL_CHANCE) // 43% chance per node that it will be a wall.
			{
				nodes.at(i).back()->wall = true;
			}
			
			//std::cout << m_gridDisplay.getVertexCount() << '\n' << m_gridDisplay.getVertexCount() - 1 << '\n';
			nodes.at(i).back()->m_vtxIndex = (gridDisplay.getVertexCount() - 4);
			count++;
				//m_Nodes.at(i).back()->m_vArray[k] = 
				//m_Nodes.at(i).back()->m_vArray[k] = &m_gridDisplay[m_gridDisplay.getVertexCount() - 1];
				//m_Nodes.at(i).back()->m_vArray[k] = &m_gridDisplay[m_gridDisplay.getVertexCount() - 1];
		}
	}

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
		{
			nodes.at(i).at(j)->addNeighbors(nodes, rows, cols);
		}
	}
}

std::shared_ptr<Node>& Grid::getNode(const int& x, const int& y)
{
	return(nodes.at(x).at(y));
}

void Grid::setNodeVertices()
{
	std::cout << "Setting Node Vertices...\n\n";
	for (int i = 0; i < m_Rows; i++)
	{
		sf::Vertex vtx(sf::Vector2f(getNode(i, 0)->x * m_xOffSet, 0), sf::Color::Black);
		lines.append(vtx);

		vtx = sf::Vertex(sf::Vector2f(getNode(i, 0)->x * m_xOffSet, 684.0f), sf::Color::Black);
		lines.append(vtx);

		for (int j = 0; j < m_Cols; j++)
		{
			if (j == 0)
			{
				sf::Vertex vtx1(sf::Vector2f(1.0f, 1.0f), sf::Color::Black);//top line.
				lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 1.0f), sf::Color::Black);//top line
				lines.append(vtx1);

				vtx1 = sf::Vertex(sf::Vector2f(1.0f, 684.0f), sf::Color::Black);//bottom line.
				lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 684.0f), sf::Color::Black);//bottom line.
				lines.append(vtx1);


				vtx1 = sf::Vertex(sf::Vector2f(1.0f, 1.0f), sf::Color::Black);//left Line
				lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(1.0f, 684.0f), sf::Color::Black);//left line
				lines.append(vtx1);

				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 1.0f), sf::Color::Black);//right line
				lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 684.04f), sf::Color::Black);//right line
				lines.append(vtx1);
			}

			if (i == 0)
			{
				vtx = sf::Vertex(sf::Vector2f(1.0f, getNode(0, j)->y * m_yOffSet), sf::Color::Black);
				lines.append(vtx);
				
				vtx = sf::Vertex(sf::Vector2f(720.0f * 0.95f, getNode(0, j)->y * m_yOffSet), sf::Color::Black);
				lines.append(vtx);
			}

			auto node = getNode(i, j);
			float xpos = node->x * m_xOffSet;
			float ypos = node->y * m_yOffSet;

			node->m_vArray[node->m_vtxIndex + 2].position = sf::Vector2f(xpos + 0.5f, ypos + 0.5f);
			node->m_vArray[node->m_vtxIndex + 3].position = sf::Vector2f(xpos + m_xOffSet - 0.5f, ypos + 0.5f);
			node->m_vArray[node->m_vtxIndex + 0].position = sf::Vector2f(xpos + m_xOffSet - 0.5f, ypos + m_yOffSet - 0.5f);
			node->m_vArray[node->m_vtxIndex + 1].position = sf::Vector2f(xpos + 0.5f, ypos + m_yOffSet - 0.5f);
			node->setColor(sf::Color(245, 245, 255));
		}
	}
}