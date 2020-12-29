#include <iostream>
#include <vector>
#include "vlasni.h"
using namespace std;

int main()
{
    vlasni first;
    first.input();
    first.vlasni_num();
    first.find_eigenvec();
    first.output_all();
        return 0;
}
