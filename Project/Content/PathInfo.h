#pragma once

class PathNode;

#define MAX_PATH_NODE 256

class PathInfo
{

public:
	PathInfo();
	virtual ~PathInfo();
	PathInfo(const PathInfo&) = delete;
	PathInfo& operator=(const PathInfo&) = delete;

	void AddPathNode(PathNode* const node);
	void InsertEdge(const int from, const int to, const int weight);
	void clear();

	std::queue<PathNode*> Dijikstra(const int start, const int end);


private:
	PathNode* mPathNodes[MAX_PATH_NODE];
	int mGraph[MAX_PATH_NODE][MAX_PATH_NODE];
	int mIdx;
};
