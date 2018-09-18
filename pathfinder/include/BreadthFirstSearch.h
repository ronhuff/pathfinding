#pragma once

#include <queue>
#include <memory>

#include "Search.h"
#include "Grid.h"

class BreadthFirstSearch : public Search
{
private:

	std::shared_ptr<Node> m_start;
	std::shared_ptr<Node> m_end;

	std::queue<std::shared_ptr<Node>> m_queue;

public:
	BreadthFirstSearch() = default;
	~BreadthFirstSearch() = default;

	virtual void init(bool custom);

	virtual void update();

	virtual void render();




	virtual bool isDone() const;
	virtual bool isSolved() const;

	virtual void setCustom(const int array[6]);
	virtual void setHeuristicFlag(bool newFlag);

private:

	Grid m_grid;
};