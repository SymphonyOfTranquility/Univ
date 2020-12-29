#ifndef _GRAPH_H_USED
#define _GRAPH_H_USED


#include "Polygon.h"
#include "Vector_overload.h"
#include "Random.h"

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::pair;


template<typename T>
struct Tvertex{
	int ind;
	vector<pair<Tvertex *, T> > neighbours;
	Tvertex(int index);
};

template<typename T>
Tvertex<T>::Tvertex(int index)
{
	ind = index;
}


template<typename T>
class Graph
{
protected:
	vector<Tvertex<T> *> vertex;
	int length;
public:
	Graph();
	Graph(int n);
	void add_vertex(vector<pair<int, T> > neigb);
	void add_edge(int index1, int index2, T value);
	void output();
	void random();
	int size_gr();
	vector<Tvertex<T> *> vertexes();
	~Graph();
};

template<typename T>
Graph<T>::Graph()
{
	vertex.clear();
	length = 0;
}

template<typename T>
Graph<T>::Graph(int n)
{
	vertex.clear();
	length = n;
	for (int i = 0; i < n; ++i) {
		Tvertex<T> *cur = new Tvertex<T>(i);
		vertex.push_back(cur);
	}
}

template<typename T>
void Graph<T>::add_vertex(vector<pair<int, T> > neighb)
{
	Tvertex<T> *new_vertex = new Tvertex<T>(length);
	++length;
	for (size_t i = 0; i < neighb.size(); ++i)	
	{
		new_vertex->neighbours.push_back({ vertex[neighb[i].first], neighb[i].second });
		vertex[neighb[i].first]->neighbours.push_back({ new_vertex, neighb[i].second });
	}
	vertex.push_back(new_vertex);
}

template<typename T>
void Graph<T>::add_edge(int index1, int index2, T value) 
{
	vector<pair<Tvertex<T> *,T> > vert1 = vertex[index1]->neighbours;
	bool flag = true;
	for (size_t i = 0;i < vert1.size(); ++i)
		if (vert1[i].first->ind == index2)
		{
			flag = false;
			break;
		}
	if (flag)
	{
		if (index1 != index2) {
			vertex[index1]->neighbours.push_back({ vertex[index2], value });
			vertex[index2]->neighbours.push_back({ vertex[index1], value });
		}
		else
			vertex[index1]->neighbours.push_back({ vertex[index2], value });
	}
}

template<typename T>
void Graph<T>::output()
{
	if (length == 0) {
		cout << "Graph is empty!!! Fill it, please.)";
		return;
	}
	cout << "Size of graph: " << length << "\n";
	for (int i = 0; i < length; ++i)
	{
		cout << "Vertex #" << i << ", neighbours: \n";
		for (size_t j = 0; j < vertex[i]->neighbours.size(); ++j) {
			cout << "	{ #" << vertex[i]->neighbours[j].first->ind << ';' << vertex[i]->neighbours[j].second << " }\n";
		}
		cout << '\n';
	}
}

template<typename T>
void Graph<T>::random()
{
	int temp_size = rand() % 10 + 1;
	length = 0;
	vertex.clear();
	vector<pair<int, T> > temp;
	temp.clear();
	add_vertex(temp);
	for (int i = 1; i < temp_size; ++i)
	{
		add_vertex(temp);
		for (int j = 0; j < i; ++j) {
			if (rand() % 2 == 0)
			{
				T *value = new T;
				add_edge(i, j, getrandom(*value));
				delete value;
			}
		}
	}
}

template<typename T>
int Graph<T>::size_gr()
{
	return length;
}

template<typename T>
vector<Tvertex<T> *> Graph<T>::vertexes()
{
	vector<Tvertex<T> *> temp;
	for (size_t i = 0;i < vertex.size(); ++i)
	{
		Tvertex<T> *cur = new Tvertex<T>(i);
		for (size_t j = 0; j < vertex[i]->neighbours.size(); ++j)
		{
			size_t to = vertex[i]->neighbours[j].first->ind;
			T val = vertex[i]->neighbours[j].second;
			if (to < i)
			{
				cur->neighbours.push_back({ temp[to],val });
				temp[to]->neighbours.push_back({ cur,val });
			}
			else if (to == i)
				cur->neighbours.push_back({ cur,val });

		}
		temp.push_back(cur);
	}
	return temp;
}

template<typename T>
Graph<T>::~Graph()
{
	for (size_t i = 0; i < vertex.size(); ++i)
		delete vertex[i];
	vertex.clear();
}

#endif