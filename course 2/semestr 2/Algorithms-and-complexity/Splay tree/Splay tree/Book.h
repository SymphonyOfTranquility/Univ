#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Book
{
	string author, title;
	int year, rating;

public:
	Book(ifstream &fin);
	int getRating();
	string getBookName();
	void show();
	~Book();
};
