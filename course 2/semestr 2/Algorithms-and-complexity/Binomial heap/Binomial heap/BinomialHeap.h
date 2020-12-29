#pragma once
#include "Book.h"
#include <algorithm>
#include <iomanip>

struct TNode
{
	shared_ptr<TNode> parent, child, brother;
	shared_ptr<Book> book;
	int degree;
	
	TNode(shared_ptr<Book> curBook)
	{
		parent = child = brother = nullptr;
		book = curBook;
		degree = 0;
	}
};


class BinomialHeap
{
	shared_ptr<TNode> root;

	int compareText(const string a, const string b);
	int compareBooks(const shared_ptr<Book> a, const shared_ptr<Book> b);
	int checkPart(const string a, const string b);

	void showDfs(shared_ptr<TNode> v, int numberOfTabs);
	shared_ptr<TNode> makeUnion(shared_ptr<TNode> curTree, shared_ptr<TNode> leftBrother = nullptr);
	shared_ptr<TNode> merge(shared_ptr<TNode> firHeap, shared_ptr<TNode> secHeap);

	pair<shared_ptr<TNode>, shared_ptr<TNode> > findNodeMin();
	
public:
	BinomialHeap(vector<shared_ptr<Book> > &library);
	void insert(shared_ptr<Book> curBook);
	shared_ptr<Book> top();
	void pop();
	void show();
	~BinomialHeap();
};

