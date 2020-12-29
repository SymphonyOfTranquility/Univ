#pragma once
#include "Book.h"
#include <algorithm>
#include <iomanip>

struct TNode
{
	vector<shared_ptr<TNode> > parent;
	shared_ptr<TNode> leftSon, rightSon;
	shared_ptr<Book> book;
	bool color;
	int version;
	TNode(shared_ptr<Book> curBook)
	{
		parent.clear();
		leftSon = rightSon = nullptr;
		book = curBook;
		color = false;
		version = -1;
	}
	TNode(shared_ptr<TNode> node)
	{
		parent.clear();
		leftSon = node->leftSon;
		rightSon = node->rightSon;
		book = node->book;
		color = node->color;
		version = -1;
	}
};


class PersistentRBTree
{
	enum Color
	{
		Red = false,
		Black = true
	};
	vector<shared_ptr<TNode> > roots;
	int numberOfRoots;

	int compareText(const string a, const string b);
	int compareBooks(const shared_ptr<TNode> a, const shared_ptr<TNode> b);
	int checkPart(const string a, const string b);
	
	shared_ptr<TNode> lastPa(shared_ptr<TNode> v);
	shared_ptr<TNode> grandpa(shared_ptr<TNode> v);
	shared_ptr<TNode> uncle(shared_ptr<TNode> v);
	void leftRotate(shared_ptr<TNode> v);
	void rightRotate(shared_ptr<TNode> v);
	void insertIfRoot(shared_ptr<TNode> v);
	void insertIfParentIsBlack(shared_ptr<TNode> v);
	void insertIfUncleIsRed(shared_ptr<TNode> v);
	void checkRotation(shared_ptr<TNode> v);
	void lastRotateNPGU(shared_ptr<TNode> v);
	
	void setPos(shared_ptr<TNode> curV, shared_ptr<TNode>& insertV);

	shared_ptr<TNode> dfs(shared_ptr<TNode> v, const string &key);
	void showDfs(shared_ptr<TNode> v, int numberOfTabs);

public:
	PersistentRBTree(vector<shared_ptr<Book> > &library);
	shared_ptr<Book> find(const string &key, int number); 
	int getNumberOfRoots();
	void show(int num);
	void showAllVersions();
	~PersistentRBTree();
};

