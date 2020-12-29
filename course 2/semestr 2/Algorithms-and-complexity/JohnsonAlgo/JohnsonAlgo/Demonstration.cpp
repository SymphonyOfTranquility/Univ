#include "Demonstration.h"

void demonstration()
{
	ifstream fin("data.txt");
	int n;
	vector<shared_ptr<Book> > library;
	fin >> n;
	n = 7;
	for (int i = 0; i < n; ++i)
		library.push_back(make_shared<Book>(fin));
	fin.close();

	shared_ptr<Graph> graph = make_shared<Graph>();
	graph->build(library);
	graph->show();
	if (!graph->johnsonAlgo())
		cout << "The input graph has a negative weight cycle\n";
	else
		graph->showDistances();

	graph->outputFile("output.txt");
	system("pause");

	//if (n <= 20)
	//	heap->show();
	/*cout << "0 - exit\n1 - show first book in alphabetical order in heap\n2 - extract first book in alpabetical order from heap\n3 - show tree\n";
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
			shared_ptr<Book> curBook = heap->top();
			if (curBook == nullptr)
				cout << "Sorry! Tree is empty\n";
			else
				curBook->show();
			cout << "\n\n1 - show first book in alphabetical order in heap\n2 - extract first book in alpabetical order from heap\n3 - show tree\n";
		}
		else if (inp == 2)
		{
			heap->pop();
			cout << "Deleted\n\n1 - show first book in alphabetical order in heap\n2 - extract first book in alpabetical order from heap\n3 - show tree\n";
		}
		else if (inp == 3) 
		{
			heap->show();
			cout << "\n\n1 - show first book in alphabetical order in heap\n2 - extract first book in alpabetical order from heap\n3 - show tree\n";
		}
	}*/
}
