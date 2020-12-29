#pragma once
#include "Book.h"
#include <algorithm>
#include <iomanip>

struct TNode
{
	shared_ptr<TNode> parent, child, rightBrother, leftBrother;
	shared_ptr<Book> book;
	int degree;

	TNode(shared_ptr<Book> curBook)
	{
		parent = child = leftBrother = rightBrother = nullptr;
		book = curBook;
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
	FibonacciHeap(vector<shared_ptr<Book> > &library);
	void push(shared_ptr<Book> curBook);
	shared_ptr<Book> top();
	void pop();
	void show();
	~FibonacciHeap();
};

