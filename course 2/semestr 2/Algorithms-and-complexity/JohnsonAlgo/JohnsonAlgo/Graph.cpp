#include "Graph.h"

int Graph::createValueOfEdge(shared_ptr<TVertex> &a, shared_ptr<TVertex> &b)
{
	if (rand()%2 == 0)
		return a->book->getRating() - b->book->getRating() - rand()%20;
	else
		return a->book->getRating() - b->book->getRating() + rand() % 20;

}

void Graph::removeLast()
{
	for (int i = edges.size() - 1; i > 0; --i)
	{
		if (vertexes[vertexes.size() - 1] == edges[i]->from)
			edges.pop_back();
		else
			break;
	}
	vertexes.pop_back();
}

bool Graph::algoBellmanFord(vector<int>& dist)
{
	int src = vertexes.size() - 1;
	dist.resize(vertexes.size());
	dist[src] = 0;
	for (int i = 1; i < vertexes.size(); ++i)
	{
		for (int j = 0; j < edges.size(); ++j) 
		{
			int from = edges[j]->from->id;
			int to = edges[j]->to->id;
			int value = edges[j]->value;
			dist[to] = min(dist[to], dist[from] + value);
		}
	}
	for (int i = 0; i < edges.size(); ++i)
	{
		int from = edges[i]->from->id;
		int to = edges[i]->to->id;
		int value = edges[i]->value;
		if (dist[to] > dist[from] + value && dist[to] != inf)
			return false;
	}
	return true;
}

void Graph::algoDijkstra(int start)
{
	distance[start][start] = 0;
	shared_ptr<FibonacciHeap> fibHeap = make_shared<FibonacciHeap>();
	fibHeap->push({ 0, start });
	while (!fibHeap->empty())
	{
		int v = fibHeap->top().second, curDist = fibHeap->top().first;
		fibHeap->pop();
		if (curDist > distance[start][v])
			continue;
		for (int i = 0; i < vertexes[v]->neighbours.size(); ++i)
		{
			int to = vertexes[v]->neighbours[i].first->id,
				len = vertexes[v]->neighbours[i].second;
			if (distance[start][v] + len < distance[start][to])
			{
				distance[start][to] = distance[start][v] + len;
				fibHeap->push({ distance[start][to], to });
			}
		}
	}

}

Graph::Graph()
{

}

void Graph::build(vector<shared_ptr<Book> > &library)
{
	shared_ptr<TVertex> tempV;
	for (int i = 0; i < library.size(); ++i)
	{
		tempV = make_shared<TVertex>(library[i]);
		tempV->id = vertexes.size();
		for (int j = 0; j < vertexes.size(); ++j)
		{
			if (rand() % 2 == 0) 
			{
				int value = createValueOfEdge(tempV, vertexes[j]);
				tempV->neighbours.push_back({ vertexes[j],  value});
				edges.push_back(make_shared<TEdge>(tempV, vertexes[j], value, int (tempV->neighbours.size() - 1)));
			}
			else if (rand() % 2 == 1) 
			{
				int value = createValueOfEdge(vertexes[j], tempV);
				vertexes[j]->neighbours.push_back({ tempV,  value });
				edges.push_back(make_shared<TEdge>(vertexes[j], tempV, value, int (vertexes[j]->neighbours.size() - 1)));
			}
		}
		vertexes.push_back(tempV);
		tempV.reset();
	}
}


bool Graph::johnsonAlgo()
{
	shared_ptr<TVertex> lastNode = make_shared<TVertex>(nullptr);
	lastNode->id = vertexes.size();
	for (int i = 0; i < vertexes.size(); ++i)
	{
		lastNode->neighbours.push_back({ vertexes[i],0 });
		edges.push_back(make_shared<TEdge>(lastNode, vertexes[i], 0, int (lastNode->neighbours.size() - 1)));
	}
	vertexes.push_back(lastNode);
	vector<int> h;
	if (!algoBellmanFord(h)) 
	{
		removeLast();
		return false;
	}
	cout << "-------------------------------BellmanFord distances------------------------------\n";
	for (int i = 0; i < h.size(); ++i)
		cout << h[i] << ' ';
	cout << '\n';
	
	for (int i = 0; i < edges.size(); ++i) 
	{
		edges[i]->value += h[edges[i]->from->id] - h[edges[i]->to->id]; 
		int from = edges[i]->from->id;
		int pos = edges[i]->pos;
		vertexes[from]->neighbours[pos].second = edges[i]->value;
	}
	outputFile("outBellman.txt");
	cout << "\n\nGRAPH BEFORE DIJKSTRA\n";
	show();

	distance.resize(vertexes.size() - 1, vector<int>(vertexes.size() - 1, inf));
	for (int i = 0; i < vertexes.size() - 1; ++i) 
	{
		algoDijkstra(i);
		for (int j = 0; j < vertexes.size() - 1; ++j)
		{
			if (distance[i][j] != inf)
				distance[i][j] += h[j] - h[i];
		}
	}

	for (int i = 0; i < edges.size(); ++i)
	{
		edges[i]->value += h[edges[i]->to->id] - h[edges[i]->from->id];
		int from = edges[i]->from->id;
		int pos = edges[i]->pos;
		vertexes[from]->neighbours[pos].second = edges[i]->value;
	}
	removeLast();
	return true;
}

void Graph::show()
{
	showVertexes();
	showEdges();
}

void Graph::showEdges()
{
	cout << "------------------------------------------EDGES------------------------------------------\n";
	for (int i = 0; i < edges.size(); ++i)
		cout << edges[i]->from->id << ' ' << edges[i]->to->id << ' ' << edges[i]->value << '\n';
}

void Graph::showVertexes()
{
	cout << "------------------------------------------VERTEXES------------------------------------------\n";
	for (int i = 0; i < vertexes.size(); ++i)
	{
		if (vertexes[i]->book)
		{
			cout.width(2);
			cout << i << ":";
			cout.width(10);
			cout << vertexes[i]->book->getRating() << " ::: ";
		}
		else 
		{
			cout.width(2);
			cout << i << ":";
			cout.width(10);
			cout << "nullptr" << " ::: ";
		}
		for (int j = 0; j < vertexes[i]->neighbours.size(); ++j)
			cout << "{ " << vertexes[i]->neighbours[j].first->id << ", " << vertexes[i]->neighbours[j].second << " }";
		cout << '\n';
	}
}


void Graph::showDistances()
{
	if (distance.size() != 0)
	{
		cout << "------------------------------------------DISTANCES------------------------------------------\n";
		for (int i = 0; i < distance.size(); ++i)
		{
			for (int j = 0; j < distance[i].size(); ++j)
			{
				cout.width(12);
				if (distance[i][j] != inf)
					cout << distance[i][j];
				else
					cout << "inf";
			}
			cout << '\n';
		}
	}
}

void Graph::outputFile(string s)
{
	ofstream fout(s);
	for (int i = 0; i < edges.size(); ++i)
	{
		int from = edges[i]->from->id;
		if (vertexes[from]->book == nullptr)
			break;
		int to = edges[i]->to->id;
		int value = edges[i]->value;
		fout << "\t" << from << " -> " << to << " [ label = \"" << value << "\" ];\n";
	}
	fout.close();
	
}

Graph::~Graph()
{
}
