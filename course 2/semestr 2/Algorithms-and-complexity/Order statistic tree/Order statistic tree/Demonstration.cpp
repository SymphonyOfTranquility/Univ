#include "Demonstration.h"

void demonstration()
{
	ifstream fin("data.txt");
	int n;
	vector<shared_ptr<Book> > library;
	fin >> n;
	//n = 16;
	for (int i = 0;i < n; ++i) 
		library.push_back(make_shared<Book>(fin));
	fin.close();

	shared_ptr<RBTree> tree = make_shared<RBTree>();
	for (int i = 0; i < n; ++i)
		tree->add(library[i]);
	//tree->show();
	cout << "0 - exit\n1 - k-th book(numbering starts from 0)\n";
	int inp;
	while (true)
	{
		cin >> inp;
		if (inp == 0)
		{
			cout << "Good bye";
			break;
		}
		else if (inp == 1)		//find author
		{
			cout << "Input the position of book in rating:\n";
			int k;
			cin >> k;
			if (k >= n)
			{
				cout << "Sorry! I don't have so many books here!\nWould you like to find other book ? \n\t0 - no\n\t1 - yes\n\n";
				continue;
			}
			shared_ptr<Book> curBook = tree->findBook(k);
			curBook->show();
			cout << "\nWould you like to find other book?\n\t0 - no\n\t1 - yes\n\n";
		}
	}
}
