#include "Algorithm_simple_probability.h"



Algorithm_simple_probability::Algorithm_simple_probability(int n, vector<double> probs, vector<double> values) :number_of_probabilities(n), probabilities(probs), events(values)
{
	double counter = 0;
	for (int i = 0; i < probabilities.size(); ++i)
	{
		probabilities[i] /= 100.0;
		counter += probabilities[i];
	}
	count_expected_value();
	count_variance();
}

double Algorithm_simple_probability::get_expected_value()
{
	return expected_value;
}

double Algorithm_simple_probability::get_variance()
{
	return variance;
}

vector<double> Algorithm_simple_probability::get_tests()
{
	return tests;
}

void Algorithm_simple_probability::generate_tests(int number)
{
	tests.clear();
	double temp;
	for (int i = 0; i < number; ++i)
	{
		temp = (double)rand() / (double)RAND_MAX;
		double cur_sum = 0;
		for (int j = 0; j < probabilities.size(); ++j)
		{
			cur_sum += probabilities[j];
			if (cur_sum > temp - 0.0001)
			{
				tests.push_back(events[j]);
				break;
			}
		}
	}
}

void Algorithm_simple_probability::set_tests(ifstream & fin, int n)
{
	double x;
	for (int i = 0; i < n; ++i) {
		fin >> x;
		tests.push_back(x);
	}
}

void Algorithm_simple_probability::output(ofstream & fout)
{
	fout << number_of_probabilities << '\n';
	for (int i = 0; i < probabilities.size(); ++i)
		fout << probabilities[i] << ' ' << events[i] << '\n';
	fout << tests.size() << '\n';
	for (int j = 0; j < tests.size(); ++j)
		fout << tests[j] << ' ';
}

void Algorithm_simple_probability::count_expected_value()
{
	expected_value = 0;
	for (int i = 0; i < probabilities.size(); ++i)
		expected_value += probabilities[i] * events[i];
}

void Algorithm_simple_probability::count_variance()
{
	variance = 0;
	variance = -expected_value*expected_value;
	for (int i = 0; i < probabilities.size(); ++i)
		variance += events[i]*events[i]*probabilities[i];
}


Algorithm_simple_probability::~Algorithm_simple_probability()
{
}
