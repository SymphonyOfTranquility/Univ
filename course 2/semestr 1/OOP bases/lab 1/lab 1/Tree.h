#ifndef _TREE_H_USED
#define _TREE_H_USED
#include "Graph.h"

template<typename T>
class Tree: public Graph<T>
{
private:
	using Graph<T>::length;
	using Graph<T>::vertex;
	int root;
	static const int NMAX = 100001;
	void dfs(int v,int p, vector<Tvertex<T> *> &vert, bool used[]);
public:
	Tree();
	Tree(int n);
	using Graph<T>::add_edge;
	using Graph<T>::add_vertex;
	using Graph<T>::output;
	int find_spanning_tree(Graph<T> &graph);
	~Tree();
};


template<typename T>
void Tree<T>::dfs(int v, int p, vector<Tvertex<T> *> &vert, bool used[])
{
	used[v] = true;
	for (size_t i = 0; i < vert[v]->neighbours.size(); ++i)
	{
		int to = vert[v]->neighbours[i].first->ind;
		T cur = vert[v]->neighbours[i].second;
		if (!used[to]) {
			add_edge(v, to, cur);
			dfs(to, v, vert, used);
		}
	}
}

template<typename T>
Tree<T>::Tree()
{
	root = 0;
	length = 0;
}

template<typename T>
Tree<T>::Tree(int n)
{
	root = 0;
	length = n;
	for (int i = 0; i < n; ++i) {
		Tvertex<T> *cur = new Tvertex<T>(i);
		vertex.push_back(cur);
	}
}

template<typename T>
int Tree<T>::find_spanning_tree(Graph<T> &graph)
{
	vector<Tvertex<T> *> vert = graph.vertexes();
	length = graph.size_gr();
	vertex.clear();
	for (int i = 0; i < length; ++i) {
		Tvertex<T> *cur = new Tvertex<T>(i);
		vertex.push_back(cur);
	}
	bool used[NMAX];
	for (int i = 0; i < length; ++i)
		used[i] = false;
	int counter = 0;
	for (int i = 0; i < length; ++i) {
		if (!used[i]) {
			dfs(i, -1, vert, used);
			++counter;
		}
	}
	if (counter > 1)
		return 0;
	else
		return 1;
}
template<typename T>
Tree<T>::~Tree()
{
	for (size_t i = 0; i < vertex.size(); ++i)
		delete vertex[i];
	vertex.clear();
}

#endif