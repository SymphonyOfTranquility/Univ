#include "Book.h"


Book::Book(ifstream &fin)
{
	string s = "";
	while (s == "")
		getline(fin, s);
	int i = 1;
	author = "";	//input author
	for (; s[i] != '|'; ++i)
		author += s[i];
	++i;
	while (s[i] != '|') ++i;
	++i;

	title = "";     //input title
	for (; s[i] != '|'; ++i)
		title += s[i];
	++i;
	while (s[i] != '|') ++i;
	++i;

	year = 0;		//input year
	bool dot = false;
	for (; s[i] != '|'; ++i)
	{
		if (s[i] == '.')
		{
			dot = true;
			break;
		}
		year = year * 10 + s[i] - '0';
	}
	if (dot)
		while (s[i] != '|') ++i;
	++i;
	while (s[i] != '|') ++i;
	++i;

	rating = 0;
	for (; s[i] != '|'; ++i)
		rating = rating * 10 + s[i] - '0';
}

int Book::getRating()
{
	return rating;
}

string Book::getBookName()
{
	return title;
}


void Book::show()
{
	cout << "Author: " << author << '\n';
	cout << "Title: " << title << '\n';
	cout << "Released: " << year << '\n';
}

Book::~Book()
{
}
