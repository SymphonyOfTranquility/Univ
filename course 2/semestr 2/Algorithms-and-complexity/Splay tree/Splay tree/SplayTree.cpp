#include "SplayTree.h"



void SplayTree::leftRotate(shared_ptr<TNode> v)
{
	shared_ptr<TNode> temp = v->rightSon;
	if (temp != nullptr)
	{
		v->rightSon = temp->leftSon;
		if (temp->leftSon != nullptr)
			temp->leftSon->parent = v;
		temp->parent = v->parent;
	}
	if (v->parent == nullptr)
		root = temp;
	else if (v == v->parent->leftSon)
		v->parent->leftSon = temp;
	else
		v->parent->rightSon = temp;
	if (temp)
		temp->leftSon = v;
	v->parent = temp;
}

void SplayTree::rightRotate(shared_ptr<TNode> v)
{
	shared_ptr<TNode> temp = v->leftSon;
	if (temp != nullptr)
	{
		v->leftSon = temp->rightSon;
		if (temp->rightSon != nullptr)
			temp->rightSon->parent = v;
		temp->parent = v->parent;
	}
	if (v->parent == nullptr)
		root = temp;
	else if (v == v->parent->leftSon)
		v->parent->leftSon = temp;
	else
		v->parent->rightSon = temp;
	if (temp)
		temp->rightSon = v;
	v->parent = temp;
}

void SplayTree::splay(shared_ptr<TNode> v)
{
	while (v->parent)
	{
		if (v->parent->parent == nullptr)												//no grandpa
		{
			if (v->parent->leftSon == v)
				rightRotate(v->parent);
			else
				leftRotate(v->parent);
		}
		else if (v->parent->leftSon == v && v->parent->parent->leftSon == v->parent)	//right zigzig
		{
			rightRotate(v->parent->parent);
			rightRotate(v->parent);
		}
		else if (v->parent->rightSon == v && v->parent->parent->rightSon == v->parent)	//left zigzig
		{
			leftRotate(v->parent->parent);
			leftRotate(v->parent);
		}
		else if (v->parent->leftSon == v && v->parent->parent->rightSon == v->parent)	// right zigzag
		{
			rightRotate(v->parent);
			leftRotate(v->parent);
		}
		else																			// left zigzag
		{
			leftRotate(v->parent);
			rightRotate(v->parent);
		}
	}
}

int SplayTree::compareText(const string a, const string b)
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

int SplayTree::compareBooks(const shared_ptr<TNode> a, const shared_ptr<TNode> b)
{
	return compareText(a->book->getBookName(), b->book->getBookName());
}

int SplayTree::checkPart(const string a, const string b)
{
	if (a.length() < b.length())
		return -1;
	for (int i = 0; i < b.length(); ++i)
	{
		if (toupper(a[i]) < toupper(b[i]))
			return -1;
		else if (toupper(a[i]) > toupper(b[i]))
			return 1;			
	}
	return 0;
}

void SplayTree::setPos(shared_ptr<TNode> curV, shared_ptr<TNode> insertV)
{
	if (curV == nullptr)
		return;
	else if (compareBooks(curV, insertV) < 1)
	{
		if (curV->leftSon != nullptr)
			setPos(curV->leftSon, insertV);
		else
		{
			curV->leftSon = insertV;
			insertV->parent = curV;
		}
	}
	else
	{
		if (curV->rightSon != nullptr)
			setPos(curV->rightSon, insertV);
		else
		{
			curV->rightSon = insertV;
			insertV->parent = curV;
		}
	}
}

shared_ptr<TNode> SplayTree::dfs(shared_ptr<TNode> v, const string &key)
{
	if (v == nullptr)
		return v;
	if (checkPart(v->book->getBookName(), key) == 1)
		return dfs(v->rightSon, key);
	if (checkPart(v->book->getBookName(), key) == -1)
		return dfs(v->leftSon, key);
	return v;
}

void SplayTree::showDfs(shared_ptr<TNode> v, int numberOfTabs)
{
	if (v->rightSon != nullptr)
		showDfs(v->rightSon, numberOfTabs + 1);
	else
		cout << '\n';

	for (int i = 0; i < numberOfTabs; ++i)
		cout << "\t";
	cout << v->book->getBookName();

	if (v->leftSon != nullptr)
		showDfs(v->leftSon, numberOfTabs + 1);
	else
		cout << '\n';
}



SplayTree::SplayTree()
{
	root = nullptr;
}

void SplayTree::insert(shared_ptr<Book> curBook)
{
	shared_ptr<TNode> v = make_shared<TNode>(curBook);
	setPos(root, v);
	if (v->parent == nullptr)
		root = v;
	splay(v);
}

shared_ptr<Book> SplayTree::find(const string &key)
{
	shared_ptr<TNode> v = dfs(root, key);
	if (v != nullptr)
		return v->book;
	return nullptr;
}

void SplayTree::show()
{
	shared_ptr<TNode> temp = root;
	showDfs(temp, 0);
}


SplayTree::~SplayTree()
{
}
