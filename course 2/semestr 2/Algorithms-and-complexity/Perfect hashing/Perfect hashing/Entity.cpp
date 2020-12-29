#include "Entity.h"



Entity::Entity(ifstream &fin, int depth)
{
	name = "";
	while (name == "")
		getline(fin,name);
	name.erase(0, 1);
	name.erase(name.size()-1, 1);
	if (depth < 2) 
	{
		int n;
		fin >> n;
		shared_ptr<Entity> temp;
		for (int i = 0; i < n; ++i)
			entity.push_back(make_shared<Entity>(fin, depth + 1));
	}
}

vector<shared_ptr<Entity>> Entity::getEntities()
{
	return entity;
}

string Entity::getName()
{
	return name;
}

bool Entity::equal(int pos, string s)
{
	string bookName = entity[pos]->getName();
	if (bookName.length() != s.length())
		return false;
	for (int i = 0; i < (int)s.length(); ++i)
		if (s[i] != bookName[i])
			return false;
	return true;
}

shared_ptr<Entity> Entity::getAuthor(int pos)
{
	return entity[pos];
}

void Entity::show()
{
	cout << "There are " << entity.size() << " books.\n";
	for (int i = 0; i < entity.size(); ++i)
		cout << entity[i]->getName() << '\n';
}


Entity::~Entity()
{
}
