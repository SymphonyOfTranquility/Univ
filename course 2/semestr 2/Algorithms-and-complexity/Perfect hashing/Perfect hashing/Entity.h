#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Entity
{
	string name;
	vector<shared_ptr<Entity> > entity;

public:
	Entity(ifstream &fin, int depth = 0);
	vector<shared_ptr<Entity> > getEntities();
	string getName();
	bool equal(int pos, string s); 
	shared_ptr<Entity> getAuthor(int pos);
	void show();
	~Entity();
};

