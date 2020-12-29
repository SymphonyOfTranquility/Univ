/*�������� � ��� ���������
Mysechko Artemiy ������������� ���� Forth*/


#include <iostream>
#include <vector>

using namespace std;

struct T_stack{
    int x;
    T_stack *next;
    T_stack();
    T_stack(int num);
};


T_stack::T_stack() ///����������� ��� ����������� �����
{
    next = NULL;
}
T_stack::T_stack(int num) ///����������� � �������� ����������� ��������
{
    x = num;
    next = NULL;
}

void output(T_stack *root, int len) ///���� �����
{
    if (!len)
    {
        cout << " Ok \n";
        return;
    }
    cout << " Ok ( ";
    if (len > 5)
        cout << "[" << len << "].. ";
    int mas[5],counter = 0,j = 0;
    while (j < len && counter < 5)
    {
        mas[counter] = root->x;
        ++counter;
        ++j;
        root = root->next;
    }
    for (int i = counter-1;i >= 0; --i){
        if (mas[i] < 0){
            cout << (unsigned) mas[i] << "(" << mas[i] << ") "; ///���� ����� ��'���� �� ���������� ���� ��������� ��������
        }                                                       ///� ���� �������� � ������.
        else
            cout << mas[i] << ' ';
    }
    cout << ")\n";
}

void stack_do_empty(T_stack *&root,int &len) /// ��������� �����(� ��������� ��������������� ���� ������� � ������ ��������)
{
    T_stack *temp = NULL;
    while (len && root)
    {
        --len;
        temp = root;
        root = root->next;
        delete temp;
    }
    len = 0;
}

void push(T_stack *&root,int num) ///��������� �������� � ����
{
    T_stack *temp = new T_stack(num);
    temp->next = root;
    root = temp;
}

void roll(T_stack *&root,int num) /*������� ROLL.*////�������:::������������ ����� ����� Forth  ������ �� ���� �� ����������
{                                 ///������ �������, ���� �������� ������� �������� � �����, �� �� ��������
    if (!root)                    ///����(����������� ����������), � ������� �� ����� ������� ��������, ��� �� ������ �������.
        return;                   ///��� ��� �� ���� ��������, ������������ ��� ���� �������� len ��������, � ��� �������,
    T_stack *temp = root,*prev = NULL, *cop = NULL;///�� ��� ������(���������), �������� � ���� ���� �����������.
    while (temp && num > 0)                        ///(� �� ��� � ���������.)
    {
        --num;
        prev = temp;
        temp = temp->next;
    }
    if (!prev)
        return;
    else if (!temp)
    {
        cop = new T_stack();
        prev->next = cop;
        temp = cop;
        while (num > 0){
            cop = new T_stack();
            temp->next = cop;
            prev = temp;
            temp = temp->next;
            --num;
        }
        prev->next = NULL;
        temp->next = root;
        root = temp;
    }
    else{
        prev->next = temp->next;
        temp->next = root;
        root = temp;
    }
}

void pick(T_stack *&root,int num,int &len) ///������� PICK ������ ��������� �� ROLL(����� ��� �� ����������� ��������, � �����)
{
    ++len;
    if (!root){
        T_stack *cop = new T_stack(),*cop2 = new T_stack(cop->x);
        cop->next = cop2;
        root = cop;
        return;
    }
    T_stack *temp = root,*prev = NULL, *cop = NULL;
    while (temp && num > 0)
    {
        --num;
        prev = temp;
        temp = temp->next;
    }
    if (!prev)
    {
        cop = new T_stack(root->x);
        cop->next = root;
        root = cop;
    }
    else if (!temp)
    {
        cop = new T_stack();
        prev->next = cop;
        temp = cop;
        while (num > 0){
            cop = new T_stack();
            temp->next = cop;
            prev = temp;
            temp = temp->next;
            --num;
        }
        cop = new T_stack(temp->x);
        cop->next = root;
        root = cop;
    }
    else{
        cop = new T_stack(temp->x);
        cop->next = root;
        root = cop;
    }
}

vector <string> words,actions[1000];///������ �������������� ��� � ����� �������, ���� ������, ��� �� ������ ����� ������������� �����.

void initial(vector<string> &words) ///����������� ���������� ���
{
    words.push_back("MOD");  actions[0].push_back("MOD");
    words.push_back("PICK"); actions[1].push_back("PICK");
    words.push_back("ROLL"); actions[2].push_back("ROLL");
    words.push_back("+");    actions[3].push_back("+");
    words.push_back("-");    actions[4].push_back("-");
    words.push_back("*");    actions[5].push_back("*");
    words.push_back("/");    actions[6].push_back("/");
    words.push_back(".");    actions[7].push_back(".");
    words.push_back(":");    actions[8].push_back(":");
    words.push_back(";");    actions[9].push_back(";");
}

bool in_word(string s) ///�������� �� � ���� �������������� ������
{
    for (int i = 0; i < words.size(); ++i)
        if (s == words[i])
            return true;
    return false;
}

vector<string> devide(string s) ///��������� ������� ������ �� �����(�� ������ �� ������).
{
    while (s.length() > 0 && s[0] == ' ')
        s.erase(0,1);
    vector<string> all_pos;
    for (int i = 0;i < s.length(); ++i)
    {
        if (s[i] != ' ')
        {
            string temp = "";
            int j = i;
            while (j < s.length() && s[j] != ' '){
                temp += s[j];
                ++j;
            }
            all_pos.push_back(temp);
            i = j-1;
        }
    }
    return all_pos;
}

bool numeral(string s,int &chis) ///��������� �������� ����� �� ����� � ������ ���� � ������ � ��� int.
{
    bool znak = 0;
    if (s[0] == '-')
        znak = 1;
    int ans = 0;
    for (int i = (s[0] == '-'? 1 : 0);i < s.length(); ++i)
    {
        if (s[i] <= '9' && s[i] >= '0')
            ans = ans*10 + s[i] - '0';
        else
            return false;
    }
    chis = ans;
    if (znak)
        chis = -chis;
    return true;
}

bool sign(string s) ///�������� �� ����
{
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "MOD");
}

int op(T_stack *&root,int &len,string znack) ///������ � ���������� +, -, *, /, MOD.
{                                            ///������� ::: �������� � ����� ����� Forth � ������, �� ���� �� ����������
    if (!len)                                ///������� ����������� ��������, � ���� ���� 1 ����� � �����,
        return -1;                           ///�� �� ������ ����������� �������� � ��������� ����� ��� �� ������ �����(�� � ROLL)
    else{                                    ///��� ��� ���� � ������ ��� �������� � ����� �� ��� � ��� ����� �� ������(���� Ok)
        if (!root->next)                     ///(� ����������� ���������.)
        {
            T_stack *cop = new T_stack();
            root->next = cop;
        }
        --len;
    }
    int a = root->x,b = root->next->x;
    T_stack *temp = root;
    delete temp;
    root = root->next;
    if (znack == "+")
        root->x = a+b;
    else if (znack == "-")
        root->x = b-a;
    else if (znack == "*")
        root->x = a*b;
    else if (znack == "/")
    {
        if (a == 0)
            return 0;
        root->x = b/a;
    }
    else if (znack == "MOD")
    {
        if (a == 0)
            return 0;
        root->x = b%a;
    }
    return 1;
}

bool del(T_stack *&root,int &len) /// ��������� �������� � �����
{                                 /// ������� ::: ���� �������� ����, �� � ��� Forth �������� ��������� ����
    if (!len)                     /// � ����������� �� ���� ������
    {
        T_stack *cop = NULL;
        if (!root)
            root = new T_stack();
        if (!root->next){
            cop = new T_stack();
            root->next = cop;
        }
        cout << root->x;
        cop = root;
        root = root->next;
        delete cop;
        return false;
    }
    --len;
    cout << root->x << ' ';
    T_stack *temp = root;
    root = root->next;
    delete temp;
    return true;
}

int dot_coma(vector<string> all_pos,int start) ///����� ������ � �����, ���� ���� �������� ���������, � ����� ��������,
{                                              ///��� �� ���� �� ���� �������� ������
    int chis = 0,chis2 = 0;                    ///� ���� Forth � ��������� ���� �������� ��������������� ���� �� ���� ��������
    for (int i = start;i < all_pos.size(); ++i)///� ���� � ����'������ ����� �� �� �� ������ �� �������
    {
        if (all_pos[i] == ":" && i != start)
            return -2;
        if (all_pos[i] == ";")
            return i;
        if (i != start+1 && !in_word(all_pos[i]))
        {
            if (!numeral(all_pos[i],chis))
                return -2;
            else{
                if (i+1>= all_pos.size() || numeral(all_pos[i+1],chis2))
                    continue;
                if (all_pos[i+1] == "PICK" || all_pos[i+1] == "ROLL"){
                    if (chis < 0)
                        return -2;
                    ++i;
                }
            }
        }
        else if (all_pos[i+1] == "PICK" || all_pos[i+1] == "ROLL")
            return -2;
    }
    return -1;
}

bool dots_new_func(vector<string> &all_pos,int start,int &pos) ///������� ��� ����������� ��� ���������� ���������
{                                                              ///���� ������� �� ������ �������, �� �� ������ �� �� ������
    int temp_p = -1;                                           ///� ��������������� �������
    bool flag = false;
    string s = "";
    vector<string> temp_pos;
    while (!flag)                                   ///�� ������� ����������� ��� ���� �� �� �������� ������ � �����,
    {                                               ///��� ���� ��� �� ������� �������.
        temp_p = dot_coma(all_pos,start);
        if (temp_p >= 0){
            flag = true;
            break;
        }
        else if (temp_p == -2)
            return false;
        getline(cin,s);
        temp_pos.clear();
        temp_pos = devide(s);
        for (int i = 0;i < temp_pos.size(); ++i)
            all_pos.push_back(temp_pos[i]);
    }
    pos = temp_p;
    for (int i = 0;i < words.size(); ++i)
        if (words[i] == all_pos[start+1])
            return false;
    words.push_back(all_pos[start+1]);
    for (int i = start+2;i < pos; ++i)
        actions[words.size()-1].push_back(all_pos[i]);
    return true;
}

bool work_with_numeral(T_stack *&m_stack,int &len,int &i,vector<string> all_pos,int chis)
{                                      ///������ � �������(��������� � ����)
    if (i + 1 >= all_pos.size()){      ///����� ��� ��������� ������� ROLL � PICK, �� ���� ����� ���� ��������� ���� �����,
        push(m_stack,chis);            ///�� �� ��������� �� �������
        ++len;
    }
    else if (all_pos[i+1] == "ROLL"){
        if (chis < 0)
            return false;
        roll(m_stack,chis);
        ++i;
    }
    else if (all_pos[i+1] == "PICK"){
        if (chis < 0)
            return false;
        pick(m_stack,chis,len);
        ++i;
    }
    else{
        push(m_stack,chis);
        ++len;
    }
    return true;
}

bool work_with_func(T_stack *&root,int &len, string s) ///������� ������� �� ������ �� ��� ��������� ��������
{
    int pos = -1;
    for (int i = 0;i < words.size(); ++i)
        if (s == words[i])
        {
            pos = i;
            break;
        }
    int chis = 0;
    for (int i = 0;i < actions[pos].size(); ++i){
        if (in_word(actions[pos][i])){
            if (actions[pos][i] == "."){
                if (!del(root,len))
                    return false;
            }
            else if (sign(actions[pos][i]))
            {
                int x = op(root,len,actions[pos][i]);
                if (x == 0)
                {
                    cout << " DIVIDE BY ZERO\n";
                    return false;
                }
                else if (x == -1)
                {
                    cout << "\n^ stack is empty\n";
                    return false;
                }
            }
            else if (!work_with_func(root,len,actions[pos][i]))
                return false;
        }
        else if (numeral(actions[pos][i],chis)){
            if (!work_with_numeral(root,len,i,actions[pos],chis))
            {
                cout << "index can't be negative.\n";
                return false;
            }
        }
    }
    return true;
}

int solve(string s,T_stack *&m_stack, int &len) ///����������� ��� ������� ���������(���� ���� � ������� ���������)
{                                                ///��'���� �� ����� �������.
    vector<string> all_pos = devide(s);
    int chis = 0;
    for (int i = 0;i < all_pos.size(); ++i)
    {
        if (all_pos[i] == "EXIT")
            return -1;
        if (in_word(all_pos[i]))
        {
            if (all_pos[i] == "ROLL" || all_pos[i] == "PICK"){
                cout << all_pos[i] << " WORD NOT FOUND\n";
                stack_do_empty(m_stack,len);
                return 0;
            }
            if (sign(all_pos[i]))
            {
                int x = op(m_stack,len,all_pos[i]);
                if (x == 0)
                {
                    cout << all_pos[i] << " DIVIDE BY ZERO\n";
                    stack_do_empty(m_stack,len);
                    return 0;
                }
                else if (x == -1)
                {
                    cout << i << "\n^ stack is empty\n";
                    return 0;
                }
            }
            else if (all_pos[i] == ".")
            {
                if (!del(m_stack,len))
                {
                    cout << ".\n stack is empty\n";
                    return 0;
                }
            }
            else if (all_pos[i] == ";")
                continue;
            else if (all_pos[i] == ":")
            {
                int pos = -1;
                if (!dots_new_func(all_pos,i,pos))
                {
                    cout << "Function '"<<  all_pos[i+1] << "' can't be defined. \n";
                    stack_do_empty(m_stack,len);
                    return 0;
                }
                i = pos;
            }
            else if (!work_with_func(m_stack,len,all_pos[i]))
            {
                stack_do_empty(m_stack,len);
                return 0;
            }
        }
        else if (numeral(all_pos[i],chis))
        {
            if (!work_with_numeral(m_stack,len,i,all_pos,chis))
            {
                cout << "index can't be negative.\n";
                stack_do_empty(m_stack,len);
                return 0;
            }
        }
        else{
            cout << all_pos[i] << ": WORD NOT FOUND\n";
            stack_do_empty(m_stack,len);
            return 0;
        }
    }
    return 1;
}

int main()
{
    initial(words);
    T_stack *m_stack = NULL;
    int len = 0;
    while (true)
    {
        string s;
        getline(cin,s);
        int step = solve(s,m_stack,len);
        if (step == 1)
            output(m_stack,len);
        else if (step == -1)
        {
            cout << "GOOD BYE!!!";
            break;
        }
    }
    return 0;
}
