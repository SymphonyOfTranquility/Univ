#pragma once
#include "Entity.h"
#include "HashFunctions.h"

#include <algorithm>
#include <iostream>

using namespace std;

const int inf = (int)(1e9 + 7);

class Graph
{
	struct TEdge
	{
		int to, value;
		TEdge(int getTo, int getValue) 
		{
			to = getTo;
			value = getValue;
		}
	};
	vector<shared_ptr<Entity> > entities;
	vector<vector<TEdge> > graph;
	vector<int> gValues;
	int ssid;

	int createSsid();
	bool dfsCheck(int v, int parent, vector<bool> &used);
	void dfsCounter(int v, int curGValue);
	void createGraph();

public:
	Graph(vector<shared_ptr<Entity> > elements);
	vector<int> getGValues();
	int getSsid();
	~Graph();
};

