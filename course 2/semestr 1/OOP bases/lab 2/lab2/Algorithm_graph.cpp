#include "Algorithm_graph.h"

Algorithm_graph::Algorithm_graph(vector<pair<int, int> > &edges, int n)
{
	graph_size = n;
	next_vertex = last_vertex = 1;
	for (int i = 0; i <= graph_size; ++i)
	{
		vertex[i].clear();
	}
	for (int i = 0; i < edges.size(); ++i) {
		Tedge e(edges[i].second, i, -1.0);
		vertex[edges[i].first].push_back(e);
	}
	/*for (int i = 1; i <= graph_size; ++i)
	{
		for (int j = 0; j < vertex[i].size(); ++j)
			cout << i << "->" << vertex[i][j].to << ' ' << vertex[i][j].number << ' ' << vertex[i][j].val << '\n';
	}*/
}

vector<pair<int, double> > Algorithm_graph::get_last_values()
{
	vector<pair<int, double> > ans;
	for (int i = 1; i <= graph_size; ++i)
	{
		bool ok = true;
		double counter = 0;
		for (int j = 0; j < (int)vertex[i].size()-1; ++j)
		{
			if (vertex[i][j].val == -1) {
				ok = false;
				break;
			}
			counter += vertex[i][j].val;
		}
		if (ok && vertex[i].size() > 0) {
			vertex[i][vertex[i].size() - 1].val = 100.0 - counter;
			ans.push_back({ vertex[i][vertex[i].size() - 1].number,vertex[i][vertex[i].size()-1].val });
		}
		else if (!ok && vertex[i].size() > 0)
			vertex[i][vertex[i].size() - 1].val = -1;
	}
	return ans;
}

void Algorithm_graph::give_value(int index, double val)
{
	for (int i = 1; i <= graph_size; ++i)
	{
		for (int j = 0; j < vertex[i].size(); ++j)
		{
			if (vertex[i][j].number == index)
			{
				if (j != vertex[i].size() - 1)
				{
					bool ok = true;
					double counter = 0;
					if (val != -1) {
						for (int k = 0; k < j; ++k)
						{
							if (vertex[i][k].val != -1)
								counter += vertex[i][k].val;
						}
						if (counter + val > 100.001f)
							ok = false;
					}
					//cout << index << ' ' << counter << ' ' << val << ' ' << vertex[i][j].val << '\n';
					if (ok)
						vertex[i][j].val = val;
					else if (vertex[i][j].val != -1 && counter + vertex[i][j].val > 100.001f)
						vertex[i][j].val = -1;

				}
				break;	
			}
		}
	}
}

vector<int> Algorithm_graph::need_to_clear()
{
	vector<int> ans;
	for (int i = 1; i <= graph_size; ++i)
	{
		for (int j = 0; j < vertex[i].size(); ++j)
		{
			if (vertex[i][j].val == -1)
				ans.push_back(vertex[i][j].number);
		}
	}
	return ans;
}

int Algorithm_graph::get_size()
{
	return graph_size;
}

bool Algorithm_graph::check_fields_non_negative(double val, int edge)
{
	int which_line = -1;
	for (int i = 1; i <= graph_size; ++i)
	{
		for (int j = 0; j < (int)vertex[i].size(); ++j)
		{
			if (vertex[i][j].number == edge)
			{
				which_line = i;
				break;
			}
		}
		if (which_line != -1)
			break;
	}
	double counter = 0;
	for (int j = 0; j < (int)vertex[which_line].size()-1; ++j)
	{
		if (vertex[which_line][j].val > 0)
		{
			if (vertex[which_line][j].number == edge)
				counter += val;
			else
				counter += vertex[which_line][j].val;
		}
	}
	if (100.0 - counter < -0.000001)
		return false;
	else
		return true;
}

vector<pair<int, int> > Algorithm_graph::get_all_edges()
{
	vector<pair<int, int> > temp;
	for (int i = 1;i <= graph_size; ++i)
	{ 
		for (int j = 0; j < vertex[i].size(); ++j)
			temp.push_back({ i,vertex[i][j].to });
	}
	return temp;
}

int Algorithm_graph::get_next_vertex()
{
	float x = (float)rand()/(float)RAND_MAX*100.f;
	last_vertex = next_vertex;
	float counter = 0;
	bool ok = false;
	for (int i = 0; i < vertex[last_vertex].size(); ++i) {
		counter += vertex[last_vertex][i].val;
		if (counter - x >= -0.0001) {
			next_vertex = vertex[last_vertex][i].to;
			ok = true;
			break;
		}
	}
	if (vertex[last_vertex].size() == 0)
		return -1;
	if (!ok)
		next_vertex = vertex[last_vertex][vertex[last_vertex].size() - 1].to;
	return next_vertex;
}

void Algorithm_graph::restart()
{
	last_vertex = next_vertex = 1;
}

int Algorithm_graph::find_edge(int from, int to)
{
	int k = 0;
	for (int i = 1; i <= graph_size; ++i)
	{
		if (i == from) {
			for (int j = 0; j < vertex[i].size(); ++j)
				if (vertex[i][j].to == to)
					return k;
				else
					++k;
		}
		else 
			k += (int)vertex[i].size();
	}
	return -1;
}

Algorithm_graph::~Algorithm_graph()
{
}

Tedge::Tedge(int to, int number, double val) :to(to), number(number), val(val)
{

}