#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct interv
{
    int begin, end, step;
    interv *next;

    interv();
    interv(interv *a);
    interv(int beg,int en,int st);
};

interv::interv()
{
    begin = end = step = 0;
    next = NULL;
}

interv::interv(interv *a)
{
    begin = a->begin;
    end = a->end;
    step = a->step;
    if (a->next)
        next = new interv(a->next);
    else
        next = NULL;
}

interv::interv(int beg,int en,int st)
{
    begin = beg;
    end = en;
    step = st;
    next = NULL;
}
///first task
void output(interv *root)
{
    int counter = 1;
    while (root)
    {
        cout << "Interval #" << counter << ": ";
        ++counter;
        cout << " begin: " << root->begin << " end: " <<  root->end << " step: " << root->step << '\n';
        root = root->next;
    }
    cout << "\n";
}

void output_all(vector<interv> all)
{
    for (int i = 0;i < all.size(); ++i){
        cout << "A bunch of integers: \n";
        output(&all[i]);
    }
}

vector<interv> rand_generator(int counter_of_mnoj)
{
    vector<interv> all;
    srand(time(NULL));
    for (int i = 0;i < counter_of_mnoj; ++i)
    {
        interv *temp_st = NULL,*temp_end = NULL;
        int n = rand()%3+1;
        for (int j = 0;j < n; ++j)
        {
            interv *temp = new interv();
            int fin = rand()%201-100, step = rand()%5+2, start = rand()%201-100;
            if (fin < start)
                swap(fin,start);
            fin = (fin-start)/step*step+start;

            temp->step = step;
            temp->begin = start;
            temp->end = fin;
            temp->next = NULL;
            if (!temp_st)
                temp_st = temp_end = temp;
            else{
                temp_end->next = temp;
                temp_end = temp;
            }
        }
        all.push_back(*temp_st);
    }
    return all;
}

int sum(int x,vector<int> &a,interv *root)
{
    int counter = 0;
    while (root)
    {
        for (int i = root->begin+100;i <= root->end+100; i += root->step){
            a[i] += x;
            ++counter;
        }
        root = root->next;
    }
    return counter;
}

int help(interv *a,interv *b)
{
    vector<int> mas;
    mas.resize(201,0);
    int couter = sum(1,mas,a)+sum(-1,mas,b);
    int counter = 0;
    bool under = 0, up = 0;
    for (int i = 0;i < 201; ++i){
        if (mas[i] < 0){
            under = true;
            counter += abs(mas[i]);
        }
        else if (mas[i] > 0){
            up = true;
            counter += mas[i];
        }
    }
    if (up && under && couter-counter != 0)
        return -1;
    if (!up && !under || couter == counter)
        return 0;
    if (up)
        return 1;
    return 2;
}

int intersection(interv *a,interv *b)
{
    if (help(a,b) == 0)
        return 0;
    return 1;
}

int one_in_another(interv *a,interv *b)
{
    int x = help(a,b);
    if (x <= 0)
        return 0;
    return x;
}

void check_intersection(vector<interv> all)
{
    cout << "Intersection of a bunch of intervals.\n";
    cout << "1 - have an intersection,\n0 - don't have an intersection\n";

    vector<bool> used;
    used.resize(all.size()+1,0);
    for (int i = 0;i < all.size(); ++i){
        for (int j = 0;j < all.size(); ++j){
            int x = intersection(&all[i],&all[j]);
            cout << x << ' ';
            if (x == 1)
                used[i] = used[j] = true;
        }
        cout << "\n";
    }

    int counter = 0;
    for (int i = 0;i < all.size(); ++i)
        if (used[i])
            ++counter;
    cout << "Percent of a intersection bunches: " << (double)counter/(double)all.size()*100.0 << "%\n\n";
}

void check_one_in_another(vector<interv> all)
{
    cout << "One in another of a bunch of intervals:\n";
    cout << "0 - don't have one in another,\n1 - num of row is in num column of array is in\n";
    cout << "2 - num of column is in num row of array is in.\n";

    vector<bool> used;
    used.resize(all.size()+1,0);
    for (int i = 0;i < all.size(); ++i){
        for (int j = 0;j < all.size(); ++j){
            int x = one_in_another(&all[i],&all[j]);
            cout << x << ' ';
            if (x == 1)
                used[i] = true;
            else if (x == 2)
                used[j] = true;
        }
        cout << "\n";
    }
    int counter = 0;
    for (int i = 0;i < all.size(); ++i)
        if (used[i])
            ++counter;
    cout << "Percent of an one in another bunches: " << (double)counter/(double)all.size()*100.0 << "%\n\n";
}

void first_task()
{
    ofstream out("out_for_first.txt");
    streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    vector<interv> all = rand_generator(150);
    output_all(all);
    check_intersection(all);
    check_one_in_another(all);
    cout.rdbuf(coutbuf);
}

///second task

int SIZE_TREE = 1;

struct vertex
{
    interv *data;
    int num, depth;
    vector<vertex *> child;

    vertex();
};

vertex::vertex()
{
    num = 0;
    depth = 0;
    data = NULL;
    child.clear();
}

vertex *create()
{
    vertex *root = new vertex();
    root->num = 1;
    root->depth = 0;
    root->data = new interv();
    root->data->begin = -100;
    root->data->end = 100;
    root->data->step = 1;
    root->data->next = NULL;
    return root;
}

vertex *help_add(vertex *root,interv *val)
{
    if (root->child.size() == 0)
        return root;
    vertex *temp = NULL, *ans = NULL;
    for (int i = 0;i < root->child.size(); ++i)
    {
        if (one_in_another(val, root->child[i]->data) == 2)
        {
            temp = help_add(root->child[i],val);
            if (!ans)
                ans = temp;
            else if (temp->depth > ans->depth)
                ans = temp;
        }
    }
    if (!ans)
        return root;
    return ans;
}

void gl_add(vertex *&root,interv *val)
{
    vertex *temp = help_add(root,val), *hel = new vertex();
    hel->data = new interv(val);
    hel->depth = temp->depth+1;
    hel->num = ++SIZE_TREE;
    temp->child.push_back(hel);
}

void add(vertex *&root)
{
    int n;
    cout << "How many vertex do you want to add?\n";
    cin >> n;
    cout << "How do you want to input data:\n 1 - randomly;\n 2 - your input;\n";
    int x;
    cin >> x;
    if (x == 1)
    {
        vector<interv> all = rand_generator(n);
        for (int i = 0;i < all.size(); ++i)
            gl_add(root,&all[i]);
    }
    else
    {
        x = 0;
        for (int i = 0;i < n; ++i)
        {
            cout << "Enter the number of intervals( < 3) in " << i << " bunch.\n";
            cin >> x;
            cout << "Enter begin, end, step for each interval.\n";
            interv *head = NULL,*tail = NULL;
            int beg,en,step;
            for (int j = 0;j < x; ++i)
            {
                cin >> beg >> en >> step;
                interv *temp = new interv(beg,en,step);
                if (!j)
                    head = tail = temp;
                else
                {
                    tail->next = temp;
                    tail = temp;
                }
            }
            gl_add(root,head);
        }
    }
}


void dfs_for_znach(vertex *root)
{
    cout << "vertex: " << root->num << ", depth: "<< root->depth << '\n';
    interv *temp = root->data;
    int counter = 1;
    output(temp);
    for (int i = 0;i < root->child.size(); ++i)
        dfs_for_znach(root->child[i]);
}

void dfs_for_child(vertex *root)
{
    cout << root->num << " : ";
    for (int i = 0;i < root->child.size(); ++i)
        cout << root->child[i]->num << ", ";

    cout << '\n';
    for (int i = 0;i < root->child.size(); ++i)
        dfs_for_child(root->child[i]);
}

void output(vertex *root)
{
    dfs_for_znach(root);
    dfs_for_child(root);
}

void second_task(vertex *&root)         //make 22 vertex
{
    ofstream out("out_for_second.txt");
    streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf());
    int st = 100,step = 2;
    for (int i = 0;i < 5; ++i){
        interv *temp = new interv(-st,st,step);
        gl_add(root,temp);
        delete temp;
        st = st-step*2;
        if (i%2 == 0)
            step *= 2;
    }
    st = 92, step = 2;
    for (int i = 0;i < 4; ++i){
        interv *temp = new interv(-st,st,step);
        gl_add(root,temp);
        delete temp;
        st = st-step*2;
        if (i%3 == 0){
            step *= 3;
        }
    }
    vector<interv> all = rand_generator(12);
    for (int i = 0;i < all.size(); ++i)
        gl_add(root,&all[i]);
    output(root);
    cout.rdbuf(coutbuf);
}


///third task

struct vert{
    vector<vert *> neigh;
    int n;
    interv *data;
    vert();
};


vert::vert()
{
    n = 0;
    data = NULL;
    neigh.clear();
}

struct graph{
    vector<vert *> all_vertex;
};

void gl_add_vertex(graph *&root, vert *ed)
{
    if (root->all_vertex.size() == 0)
        root->all_vertex.push_back(ed);
    else{
        for (int i = 0;i < root->all_vertex.size(); ++i)
        {
            vert *cur = root->all_vertex[i];
            if (intersection(ed->data,cur->data))
            {
                cur->neigh.push_back(ed);
                ed->neigh.push_back(cur);
            }
        }
        root->all_vertex.push_back(ed);
    }
    ed->n = root->all_vertex.size();
}

vert *convert(interv *a)
{
    vert *temp = new vert();
    temp->data = new interv(a);
    return temp;
}

void add(graph *&root)
{
    int n;
    cout << "How many vertex do you want to add to th GRAPH?\n";
    cin >> n;
    cout << "How do you want to input data:\n 1 - randomly;\n 2 - your input;\n";
    int x;
    cin >> x;
    if (x == 1)
    {
        vector<interv> all = rand_generator(n);
        for (int i = 0;i < all.size(); ++i)
            gl_add_vertex(root,convert(&all[i]));
    }
    else
    {
        x = 0;
        for (int i = 0;i < n; ++i)
        {
            cout << "Enter the number of intervals( < 3) in " << i << " bunch.\n";
            cin >> x;
            cout << "Enter begin, end, step for each interval.\n";
            interv *head = NULL,*tail = NULL;
            int beg,en,step;
            for (int j = 0;j < x; ++i)
            {
                cin >> beg >> en >> step;
                interv *temp = new interv(beg,en,step);
                if (!j)
                    head = tail = temp;
                else
                {
                    tail->next = temp;
                    tail = temp;
                }
            }
            gl_add_vertex(root,convert(head));
        }
    }
}

void output(graph *root)
{
    for (int i = 0;i < root->all_vertex.size(); ++i)
    {
        cout << "Vertex #" << i+1 << ": ";
        interv *cur = root->all_vertex[i]->data;
        output(cur);
    }
    cout << "Graph is:\n";
    for (int i = 0;i < root->all_vertex.size(); ++i)
    {
        cout << i+1 << " : ";
        vert *cur = root->all_vertex[i];
        for (int j = 0;j < cur->neigh.size(); ++j)
            cout << cur->neigh[j]->n << ", ";
        cout << '\n';
    }
}

int dfs_the_most_depth(vertex *root,vector<vertex *> &all_ver)
{
    all_ver.push_back(root);
    if (!root)
        return 0;
    int maxi = root->depth;
    for (int i = 0;i < root->child.size(); ++i)
        maxi = max(maxi,dfs_the_most_depth(root->child[i],all_ver));
    return maxi;
}

void Restore_Heap(vector<vertex *> &m,int father,int count_tree)
{
    int maxson;
    while (father <= count_tree/2)
    {
      //  cout << father << ' ';
        if (father*2 == count_tree)
            maxson = father*2;
        else if (m[father*2]->depth > m[father*2-1]->depth)
            maxson = father*2+1;
        else
            maxson = father*2;
        if (m[father-1]->depth < m[maxson-1]->depth)
        {
            swap(m[father-1],m[maxson-1]);
            father = maxson;
        }
        else father = count_tree;
    }
    //cout << '\n';

}

void my_sort(vector<vertex *> &m)
{
    for(int i = m.size()/2;i > 0; --i)
        Restore_Heap(m,i,m.size());
    for (int i = m.size();i > 0; --i)
    {
        swap(m[0],m[i-1]);
        Restore_Heap(m,1,i-1);
    }
}

graph *third_task(vertex *root)
{
    ofstream out("out_for_third.txt");
    streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf());
    vector<vertex *> all_vert; all_vert.clear();
    int max_depth = dfs_the_most_depth(root,all_vert);
    my_sort(all_vert);

    graph *cur_gr = new graph();
    cur_gr->all_vertex.clear();
    for (int i = all_vert.size()-1;i >= 0; --i)
    {
        gl_add_vertex(cur_gr,convert(all_vert[i]->data));
        while(i > 0 && all_vert[i]->depth == all_vert[i-1]->depth){
            gl_add_vertex(cur_gr,convert(all_vert[i-1]->data));
            --i;
        }
        cout << "\n----------------------------\nGRAPH WITH DEPTH :" << all_vert[i]->depth << '\n';
        output(cur_gr);
    }
    cout.rdbuf(coutbuf);
    return cur_gr;
}

///task 4

int SIZE_BINARY_TREE = 0;

struct binary_tree
{
    int num;
    int func;
    interv *data;
    binary_tree *lef, *righ;
    binary_tree();
};

binary_tree::binary_tree()
{
    num = 0;
    func = 0;
    lef = righ = NULL;
    data = NULL;
}

vector<bool> used;

int bfs(vert *v)
{
    int head = 0,tail = 1;
    vector<pair<vert *,int> > Queue;
    Queue.clear();
    Queue.push_back({v,0});
    used[v->n] = true;
    int counter = 0;
    while (head < tail)
    {
        vert *cur = Queue[head].first;
        int len = Queue[head].second;
        ++head;
        if (len == 3){
            ++counter;
            continue;
        }
        for (int i = 0;i < cur->neigh.size(); ++i)
            if (!used[cur->neigh[i]->n])
            {
                used[cur->neigh[i]->n] = true;
                Queue.push_back({cur->neigh[i],len+1});
                ++tail;
            }
    }
    return counter;
}

void rec(binary_tree *tree, vert *a, int key)
{
    while (tree->func > key)
    {
        if (tree->righ)
            tree = tree->righ;
        else{
            binary_tree *temp = new binary_tree();
            temp->data = new interv(a->data);
            temp->func = key;
            tree->righ = temp;
            ++SIZE_BINARY_TREE;
            temp->num = SIZE_BINARY_TREE;
        }
    }
    if (tree->lef)
        rec(tree->lef,a,key);
    else
    {
        binary_tree *temp = new binary_tree();
        temp->data = new interv(a->data);
        temp->func = key;
        tree->lef = temp;
        ++SIZE_BINARY_TREE;
        temp->num = SIZE_BINARY_TREE;
    }
}

void dfs_for_znach(binary_tree *root)
{
    cout << "vertex: " << root->num << '\n';
    interv *temp = root->data;
    int counter = 1;
    output(temp);
    if (root->lef)
        dfs_for_znach(root->lef);
    if (root->righ)
        dfs_for_znach(root->righ);
}

void dfs_for_child(binary_tree *root)
{
    cout << root->num << " : ";
    cout << " left : ";
    if (root->lef)
        cout << root->lef->num << ", ";
    cout << " right : ";
    if (root->righ)
        cout << root->righ->num << ";";
    cout << '\n';

    if (root->lef)
        dfs_for_child(root->lef);
    if (root->righ)
        dfs_for_child(root->righ);
}

void output(binary_tree *root)
{
    dfs_for_znach(root);
    dfs_for_child(root);
}


void fourth_task(graph *before)
{
    ofstream out("out_for_fourth.txt");
    streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf());
    binary_tree *root = NULL;
    int n = before->all_vertex.size();
    int key[n+1];
    cout << "KEYS: ";
    for (int i = 0;i < n; ++i){
        used.resize(n+1,0);
        key[i+1] = bfs(before->all_vertex[i]);
        cout << key[i+1] << ' ';
        used.clear();
    }
    cout << '\n';
    root = new binary_tree();
    root->func = key[before->all_vertex[0]->n];
    root->data = new interv(before->all_vertex[0]->data);
    root->num = SIZE_BINARY_TREE+1;
    SIZE_BINARY_TREE++;
    binary_tree *temp;
    for (int i = 1;i < n; ++i){
        temp = root;
        rec(temp,before->all_vertex[i],key[before->all_vertex[i]->n]);
    }
    output(root);
    cout.rdbuf(coutbuf);
}

int main()
{
    first_task();///task1
    cout << "------------------------TASK2-----------------------\n";
    vertex *all = create(); ///task2
    second_task(all);
    /*vertex *temp = create();
    add(temp);                            //тестові функції, їх може використовувати користувач
    output(temp)*/
    cout << "------------------------TASK3-----------------------\n";
    graph *task3 = new graph(); ///task3
    task3->all_vertex.clear();

   /* add(task3);                   //тестові функції, їх може використовувати користувач
    output(task3);*/
    graph *task4 = third_task(all);
    cout << "------------------------TASK4-----------------------\n";
    fourth_task(task4);

    return 0;
}

