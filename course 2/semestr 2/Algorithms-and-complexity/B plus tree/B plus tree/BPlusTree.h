#pragma once
#include "Book.h"
#include <algorithm>
#include <iomanip>

struct TNode
{
	shared_ptr<TNode> parent;
	vector<shared_ptr<TNode> > sons;
	vector<shared_ptr<Book> > books;
	bool leaf;
	TNode()
	{
		parent = nullptr;
		sons.clear();
		leaf = false;
		books.clear();
	}
};


class BPlusTree
{
	const int MAX_SIZE = 4;
	shared_ptr<TNode> root;

	int compareText(const string a, const string b);
	int compareBooks(const shared_ptr<Book> a, const shared_ptr<Book> b);
	int checkPart(const string a, const string b);

	void insert(shared_ptr<Book> &value);
	int binarySearch(shared_ptr<TNode> v, string value);
	void split(shared_ptr<TNode> curV, shared_ptr<Book> &value);

	shared_ptr<TNode> dfs(shared_ptr<TNode> v, const string &key);
	void showDfs(shared_ptr<TNode> v, int numberOfTabs);

	shared_ptr<TNode> dfsFind(shared_ptr<TNode> v, const string &key);
	int binarySearchFind(shared_ptr<TNode> v, string value);
	
public:
	BPlusTree(vector<shared_ptr<Book> > &library);
	shared_ptr<Book> find(const string &key);
	void show();
	~BPlusTree();
};

