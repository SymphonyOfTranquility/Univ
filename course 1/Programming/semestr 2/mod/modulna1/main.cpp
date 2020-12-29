#include <iostream>

using namespace std;

struct T_roz{
    int day_of_week, number_pare,aud;
    T_roz *next;
};

///first_task

string out_day(int n)
{
    if (n == 1)
        return "Monday";
    else if (n == 2)
        return "Tuesday";
    else if (n == 3)
        return "Wednesday";
    else if (n == 4)
        return "Thursday";
    else if (n == 5)
        return "Friday";
    else if (n == 6)
        return "Saturday";
    else
        return "Sunday";
}

void output_el(T_roz *a,int n,bool with_pointer)
{
    T_roz *temp = a;
    while (temp && n --> 0)
        temp = temp->next;
    if (temp)
    {
        cout << out_day(temp->day_of_week) << ' ' << temp->number_pare << ' ' << temp->aud;
        if (with_pointer)
            cout << ' ' << temp;
        cout << '\n';
    }
    else cout << n << "-element doesn't exist\n";
}

void output_all(T_roz *a,bool with_pointer)
{
    if (!a)
    {
        cout << "empty_list\n\n";
        return;
    }
    T_roz *temp = a;
    cout << "current list is:\n";
    while (temp)
    {
        cout << out_day(temp->day_of_week) << ' ' << temp->number_pare << ' ' << temp->aud;
        if (with_pointer)
            cout << ' ' << temp;
        cout << '\n';
        temp = temp->next;
    }
    cout << '\n';
}

T_roz *my_add(int day,int pare,int aud)
{
    T_roz *a = new T_roz();
    a->day_of_week = day, a->number_pare = pare,a->aud = aud,a->next = NULL;
    return a;
}

T_roz *create_for_first_task()
{
    T_roz *temp = NULL,*a = NULL,*end_list = NULL;
    temp = my_add(2,1,39);a = end_list = temp;
    output_all(a,true);

    temp = my_add(2,2,41);end_list->next = temp;end_list = temp;
    output_all(a,true);

    temp = my_add(3,1,25);end_list->next = temp;end_list = temp;
    output_all(a,true);

    temp = my_add(5,3,221);end_list->next = temp;end_list = temp;
    output_all(a,true);

    T_roz *after = a->next;
    a->next = after->next;
    delete after;
    output_all(a,true);

    return a;
}

///second task

T_roz* add_el(T_roz *root)
{
    int day,pare, aud;
    cout << "add element to the list: day, pare, aud\n";
    cin >> day >> pare >> aud;

    T_roz *temp = my_add(day,pare,aud);

    if (root){
        T_roz *x = root,*prev = NULL;
        bool exist_day = false;
        while (x)
        {
            if (x->day_of_week == temp->day_of_week)
            {
                exist_day = true;
                if (x->number_pare > temp->number_pare){
                    break;
                }
            }
            else if (exist_day)
                break;
            prev = x;
            x = x->next;
        }
        if (exist_day)
        {
            temp->next = x;
            if (prev)
                prev->next = temp;
            else
                root = temp;
        }
        else{
            x = root,prev = NULL;
            while (x)
            {
                if (x->day_of_week > temp->day_of_week)
                    break;
                prev = x;
                x = x->next;
            }
            temp->next = x;
            if (prev)
                prev->next = temp;
            else
                root = temp;
        }
    }
    else
        root = temp;
    return root;
}

///third task

bool rules(T_roz *x,T_roz *y,T_roz *z)
{
    //first_rule
    if (x->day_of_week == y->day_of_week && x->day_of_week == z->day_of_week)
        return true;
    //second_rule
    if (x->aud == z->aud && z->aud != y->aud)
        return true;
    return false;
}

T_roz* rules_for_list(T_roz *root)
{
    T_roz *temp = root;
    if (root && root->next){
        while (temp->next->next)
        {
            if (rules(temp,temp->next,temp->next->next))
            {
                T_roz *x = temp->next,*z = temp->next->next;
                x->next = z->next;
                delete z;
            }
            else temp = temp->next;
        }
    }
    return root;
}

///forth task
T_roz *add_to_queue(T_roz *q,T_roz *el)
{
    if (q){
        T_roz *temp = q;
        while (temp->next)
            temp = temp->next;
        temp->next = el;
        el->next = NULL;
    }
    else{
        q = el;
        q->next = NULL;
    }
    return q;
}

bool can_add(T_roz *root,T_roz *MyQueue)
{
    return !rules(root,root->next,MyQueue);
}

T_roz* modified_rules(T_roz *root)
{
    T_roz *temp = root;
    T_roz *MyQueue = NULL;
    if (root && root->next){
        while (temp->next->next)
        {
            if (rules(temp,temp->next,temp->next->next))
            {
                T_roz *x = temp->next,*z = temp->next->next;
                x->next = z->next;
                MyQueue = add_to_queue(MyQueue,z);
                if (can_add(temp,MyQueue))
                {
                    z = MyQueue;
                    MyQueue = MyQueue->next;
                    z->next = x->next;
                    x->next = z;
                    temp = temp->next;
                }
            }
            else temp = temp->next;
        }
    }
    output_all(MyQueue,true);
    output_all(root,true);
    while (MyQueue)
    {
        temp = MyQueue;
        MyQueue = MyQueue->next;
        delete temp;
    }
    return root;
}

T_roz *copy_list(T_roz *root)
{
    T_roz *new_root = NULL,*temp_for_new = NULL,*temp_end = NULL;
    T_roz *temp = root;
    while (temp){
        temp_for_new = my_add(temp->day_of_week,temp->number_pare,temp->aud);
        if (new_root == NULL)
            new_root = temp_for_new;
        else
            temp_end->next = temp_for_new;
        temp_end = temp_for_new;
        temp = temp->next;
    }
    return new_root;
}

int main()
{
    ///first task
    cout << "------------------------FIRST TASK-------------------------\n";
    T_roz *list_task = create_for_first_task();

    ///second task
    cout << "------------------------SECOND TASK------------------------\n";
    cout << "add 6 elements to the list:\n";
    for (int i = 0;i < 5; ++i){
        list_task = add_el(list_task);
        output_all(list_task,true);
    }


    T_roz *list_task_mod = copy_list(list_task);

    ///third task
    cout << "------------------------THIRD TASK-------------------------\n";
    list_task = rules_for_list(list_task);
    output_all(list_task,true);

    ///fourth task
    cout << "------------------------FOURTH TASK------------------------\n";
    list_task_mod = modified_rules(list_task_mod);
    output_all(list_task_mod,true);

    return 0;
}
