#include "OptimalBSTree.h"


int OptimalBSTree::compareText(const string a, const string b)
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

int OptimalBSTree::compareBooks(const shared_ptr<TNode> a, const shared_ptr<TNode> b)
{
	return compareText(a->book->getBookName(), b->book->getBookName());
}

int OptimalBSTree::checkPart(const string a, const string b)
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

void OptimalBSTree::restoreHeap(vector<shared_ptr<TNode>>& mas, int father, int countTree)
{
	int maxson;
	while (father <= countTree / 2)
	{
		if (father * 2 == countTree)
			maxson = father * 2;
		else if (compareBooks(mas[father * 2], mas[father * 2 - 1]) == 1)
			maxson = father * 2 + 1;
		else
			maxson = father * 2;
		if (compareBooks(mas[father - 1], mas[maxson - 1]) == -1)
		{
			swap(mas[father - 1], mas[maxson - 1]);
			father = maxson;
		}
		else
			father = countTree;
	}
}

void OptimalBSTree::mySort(vector<shared_ptr<TNode>> &mas)
{
	for (int i = mas.size() / 2; i > 0; --i)
		restoreHeap(mas, i, mas.size());

	for (int i = mas.size(); i > 0; --i)
	{
		swap(mas[i - 1], mas[0]);
		restoreHeap(mas, 1, i - 1);
	}
}

void OptimalBSTree::buildTree(vector<shared_ptr<TNode>>& mas, shared_ptr<TNode> vertex, int i, int j)
{
	if (roots[i][j] < 0)
		return;
	shared_ptr<TNode> curV = mas[roots[i][j] - 1];
	if (vertex == nullptr) 
	{
		root = curV;
	}
	else 
	{
		curV->parent = vertex;
		if (compareBooks(curV, vertex) == 1)
			vertex->rightSon = curV;
		else
			vertex->leftSon = curV;
	}
	if (roots[i][j] > i)
		buildTree(mas, curV, i, roots[i][j] - 1);
	if (roots[i][j] < j)
		buildTree(mas, curV, roots[i][j] + 1, j);
}

void OptimalBSTree::showMatrixRootsAndWeights()
{
	cout << "<-------------------------------prefics weight list------------------------------->\n";
	for (int i = 0; i < prefWeightList.size(); ++i)
	{
		cout.width(9);
		cout << fixed << setprecision(6) << prefWeightList[i];
	}
	cout << "\n\n<-------------------------------matrix of weights------------------------------->\n";
	for (int i = 0; i < weights.size(); ++i)
	{
		for (int j = 0; j < weights[i].size(); ++j)
		{
			cout.width(9);
			if (weights[i][j] == 1e+6)
				cout << -1;
			else
				cout << fixed << setprecision(6) << weights[i][j];
		}
		cout << '\n';
	}

	cout << "\n<-------------------------------matrix of roots------------------------------->\n";
	for (int i = 0; i < roots.size(); ++i)
	{
		for (int j = 0; j < roots[i].size(); ++j) {
			cout.width(3);
			cout << roots[i][j];
		}
		cout << '\n';
	}
}

void OptimalBSTree::buildRootsAndWeights(vector<shared_ptr<TNode> >& nodeList)
{
	if (nodeList.empty())
		return;
	prefWeightList.push_back(nodeList[0]->weight);
	for (int i = 1; i < nodeList.size(); ++i) 
		prefWeightList.push_back(prefWeightList[i - 1] + nodeList[i]->weight);
	roots.resize(nodeList.size() + 2, vector<short int>(nodeList.size() + 2, -1));
	weights.resize(nodeList.size() + 2, vector<float>(nodeList.size() + 2, inf));
	for (int i = 1; i <= nodeList.size()+1; ++i)
	{
		roots[i][i - 1] = 0;
		weights[i][i - 1] = 0;
	}
	for (int step = 1; step <= nodeList.size(); ++step)
	{
		for (int i = 1; i + step <= nodeList.size()+1; ++i)
		{
			int j = i + step - 1;
			int myLeft = i, myRight = j;
			if (step > 1)
			{
				myLeft = roots[i][j-1];
				myRight = roots[i+1][j];
			}
			
			double prefSum = prefWeightList[j-1] - (i > 1 ? prefWeightList[i-2] : 0);
			for (int k = myLeft; k <= myRight; ++k)
			{
				double val = weights[i][k - 1] + weights[k + 1][j] + prefSum;
				if (val < weights[i][j])
				{
					weights[i][j] = val;
					roots[i][j] = k;
				}
			}
		}
	}

	if (nodeList.size() <= 16)
		showMatrixRootsAndWeights();

	buildTree(nodeList, nullptr, 1, nodeList.size());
}

shared_ptr<TNode> OptimalBSTree::dfs(shared_ptr<TNode> v, const string &key)
{
	if (v == nullptr)
		return v;
	if (checkPart(v->book->getBookName(), key) == 1)
		return dfs(v->leftSon, key);
	if (checkPart(v->book->getBookName(), key) == -1)
		return dfs(v->rightSon, key);
	return v;
}

void OptimalBSTree::showDfs(shared_ptr<TNode> v, int numberOfTabs)
{
	if (v->rightSon != nullptr)
		showDfs(v->rightSon, numberOfTabs + 1);
	else
		cout << '\n';

	for (int i = 0; i < numberOfTabs; ++i)
		cout << "\t";
	cout << v->book->getBookName() << "   " << v->weight;

	if (v->leftSon != nullptr)
		showDfs(v->leftSon, numberOfTabs + 1);
	else
		cout << '\n';
}



OptimalBSTree::OptimalBSTree(vector<shared_ptr<Book> > &library)
{
	vector<shared_ptr<TNode> > tempList, nodeList;
	for (int i = 0; i < library.size(); ++i) 
		tempList.push_back(make_shared<TNode>(library[i]));

	mySort(tempList);

	double allWeight = 0;
	for (int i = 0; i < tempList.size(); ++i) 
	{
		if (tempList[i]->book->getBookName() != "") {
			nodeList.push_back(tempList[i]);
			nodeList[nodeList.size()-1]->weight = rand() % (library.size()*library.size());
			allWeight += nodeList[nodeList.size() - 1]->weight;
		}
	}
	tempList.clear();
	for (int i = 0; i < nodeList.size(); ++i)
		nodeList[i]->weight /= allWeight;

	buildRootsAndWeights(nodeList);
}

shared_ptr<Book> OptimalBSTree::find(const string &key)
{
	shared_ptr<TNode> v = dfs(root, key);
	if (v != nullptr)
		return v->book;
	return nullptr;
}

void OptimalBSTree::show()
{
	shared_ptr<TNode> temp = root;
	showDfs(temp, 0);
}


OptimalBSTree::~OptimalBSTree()
{
}
