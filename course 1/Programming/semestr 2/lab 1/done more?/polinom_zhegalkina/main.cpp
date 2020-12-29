#include <iostream>

using namespace std;

const int NMAX = 1000;

struct T_polin
{
    bool x[NMAX];
    int counter,len;
    T_polin *next;
    T_polin();
    T_polin(T_polin *a);
    T_polin(T_polin *a,T_polin *b);
};

T_polin::T_polin() ///конструктор загальної об'яви структури
{
    for (int i = 0;i < NMAX; ++i)
        x[i] = 0;
    counter = 1;
    len = 0;
    next = NULL;
}

T_polin::T_polin(T_polin *a) ///конструктор об'яви структури, яка копіює вказану
{
    for (int i = 0;i < NMAX; ++i)
        x[i] = a->x[i];
    counter = a->counter;
    len = a->len;
    next = NULL;
}

T_polin::T_polin(T_polin *a,T_polin *b) ///конструктор об'яви структури, яка є добутком вказаних
{
    if (a->x[0] || b->x[0]){
        x[0] = 1;
        for (int i = 1;i < NMAX; ++i)
            x[i] = 0;
        len = 1;
    }
    else{
        x[0] = 0;
        len = 0;
        for (int i = 1;i < NMAX; ++i)
            if (a->x[i] || b->x[i]){
                x[i] = 1;
                ++len;
            }
            else x[i] = 0;
    }
    counter = 1;
    next = NULL;
}

bool comp(T_polin *a,T_polin *b) ///перевірка на рівність елементів поліномів
{
    for (int i = 0;i < NMAX; ++i)
        if (a->x[i] != b->x[i])
            return false;
    return true;
}

void del_same_el(T_polin *&root) ///видалення повторюваних елементів
{
    if (!root)
        return;
    T_polin *temp = NULL,*prov_el = root,*prev = NULL;

    while (prov_el)
    {
        prev = prov_el;
        temp = prov_el->next;
        while (temp)
        {
            if (comp(temp,prov_el))
            {
                prev->next = temp->next;
                prov_el->counter += temp->counter;
                delete temp;
                temp = prev;
            }
            prev = temp;
            temp = temp->next;
        }
        prov_el = prov_el->next;
    }
    temp = root;prev = NULL;
    while (temp)
    {
        if (temp->counter%2 == 0)
        {
            if (!prev){
                root = root->next;
                delete temp;
                temp = root;
            }
            else{
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            }
        }
        else{
            temp->counter %= 2;
            prev = temp;
            temp = temp->next;
        }
    }
}

bool check(string s,int n) ///перевірка, що считані данні правильні
{
    for (int i = 0;i < s.length(); ++i)
        if (s[i] != 'x' && s[i] != '+' && (s[i] > '9' || s[i] < '0')){
            s.erase(i,1);
            --i;
        }
    if (s[0] == '+' || s[s.length()-1] == '+')
        return false;
    bool my_plus = false;
    for (int i = 0;i < s.length(); ++i)
    {
        if (s[i] == '+')
        {
            if (my_plus)
                return false;
            my_plus = true;
        }
        else if (s[i] == 'x')
        {
            my_plus = false;
            int j = i+1, num = 0;
            if (i+1 == s.length() || s[i+1] == 'x' || s[i+1] == '+' || s[i+1] == '0')
                return false;
            while (j < s.length() && '0' <= s[j] && s[j] <= '9' && j-i < 7)
            {
                num = num*10 + s[j]-'0';
                ++j;
            }
            if (num > n)
                return false;
            i = j-1;
        }
        else{
            if (s[i] != '1' || i > 0 && s[i-1] != '+' || s[i+1] != '+' && i+1 < s.length())
                return false;
            my_plus = false;
        }
    }
    return true;
}

T_polin *input() ///зчитування поліному
{
    int nmax;
    do{
        cout << "Please enter number of different variables \"n\", it has to be lower 1000: \n";
        cin >> nmax;
    }
    while (nmax > 1000 || nmax < 0);
    T_polin *root = NULL,*end_t = NULL,*temp = new T_polin();
    root = end_t = temp;
    cout << "Please enter polynomial in one line, numeration of variables from 1 to " << nmax << ":\n";
    cout << "For example (n = 4): x4x2 + x1 + 1.\n";
    string s;
    getline(cin,s);
    bool flag = false;
    while (!flag)
    {
        getline(cin,s);
        if (!check(s,nmax))
        {
            cout << "Mistake in polynomial, retry: \n";
            continue;
        }
        string word = "";
        for (int i = 0;i < s.length(); ++i)
        {
            if (s[i] == '+')
            {
                temp = new T_polin();
                end_t->next = temp;
                end_t = temp;
            }
            else if (s[i] == 'x')
            {
                int j = i+1,num = 0;
                while (j < s.length() && '9' >= s[j] && s[j] >= '0'){
                    num = num*10 + s[j]-'0';
                    ++j;
                }
                if (!temp->x[num]){
                    temp->x[num] = true;
                    ++temp->len;
                }
                i = j-1;
            }
            else if ('0' <= s[i] && s[i] <= '9'){
                temp->x[0] = true;
                temp->len = 1;
            }
        }
        flag = true;
    }
    del_same_el(root);
    return root;
}

void output(T_polin *root) ///вивід поліномів
{
    if (!root){
        cout << "Polynomial is empty.\n";
        return;
    }
    T_polin *temp = root;
    bool out = false;
    while (temp)
    {
        if (out)
            cout << " + ";
        else out = true;
        if (temp->x[0])
            cout << 1;
        else{
            for (int i = 1;i < NMAX; ++i)
                if (temp->x[i])
                    cout << 'x' << i;
        }
        temp = temp->next;
    }
    cout << "\n\n";

}

T_polin *sum(T_polin *a,T_polin *b) /// сума поліномів
{
    T_polin *c = NULL, *temp_a = a, *temp_b = b,*end_c = NULL, *temp_c = NULL;
    while (temp_a)
    {
        temp_c = new T_polin(temp_a);
        if (!c)
            c = end_c = temp_c;
        else
        {
            end_c->next = temp_c;
            end_c = temp_c;
        }
        temp_a = temp_a->next;
    }
    while (temp_b)
    {
        temp_c = new T_polin(temp_b);
        if (!c)
            c = end_c = temp_c;
        else
        {
            end_c->next = temp_c;
            end_c = temp_c;
        }
        temp_b = temp_b->next;
    }
    del_same_el(c);
    return c;
}

T_polin *dob(T_polin *a, T_polin *b) ///добуток поліномів
{
    T_polin *c = NULL,*temp_a = a,*temp_b = b, *end_c = NULL,*temp_c = NULL;
    while (temp_a)
    {
        temp_b = b;
        while (temp_b)
        {
            temp_c = new T_polin(temp_a,temp_b);
            if (!c)
                c = end_c = temp_c;
            else{
                end_c->next = temp_c;
                end_c = temp_c;
            }
            temp_b = temp_b->next;
        }
        temp_a = temp_a->next;
    }
    del_same_el(c);
    return c;
}



int main()
{
    T_polin *p1 = input();
    cout << "\np1: \n";
    output(p1);

    T_polin *p2 = input();
    cout << "\np2: \n";
    output(p2);
    cout << "sum :\n";
    T_polin *p3 = sum(p1,p2);
    output(p3);

    cout << "dob :\n";
    T_polin *p4 = dob(p1,p2);
    output(p4);
}
