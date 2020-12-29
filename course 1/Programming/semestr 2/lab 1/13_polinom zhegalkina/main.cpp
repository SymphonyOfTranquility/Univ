#include <iostream>

using namespace std;

const int nmax = 10;

struct T_polin{
    bool x,y,z,w,_const;
    int counter;
    T_polin *next;
};

T_polin *adv(int x,int y,int z,int w,int _const)
{
    T_polin *temp = new T_polin();
    temp->x = x;
    temp->y = y;
    temp->z = z;
    temp->w = w;
    temp->_const = _const;
    temp->counter = 1;
    temp->next = NULL;
}

T_polin *del_same_el(T_polin *root)
{
    T_polin *temp = root,*prev = NULL;
    while (temp)
    {
        if (temp->counter%2 == 0)
        {
            if (prev == NULL)
            {
                root = prev = temp;
                temp = temp->next;
                delete prev;
            }
            else{
                prev->next = temp->next;
                delete temp;
                temp-
            }
        }
        else temp->counter %= 2
    return root;
}


bool correct_polinom(string s)
{
    int n = s.length();
    if (s[0] == '+' || s[n-1] == '+')
        return false;
    for (int i = 0;i < n; ++i)
    {
        if (i < n-1 && s[i] == '+' && s[i+1] == '+')
            return false;
        if (s[i] != '+' && s[i] != 'x' && s[i] != 'y' && s[i] != 'z' && s[i] != 'w')
        {
            if (s[i] == '1')
            {
                if (i < n-1 && i > 0)
                {
                    if (s[i+1] != '+' || s[i-1] != '+')
                        return false;
                }
                else if (i == n-1 && i == 0)
                    continue;
                else if (i == n-1)
                {
                    if (s[i-1] != '+')
                        return false;
                }
                else
                    if (s[i+1] != '+')
                        return false;
            }
            else
                return false;
        }
    }
    return true;
}

T_polin *read_polinom(int num)
{
    string s;
    bool correct;
    do{
        cout << "insert polinom zhegalkina:" << num << "\n";
        cin >> s;
        correct = correct_polinom(s);
        if (!correct)
            cout << "mistake!!!\n";
    }
    while (!correct);
    T_polin *p;
    p = adv(0,0,0,0,0);
    for (int i = 0;i < s.length(); ++i)
    {
        if (s[i] == '+')
        {
            if (p != NULL){
                T_polin *root = p->next,*prev = root;
                while (root)
                {
                    if (riv(root,p))
                    {
                        prev->next =
                    }
                }
            }
            T_polin *temp = new T_polin();
            temp = adv(0,0,0,0,0);
            temp->next = p;
            p = temp;
        }
        else
        {
            if (s[i] == 'x')
                p->x = true;
            else if (s[i] == 'y')
                p->y = true;
            else if (s[i] == 'z')
                p->z = true;
            else if (s[i] == 'w')
                p->w = true;
            else if (s[i] == '1')
                p->_const = true;
        }
    }
    return p;
}

void write_polinom(T_polin *p)
{
    T_polin *temp = p;
    bool first_out = true;
    while (temp != NULL)
    {
        if (!first_out)
            cout << '+';
        else
            first_out = false;
        if (temp->x)
            cout << 'x';
        if (temp->y)
            cout << 'y';
        if (temp->z)
            cout << 'z';
        if (temp->w)
            cout << 'w';
        if (temp->_const)
            cout << '1';
        temp = temp->next;
    }
    cout << '\n';
}

bool riv(T_polin *a,T_polin *b)
{
    if (a->w == b->w && a->z == b->z && a->y == b->y && a->x == b->x && a->_const == b->_const)
        return true;
    return false;
}

T_polin *sum(T_polin *a,T_polin *b)
{
    T_polin *c = NULL,*temp_a = a,*root = NULL,*temp_c = NULL,*temp_b = b;
    while (temp_a)
    {
        root = adv(temp_a->x,temp_a->y,temp_a->z,temp_a->w,temp_a->_const);
        if (temp_c != NULL){
            temp_c->next = root;
            temp_c = root;
        }
        else
            c = temp_c = root;
        temp_a = temp_a->next;
    }
    while (temp_b)
    {
        temp_c = c;
        bool flag = false;
        while (temp_c)
        {
            if (riv(temp_c,temp_b)){
                ++temp_c->counter;
                flag = true;
                break;
            }
            temp_c = temp_c->next;
        }
        if (!flag){
            root = adv(temp_b->x,temp_b->y,temp_b->z,temp_b->w,temp_b->_const);
            root->next = c;
            c = root;
        }
        temp_b = temp_b->next;
    }
    return del_same_el(c);
}

int main()
{
    T_polin *p1,*p2;
    p1 = read_polinom(1);
    p2 = read_polinom(2);
    write_polinom(sum(p1,p2));
    write_polinom(p1);
    write_polinom(del_same_el(p1));
    write_polinom(p2);
    write_polinom(del_same_el(p2));
    return 0;
}
