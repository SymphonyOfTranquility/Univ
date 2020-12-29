#pragma once
#include "Prime_numbers.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Laws
{
private:
	static vector<int> laws;
	static vector<int> time_need_to_adopt; 
public:
	Laws();
	void fill_laws();
	void fill_vote_for_and_against(vector<int> &vote_for, vector<int> &criterion);
	int get_n();
	int get_time(int index);
	void output(ofstream &fout);
	~Laws();
};

