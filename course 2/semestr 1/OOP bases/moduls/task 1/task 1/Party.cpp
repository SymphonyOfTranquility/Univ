#include "Party.h"



int Party::compare(vector<int> a, vector<int> b)
{
	int counter = 0;
	for (size_t i = 0; i < a.size(); ++i)
	{
		int l = 0, r = (int) b.size();
		while (r - l > 1)
		{
			int mid = (r + l) >> 1;
			if (b[mid] > a[i])
				r = mid;
			else
				l = mid;
		}
		if (a[i] == b[l])
			++counter;
	}
	return counter;
}

int Party::get_own_value()
{
	return own_value;
}

int Party::get_sum_criterion()
{
	int ans = 0;
	for (int i = 0; i < (int)criterion.size(); ++i)
		ans += criterion[i];
	return ans;
}

int Party::get_number_of_members()
{
	return members.msize();
}

vector<int> Party::get_vote_for()
{
	return vote_for;
}

Crowd Party::get_members()
{
	return members;
}

Party::Party()
{
	own_value = -1;
	vote_for.clear();
	criterion.clear();
}

Party::Party(Laws law, int x)
{
	own_value = x;
	law.fill_vote_for_and_against(vote_for,criterion);
}

void Party::add_the_most(Crowd &people, int n)
{
	vector<pair<int, int> > most_usefull;
	most_usefull.clear();
	for (int i = 0; i < people.msize(); ++i)
	{
		int res = compare(people.elem_vote_for(i), vote_for);
		most_usefull.push_back({ res,people.get_own_value(i) });
	}
	sort(most_usefull.begin(), most_usefull.end());
	for (int i = (int)most_usefull.size() - 1; i >= max((int)0, (int)most_usefull.size() - n); --i) {
		members.add(people.get_person_number_N(most_usefull[i].second));
		people.del(most_usefull[i].second);
	}
	
}

void Party::output(ofstream &fout)
{
	fout << "Party #" << own_value << '\n';
	fout << "Members:\n";
	for (int i = 0; i < members.msize(); ++i)
		fout << "\tPerson#" << members.get_person_in_arr(i).get_own_value() << '\n';
	fout << "Vote for:\n";
	for (size_t i = 0; i < vote_for.size(); ++i)
		fout << "\tLaw #" << vote_for[i] << ", Criterion: "  << criterion[vote_for[i]] << ";\n";
}


Party::~Party()
{
}
