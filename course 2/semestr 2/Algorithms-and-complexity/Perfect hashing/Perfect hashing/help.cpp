#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool check_on_dots(string s)
{
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == ':')
			return true;
	return false;
}

string getAuthor(string s)
{
	int i = 0;
	while (s.length() > i && s[i] != '|')
		++i;
	string s1 = "|";
	++i;
	while (s.length() > i && s[i] != '|')
	{
        if (s[i] == -106)
            s[i] = 45;
		s1 += s[i];
		++i;
	}
	s1 += '|';
	return s1;
}

string getBook(string s)
{
	int i = 0;
	while (s.length() > i && s[i] != '|')
		++i;
	++i;
	while (s.length() > i && s[i] != '|')
		++i;
	++i;
	while (s.length() > i && s[i] != '|')
		++i;
	string s1 = "|";
	++i;
	while (s.length() > i && s[i] != '|')
	{
        if (s[i] == -106)
            s[i] = 45;
		s1 += s[i];
		++i;
	}
	s1 += '|';
	return s1;
}

vector<pair<string, vector<string> > > all;

int main()
{
	ifstream fin("temp_data.txt");
	ofstream fout("Data.txt");
	string s = "1";
	while (getline(fin, s))
	{
		if (check_on_dots(s))
			continue;
		string author = getBook(s), book = getAuthor(s);
		bool ok = false;
		for (int i = 0; i < all.size(); ++i)
			if (all[i].first == author)
			{
				ok = true;
				all[i].second.push_back(book);
				break;
			}
		if (!ok)
		{
			vector<string> temp;
			temp.push_back(book);
			all.push_back({ author, temp });
		}
	}
	sort(all.begin(), all.end());
	fout << "|Library|\n" << all.size() << '\n';
	for (int i = 0; i < all.size(); ++i)
	{
		fout << all[i].first << '\n' << all[i].second.size() << '\n';
		for (int j = 0; j < all[i].second.size(); ++j)
			fout << all[i].second[j] << '\n';
		fout << '\n';
	}
}
