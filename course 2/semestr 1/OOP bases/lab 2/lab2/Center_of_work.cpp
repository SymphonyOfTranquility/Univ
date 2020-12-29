#include "Center_of_work.h"
#include <vector>

void main_part()
{
	vector<shared_ptr<Work_with_window> > all_windows;
	string s[3];
	s[0] = "Data\\Main window information.dat";
	s[1] = "Data\\Simple Probability information.dat";
	s[2] = "Data\\Walk on the graph information.dat";
	shared_ptr<Work_with_window> temp_window = shared_ptr<Work_with_window>(new Work_with_window(s[0]));
	all_windows.push_back(temp_window);

	while (all_windows.size())
	{
		for (int i = 0; i < all_windows.size(); ++i)
		{
			all_windows[i].get()->work();
			int temp = all_windows[i].get()->need_new_window();
			if (temp)
			{
				temp_window.reset();
				temp_window = shared_ptr<Work_with_window>(new Work_with_window(s[temp]));
			//	cout << temp << '\n';
				all_windows.push_back(temp_window);
			}
			if (!all_windows[i].get()->is_open())
			{
				all_windows[i].reset();
				for (int j = i; j < all_windows.size() - 1; ++j)
					all_windows[j] = move(all_windows[j + 1]);
				all_windows.pop_back();
			}
		}
	}

}
