#include "Person.h"



Person::Person()
{
	own_value = -1;
	strategy_of_voting = want_to_be_in_party = number_of_party = 0;
	vote_for.clear();
	criterion.clear();
}

Person::Person(Laws law,int x)
{
	own_value = x;
	law.fill_vote_for_and_against(vote_for,criterion);
	int index = rand() % primes.size();
	strategy_of_voting = rand() % primes[index] % 3;
	index = rand() % primes.size();
	want_to_be_in_party = rand() % primes[index] % 2;
	number_of_party = -1;
}

bool Person::get_want_to_be()
{
	return want_to_be_in_party;
}

int Person::get_strategy_of_voting()
{
	return strategy_of_voting;
}

int Person::get_own_value()
{
	return own_value;
}

int Person::get_sum_criterion()
{
	int ans = 0;
	for (int i = 0; i < (int)criterion.size(); ++i)
		ans += criterion[i];
	return ans;
}

vector<int> Person::get_vote_for()
{
	return vote_for;
}

void Person::output(ofstream &fout)
{
	fout << "Wants to be in party: " << want_to_be_in_party << '\n';
	fout << "Strategy of voting: " << (strategy_of_voting == 2 ? "random" : (strategy_of_voting == 1 ? "own_voting" : "party_voting")) << '\n';
	fout << "Votes for:\n";
	for (size_t i = 0; i < vote_for.size(); ++i)
		fout << "\tLaw #" << vote_for[i] << " Criterion: " <<  criterion[vote_for[i]] << ";\n";
}


Person::~Person()
{
}
