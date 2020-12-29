#pragma once
#include "Base1.h"
#include "Base2.h"
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Delta.h"
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
bool dfs_to_add_help_bases(shared_ptr<T> &cur,const int &num,const int &where,const int &what)
{
	if (cur.get() == nullptr || cur.get()->get_n() > num)
		return false;
	int cur_type = 1;
	if (typeid(*cur.get()) == typeid(Beta))
		cur_type = 2;
	else if (typeid(*cur.get()) == typeid(Gamma))
		cur_type = 3;
	else if(typeid(*cur.get()) == typeid(Delta))
		cur_type = 4;

	if (num == cur.get()->get_n() && cur_type == where)
	{
		if (!cur.get()->check_val_base1() && what <= 2)
		{
			if (what == 1)
			{
				shared_ptr<Base1> temp = shared_ptr<Base1>(new Alpha);
				cur.get()->add_base1(temp);
			}
			else
			{
				shared_ptr<Base1> temp = shared_ptr<Base1>(new Beta);
				cur.get()->add_base1(temp);
			}
			return true;
		}
		else if (!cur.get()->check_x_val_base2() && what > 2 && what % 2 == 1)
		{
			if (what == 3)
			{
				shared_ptr<Base2> temp = shared_ptr<Base2>(new Gamma);
				cur.get()->add_base2(temp, 0);
			}
			else
			{
				shared_ptr<Base2> temp = shared_ptr<Base2>(new Delta);
				cur.get()->add_base2(temp, 0);
			}
			return true;
		}
		else if (!cur.get()->check_x_val_base2() && what > 2 && what % 2 == 0)
		{
			if (what == 4)
			{
				shared_ptr<Base2> temp = shared_ptr<Base2>(new Gamma);
				cur.get()->add_base2(temp, 0);
			}
			else
			{
				shared_ptr<Base2> temp = shared_ptr<Base2>(new Delta);
				cur.get()->add_base2(temp, 0);
			}
			return true;
		}
	}
	shared_ptr<Base1> value_base1 = cur.get()->get_val_base1();
	shared_ptr<Base2> x_base2 = cur.get()->get_x_val_base2();
	shared_ptr<Base2> y_base2 = cur.get()->get_y_val_base2();
	bool res = dfs_to_add_help_bases(value_base1, num, where, what);
	res = res || dfs_to_add_help_bases(x_base2, num, where, what);
	res = res || dfs_to_add_help_bases(y_base2, num, where, what);
	value_base1.reset();
	x_base2.reset();
	y_base2.reset();
	return res;
}

bool dfs_to_add(vector<pair<shared_ptr<Base1>,int> > &temp_base1, vector<pair<shared_ptr<Base2>, int> > &temp_base2, int num, int where, int what)
{
	for (int i = 0; i < temp_base1.size(); ++i)
	{
		if (dfs_to_add_help_bases(temp_base1[i].first, num, where, what))
			return true;
	}
	for (int i = 0; i < temp_base2.size(); ++i)
	{
		if (dfs_to_add_help_bases(temp_base2[i].first, num, where, what))
			return true;
	}
	return false;
}

template<typename T>
bool bin_search(vector<pair<shared_ptr<T>, int> > &cur, int val)
{
	if (cur.empty() || val < cur[0].second)
		return 0;
	size_t m_left = 0, m_right = cur.size();
	while (m_right - m_left > 1)
	{
		size_t mid = (m_left + m_right) / 2;
		if (cur[mid].second > val)
			m_right = mid;
		else
			m_left = mid;
	}
	if (cur[m_left].second == val) 
	{
		cur[m_left].first.reset();
		return true;
	}
	return false;
}

template <typename T>
void shift(vector<pair<shared_ptr<T>, int> > &cur, int val)
{
	bool flag = false;
	for (int i = 0; i < cur.size(); ++i)
	{
		if (cur[i].first.get() == nullptr)
			flag = true;
		else {
			if (cur[i].second > val)
				--cur[i].second;
			if (flag) {
				cur[i - 1].second = cur[i].second;
				cur[i - 1].first = move(cur[i].first);
			}
		}
	}
	if (flag)
		cur.pop_back();
}

template <typename T>
int dfs_to_delete(shared_ptr<T> &cur, int counter)
{
	if (cur.get() == nullptr)
		return counter;
	if (typeid(*cur.get()) == typeid(Alpha))
		counter = counter - 2 * cur.get()->get_n() + 14;
	else if (typeid(*cur.get()) == typeid(Beta))
		counter = counter - cur.get()->get_n();
	else if (typeid(*cur.get()) == typeid(Gamma))
		counter = counter - cur.get()->get_n();
	else if (typeid(*cur.get()) == typeid(Delta))
		counter = counter + 3 * cur.get()->get_n() - 41;
	shared_ptr<Base2> temp_b2 = cur.get()->get_x_val_base2();
	counter = dfs_to_delete(temp_b2, counter);
	temp_b2.reset();
	temp_b2 = cur.get()->get_y_val_base2();
	counter = dfs_to_delete(temp_b2, counter);
	shared_ptr<Base1> temp_b1 = cur.get()->get_val_base1();
	counter = dfs_to_delete(temp_b1, counter);
	temp_b2.reset(); temp_b1.reset();
	if (typeid(*cur.get()) == typeid(Alpha) || typeid(*cur.get()) == typeid(Beta))
		counter = 3 * counter + cur.get()->get_n() + 41;
 	else if (typeid(*cur.get()) == typeid(Gamma) || typeid(*cur.get()) == typeid(Delta))
		counter = counter / 2 - cur.get()->get_n();
	return counter;
}

void checker()
{
	int inp, n = 1;
	vector<pair<shared_ptr<Base1>,int> > temp_base1;
	vector<pair<shared_ptr<Base2>,int> > temp_base2;
	cout << "0 - exit\n1 - add Base1 to vector\n2 - add Base2 to vector\n3 - add to Class(Alpha, Beta, Gamma or Delta) instance with number N\n";
	cout << "4 - delete an element from vector\n5 - show what S would be if we would delete all elements\n";///\n6 - all combinations of M elements\n";
	while (true) 
	{
		cin >> inp;
		bool flag = false;
		if (inp == 0)			//exit
		{
			cout << "See you next time\n";
			break;
		}	 
		else if (inp == 1)	//input in vector Base1
		{
			cout << "What do you want to add:\n   1 - Alpha\n   2 - Beta\n";
			flag = false;
			do 
			{
				if (flag)
					cout << "Input please 1 or 2\n";
				cin >> inp;
				flag = true;
			} while (inp > 2 || inp <= 0);  //input what'
			shared_ptr<Base1> temp;
			if (inp == 1) 
			{ 
				temp = shared_ptr<Base1>(new Alpha);
				temp_base1.push_back({ temp,n });
				temp.reset();
			}
			else 
			{
				temp = shared_ptr<Base1>(new Beta);
				temp_base1.push_back({ temp,n });
				temp.reset();
			}
			++n;
			cout << "An element was added to vector\n";
		}
		else if (inp == 2)		//input in vector Base2
		{
			cout << "What do you want to add:\n   1 - Gamma\n   2 - Delta\n";
			flag = false;
			do
			{
				if (flag)
					cout << "Input please 1 or 2\n";
				cin >> inp;
				flag = true;
			} while (inp > 2 || inp <= 0);	// what input
			shared_ptr<Base2> temp;
			if (inp == 1) 
			{
				temp = shared_ptr<Base2>(new Gamma);
				temp_base2.push_back({ temp,n });
				temp.reset();
			}
			else 
			{
				temp = shared_ptr<Base2>(new Delta);
				temp_base2.push_back({ temp,n });
				temp.reset();
			}
			++n;
			cout << "An element was added to vector\n";
		}
		else if (inp == 3)		//input in Base1 or Base2 in element N;
		{
			int what;
			cout << "Input to which type of data do you want to add:\n";
			cout << "   1 - Alpha\n   2 - Beta\n   3 - Gamma\n   4 - Delta\n";
			flag = false;
			do
			{
				if (flag)
					cout << "Input please 1, 2, 3 or 4\n";
				cin >> what;
				flag = true;
			} while (inp > 4 || inp <= 0);  //input what
			cout << "Input the number where we have to add\n";
			cin >> inp;								  //input number
			int num = inp;
			cout << "Input what type of data do you want to add:\n";
			cout << "   1 - Alpha\n   2 - Beta\n   3 - Gamma\n   4 - Delta\n";
			flag = false;
			do
			{
				if (flag)
					cout << "Input please 1, 2, 3 or 4\n";
				cin >> inp;
				flag = true;
			} while (inp > 4 || inp <= 0);  //input where
			if (inp == 4)
				++inp;
			if (inp > 2)
			{
				int a;
				cout << "Input where in Base2(x,y) you want to add:\n   0 - x,\n   1 - y\n";
				flag = false;
				do 
				{
					if (flag)
						cout << "Input please 1 or 2\n";
					cin >> a;
					flag = true;
				} while (a > 1 || a < 0);	  //input sub_where
				inp += a;
			}
			if (dfs_to_add(temp_base1, temp_base2, num, what, inp))
				cout << "An element was added\n";
			else
				cout << "There were some trubles like n was more than maxindex of class or position was filled with other object\n";
		}
		else if (inp == 4)		//delete an element
		{
			if (n == 1)
			{
				cout << "Vector is empty! Add something please.\n";
				continue;
			}
			cout << "What number of vector element do you want delete?\n";
			do
			{
				cout << "Number have to be less than " << n << '\n';
				cin >> inp;
			} while (inp >= n);  //input the number;
			if (!bin_search(temp_base1, inp))	//bin_search of an element
				bin_search(temp_base2, inp);
			shift(temp_base1, inp);			//shift of vector
			shift(temp_base2, inp);			//shift of vector
			--n;
			cout << "An element was deleted\n";
			cout << "Current S is " << S << '\n';
		}
		else if (inp == 5)		//prediction of S
		{
			cout << "current value of S = " << S << '\n';
			int counter = S;
			for (int i = 1, ind1 = 0, ind2 = 0; i < n; ++i)
			{
				if (ind1 < temp_base1.size() && temp_base1[ind1].second == i)
				{
					counter = dfs_to_delete(temp_base1[ind1].first, counter);
					++ind1;
				}
				else if (ind2 < temp_base1.size() && temp_base2[ind2].second == i) {
					counter = dfs_to_delete(temp_base2[ind2].first, counter);
					++ind2;
				}

			}
			cout << "Future count of S = " << counter << '\n';
		}
	}

	for (size_t i = 0; i < temp_base1.size(); ++i)
		temp_base1[i].first.reset();
	for (size_t i = 0; i < temp_base2.size(); ++i)
		temp_base2[i].first.reset();
}
