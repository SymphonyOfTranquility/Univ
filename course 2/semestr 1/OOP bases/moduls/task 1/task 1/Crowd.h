#pragma once
#include "Person.h"
#include "Laws.h"
#include <iostream>
#include <fstream>

using namespace std;

class Crowd
{
	vector<Person> people;
public:
	Crowd();
	Crowd(int n, Laws &law);
	void output(ofstream &fout);
	Crowd who_want_to_be_in_party();
	void add(Person p);
	int msize();
	vector<int> elem_vote_for(int index);
	Person get_person_in_arr(int index);
	Person get_person_number_N(int index);
	int get_own_value(int index);
	void del(int index);
	vector<pair<int,int> > mood(vector<int> cur_laws, Laws law);
	void give_value(int x, Person &person);
	~Crowd();
};

