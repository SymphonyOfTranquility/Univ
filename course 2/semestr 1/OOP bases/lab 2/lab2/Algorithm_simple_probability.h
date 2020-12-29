#pragma once
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Algorithm_simple_probability
{
	int number_of_probabilities;
	double expected_value, variance;
	vector<double> probabilities;
	vector<double> events;
	vector<double> tests;

	void count_expected_value();
	void count_variance();
public:
	Algorithm_simple_probability(int n, vector<double> probs, vector<double> values);
	double get_expected_value();
	double get_variance();
	vector<double> get_tests();
	void generate_tests(int number);
	void set_tests(ifstream &fin, int n);
	void output(ofstream &fout);
	~Algorithm_simple_probability();
};

