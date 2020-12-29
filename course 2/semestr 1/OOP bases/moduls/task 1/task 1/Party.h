#pragma once
#include "Person.h"
#include "Crowd.h"
#include "Laws.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Party
{
protected:
	Crowd members;
	int own_value;

	vector<int> vote_for;
	vector<int> criterion;
public:
	Party();
	Party(Laws law,int x);
	void add_the_most(Crowd &people, int n);
	int compare(vector<int> a, vector<int> b);
	int get_own_value();
	int get_sum_criterion();
	int get_number_of_members();
	vector<int> get_vote_for();
	Crowd get_members();
	void output(ofstream &fout);
	~Party();
};

