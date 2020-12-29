#pragma once
#include "Book.h"
#include "FibonacciHeap.h"

struct TVertex
{
	int id;
	shared_ptr<Book> book;
	vector<pair<shared_ptr<TVertex>, int> > neighbours;

	TVertex(shared_ptr<Book> curBook)
	{
		book = curBook;
		neighbours.clear();
	}
};

struct TEdge
{
	shared_ptr<TVertex> from, to;
	int value, pos;
	TEdge(shared_ptr<TVertex> from, shared_ptr<TVertex> to, int value, int pos) :from(from), to(to), value(value), pos(pos)
	{}
};

class Graph
{
	const int inf = 1e+9 + 7;
	vector<shared_ptr<TVertex> > vertexes;
	vector<shared_ptr<TEdge> > edges;
	vector<vector<int> > distance;
	int createValueOfEdge(shared_ptr<TVertex> &a, shared_ptr<TVertex> &b);

	void removeLast();
	bool algoBellmanFord(vector<int> &h);
	void algoDijkstra(int start);
public:
	Graph();
	void build(vector<shared_ptr<Book> > &library);
	bool johnsonAlgo();
	void show();
	void showEdges();
	void showVertexes();
	void showDistances();
	void outputFile(string s);
	~Graph();
};

