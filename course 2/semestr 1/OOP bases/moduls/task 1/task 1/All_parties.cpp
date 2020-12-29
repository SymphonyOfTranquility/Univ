#include "All_parties.h"



All_parties::All_parties()
{
}

All_parties::All_parties(int n, Laws &law, Crowd people, int number_of_all_people)
{
	for (int i = 0; i < n; ++i)
	{
		Party temp(law, i);
		temp.add_the_most(people, (int) sqrt(number_of_all_people));
		parties.push_back(temp);
	}
}

int All_parties::msize()
{
	return (int)parties.size();
}

Party All_parties::get_party_in_arr(int index)
{
	return parties[index];
}

Party All_parties::get_party_number_N(int index)
{
	for (int i = 0; i < parties.size(); ++i)
		if (parties[i].get_own_value() == index)
			return parties[i];
	Party temp;
	return temp;
}

void All_parties::add(Party temp)
{
	parties.push_back(temp);
}

void All_parties::output(ofstream &fout)
{
	fout << "--------------------------------PARTIES--------------------------------\n";
	for (size_t i = 0; i < parties.size(); ++i)
		parties[i].output(fout);
}

void All_parties::clear()
{
	parties.clear();
}

void All_parties::give_value(int x, Party & party)
{
	parties[x] = party;
}


All_parties::~All_parties()
{
}
