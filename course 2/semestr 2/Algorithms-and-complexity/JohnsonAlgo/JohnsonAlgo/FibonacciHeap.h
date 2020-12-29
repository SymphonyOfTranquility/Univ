#pragma once
#include "Book.h"
#include <algorithm>
#include <iomanip>

struct TNode
{
	shared_ptr<TNode> parent, child, rightBrother, leftBrother;
	pair<int, int> data;
	int degree;

	TNode(pair<int,int> curData)
	{
		parent = child = leftBrother = rightBrother = nullptr;
		data = curData;
		degree = 0;
	}
};


class FibonacciHeap
{
	shared_ptr<TNode> root;
	int size;

	int compareText(const string a, const string b);
	int compareBooks(const shared_ptr<Book> a, const shared_ptr<Book> b);
	int checkPart(const string a, const string b);

	void showDfs(shared_ptr<TNode> v, int numberOfTabs);
	shared_ptr<TNode> merge(shared_ptr<TNode> firHeap, shared_ptr<TNode> secHeap);
	void consolidate();
	
public:
	FibonacciHeap();
	void push(pair<int, int> curData);
	pair<int,int> top();
	void pop();
	void show();
	bool empty();
	~FibonacciHeap();
};

