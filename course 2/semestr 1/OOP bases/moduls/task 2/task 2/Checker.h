#pragma once
#include "my_func.h"

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

void out_tabs(int tabs)
{
	for (int i = 0; i < tabs; ++i)
		cout << "	";
}

int calculate_ans(int tabs)
{
	int inp;
	cin >> inp;
	if (inp <= 4) {
		out_tabs(tabs);
		cout << "Input value:\n";
	}
	if(inp != 7)
		out_tabs(tabs);
	if (inp == 1)
	{
		int value;
		cin >> value;
		if (value < 0)
			return RETURN_EXP;
		return my_func(value);
	}
	else if (inp == 2)
	{
		int value;
		cin >> value;
		if (value > 0)
			return RETURN_EXP;
		return my_func(value);
	}
	else if (inp == 3)
	{
		double value;
		cin >> value;
		return my_func(value);
	}
	else if (inp == 4)
	{
		string value;
		cin >> value;
		return my_func(value);
	}
	else if (inp == 5)
	{
		cout << "Input type of pair elements.\n";
		out_tabs(tabs);
		cout << "First element:  ";
		int x = calculate_ans(tabs + 1);
		out_tabs(tabs);
		cout << "Second element:  ";
		return calculate_ans(tabs + 1)*(x + 1) % 541;
	}
	else if (inp == 6)
	{
		cout << "Input the number of elements:\n";
		int n;
		out_tabs(tabs);
		cin >> n;
		int ans = 0;
		for (int i = 0; i < n; ++i)
		{
			out_tabs(tabs);
			cout << "The " << i + 1 << "th element type is:   ";
			ans = (ans + calculate_ans(tabs + 1)) % 741;
		}
		return ans;
	}
	else
		return RETURN_EXP;
}

int demonstration(ifstream &fin, int tabs)
{
	string type;
	fin >> type;
	out_tabs(tabs);
	cout << type << '\n';
	if (type == "positive_number" || type == "negative_number")
	{
		int value;
		fin >> value;
		out_tabs(tabs);
		cout << value << '\n';
		return my_func(value);
	}
	else if (type == "double_number")
	{
		double value;
		fin >> value;
		out_tabs(tabs);
		cout << value << '\n';
		return my_func(value);
	}
	else if (type == "string")
	{
		string value;
		fin >> value;
		out_tabs(tabs);
		cout << value << '\n';
		return my_func(value);
	}
	else if (type == "pair<a,b>")
	{
		out_tabs(tabs);
		cout << "First element:\n";
		int x = demonstration(fin, tabs + 1);
		out_tabs(tabs);
		cout << "Second element:\n";
		return demonstration(fin, tabs + 1)*(x + 1) % 541;
	}
	else if (type == "list")
	{
		int n;
		fin >> n;
		out_tabs(tabs);
		cout << "There are " << n << " elements\n";
		int ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			out_tabs(tabs);
			cout << "The " << i << "th element is:\n";
			ans = (ans + demonstration(fin, tabs + 1)) % 741;
		}
		return ans % 741;
	}
	else {
		return 8941;
	}
}

void checker()
{
	int inp;
	cout << "0 - exit\n1 - input your own values\n2 - input from file\n";
	while (true)
	{
		cin >> inp;
		bool flag = false;
		if (inp == 0)			//exit
		{
			cout << "See you next time\n";
			break;
		}
		else if (inp == 1)	
		{
			cout << "What type of values do you want to add:\n";
			cout << "	1 - positive numbers\n	2 - negative numbers\n	3 - double numbers\n	4 - string\n	5 - pair<a,b>\n	6 - list\n";
			cout << "	7 - else\n";
			cout << "Answer is " << calculate_ans(0) << '\n';
		}
		else if (inp == 2)
		{
			//cout << "--------------------------------Demonstration--------------------------------\n";
			string s;
			s = "Data/0.dat";
			for (int i = 1; i <= 7; ++i)
			{
				cout << "-------------------------------Demonstration " << i << "-------------------------------\n";
				s[5] = i + '0';
				ifstream fin(s);
				cout << "Answer is " << demonstration(fin, 0) << '\n';
				fin.close();
				cout << "\n\n";
			}
		}
	}

}
