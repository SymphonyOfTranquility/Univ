#include "Parlament.h"



Parlament::Parlament(int n, Laws law)
{
	for (int i = 0; i < law.get_n(); ++i)
		if (rand() % primes[rand() % primes.size()] % 3 == 1)
			adopted.push_back(i);
	period = 200;
	number_of_members = (int) (cbrt(n)*cbrt(n));
	part_of_votes = 3;
	how_to_choose_law = rand() % primes[rand() % primes.size()] % 3;
}

void Parlament::election_to_Parlament(All_parties & all_parties, Crowd & people)
{
	vector<pair<int, int> > number_of_votes;
	for (int i = 0; i < all_parties.msize(); ++i)
		number_of_votes.push_back({ 0,all_parties.get_party_in_arr(i).get_own_value() });

	for (int i = 0; i < people.msize(); ++i)
	{
		Person temp_person = people.get_person_in_arr(i);
		int max_person = -1, max_index = -1;
		for (int j = 0; j < all_parties.msize(); ++j) 
		{
			Party temp_party = all_parties.get_party_in_arr(j);
			int cur = temp_party.compare(temp_person.get_vote_for(), temp_party.get_vote_for());
			if (cur > max_person)
			{
				max_person = cur;
				max_index = j;
			}
		}
		++number_of_votes[max_index].first;
	}
	sort(number_of_votes.begin(), number_of_votes.end());
	vector<int> count_members;
	for (int i = 0; i < all_parties.msize(); ++i) 
		count_members.push_back(number_of_votes[i].first*number_of_members / people.msize());
	int counter = 0;
	bool flag = false;
	parties.clear();
	number_of_members_for_each_party.clear();	
	for (int i = (int) count_members.size()-1;i >= 0; --i)
	{
		int k = i - 1;
		while (count_members[i] > number_of_members / part_of_votes && k >= 0)
		{
			++count_members[k];
			--count_members[i];
			--k;
			if (k == -1)
				k = i - 1;
		}
		if (counter + count_members[i] > number_of_members)
		{
			count_members[i] = number_of_members - counter;
			flag = true;
		}
		parties.add(all_parties.get_party_number_N(number_of_votes[i].second));
		number_of_members_for_each_party.push_back({ number_of_votes[i].second,count_members[i] });
		counter += count_members[i];
		if (flag)
			break;
	}
	if (counter < number_of_members)
	{
		int i = 0;
		while (counter < number_of_members)
		{
			if (number_of_members_for_each_party[i].second == number_of_members / part_of_votes) 
			{
				if (i < number_of_members%part_of_votes)
				{
					++number_of_members_for_each_party[i].second;
					++counter;
				}
			}
			else
			{
				++number_of_members_for_each_party[i].second;
				++counter;
			}
			++i;
		}
	}
	main_party = parties.get_party_in_arr(0);
	sort(adopted.begin(), adopted.end());
}

bool Parlament::adopt_law(int cur_law, bool what_do)
{
	int cur_vote_for = 0;
	for (int k = 0; k < parties.msize(); ++k)
	{
		Party cur_party = parties.get_party_in_arr(k);
		Crowd people = cur_party.get_members();
		for (int i = 0; i < number_of_members_for_each_party[k].second; ++i)
		{
			if (people.get_person_in_arr(i).get_strategy_of_voting() == 2)
			{
				if (rand() % primes[rand() % primes.size()] % 2 == rand() % primes[rand() % primes.size()] % 2)
					++cur_vote_for;
			}
			else 
			{
				vector<int> temp;
				if (people.get_person_in_arr(i).get_strategy_of_voting() == 0)
					temp = people.get_person_in_arr(i).get_vote_for();
				else 
					temp = cur_party.get_vote_for();
				for (int j = 0; j < temp.size(); ++j)
					if (temp[j] == cur_law)
					{
						++cur_vote_for;
						break;
					}
			}
		}
	}
	if (cur_vote_for >= part_of_votes && !what_do)
	{
		adopted.push_back(cur_law);
		sort(adopted.begin(), adopted.end());
		return true;
	}
	else if (number_of_members - cur_vote_for >= part_of_votes && what_do)
	{
		int x = 0;
		for (int i = 0; i < adopted.size() - 1; ++i)
		{
			if (adopted[i] == cur_law)
				++x;
			adopted[i] = adopted[i + x];
		}
		if (adopted.size() > 0)
			adopted.pop_back();
		if (adopted.size() > 0)
			sort(adopted.begin(), adopted.end());
		return true;
	}
	else
		return false;
}

int Parlament::get_period()
{
	return period;
}

int Parlament::get_number_of_members()
{
	return number_of_members;
}

int Parlament::get_part_of_votes()
{
	return part_of_votes;
}

int Parlament::get_how_to_choose_law()
{
	return how_to_choose_law;
}

bool Parlament::change_period()
{
	int counter = 0;
	int new_val = 80 + rand() % 300;
	for (int i = 0; i < parties.msize(); ++i)
	{
		Party temp_party = parties.get_party_in_arr(i);
		Crowd temp_crowd = temp_party.get_members();
		int sum = 0;
		for (int j = 0;j < number_of_members_for_each_party[i].first; ++j) 
			sum += temp_crowd.get_person_in_arr(j).get_sum_criterion();
		if (sum % 2 == temp_party.get_sum_criterion() / new_val % 2)
			++counter;
	}
	if (counter > parties.msize() / 3) {
		period = new_val;
		return true;
	}
	else
		return false;
}

bool Parlament::change_part_of_votes()
{
	int counter = 0;
	int new_val = 2 + rand()%(parties.msize()-2);
	for (int i = 0; i < parties.msize(); ++i)
	{
		Party temp_party = parties.get_party_in_arr(i);
		Crowd temp_crowd = temp_party.get_members();
		int sum = 0;
		for (int j = 0; j < number_of_members_for_each_party[i].first; ++j)
			sum += temp_crowd.get_person_in_arr(j).get_sum_criterion();
		if ((sum / temp_party.get_sum_criterion() + new_val)  % 2)
			++counter;
	}
	if (counter > parties.msize() / 3) {
		part_of_votes = new_val;
		return true;
	}
	else return false;
}

bool Parlament::change_number_of_members(int num)
{
	int counter = 0;
	int new_val = (int)min(cbrt(num)*sqrt(cbrt(num)) + rand()%10,sqrt(num)*sqrt(cbrt(num)));
	for (int i = 0; i < parties.msize(); ++i)
	{
		Party temp_party = parties.get_party_in_arr(i);
		Crowd temp_crowd = temp_party.get_members();
		int sum = 0;
		for (int j = 0; j < number_of_members_for_each_party[i].first; ++j)
			sum += temp_crowd.get_person_in_arr(j).get_sum_criterion();
		if ((sum + temp_party.get_sum_criterion()) / new_val % 2)
			++counter;
	}
	if (counter > parties.msize() / 3) {
		number_of_members = new_val;
		return true;
	}
	else
		return false;
}

Party Parlament::get_main_party()
{
	return main_party;
}

vector<int> Parlament::get_adopted()
{
	return adopted;
}

All_parties Parlament::get_parties()
{
	return parties;
}

void Parlament::output()
{
	cout << "Number of parties: " << parties.msize() << '\n';
	cout << "Number of members: " << number_of_members << '\n';
	for (int i = 0; i < parties.msize(); ++i)
	{
		cout << "\tParty #" << number_of_members_for_each_party[i].first << ", " << number_of_members_for_each_party[i].second << '\n';
	}
	cout << "Main party:\n";
	cout << "\tParty #" << main_party.get_own_value() << '\n';
	cout << "Adopted laws:\n";
	for (int i = 0; i < adopted.size(); ++i)
		cout << adopted[i] << ", ";
	cout << '\n';

}


Parlament::~Parlament()
{
}
