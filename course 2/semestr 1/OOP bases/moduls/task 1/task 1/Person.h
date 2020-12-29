#pragma once
#include "Laws.h"
#include <iostream>
#include <fstream>

using namespace std;

class Person
{
protected:
	vector<int> vote_for;
	vector<int> criterion;

	int own_value;
	int strategy_of_voting;
	bool want_to_be_in_party;
	int number_of_party;
	
public:
	Person();
	Person(Laws law, int x);
	bool get_want_to_be();
	int get_strategy_of_voting();
	int get_own_value();
	int get_sum_criterion();
	vector<int> get_vote_for();
	void output(ofstream &fout);
	~Person();
};

