#include "Laws.h"

vector<int> Laws::laws;
vector<int> Laws::time_need_to_adopt;

Laws::Laws()
{
}


void Laws::fill_laws()
{
	resheto();
	int number = 177;
	for (int i = 0; i < number; ++i)
	{
		time_need_to_adopt.push_back(rand() % 37 + i % 53 + 2);
		laws.push_back((i + time_need_to_adopt[i] + rand()) % 1009 + 5);
	}
}

void Laws::fill_vote_for_and_against(vector<int> &vote_for, vector<int> &criterion)
{
	vote_for.clear();
	criterion.clear();
	for (size_t i = 0; i < laws.size(); ++i)
	{
		criterion.push_back(primes[rand() % primes.size()]);
		int temp = laws[i] % criterion[i];
		if (temp % 2 == rand() % 2)
			vote_for.push_back((int)i);
	}
}

int Laws::get_n()
{
	return laws.size();
}

int Laws::get_time(int index)
{
	return time_need_to_adopt[index];
}

void Laws::output(ofstream &fout)
{
	fout << "----------------------------------LAWS----------------------------------\n";
	for (size_t i = 0; i < laws.size(); ++i)
	{
		fout << "Law #" << i << ": ";
		fout << laws[i] << ", complexity: " << time_need_to_adopt[i] << ";\n";
	}
}



Laws::~Laws()
{
}
