#include "BPlusTree.h"


int BPlusTree::compareText(const string a, const string b)
{
	for (int i = 0; i < min(a.length(),b.length()); ++i)
	{
		if (toupper(a[i]) < toupper(b[i]))
			return -1;
		else if (toupper(a[i]) > toupper(b[i]))
			return 1;
	}
	if (a.length() > b.length())
		return 1;
	else if (a.length() < b.length())
		return -1;
	else
		return 0;
}

int BPlusTree::compareBooks(const shared_ptr<Book> a, const shared_ptr<Book> b)
{
	return compareText(a->getBookName(), b->getBookName());
}

int BPlusTree::checkPart(const string a, const string b)
{
	for (int i = 0; i < min(a.length(),b.length()); ++i)
	{
		if (toupper(a[i]) < toupper(b[i]))
			return -1;
		else if (toupper(a[i]) > toupper(b[i]))
			return 1;			
	}
	if (a.length() < b.length())
		return -1;
	return 0;
}

void BPlusTree::insert(shared_ptr<Book>& value)
{
	if (root == nullptr)
	{
		root = make_shared<TNode>();
		root->books.push_back(value);
		root->leaf = true;
		return;
	}
	
	shared_ptr<TNode> leafNode = dfs(root, value->getBookName());
	if (leafNode->books.size() == MAX_SIZE)
	{
		split(leafNode, value);
		leafNode = dfs(root, value->getBookName());
	}
	int needPos = binarySearch(leafNode, value->getBookName());
	leafNode->books.push_back(nullptr);

	for (int i = leafNode->books.size() - 1; i > needPos + 1; --i)
		leafNode->books[i] = leafNode->books[i - 1];
	leafNode->books[needPos + 1] = value;
}

int BPlusTree::binarySearch(shared_ptr<TNode> v, string value)
{
	int l = -1, r = v->books.size();
	while (r - l > 1)
	{
		int mid = (r + l) / 2;
		if (compareText(v->books[mid]->getBookName(), value) == 1)
			r = mid;
		else
			l = mid;
	}
	return l;
}

void BPlusTree::split(shared_ptr<TNode> curV, shared_ptr<Book>& value)
{
	shared_ptr<TNode> father = curV->parent;
	if (father == nullptr)
	{
		root = make_shared<TNode>();
		curV->parent = root;
		father = root;
	}
	if (father->sons.size() == MAX_SIZE)
		split(father, value);
	father = curV->parent;
	int mid = MAX_SIZE / 2-1;
	if (curV->leaf)
		++mid;
	shared_ptr<TNode> newNode = make_shared<TNode>();
	if (father->books.size() > 0)
	{
		int needPos = binarySearch(father, curV->books[mid]->getBookName());
		father->books.push_back(nullptr);
		father->sons.push_back(nullptr);
		for (int i = father->books.size() - 1; i > needPos + 1; --i)
		{
			father->books[i] = father->books[i - 1];
			father->sons[i + 1] = father->sons[i];
		}
		father->books[needPos + 1] = curV->books[mid];
		father->sons[needPos + 2] = newNode;
	}
	else
	{
		father->books.push_back(curV->books[mid]);
		father->sons.push_back(curV);
		father->sons.push_back(newNode);
	}
	newNode->parent = father;

	if (curV->leaf) 
	{
		newNode->leaf = true;
		for (int i = mid; i < MAX_SIZE; ++i)
			newNode->books.push_back(curV->books[i]);
		for (int i = MAX_SIZE - 1; i >= mid; --i)
			curV->books.pop_back();
	}
	else
	{
		for (int i = mid + 1; i < MAX_SIZE-1; ++i) {
			newNode->books.push_back(curV->books[i]);
			curV->sons[i]->parent = newNode;
			newNode->sons.push_back(curV->sons[i]);
		}
		curV->sons[MAX_SIZE - 1]->parent = newNode;
		newNode->sons.push_back(curV->sons[MAX_SIZE - 1]);
		for (int i = MAX_SIZE - 2; i >= mid; --i) 
		{
			curV->books.pop_back();
			curV->sons.pop_back();
		}
	}
}

shared_ptr<TNode> BPlusTree::dfs(shared_ptr<TNode> v, const string &key)
{
	if (v == nullptr || v->leaf)
		return v;
	int needPos = binarySearch(v, key);
	return dfs(v->sons[needPos + 1], key);
}

void BPlusTree::showDfs(shared_ptr<TNode> v, int numberOfTabs)
{
	for (int i = 0; i < v->sons.size(); ++i)
	{
		showDfs(v->sons[i], numberOfTabs + 1);
		cout << '\n';
		for (int j = 0; j < numberOfTabs; ++j)
			cout << "\t";
		if (i + 1 < v->sons.size())
			cout << v->books[i]->getBookName() << '\n';
	}
	if (v->leaf) 
	{
		for (int i = 0; i < v->books.size(); ++i)
		{
			for (int j = 0; j < numberOfTabs; ++j)
				cout << "\t";
			cout << v->books[i]->getBookName() << '\n';
		}
	}
}

shared_ptr<TNode> BPlusTree::dfsFind(shared_ptr<TNode> v, const string & key)
{
	if (v == nullptr || v->leaf)
		return v;
	int needPos = binarySearchFind(v, key);
	return dfsFind(v->sons[needPos + 1], key);
}

int BPlusTree::binarySearchFind(shared_ptr<TNode> v, string value)
{
	int l = -1, r = v->books.size();
	while (r - l > 1)
	{
		int mid = (r + l) / 2;
		if (checkPart(v->books[mid]->getBookName(), value) == 1)
			r = mid;
		else
			l = mid;
	}
	return l;
}



BPlusTree::BPlusTree(vector<shared_ptr<Book> > &library)
{
	for (int i = 0; i < library.size(); ++i)
		insert(library[i]);
}

shared_ptr<Book> BPlusTree::find(const string &key)
{
	shared_ptr<TNode> v = dfsFind(root, key);
	if (v != nullptr) {
		int needPos = binarySearchFind(v, key);
		if (needPos < 0)
			return nullptr;
		if (checkPart(v->books[needPos]->getBookName(), key) == 0)
			return v->books[needPos];
		else
			return false;
	}
	return nullptr;
}

void BPlusTree::show()
{
	cout << "\n\n-------------------------------------TREE-------------------------------------\n\n";
	shared_ptr<TNode> temp = root;
	showDfs(temp, 0);
}


BPlusTree::~BPlusTree()
{
}
