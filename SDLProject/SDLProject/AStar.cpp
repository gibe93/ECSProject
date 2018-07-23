#include "AStar.h"
#include <algorithm>
#include "Vector2D.h"

using namespace std::placeholders;

Node::Node(Coord coordinates_, Node *parent_)
{
	parent = parent_;
	coordinates = coordinates_;
	G = H = 0;
}

uint Node::getScore()
{
	return G + H;
}

Generator::Generator()
{
	setDiagonalMovement(false);
	setHeuristic(&Heuristic::manhattan);
	direction = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

void Generator::setWorldSize(Coord worldSize_)
{
	worldSize = worldSize_;
}

void Generator::setDiagonalMovement(bool enable_)
{
	directions = (enable_ ? 8 : 4);
}

void Generator::setHeuristic(HeuristicFunction heuristic_)
{
	heuristic = std::bind(heuristic_, _1, _2);
}

void Generator::addCollision(Coord coordinates_)
{
	walls.push_back(coordinates_);
}

void Generator::removeCollision(Coord coordinates_)
{
	auto it = std::find(walls.begin(), walls.end(), coordinates_);
	if (it != walls.end()) {
		walls.erase(it);
	}
}

void Generator::clearCollisions()
{
	walls.clear();
}

CoordinateList Generator::findPath(Coord source_, Coord target_)
{
	Node *current = nullptr;
	NodeSet openSet, closedSet;
	openSet.insert(new Node(source_));
	if(std::find(walls.begin(), walls.end(), target_) != walls.end())
	{
		std::cout << "wrong location" << std::endl;
	}
	else {
		while (!openSet.empty()) {
			current = *openSet.begin();
			for (auto node : openSet) {
				if (node->getScore() <= current->getScore()) {
					current = node;
				}
			}

			if (current->coordinates == target_) {
				break;
			}

			closedSet.insert(current);
			openSet.erase(std::find(openSet.begin(), openSet.end(), current));

			for (uint i = 0; i < directions; ++i) {
				Coord newCoordinates(current->coordinates + direction[i]);
				if (detectCollision(newCoordinates) ||
					findNodeOnList(closedSet, newCoordinates)) {
					continue;
				}

				uint totalCost = current->G + ((i < 4) ? 10 : 14);

				Node *successor = findNodeOnList(openSet, newCoordinates);
				if (successor == nullptr) {
					successor = new Node(newCoordinates, current);
					successor->G = totalCost;
					successor->H = heuristic(successor->coordinates, target_);
					openSet.insert(successor);
				}
				else if (totalCost < successor->G) {
					successor->parent = current;
					successor->G = totalCost;
				}
			}
		}
	}
	CoordinateList path;
	while (current != nullptr) {
		path.push_back(current->coordinates);
		current = current->parent;
	}

	releaseNodes(openSet);
	releaseNodes(closedSet);

	return path;
}

Node* Generator::findNodeOnList(NodeSet& nodes_, Coord coordinates_)
{
	for (auto node : nodes_) {
		if (node->coordinates == coordinates_) {
			return node;
		}
	}
	return nullptr;
}

void Generator::releaseNodes(NodeSet& nodes_)
{
	for (auto it = nodes_.begin(); it != nodes_.end();) {
		delete *it;
		it = nodes_.erase(it);
	}
}

bool Generator::detectCollision(Coord coordinates_)
{
	if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
		coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
		std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
		return true;
	}
	return false;
}

Coord Heuristic::getDelta(Coord source_, Coord target_)
{
	return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}

uint Heuristic::manhattan(Coord source_, Coord target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return static_cast<uint>(10 * (delta.x + delta.y));
}

uint Heuristic::euclidean(Coord source_, Coord target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

uint Heuristic::octagonal(Coord source_, Coord target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}