#pragma once
#include "Book.h"
#include <algorithm>
#include <iomanip>

struct TNode
{
	shared_ptr<TNode> parent, leftSon, rightSon;
	shared_ptr<Book> book;
	float weight;
	TNode(shared_ptr<Book> curBook)
	{
		parent = leftSon = rightSon = nullptr;
		book = curBook;
		weight = 0;
	}
};


class OptimalBSTree
{
	const int inf = 1000000;
	shared_ptr<TNode> root;
	vector<float> prefWeightList;
	vector<vector<float> > weights;
	vector<vector<short int> > roots;

	int compareText(const string a, const string b);
	int compareBooks(const shared_ptr<TNode> a, const shared_ptr<TNode> b);
	int checkPart(const string a, const string b);

	void restoreHeap(vector<shared_ptr<TNode> > &mas, int father, int countTree);
	void mySort(vector<shared_ptr<TNode> > &mas);
	
	void buildTree(vector<shared_ptr<TNode> > &mas, shared_ptr<TNode> vertex, int i, int j);
	void showMatrixRootsAndWeights();
	void buildRootsAndWeights(vector<shared_ptr<TNode> > &nodeList);

	shared_ptr<TNode> dfs(shared_ptr<TNode> v, const string &key);
	void showDfs(shared_ptr<TNode> v, int numberOfTabs);

public:
	OptimalBSTree(vector<shared_ptr<Book> > &library);
	shared_ptr<Book> find(const string &key);
	void show();
	~OptimalBSTree();
};

