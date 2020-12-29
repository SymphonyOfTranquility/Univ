#include "RBTree.h"



shared_ptr<TNode> RBTree::grandpa(shared_ptr<TNode> v)
{
	if (v != nullptr && v->parent != nullptr)
		return v->parent->parent;
	else
		return nullptr;
}

shared_ptr<TNode> RBTree::uncle(shared_ptr<TNode> v)
{
	shared_ptr<TNode> grand = grandpa(v);
	if (grand == nullptr)
		return nullptr;
	if (grand->leftSon == v->parent)
		return grand->rightSon;
	else
		return grand->leftSon;
}

void RBTree::leftRotate(shared_ptr<TNode> v)
{
	shared_ptr<TNode> temp = v->rightSon;
	int vRightVal;
	if (v->rightSon != nullptr)
		vRightVal = v->rightSon->numberOfElements;
	else
		vRightVal = 0;
	int tempLeftVal;
	if (temp->leftSon != nullptr)
		tempLeftVal = temp->leftSon->numberOfElements;
	else
		tempLeftVal = 0;
	temp->parent = v->parent;
	if (v->parent != nullptr)
	{
		if (v->parent->leftSon == v)
			v->parent->leftSon = temp;
		else
			v->parent->rightSon = temp;
	}

	v->rightSon = temp->leftSon;
	if (temp->leftSon != nullptr)
		temp->leftSon->parent = v;
	v->parent = temp;
	temp->leftSon = v;
	v->numberOfElements = v->numberOfElements - vRightVal + tempLeftVal;
	temp->numberOfElements = temp->numberOfElements - tempLeftVal + v->numberOfElements;
}

void RBTree::rightRotate(shared_ptr<TNode> v)
{
	shared_ptr<TNode> temp = v->leftSon;
	int vLeftVal;
	if (v->leftSon != nullptr)
		vLeftVal = v->leftSon->numberOfElements;
	else
		vLeftVal = 0;
	int tempRightVal;
	if (temp->rightSon != nullptr)
		tempRightVal = temp->rightSon->numberOfElements;
	else
		tempRightVal = 0;
	temp->parent = v->parent;
	if (v->parent != nullptr)
	{
		if (v->parent->leftSon == v)
			v->parent->leftSon = temp;
		else
			v->parent->rightSon = temp;
	}

	v->leftSon = temp->rightSon;
	if (temp->rightSon != nullptr)
		temp->rightSon->parent = v;
	v->parent = temp;
	temp->rightSon = v;
	v->numberOfElements = v->numberOfElements - vLeftVal + tempRightVal;
	temp->numberOfElements = temp->numberOfElements - tempRightVal + v->numberOfElements;
}

void RBTree::insertIfRoot(shared_ptr<TNode> v)
{
	if (v->parent == nullptr)
		v->color = Black;
	else
		insertIfParentIsBlack(v);
}

void RBTree::insertIfParentIsBlack(shared_ptr<TNode> v)
{
	if (v->parent->color == Black)
		return;
	insertIfUncleIsRed(v);
}

void RBTree::insertIfUncleIsRed(shared_ptr<TNode> v)
{
	shared_ptr<TNode> un = uncle(v);
	if (un != nullptr && un->color == Red)
	{
		v->parent->color = Black;
		un->color = Black;
		shared_ptr<TNode> grand = grandpa(v);
		grand->color = Red;
		insertIfRoot(grand);
	}
	else
		checkRotation(v);
}

void RBTree::checkRotation(shared_ptr<TNode> v)
{
	shared_ptr<TNode> grand = grandpa(v);

	if (v == v->parent->rightSon && v->parent == grand->leftSon)
	{
		leftRotate(v->parent);
		v = v->leftSon;
	}
	else if (v == v->parent->leftSon && v->parent == grand->rightSon)
	{
		rightRotate(v->parent);
		v = v->rightSon;
	}
	lastRotateNPGU(v);
}

void RBTree::lastRotateNPGU(shared_ptr<TNode> v)
{
	shared_ptr<TNode> grand = grandpa(v);
	v->parent->color = Black;
	grand->color = Red;
	if (v == v->parent->leftSon)
		rightRotate(grand);
	else
		leftRotate(grand);
}

void RBTree::setPos(shared_ptr<TNode> &curV, shared_ptr<TNode> &insertV)
{
	if (curV == nullptr)
		curV = insertV;
	else if (curV->book->getRating() >= insertV->book->getRating())
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

void RBTree::dfs(shared_ptr<TNode> v, int numberOfTabs)
{
	if (v->rightSon != nullptr)
		dfs(v->rightSon, numberOfTabs + 1);
	else
		cout << '\n';

	for (int i = 0; i < numberOfTabs; ++i)
		cout << "\t";
	cout << v->book->getRating();
	if (v->color == Red)
		cout << " Red " << v->numberOfElements << '\n';
	else
		cout << " Black " << v->numberOfElements << '\n';

	if (v->leftSon != nullptr)
		dfs(v->leftSon, numberOfTabs + 1);
	else
		cout << '\n';
}

shared_ptr<TNode> RBTree::findBookDfs(shared_ptr<TNode> v, int k)
{
	int value;
	if (v->leftSon == nullptr)
		value = 0;
	else
		value = v->leftSon->numberOfElements;
	if (value == k)
		return v;
	else if (value > k)
		return findBookDfs(v->leftSon, k);
	else
		return findBookDfs(v->rightSon, k - value - 1);
}

RBTree::RBTree()
{
	root = nullptr;
}

void RBTree::add(shared_ptr<Book> curBook)
{
	shared_ptr<TNode> vertex = make_shared<TNode>(curBook);
	vertex->color = Red;
	setPos(root, vertex);
	insertIfRoot(vertex);
	while (root->parent != nullptr)
		root = root->parent;
	while (vertex)
	{
		++vertex->numberOfElements;
		vertex = vertex->parent;
	}
}

void RBTree::show()
{
	shared_ptr<TNode> temp = root;
	dfs(temp, 0);
}

shared_ptr<Book> RBTree::findBook(int k)
{
	shared_ptr<TNode> temp = findBookDfs(root, k);
	return temp->book;
}


RBTree::~RBTree()
{
}
