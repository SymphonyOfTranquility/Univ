#include "Demonstration.h"

void demostration()
{
	ifstream fin("Data.txt");
	shared_ptr<Entity> library = make_shared<Entity>(fin);
	fin.close();

	shared_ptr<Graph> graph;
	vector<int> authorHashFunction, bookHashFunction;
	shared_ptr<Entity> curAuthor;
	int authorHashSsid, bookHashSsid;
	bool isBook = false, isAuthor = false;
	int authorsPos = -1;
	cout << "0 - exit\n1 - find Author\n";
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
			isBook = false; isAuthor = true;
			cout << "Input full name of author:\n";
			string authorName = "";
			while (authorName == "")
				getline(cin,authorName);
			if (authorHashFunction.empty())
			{
				graph = make_shared<Graph>(library->getEntities());
				authorHashFunction = graph->getGValues();
				authorHashSsid = graph->getSsid();
				graph.reset();
			}
			int needHash1 = firstHash(authorName, authorHashSsid);
			int needHash2 = secondHash(authorName, authorHashSsid);
			authorsPos = authorHashFunction[needHash1] + authorHashFunction[needHash2];
			if (library->equal(authorsPos, authorName))
			{
				curAuthor = library->getAuthor(authorsPos);
				cout << "\nYEAH! This author excists in my library!\n";
				cout << "Would you like to find some of his books?\n\t1 - continue to find author\n\t2 - find a book\n\t3 - show all books\n";
			}
			else 
			{
				cout << "\nSorry! This author doesn't exists in my library.\n";
				cout << "\t1 - find Author\n";
			}
		}
		else if (inp == 2 && (isAuthor || isBook) )			//find book
		{
			if (isAuthor)
				bookHashFunction.clear();
			isBook = true; isAuthor = false;
			cout << "Input full title of book:\n";
			string bookTitle = "";
			while (bookTitle == "")
				getline(cin, bookTitle);
			if (bookHashFunction.empty())
			{
				graph = make_shared<Graph>(curAuthor->getEntities());
				bookHashFunction = graph->getGValues();
				bookHashSsid = graph->getSsid();
				graph.reset();
			}
			int needHash1 = firstHash(bookTitle, bookHashSsid);
			int needHash2 = secondHash(bookTitle, bookHashSsid);
			int curNameHash = bookHashFunction[needHash1] + bookHashFunction[needHash2];
			if (curAuthor->equal(curNameHash, bookTitle))
				cout << "\nYEAH! This book excists in my library!\n";
			else
				cout << "Sorry! This book doesn't exists in my library.\n";
			cout << "Would you like to find another book of this author?\n\t1 - find new author\n\t2 - find other book\n3 - show all books\n";
		}
		else if (inp == 3)
		{
			if (curAuthor != nullptr)
				curAuthor->show();
		}
	}
}
