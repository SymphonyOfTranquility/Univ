#pragma once
#include "Book.h"
#include <algorithm>

struct TNode
{
	shared_ptr<TNode> parent, leftSon, rightSon;
	shared_ptr<Book> book;
	TNode(shared_ptr<Book> curBook)
	{
		parent = leftSon = rightSon = nullptr;
		book = curBook;
	}
};


class SplayTree
{
	shared_ptr<TNode> root;
	void leftRotate(shared_ptr<TNode> v);
	void rightRotate(shared_ptr<TNode> v);
	void splay(shared_ptr<TNode> v);
	int compareText(const string a, const string b);
	int compareBooks(const shared_ptr<TNode> a, const shared_ptr<TNode> b);
	int checkPart(const string a, const string b);
	void setPos(shared_ptr<TNode> curV, shared_ptr<TNode> insertV);
	shared_ptr<TNode> dfs(shared_ptr<TNode> v, const string &key);
	void showDfs(shared_ptr<TNode> v, int numberOfTabs);

public:
	SplayTree();
	void insert(shared_ptr<Book> curBook);
	shared_ptr<Book> find(const string &key);
	void show();
	~SplayTree();
};

