#include "Demonstration.h"

void demonstration()
{
	ifstream fin("data.txt");
	int n;
	vector<shared_ptr<Book> > library;
	fin >> n;
	//n = 16;
	for (int i = 0; i < n; ++i)
		library.push_back(make_shared<Book>(fin));
	fin.close();

	shared_ptr<SplayTree> tree = make_shared<SplayTree>();
	for (int i = 0; i < n; ++i)
		tree->insert(library[i]);
	//tree->show();
	cout << "0 - exit\n1 - Input the title of the book(numbering starts from 1)\n";
	int inp;
	while (true)
	{
		cin >> inp;
		if (inp == 0)
		{
			cout << "Bye\n";
			break;
		}
		else if (inp == 1)		//find author
		{
			cout << "Input the title of book:\n";
			string k = "";
			while (k == "")
				getline(cin, k);
			shared_ptr<Book> curBook = tree->find(k);
			if (curBook == nullptr)
				cout << "Sorry! I don't have book with such title!";
			else 
				curBook->show();
			cout << "\nWould you like to find other book?\n\t0 - no\n\t1 - yes\n\n";
		}
	}
}
