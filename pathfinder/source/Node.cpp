#include "..\include\Node.h"

Node::Node(int& newx, int& newy)
	: x(float(newx)), y(float(newy)), f(std::numeric_limits<float>::infinity()), g(std::numeric_limits<float>::infinity()), h(0), wall(false)
{
	//previous = std::make_shared<Node>();
	previous = nullptr;
	square.setFillColor(sf::Color::Transparent);
	
	auto randNum = rand() % 10;
	if (randNum < 4) // 40% chance per node that it will be a wall.
	{
		wall = true;
		
		square.setFillColor(sf::Color::Black);
	}
}

Node::~Node()
{

}

void Node::addNeighbors(std::vector<std::vector<std::shared_ptr<Node>>>& nodes, const int& ROWS, const int& COLS)
{
	float x = this->x;
	float y = this->y;

	if (x < COLS - 1) {
		neighbors.push_back((nodes.at((x + 1.0f)).at(y)));
	}
	if (x > 0) {
		neighbors.push_back(nodes.at(x - 1.0f).at(y));
	}
	if (y < ROWS - 1) {
		neighbors.push_back(nodes.at(x).at(y + 1.0f));
	}
	if (y > 0) {
		neighbors.push_back(nodes.at(x).at(y - 1.0f));
	}
	if (x > 0 && y > 0)
	{
		neighbors.push_back(nodes.at(x - 1.0f).at(y - 1.0f));
	}
	if (x < COLS - 1 && y > 0)
	{
		neighbors.push_back(nodes.at(x + 1.0f).at(y - 1.0f));
	}
	if (x > 0.0f && y < ROWS - 1.0f)
	{
		neighbors.push_back(nodes.at(x - 1.0f).at(y + 1.0f));
	}
	if (x < COLS - 1.0f && y < ROWS - 1.0f)
	{
		neighbors.push_back(nodes.at(x + 1.0f).at(y + 1.0f));
	}
}