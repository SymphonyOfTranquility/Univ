#include "Base2.h"

int S = 0;

int Base2::gamma_size = 1;
int Base2::delta_size = 1;

Base2::Base2()
{
}

int Base2::get_n()
{
	return N;
}

shared_ptr<Base1> Base2::get_val_base1()
{
	return val_base1;
}

shared_ptr<Base2> Base2::get_x_val_base2()
{
	return x_val_base2;
}

shared_ptr<Base2> Base2::get_y_val_base2()
{
	return y_val_base2;
}

bool Base2::check_val_base1()
{
	if (val_base1.get() != nullptr)
		return true;
	return false;
}

bool Base2::check_x_val_base2()
{
	if (x_val_base2.get() != nullptr)
		return true;
	return false;
}

bool Base2::check_y_val_base2()
{
	if (y_val_base2.get() != nullptr)
		return true;
	return false;
}

bool Base2::add_base1(shared_ptr<Base1> &val)
{
	if (val_base1.get() == nullptr) {
		val_base1 = move(val);
		return true;
	}
	else
		return false;
}

bool Base2::add_base2(shared_ptr<Base2>& val, bool where)
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

Base2::~Base2()
{
	x_val_base2.reset();
	y_val_base2.reset();
	val_base1.reset();
	S = S / 2 - N;
}
