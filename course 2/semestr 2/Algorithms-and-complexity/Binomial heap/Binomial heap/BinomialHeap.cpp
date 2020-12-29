#include "BinomialHeap.h"


int BinomialHeap::compareText(const string a, const string b)
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

int BinomialHeap::compareBooks(const shared_ptr<Book> a, const shared_ptr<Book> b)
{
	return compareText(a->getBookName(), b->getBookName());
}

int BinomialHeap::checkPart(const string a, const string b)
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

void BinomialHeap::showDfs(shared_ptr<TNode> v, int numberOfTabs)
{
	shared_ptr<TNode> child = v->child;
	while (child)
	{
		showDfs(child, numberOfTabs + 1);
		child = child->brother;
	}
	for (int j = 0; j < numberOfTabs; ++j)
		cout << "\t";
	cout << v->book->getBookName() << "\n";
}

shared_ptr<TNode> BinomialHeap::makeUnion(shared_ptr<TNode> curTree, shared_ptr<TNode> leftBrother)
{
	if (curTree == nullptr || curTree->brother == nullptr)
		return curTree;
	shared_ptr<TNode> rightBrother = curTree->brother;
	while (rightBrother && curTree->degree == rightBrother->degree)
	{
		if (compareBooks(curTree->book, rightBrother->book) <= 0)
		{
			curTree->brother = rightBrother->brother;
			rightBrother->brother = curTree->child;
			curTree->child = rightBrother;
			rightBrother->parent = curTree;
			++curTree->degree;
		}
		else
		{
			curTree->brother = rightBrother->child;
			rightBrother->child = curTree;
			curTree->parent = rightBrother;
			if (leftBrother)
				leftBrother->brother = rightBrother;
			++rightBrother->degree;

			curTree = rightBrother;
		}
		if (curTree->brother)
		{
			shared_ptr<TNode> moveOnHeap = curTree, curLeft = leftBrother, curRight = moveOnHeap->brother;
			bool change = false;
			while (curRight && moveOnHeap->degree > curRight->degree)
			{
				if (curLeft)
					curLeft->brother = curRight;
				if (!change) 
				{
					curTree = curRight;
					change = true;
				}
				moveOnHeap->brother = curRight->brother;
				curRight->brother = moveOnHeap;
				curLeft = moveOnHeap;
				moveOnHeap = curRight;
				curRight = curRight->brother;
			}
		}
		rightBrother = curTree->brother;
	}
	makeUnion(curTree->brother, curTree);
	return curTree;
}



shared_ptr<TNode> BinomialHeap::merge(shared_ptr<TNode> firHeap, shared_ptr<TNode> secHeap)
{
	if (firHeap == nullptr)
		return secHeap;
	else if (secHeap == nullptr)
		return firHeap;

	shared_ptr<TNode> newHeap, moveOnHeap;
	if (firHeap->degree > secHeap->degree) 
	{
		moveOnHeap = newHeap = secHeap;
		secHeap = secHeap->brother;
	}
	else
	{
		moveOnHeap = newHeap = firHeap;
		firHeap = firHeap->brother;
	}

	while (firHeap && secHeap)
	{
		if (firHeap->degree < secHeap->degree)
		{
			moveOnHeap->brother = firHeap;
			moveOnHeap = firHeap;
			firHeap = firHeap->brother;
		}
		else
		{
			moveOnHeap->brother = secHeap;
			moveOnHeap = secHeap;
			secHeap = secHeap->brother;
		}
	}

	while (firHeap)
	{
		moveOnHeap->brother = firHeap;
		moveOnHeap = firHeap;
		firHeap = firHeap->brother;
	}
	while (secHeap)
	{
		moveOnHeap->brother = secHeap;
		moveOnHeap = secHeap;
		secHeap = secHeap->brother;
	}

	newHeap = makeUnion(newHeap);

	return newHeap;
}

void BinomialHeap::insert(shared_ptr<Book> curBook)
{
	shared_ptr<TNode> newNode = make_shared<TNode>(curBook);
	
	root = merge(root, newNode);
}

pair<shared_ptr<TNode>, shared_ptr<TNode> > BinomialHeap::findNodeMin()
{
	if (!root)
		return { nullptr, nullptr };
	shared_ptr<TNode> moveOnHeap = root->brother, toExtract = root, leftBrother = root, leftExtract = nullptr;
	shared_ptr<Book> minBook = root->book;
	while (moveOnHeap)
	{
		if (compareBooks(moveOnHeap->book, minBook) == -1)
		{
			minBook = moveOnHeap->book;
			leftExtract = leftBrother;
			toExtract = moveOnHeap;
		}
		leftBrother = moveOnHeap;
		moveOnHeap = moveOnHeap->brother;
	}
	return { toExtract,leftExtract };
}


BinomialHeap::BinomialHeap(vector<shared_ptr<Book> > &library)
{
	for (int i = 0; i < library.size(); ++i) 
		insert(library[i]);
}

shared_ptr<Book> BinomialHeap::top()
{
	pair<shared_ptr<TNode>, shared_ptr<TNode> > minNode = findNodeMin();
	if (minNode.first)
		return minNode.first->book;
	else
		return nullptr;
}

void BinomialHeap::pop()
{
	if (!root)
		return;
	pair<shared_ptr<TNode>, shared_ptr<TNode> > minNode = findNodeMin();
	shared_ptr<TNode> toExtract = minNode.first, leftExtract = minNode.second;
	
	if (root == toExtract)
		root = root->brother;
	else
		leftExtract->brother = toExtract->brother;
	
	shared_ptr<TNode> newHeap, tempMove, moveOnHeap = toExtract->child;
	while (moveOnHeap)
	{
		moveOnHeap->parent = nullptr;
		tempMove = moveOnHeap->brother;
		if (newHeap)
			moveOnHeap->brother = newHeap;
		else
			moveOnHeap->brother = nullptr;
		newHeap = moveOnHeap;

		moveOnHeap = tempMove;
	}
	root = merge(root, newHeap);
}

void BinomialHeap::show()
{
	cout << "\n\n-------------------------------------TREE-------------------------------------\n\n";
	shared_ptr<TNode> temp = root;
	while (temp) 
	{
		showDfs(temp, 0);
		temp = temp->brother;
		cout << '\n';
	}
}


BinomialHeap::~BinomialHeap()
{
}
