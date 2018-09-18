#include "..\include\BreadthFirstSearch.h"


void BreadthFirstSearch::init(bool custom)
{

	m_start->explored = true;
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
	m_queue.push(m_start);
	return(true);
}

void BreadthFirstSearch::update()
{
	std::unique_ptr<Node> temp = m_queue.front;
	if (temp == m_end)
	{
		std:: << "*DBG We're done!\n";
		return;
	}
	for (auto neighbit = temp->neighbors.begin(); neighbit != temp->neighbors.end(); neighbit++)
	{
		if (!(*neighbit)->explored)
		{
			(*neighbit)->explored = true;
		}
		m_queue.push;
	}
}

void BreadthFirstSearch::render()
{

}

bool BreadthFirstSearch::isDone() const
{
	return false;
}

bool BreadthFirstSearch::isSolved() const
{
	return false;
}

void BreadthFirstSearch::setCustom(const int array[6])
{
}

void BreadthFirstSearch::setHeuristicFlag(bool newFlag)
{
}
