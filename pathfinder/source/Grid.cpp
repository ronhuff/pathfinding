#include "..\include\Grid.h"
Grid::Grid()
	:m_gridDisplay(sf::Quads, 0), m_lines(sf::Lines, 0)
{
	//for (int k = 0; k < 4; k++)
	//{
	//	//add vertices
	//	sf::Vertex temp(sf::Vector2f(0.0f, 0.0f), sf::Color::White);
	//	m_gridDisplay.append(temp);
	//}
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
	int count = 0;
	for (int i = 0; i < m_Cols; i++)
	{
		std::vector<std::shared_ptr<Node>> tempVec;
		m_Nodes.push_back(tempVec);
		for (int j = 0; j < m_Rows; j++)
		{

			
			for (int k = 0; k < 4; k++)
			{
				//add vertices
				sf::Vertex temp(sf::Vector2f(0.0f, 0.0f), sf::Color::White);
				m_gridDisplay.append(temp);
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
			m_Nodes.at(i).push_back(std::make_shared<Node>(i, j, m_gridDisplay));
			//std::cout << m_gridDisplay.getVertexCount() << '\n' << m_gridDisplay.getVertexCount() - 1 << '\n';
			m_Nodes.at(i).back()->m_vtxIndex = (m_gridDisplay.getVertexCount() - 4);
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
		
		sf::Vertex vtx(sf::Vector2f(getNode(i, 0)->x * m_xOffSet, 0), sf::Color::Black);
		m_lines.append(vtx);

		vtx = sf::Vertex(sf::Vector2f(getNode(i, 0)->x * m_xOffSet, 684.0f), sf::Color::Black);
		
		m_lines.append(vtx);

		for (int j = 0; j < m_Cols; j++)
		{
			if (j == 0)
			{
				sf::Vertex vtx1(sf::Vector2f(1.0f, 1.0f), sf::Color::Black);//top line.
				m_lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 1.0f), sf::Color::Black);//top line
				m_lines.append(vtx1);

				vtx1 = sf::Vertex(sf::Vector2f(1.0f, 684.0f), sf::Color::Black);//bottom line.
				m_lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 684.0f), sf::Color::Black);//bottom line.
				m_lines.append(vtx1);


				vtx1 = sf::Vertex(sf::Vector2f(1.0f, 1.0f), sf::Color::Black);//left Line
				m_lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(1.0f, 684.0f), sf::Color::Black);//left line
				m_lines.append(vtx1);

				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 1.0f), sf::Color::Black);//right line
				m_lines.append(vtx1);
				vtx1 = sf::Vertex(sf::Vector2f(684.0f, 684.04), sf::Color::Black);//right line
				m_lines.append(vtx1);
			}

			if (i == 0)
			{
				vtx = sf::Vertex(sf::Vector2f(1.0f, getNode(0, j)->y * m_yOffSet), sf::Color::Black);
				m_lines.append(vtx);
				vtx = sf::Vertex(sf::Vector2f(720.0f * 0.95f, getNode(0, j)->y * m_yOffSet), sf::Color::Black);

				m_lines.append(vtx);

			}


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
				//node.
				//m_gridDisplay[index + k] = sf::Vertex(0.0f,0.0f);
				//sf::Vertex vtx(sf::Vector2f(0.0f, 0.0f));
				//m_gridDisplay.append(vtx);
				//node->m_vArray[k] = &m_gridDisplay[index + k];
			}



			//std::cout << node->m_vArray[node->m_1DIndex].position.y << '\n';
			//std::cout << m_gridDisplay[0].position.y << '\n';

			node->m_vArray[node->m_vtxIndex + 2].position = sf::Vector2f(xpos + 0.5f, ypos + 0.5f);
			node->m_vArray[node->m_vtxIndex + 3].position = sf::Vector2f(xpos + m_xOffSet - 0.5f, ypos + 0.5f);
			node->m_vArray[node->m_vtxIndex + 0].position = sf::Vector2f(xpos + m_xOffSet - 0.5f, ypos + m_yOffSet - 0.5f);
			node->m_vArray[node->m_vtxIndex + 1].position = sf::Vector2f(xpos + 0.5f, ypos + m_yOffSet - 0.5f);
			node->setColor(sf::Color::White);
		}
	}
}

void Grid::draw(sf::RenderWindow& window) //draws the current state of the grid.
{
	for (int i = 0; i < m_Cols; i++)
	{
		for (int j = 0; j < m_Rows; j++)
		{
			//window.draw(getNode(i, j)->square);
		}
	}
}
