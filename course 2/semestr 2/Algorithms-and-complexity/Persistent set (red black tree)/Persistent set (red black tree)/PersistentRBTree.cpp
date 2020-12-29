#include "PersistentRBTree.h"


int PersistentRBTree::compareText(const string a, const string b)
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

int PersistentRBTree::compareBooks(const shared_ptr<TNode> a, const shared_ptr<TNode> b)
{
	return compareText(a->book->getBookName(), b->book->getBookName());
}

int PersistentRBTree::checkPart(const string a, const string b)
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

shared_ptr<TNode> PersistentRBTree::lastPa(shared_ptr<TNode> v)
{
	if (v->parent.empty())
		return nullptr;
	else
		return v->parent[v->parent.size()-1];
}

shared_ptr<TNode> PersistentRBTree::grandpa(shared_ptr<TNode> v)
{
	if (v != nullptr && lastPa(v) != nullptr)
		return lastPa(lastPa(v));
	else
		return nullptr;
}

shared_ptr<TNode> PersistentRBTree::uncle(shared_ptr<TNode> v)
{
	shared_ptr<TNode> grand = grandpa(v);
	if (grand == nullptr)
		return nullptr;
	if (grand->leftSon == lastPa(v))
		return grand->rightSon;
	else
		return grand->leftSon;
}

void PersistentRBTree::leftRotate(shared_ptr<TNode> v)
{
	shared_ptr<TNode> temp = v->rightSon;
	temp->parent = v->parent;
	if (lastPa(v) != nullptr)
	{
		if (lastPa(v)->leftSon == v)
			lastPa(v)->leftSon = temp;
		else
			lastPa(v)->rightSon = temp;
	}

	v->rightSon = temp->leftSon;
	if (temp->leftSon != nullptr) 
	{
		temp->leftSon->parent.pop_back();
		temp->leftSon->parent.push_back(v);
	}
	temp->leftSon = v;
	if (v != roots[numberOfRoots - 1])
		v->parent.pop_back();
	else
		roots[numberOfRoots - 1] = temp;
	v->parent.push_back(temp);
}

void PersistentRBTree::rightRotate(shared_ptr<TNode> v)
{
	shared_ptr<TNode> temp = v->leftSon;
	temp->parent = v->parent;
	if (lastPa(v) != nullptr)
	{
		if (lastPa(v)->leftSon == v)
			lastPa(v)->leftSon = temp;
		else
			lastPa(v)->rightSon = temp;
	}

	v->leftSon = temp->rightSon;
	if (temp->rightSon != nullptr) {
		temp->rightSon->parent.pop_back();
		temp->rightSon->parent.push_back(v);
	}
	temp->rightSon = v;
	if (v != roots[numberOfRoots - 1]) 
		v->parent.pop_back();
	else 
		roots[numberOfRoots - 1] = temp;
	v->parent.push_back(temp);
}

void PersistentRBTree::insertIfRoot(shared_ptr<TNode> v)
{
	if (lastPa(v) == nullptr)
		v->color = Black;
	else
		insertIfParentIsBlack(v);
}

void PersistentRBTree::insertIfParentIsBlack(shared_ptr<TNode> v)
{
	if (lastPa(v)->color == Black)
		return;
	insertIfUncleIsRed(v);
}

void PersistentRBTree::insertIfUncleIsRed(shared_ptr<TNode> v)
{
	shared_ptr<TNode> un = uncle(v);
	if (un != nullptr && un->color == Red)
	{
		lastPa(v)->color = Black;
		un->parent.pop_back();

		shared_ptr<TNode> newUn = make_shared<TNode>(un);
		newUn->color = Black;
		shared_ptr<TNode> grand = grandpa(v);
		grand->color = Red;
		newUn->parent.push_back(grand);
		if (grand->leftSon == un)
			grand->leftSon = newUn;
		else
			grand->rightSon = newUn;

		insertIfRoot(grand);
	}
	else
		checkRotation(v);
}

void PersistentRBTree::checkRotation(shared_ptr<TNode> v)
{
	shared_ptr<TNode> grand = grandpa(v);

	if (v == lastPa(v)->rightSon && lastPa(v) == grand->leftSon)
	{
		leftRotate(lastPa(v));
		v = v->leftSon;
	}
	else if (v == lastPa(v)->leftSon && lastPa(v) == grand->rightSon)
	{
		rightRotate(lastPa(v));
		v = v->rightSon;
	}
	lastRotateNPGU(v);
}

void PersistentRBTree::lastRotateNPGU(shared_ptr<TNode> v)
{
	shared_ptr<TNode> grand = grandpa(v);
	lastPa(v)->color = Black;
	grand->color = Red;
	if (v == lastPa(v)->leftSon)
		rightRotate(grand);
	else
		leftRotate(grand);
}

void PersistentRBTree::setPos(shared_ptr<TNode> curV, shared_ptr<TNode> &insertV)
{
	shared_ptr<TNode> realNode;
	if (curV == nullptr)
	{
		realNode = make_shared<TNode>(roots[numberOfRoots - 2]);
		roots[numberOfRoots - 1] = realNode;
	}	
	else
	{
		realNode = make_shared<TNode>(curV);
		realNode->parent.push_back(curV->parent[curV->parent.size()-1]);
		curV->parent.pop_back();
		if (curV == realNode->parent[0]->rightSon)
			realNode->parent[0]->rightSon = realNode;
		else
			realNode->parent[0]->leftSon = realNode;
	}
	realNode->version = numberOfRoots - 1;
	if (realNode->leftSon != nullptr)
		realNode->leftSon->parent.push_back(realNode);
	if (realNode->rightSon != nullptr)
		realNode->rightSon->parent.push_back(realNode);

	if (compareBooks(realNode,insertV) == 1)
	{
		if (realNode->leftSon != nullptr)
			setPos(realNode->leftSon, insertV);
		else
		{
			realNode->leftSon = insertV;
			insertV->parent.push_back(realNode);
		}
	}
	else
	{
		if (realNode->rightSon != nullptr)
			setPos(realNode->rightSon, insertV);
		else
		{
			realNode->rightSon = insertV;
			insertV->parent.push_back(realNode);
		}
	}
}


shared_ptr<TNode> PersistentRBTree::dfs(shared_ptr<TNode> v, const string &key)
{
	if (v == nullptr)
		return v;
	if (checkPart(v->book->getBookName(), key) == 1)
		return dfs(v->leftSon, key);
	if (checkPart(v->book->getBookName(), key) == -1)
		return dfs(v->rightSon, key);
	return v;
}

void PersistentRBTree::showDfs(shared_ptr<TNode> v, int numberOfTabs)
{
	if (v->rightSon != nullptr)
		showDfs(v->rightSon, numberOfTabs + 1);
	else
		cout << '\n';

	for (int i = 0; i < numberOfTabs; ++i)
		cout << "\t";
	cout << v->book->getBookName();
	if (v->color == Red)
		cout << " $RED$";
	else
		cout << " $BLACK$";

	if (v->leftSon != nullptr)
		showDfs(v->leftSon, numberOfTabs + 1);
	else
		cout << '\n';
}



PersistentRBTree::PersistentRBTree(vector<shared_ptr<Book> > &library)
{
	shared_ptr<TNode> tempNode;
	numberOfRoots = 0;
	for (int i = 0; i < library.size(); ++i) 
	{
		tempNode = make_shared<TNode>(library[i]);
		tempNode->version = numberOfRoots;
		if (numberOfRoots == 0)
		{
			roots.push_back(tempNode);
			++numberOfRoots;
			tempNode->color = Black;
		}
		else
		{
			++numberOfRoots;
			roots.push_back(nullptr);
			setPos(roots[numberOfRoots-1], tempNode);
			insertIfRoot(tempNode);
		}
		if (library.size() <= 16)
		{
			cout << "----------------------------------ALL CURRENT VERSIONS----------------------------------\n";
			for (int i = 0; i < numberOfRoots; ++i)
			{
				cout << "--------------------------------version " << i << "--------------------------------\n";
				show(i);
			}
		}

	}
}

shared_ptr<Book> PersistentRBTree::find(const string &key, int number)
{
	if (number >= numberOfRoots)
		return nullptr;
	shared_ptr<TNode> v = dfs(roots[number], key);
	if (v != nullptr)
		return v->book;
	return nullptr;
}

int PersistentRBTree::getNumberOfRoots()
{
	return numberOfRoots;
}


void PersistentRBTree::show(int num)
{
	shared_ptr<TNode> temp = roots[num];
	showDfs(temp, 0);
}

void PersistentRBTree::showAllVersions()
{
	cout << "----------------------------------ALL CURRENT VERSIONS----------------------------------\n";
	for (int i = 0; i < numberOfRoots; ++i) {
		cout << "--------------------------------version " << i << "--------------------------------\n";
		show(i);
	}
}


PersistentRBTree::~PersistentRBTree()
{
}
