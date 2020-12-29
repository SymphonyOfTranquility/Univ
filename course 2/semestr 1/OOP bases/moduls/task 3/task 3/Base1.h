#pragma once
#include "Base2.h"
#include "externs.h"
#include <memory>

using namespace std;

class Base1
{
protected:
	static int alpha_size;
	static int beta_size;
	int	N;
	shared_ptr<Base1> val_base1;
	shared_ptr<Base2> x_val_base2;
	shared_ptr<Base2> y_val_base2;
public:
	Base1();
	int get_n();
	shared_ptr<Base1> get_val_base1();
	shared_ptr<Base2> get_x_val_base2();
	shared_ptr<Base2> get_y_val_base2();
	bool check_val_base1();
	bool check_x_val_base2();
	bool check_y_val_base2();
	bool add_base1(shared_ptr<Base1> &val);
	bool add_base2(shared_ptr<Base2> &val,bool where);
	virtual ~Base1();
};

