#pragma once
#include "Party.h"
#include "All_parties.h"
#include "Crowd.h"
#include "Laws.h"

class Parlament 
{
protected:
	All_parties parties;
	vector<pair<int,int> > number_of_members_for_each_party;
	Party main_party;

	vector<pair<int, int> > need_to_adopt;
	vector<int> adopted;
	vector<int> need_to_change;

	int period;
	int number_of_members;
	int how_to_choose_law;
	int part_of_votes;


public:
	Parlament(int n, Laws law);
	void election_to_Parlament(All_parties &all_parties, Crowd &people);
	bool adopt_law(int cur_law, bool what_do);
	int get_period();
	int get_number_of_members();
	int get_part_of_votes();
	int get_how_to_choose_law();
	bool change_period();
	bool change_part_of_votes();
	bool change_number_of_members(int num);
	Party get_main_party();
	vector<int> get_adopted();
	All_parties get_parties();
	void output();
	~Parlament();
};

