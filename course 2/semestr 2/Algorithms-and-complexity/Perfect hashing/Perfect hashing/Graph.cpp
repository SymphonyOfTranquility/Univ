#include "Graph.h"


int Graph::createSsid()
{
	long long val;
	if (entities.size() > 3)
		val = long long(double(log(2 * (double)entities.size()) / log(2)*(double)entities.size()));
	else
		val = (long long)exp(1);
	val += rand() % val;
	val *= (long long)(double (log(val + rand())/log(2)));
	int temp = 50;
	while (val / entities.size() >= temp)
		val /= 2;
	return (int)val;
}

bool Graph::dfsCheck(int v, int parent, vector<bool> &used)
{
	used[v] = true;
	for (int i = 0; i < (int)graph[v].size(); ++i) 
	{
		int vTo = graph[v][i].to;
		if (vTo == parent)
			continue;

		if (used[vTo])
			return false;

		dfsCheck(vTo, v, used);
	}
	return true;
}

void Graph::dfsCounter(int v, int curGValue)
{
	gValues[v] = curGValue;
	for (int i = 0; i < (int)graph[v].size(); ++i)
	{
		int vTo = graph[v][i].to, value = graph[v][i].value;
		if (gValues[vTo] == -inf)
			dfsCounter(vTo, value - curGValue);
	}
}

void Graph::createGraph()
{
	int cycle = -1;
	vector<bool> used;
	while (cycle == -1) 
	{
		cycle = 0;
		ssid = createSsid();
		int hash1, hash2;
		graph.clear();
		graph.resize(ssid);
		for (int i = 0; i < (int)entities.size(); ++i)
		{
			hash1 = firstHash(entities[i]->getName(), ssid);
			hash2 = secondHash(entities[i]->getName(), ssid);
			graph[hash1].push_back(TEdge (hash2, i) );
			graph[hash2].push_back(TEdge (hash1, i));
		}
		used.resize(ssid, false);
		for (int i = 0; i < ssid && !cycle; ++i)
		{
			if (!used[i])
			{
				if (!dfsCheck(i, -1, used))
				{
					cycle = -1;
					++ssid;
					break;
				}
			}
		}
	}
	gValues.resize(ssid, -inf);
	for (int i = 0; i < ssid; ++i)
	{
		if (gValues[i] == -inf)
			dfsCounter(i, 0);
	}
}

Graph::Graph(vector<shared_ptr<Entity> > elements)
{
	entities = elements;
	createGraph();
}

vector<int> Graph::getGValues()
{
	return gValues;
}

int Graph::getSsid()
{
	return ssid;
}

Graph::~Graph()
{
}
