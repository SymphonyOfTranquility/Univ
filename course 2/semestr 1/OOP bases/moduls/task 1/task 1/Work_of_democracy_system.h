#pragma once
#include "Laws.h"
#include "Person.h"
#include "Crowd.h"
#include "Party.h"
#include "All_parties.h"
#include "Parlament.h"

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void change_mind_of_people(Crowd &people, All_parties &parties, Laws &law)
{
	for (int i = 0; i < people.msize(); ++i)
	{
		if (rand() % primes[rand() % primes.size()] % 10 < 3)
		{
			Person temp(law,people.get_person_in_arr(i).get_own_value());
			people.give_value(i, temp);
		}
	}

	Crowd want_to_vote = people.who_want_to_be_in_party();

	for (int i = 0; i < parties.msize(); ++i)
	{
		if (rand() % primes[rand() % primes.size()] % 100 < 20)
		{
			Party temp(law, parties.get_party_in_arr(i).get_own_value());
			temp.add_the_most(want_to_vote, (int)sqrt(people.msize()));
			parties.give_value(i, temp);
		}
	}
}

void work()
{
	srand((unsigned int) time(NULL));
	Laws law;
	law.fill_laws();
	int ALL_NUM = 200;
	Crowd people(ALL_NUM, law);
	Crowd will_be_in_party = people.who_want_to_be_in_party();
	cout << "Current values are in file \"All_current_data.txt\"\n";
	ofstream fout("All_current_data.txt");
	law.output(fout);
	people.output(fout);
	All_parties parties((int)cbrt(ALL_NUM), law, will_be_in_party, ALL_NUM);
	parties.output(fout);
	Parlament parlament(ALL_NUM, law);
	int start_time = 0, end_time = 2000;
	cout << "There are " << ALL_NUM << " people.\n";
	cout << "There are " << law.get_n() << " laws.\n";
	cout << "There are " << parties.msize() << " parties.\n";

	vector<pair<int, int>> mood = people.mood(parlament.get_adopted(),law);
	cout << "----------------------Over all mood of people----------------------\n";
	sort(mood.begin(), mood.end());
	for (int i = 0; i < mood.size(); ++i)
		cout << "Person #" << mood[i].second << " mood: " << mood[i].first << '\n';
	while (start_time < end_time)
	{
		cout << "----------------------ELECTIONS!!! ELECTIONS!!!-----------------------\n";
		parlament.election_to_Parlament(parties, people);
		cout << "Current parlament is:\n";
		parlament.output();
		int time_left = parlament.get_period();
		vector<int> adopted_laws = parlament.get_adopted();
		vector<int> main_party_vote_for = parlament.get_main_party().get_vote_for();
		All_parties cur_parl = parlament.get_parties();
		cout << "\nIt's time to cancel or adopt some laws))))\n";
		while (time_left > 0)
		{
			if (rand() % primes[rand() % primes.size()] % 100 < 6)
			{
				cout << "We are going to change a PERIOD of work.\n";
				if (parlament.change_period())
					cout << "Now it is" << parlament.get_period() << '\n';
				else
					cout << "It haven't been accepted";
				time_left -= law.get_time(rand() % law.get_n());
			}
			if (rand() % primes[rand() % primes.size()] % 100 < 6)
			{
				cout << "We are going to change the PART OF VOTES that can accept a law\n";
				if (parlament.change_part_of_votes())
					cout << "Now it have to be" << parlament.get_part_of_votes() << " to accept a law.\n";
				else
					cout << "It haven't been accepted";
				time_left -= law.get_time(rand() % law.get_n());
			}
			if (rand() % primes[rand() % primes.size()] % 100 < 6)
			{
				cout << "We are going to change the NUMBER OF MEMBERS in parlament.\n";
				if (parlament.change_number_of_members(ALL_NUM)) {
					cout << "Now there are " << parlament.get_number_of_members() << " members in government.\n";
					break;
				}
				else
					cout << "It haven't been accepted";
				time_left -= law.get_time(rand()%law.get_n());
			}
			int how_vote = rand() % 3;
			adopted_laws = parlament.get_adopted();
			if (how_vote == 0)
			{
				bool flag = true, can_be_adopted = false, help = false;
				int rand_law;
				int counter = 0;
				while (flag)
				{
					++counter;
					if (counter > 10000)
					{
						rand_law = -1;
						break;
					}
					flag = false;
					rand_law = rand() % law.get_n();
					bool is_adopted = false;
					for (int i = 0; i < adopted_laws.size(); ++i)
						if (adopted_laws[i] == rand_law)
						{
							is_adopted = true;
							break;
						}
					for (int i = 0; i < main_party_vote_for.size(); ++i)
						if (main_party_vote_for[i] == rand_law)
						{
							if (is_adopted)
								flag = true;
							else
								can_be_adopted = true;
							break;
						}
					if (!flag && is_adopted)
						can_be_adopted = help = true;
					else
						flag = true;
				}
				if (rand_law == -1)
					break;
				time_left -= law.get_time(rand_law);
				if (help)
					cout << "Party #" << parlament.get_main_party().get_own_value() << " offered to CANCEL the law #" << rand_law << '\n';
				else
					cout << "Party #" << parlament.get_main_party().get_own_value() << " offered to ADOPT the law #" << rand_law << '\n';

				if (parlament.adopt_law(rand_law, help))
					cout << "YEAH! This decision is ACCECPTED\n";
				else
					cout << "Sorry but most are AGAINST this decision\n";
			}
			else if (how_vote == 1)
			{
				int need_to_adopt = -1;
				bool flag = false;
				for (int i = 0; i < cur_parl.msize() && !flag; ++i)
				{
					vector<int> temp = cur_parl.get_party_in_arr(i).get_vote_for();
					for (int j = 0; j < temp.size(); ++j)
					{
						int l = 0, r = (int) adopted_laws.size();
						while (r - l > 1)
						{
							int mid = (r + l) >> 1;
							if (adopted_laws[mid] > temp[j])
								r = mid;
							else
								l = mid;
						}
						if (temp[j] != adopted_laws[l])
						{
							need_to_adopt = temp[j];
							flag = true;
							break;
						}
					}
				}
				if (need_to_adopt == -1)
					break;
				cout << "Party #" << parlament.get_main_party().get_own_value() << " offered to ADOPT the law #" << need_to_adopt << '\n';

				if (parlament.adopt_law(need_to_adopt, 0))
					cout << "YEAH! This decision is ACCECPTED\n";
				else
					cout << "Sorry but most are AGAINST this decision\n";
				time_left = law.get_time(need_to_adopt);
			}
			else
			{
				int need_to_adopt = -1; 
				bool flag = false;
				for (int i = 0; i < adopted_laws.size() && !flag; ++i)
				{
					for (int k = 0; k < cur_parl.msize() && !flag; ++k) 
					{
						vector<int> temp = cur_parl.get_party_in_arr(k).get_vote_for();
						bool temp_fl = true;
						for (int j = 0; j < temp.size(); ++j)
						{
							if (temp[j] == adopted_laws[i])
							{
								temp_fl = false;
								break;
							}
						}
						if (temp_fl)
						{
							need_to_adopt = adopted_laws[i];
							flag = true;
						}
					}
				}
				if (need_to_adopt == -1)
					break;
				cout << "Party #" << parlament.get_main_party().get_own_value() << " offered to CANCEL the law #" << need_to_adopt << '\n';

				if (parlament.adopt_law(need_to_adopt, 1))
					cout << "YEAH! This decision is ACCECPTED\n";
				else
					cout << "Sorry but most are AGAINST this decision\n";
				time_left = law.get_time(need_to_adopt);
			}
		}
		start_time += parlament.get_period();
		change_mind_of_people(people, parties, law);
	}
	mood = people.mood(parlament.get_adopted(),law);
	cout << "---------------------Over all mood of people-------------------\n";
	sort(mood.begin(), mood.end());
	for (int i = 0; i < mood.size(); ++i)
		cout << "Person #" << mood[i].second << " mood: " << mood[i].first << '\n';
	system("pause");
}