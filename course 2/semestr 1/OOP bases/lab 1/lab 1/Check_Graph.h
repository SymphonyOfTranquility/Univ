#ifndef _CHECK_GRAPH_H_USED
#define _CHECK_GRAPH_H_USED

#include "Triangle.h"
#include "Tetragon.h"
#include "Pentagon.h"
#include "Graph.h"
#include "Tree.h"
#include "Vector_overload.h"

#include <iostream>
#include <time.h>
#include <random>


using std::cin;
using std::cout;

template<typename T>
void check(Graph<T> &gr)
{
	cout << "You will work with Classes Graph and Tree.\n";
	cout << "0 - exit\n1 - add vertex\n2 - add edge\n3 - size of graph\n4 - output graph\n5 - find spanning tree\n";
	cout << "6 - random filling\n";
	int x;
	srand(time(NULL));
	while (true)
	{

		cin >> x;
		if (x == 0)
			break;
		else if (x == 1)
		{
			cout << "There are " << gr.size_gr() << " vertexes. Input with which vertexes it has to be connected.\n";
			cout << "First is number of vertex, next is data, end of input is \"-1\":\n";
			int v;
			vector<pair<int, T> > neighbours;
			while (cin >> v)
			{
				if (v == -1)
					break;
				if (v >= gr.size_gr() || v < 0)
				{
					cout << "It's non existing vertex. Input other data!\n";
					continue;
				}
				T cur;
				cin >> cur;
				neighbours.push_back({ v,cur });
			}
			gr.add_vertex(neighbours);
		}
		else if (x == 2)
		{
			if (gr.size_gr() == 0)
			{
				cout << "Sorry Graph has less than 2 vertexes. I can't add an edge :)\n";
				continue;
			}
			cout << "Input vertexes that you want to connect. If they were connected before this operation, nothing would happen\n";
			int x1, x2;
			while (cin >> x1 >> x2)
			{
				if (x1 >= gr.size_gr() || x1 < 0 || x2 < 0 || x2 >= gr.size_gr())
				{
					cout << "This vertexes don't exist. Input other.\n";
					continue;
				}
				break;
			}
			T val;
			cin >> val;
			gr.add_edge(x1, x2, val);
		}
		else if (x == 3)
		{
			cout << "Size is " << gr.size_gr();
		}
		else if (x == 4)
		{
			gr.output();
		}
		else if (x == 5)
		{
			Tree<T> tree;
			if (!tree.find_spanning_tree(gr))
				cout << "There are several trees\n";
			else
				cout << "Yeah we found a tree\n";
			tree.output();
		}
		else if (x == 6)
		{
			gr.random();
			gr.output();
		}

		cout << "\n --------------------------------------------------\n\n";
	}
}
#endif