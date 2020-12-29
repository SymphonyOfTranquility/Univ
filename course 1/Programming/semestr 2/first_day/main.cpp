#include <iostream>

using namespace std;

typedef struct Node{
    int dat;
    Node *next;
} Listn, *Listp;

int main()
{
    Listp p_node;
    Node *p_node2;
    Listn node;
    Node **pp_node;
    p_node = new Listn;
    p_node->dat = 123;
    p_node->next = NULL;
    cout << (*p_node).dat<<'\n';
    cout << p_node <<'\n';
    node = *p_node;
    cout << node.dat <<'\n';
    pp_node = &p_node;
    p_node2 = *pp_node;
    cout << (*pp_node)->dat << '\n';
    return 0;
}
