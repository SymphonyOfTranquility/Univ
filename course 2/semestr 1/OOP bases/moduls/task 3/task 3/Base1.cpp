#include "Base1.h"

int Base1::alpha_size = 1;
int Base1::beta_size = 1;

Base1::Base1()
{
}

int Base1::get_n()
{
	return N;
}

shared_ptr<Base1> Base1::get_val_base1()
{
	return val_base1;
}

shared_ptr<Base2> Base1::get_x_val_base2()
{
	return x_val_base2;
}

shared_ptr<Base2> Base1::get_y_val_base2()
{
	return y_val_base2;
}

bool Base1::check_val_base1()
{
	if (val_base1.get() != nullptr)
		return true;
	return false;
}

bool Base1::check_x_val_base2()
{
	if (x_val_base2.get() != nullptr)
		return true;
	return false;
}

bool Base1::check_y_val_base2()
{
	if (y_val_base2.get() != nullptr)
		return true;
	return false;
}

bool Base1::add_base1(shared_ptr<Base1> &val)
{
	if (val_base1.get() == nullptr) {
		val_base1 = move(val);
		return true;
	}
	else
		return false;
}

bool Base1::add_base2(shared_ptr<Base2>& val, bool where)
{
	if (!where && x_val_base2.get() == nullptr)
	{
		x_val_base2 = move(val);
		return true;
	}
	else if (where && y_val_base2.get() == nullptr)
	{
		y_val_base2 = move(val);
		return true;
	}
	else 
		return false;
}


Base1::~Base1()
{
	x_val_base2.reset();
	y_val_base2.reset();
	val_base1.reset();
	S = 3 * S + N + 41;
}
