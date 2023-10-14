#include "pch.h"
#include "PathInfo.h"
#include "PathNode.h"


PathInfo::PathInfo()
	: mPathNodes{}
	, mGraph{}
	, mIdx(0)
{
	clear();
}

PathInfo::~PathInfo()
{
}

void PathInfo::AddPathNode(PathNode* const node)
{
	mPathNodes[mIdx] = node;
    node->SetIdx(mIdx);
	++mIdx;
}

void PathInfo::InsertEdge(const int from, const int to, const int weight)
{   
	mGraph[from][to] = weight;
}

void PathInfo::clear()
{
	memset(mGraph, -1, sizeof(mGraph));
	memset(mPathNodes, 0, sizeof(mPathNodes));
	mIdx = 0;
}

std::vector<PathNode*> PathInfo::Dijikstra(const int start, const int end)
{
    if (start == end)
    {
        return std::vector<PathNode*>();
    }

    const int MAX_DISTANCE = 99999999;

    bool visited[MAX_PATH_NODE] = {false,};
    int distance[MAX_PATH_NODE] = {0, };
    int parent[MAX_PATH_NODE] = {0, };

    for (int i = 0; i < MAX_PATH_NODE; i++)
    {		
		distance[i] = MAX_DISTANCE;		
	}

    distance[start] = 0;
    parent[start] = start;

    while (true)
    {        
        int closet = MAX_DISTANCE;
        int now = -1;

        for (int i = 0; i <= mIdx; i++)
        {            
            if (visited[i])
                continue;            
            if (distance[i] == MAX_DISTANCE || distance[i] >= closet)
                continue;
            
            closet = distance[i];
            now = i;
        }

        if (now == -1)
            break;

        
        visited[now] = true;
        
        for (int next = 0; next <= mIdx; next++)
        {            
            if (mGraph[now][next] == -1)
                continue;            
            if (visited[next])
                continue;
            
            int nextDist = distance[now] + mGraph[now][next];            
            if (nextDist < distance[next])
            {
                distance[next] = nextDist;
                parent[next] = now;
            }
        }
    }

    std::vector<PathNode*> path;    
    
    int next = end;
        
    while (next != start)
    {        
        path.push_back(mPathNodes[next]);
		next = parent[next];
    }    

   /* std::reverse(path.begin(), path.end());

    std::queue<PathNode*> q;
    for (auto node : path)  
    {
		q.push(node);
	}*/

	return path;
}

