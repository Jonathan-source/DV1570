#pragma once

struct Node
{
	float f = FLT_MAX, g = FLT_MAX, h = FLT_MAX;
	Vector3 position{};
	std::vector<Node*> connections;
	Node* parent = nullptr;
	bool reachable = true;
	void ResetFGH()
	{
		f = FLT_MAX, g = FLT_MAX, h = FLT_MAX;
	}
};

class PathFinderManager
{
public:
	PathFinderManager() = delete;
	static void UpdateConnections(std::vector<std::vector<Node*>>& grid);
	static std::vector<std::vector<Node*>> InitializeGrid(int size, int spacing);
	static std::vector<Node*> AStar(Node* startNode, Node* goalNode);
	static bool IsInVector(const std::vector<Node*>& vector, Node* node);
	static std::vector<Node*> GetNeighbors(const Node* node, const std::vector<std::vector<Node*>>& grid);
	static Node* GetClosestNode(Vector3 position, const std::vector<std::vector<Node*>>& grid);

};

