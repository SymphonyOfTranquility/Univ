#pragma once
#include "Book.h"

struct TNode
{
	shared_ptr<TNode> parent, leftSon, rightSon;
	shared_ptr<Book> book;
	bool color;
	int numberOfElements;
	TNode(shared_ptr<Book> curBook)
	{
		color = 0;
		parent = leftSon = rightSon = nullptr;
		book = curBook;
		numberOfElements = 0;
	}
};

class RBTree
{
	enum Color
	{
		Red = false,
		Black = true
	};

	shared_ptr<TNode> root;
	shared_ptr<TNode> grandpa(shared_ptr<TNode> v);
	shared_ptr<TNode> uncle(shared_ptr<TNode> v);
	void leftRotate(shared_ptr<TNode> v);
	void rightRotate(shared_ptr<TNode> v);
	void insertIfRoot(shared_ptr<TNode> v);
	void insertIfParentIsBlack(shared_ptr<TNode> v);
	void insertIfUncleIsRed(shared_ptr<TNode> v);
	void checkRotation(shared_ptr<TNode> v);
	void lastRotateNPGU(shared_ptr<TNode> v); //new parent grand uncle rotation
	void setPos(shared_ptr<TNode> &curV, shared_ptr<TNode> &insertV);

	void dfs(shared_ptr<TNode> v, int numberOfTabs);
	shared_ptr<TNode> findBookDfs(shared_ptr<TNode> v, int k);

public:
	RBTree();
	void add(shared_ptr<Book> curBook);
	void show();
	shared_ptr<Book> findBook(int k);
	~RBTree();
};

