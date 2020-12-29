#include "CenterOfWork.h"

void MainPart()
{
	vector<shared_ptr<WorkWithWindow> > allWindows;
	string s;
	s = "Data\\Board window.dat";
	shared_ptr<WorkWithWindow> tempWindow = shared_ptr<WorkWithWindow>(new WorkWithWindow(s));

	allWindows.push_back(tempWindow);

	while (allWindows.size())
	{
		for (int i = 0; i < allWindows.size(); ++i)
		{
			allWindows[i].get()->work();
			//int temp = allWindows[i].get()->needNewWindow();
			//if (temp)
			//{
			//	temp_window.reset();
			//	temp_window = shared_ptr<WorkWithWindow>(new WorkWithWindow(s));
			//	//	cout << temp << '\n';
			//	allWindows.push_back(temp_window);
			//}
			if (!allWindows[i].get()->isOpen())
			{
				allWindows[i].reset();
				for (int j = i; j < allWindows.size() - 1; ++j)
					allWindows[j] = move(allWindows[j + 1]);
				allWindows.pop_back();
			}
		}
	}
}