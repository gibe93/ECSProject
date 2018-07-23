#pragma once
#include <vector>
#include <functional>
#include <set>
#include <iostream>


struct Coord
{
public:
	int x, y;

	bool operator == (const Coord& coordinates_)
	{
		return (x == coordinates_.x && y == coordinates_.y);
	}
	friend Coord operator + (const Coord& left_, const Coord& right_)
	{
		return{ left_.x + right_.x, left_.y + right_.y };
	}
};

using uint = unsigned int;
using HeuristicFunction = std::function<uint(Coord, Coord)>;
using CoordinateList = std::vector<Coord>;

class Node
{
public:
	uint G, H;
	Coord coordinates;
	Node *parent;

	Node(Coord coord_, Node *parent_ = nullptr);
	uint getScore();
};

using NodeSet = std::set<Node*>;

class Generator
{
	bool detectCollision(Coord coordinates_);
	Node* findNodeOnList(NodeSet& nodes_, Coord coordinates_);
	void releaseNodes(NodeSet& nodes_);

public:
	Generator();
	void setWorldSize(Coord worldSize_);
	void setDiagonalMovement(bool enable_);
	void setHeuristic(HeuristicFunction heuristic_);
	CoordinateList findPath(Coord source_, Coord target_);
	void addCollision(Coord coordinates_);
	void removeCollision(Coord coordinates_);
	void clearCollisions();

private:
	HeuristicFunction heuristic;
	CoordinateList direction, walls;
	Coord worldSize;
	uint directions;
};

class Heuristic
{
	static Coord getDelta(Coord source_, Coord target_);

public:
	static uint manhattan(Coord source_, Coord target_);
	static uint euclidean(Coord source_, Coord target_);
	static uint octagonal(Coord source_, Coord target_);
};


