#pragma once
#include "Party.h"
#include "Laws.h"
#include "Crowd.h"

#include <iostream>
#include <fstream>

using namespace std;

class All_parties
{
	vector<Party> parties;
public:
	All_parties();
	All_parties(int n, Laws &law, Crowd people, int number_of_all_people);
	int msize();
	Party get_party_in_arr(int index);
	Party get_party_number_N(int index);
	void add(Party temp);
	void output(ofstream &fout);
	void clear();
	void give_value(int x,Party &party);
	~All_parties();
};

