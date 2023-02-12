
#include "state.h"
#include "profiler.h"
#include "cstdlib"
#include "ctime"

using namespace std;

vector<State*> OPEN_TABLE;
vector<State*> CLOSED_TABLE;
bool           flag = false;
int            cnt  = 0;

struct data
{
    int num;
    int index;
};




State* State::search_width_first() {
    // step1: push the original node
    int level = 0;
    OPEN_TABLE.push_back(&(*this));

    // step 2-8
    // step2: check whether the open_table is empty
    while (!OPEN_TABLE.empty()) {
        level++;
        // step3: pop the first node in open_table and push it into the closed_table, notated as n
        State* node_tem = OPEN_TABLE[0];
        OPEN_TABLE.erase(OPEN_TABLE.begin());
        CLOSED_TABLE.push_back(node_tem);

        // step4: judge whether n is the aim node
        if (node_tem->is_aim()) {
            //cout << "----" << cnt << "----" << endl;
            return node_tem;
        }

        // step5 and step6: produce children nodes and initialize them
        node_tem->produce_children();

        // step7 and step8 can be ignored
    }
    cout << "----" << cnt << "----" << endl;
    return NULL;
}


bool State::is_aim() {
    if (this->cells[0][0] == 1) {
        if (this->cells[0][1] == 2) {
            if (this->cells[0][2] == 3) {
                if (this->cells[1][2] == 4) {
                    if (this->cells[2][2] == 5) {
                        if (this->cells[2][1] == 6) {
                            if (this->cells[2][0] == 7) {
                                if (this->cells[1][0] == 8) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void State::produce_children() {
    if (x_whitespace > 0) { // it can moves to its left
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace - 1][y_whitespace];
        tem->cells[x_whitespace - 1][y_whitespace] = 0;
        tem->x_whitespace--;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.push_back(tem);
        }
    }
    if (y_whitespace > 0) {
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace][y_whitespace - 1];
        tem->cells[x_whitespace][y_whitespace - 1] = 0;
        tem->y_whitespace--;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.push_back(tem);
        }
    }
    if (x_whitespace < 2) {
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace + 1][y_whitespace];
        tem->cells[x_whitespace + 1][y_whitespace] = 0;
        tem->x_whitespace++;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.push_back(tem);
        }
    }
    if (y_whitespace < 2) {
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace][y_whitespace + 1];
        tem->cells[x_whitespace][y_whitespace + 1] = 0;
        tem->y_whitespace++;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.push_back(tem);
        }
    }
}

State* State::produce_single_child() {
    cnt++;
    State* tem = new State(0);
    for (int i = 0; i < GRID_LENGTH; i++) {
        for (int j = 0; j < GRID_LENGTH; j++) {
            tem->cells[i][j] = cells[i][j];
        }
    }
    tem->x_whitespace = x_whitespace;
    tem->y_whitespace = y_whitespace;
    tem->depth        = depth + 1;
    tem->parent       = this;
    return tem;
}

bool State::is_in_table(vector<State*> table, State* p) {
    bool flag1 = false;
    for (vector<State*>::iterator it = table.begin(); it != table.end(); it++) {
        bool flag2 = true;
        for (int i = 0; i < GRID_LENGTH; i++) {
            for (int j = 0; j < GRID_LENGTH; j++) {
                if ((*it)->cells[i][j] != p->cells[i][j]) {
                    flag2 = false;
                    break;
                }
            }
        }
        if (flag2) {
            flag1 = true;
            break;
        }
    }
    return flag1;
}

void State::init() {
    x_whitespace = 1;
    y_whitespace = 1;
    parent       = NULL;

    cells[1][1] = 0;

    cout << "重排九宫格" << endl
         << "tips: 输入八个数字，从1至8各一个，可打乱顺序" << endl;
    cout << " ? - - " << endl
         << " - - - " << endl
         << " - - - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[0][0];
    cout << endl;
    cout << " - ? - " << endl
         << " - - - " << endl
         << " - - - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[0][1];
    cout << endl;
    cout << " - - ? " << endl
         << " - - - " << endl
         << " - - - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[0][2];
    cout << endl;
    cout << " - - - " << endl
         << " - - ? " << endl
         << " - - - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[1][2];
    cout << endl;
    cout << " - - - " << endl
         << " - - - " << endl
         << " - - ? " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[2][2];
    cout << endl;
    cout << " - - - " << endl
         << " - - - " << endl
         << " - ? - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[2][1];
    cout << endl;
    cout << " - - - " << endl
         << " - - - " << endl
         << " ? - - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[2][0];
    cout << endl;
    cout << " - - - " << endl
         << " ? - - " << endl
         << " - - - " << endl;
    cout << "请输入此位置的数字:" << endl;
    cin >> cells[1][0];
    cout << endl;
}


State* State::search_depth_first(){
    // step1: push the original node
    int level = 0;
    OPEN_TABLE.push_back(&(*this));

    // step 2-8
    // step2: check whether the open_table is empty
    while (!OPEN_TABLE.empty()) {
        level++;
        // step3: pop the first node in open_table and push it into the closed_table, notated as n
        State* node_tem = OPEN_TABLE[0];
        OPEN_TABLE.erase(OPEN_TABLE.begin());
        CLOSED_TABLE.push_back(node_tem);

        // step4: judge whether n is the aim node
        if (node_tem->is_aim()) {
            //cout << "----" << cnt << "----" << endl;
            return node_tem;
        }

        // step5 and step6: produce children nodes and initialize them
        node_tem->produce_children_depth_first();

        // step7 and step8 can be ignored
    }
    cout << "----" << cnt << "----" << endl;
    return NULL;    
}

void State::produce_children_depth_first() {
    if (x_whitespace > 0) { // it can moves to its left
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace - 1][y_whitespace];
        tem->cells[x_whitespace - 1][y_whitespace] = 0;
        tem->x_whitespace--;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.insert(OPEN_TABLE.begin() ,tem);
        }
    }
    if (y_whitespace > 0) {
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace][y_whitespace - 1];
        tem->cells[x_whitespace][y_whitespace - 1] = 0;
        tem->y_whitespace--;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.insert(OPEN_TABLE.begin() ,tem);
        }
    }
    if (x_whitespace < 2) {
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace + 1][y_whitespace];
        tem->cells[x_whitespace + 1][y_whitespace] = 0;
        tem->x_whitespace++;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.insert(OPEN_TABLE.begin() ,tem);
        }
    }
    if (y_whitespace < 2) {
        State* tem                                 = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace]     = tem->cells[x_whitespace][y_whitespace + 1];
        tem->cells[x_whitespace][y_whitespace + 1] = 0;
        tem->y_whitespace++;
        if (!is_in_table(OPEN_TABLE, tem) && !is_in_table(CLOSED_TABLE, tem)) {
            OPEN_TABLE.insert(OPEN_TABLE.begin() ,tem);
        }
    }
}

void State::test(){
    cout<<"输入1是广度优先平均时间测试，输入2是深度优先平均时间测试"<<endl;
    char a;
    cin>>a;
    int times;
    if(int(a) == 49){
        cout<<"请输入想测试的次数"<<endl;
        cin>>times;
        double time = 0.;
        PROFILE_SCOPE("Search");
        for(int i = 0; i < times; i++){
            randomly_init();
            this->search_width_first();
        }
        PROFILE_DISPLAY_AVERAGE(times);
    }
    else if(int(a) == 50){
        cout<<"请输入想测试的次数"<<endl;
        cin>>times;
        double time = 0.;
        PROFILE_SCOPE("Search");
        for(int i = 0; i < times; i++){
            randomly_init();
            this->search_depth_first();
        }
        PROFILE_DISPLAY_AVERAGE(times);
    }
    else{
        cout<<"输入错误，请重启程序"<<endl;
    }
}


void State::randomly_init(){
    int a[8];
    struct data dddd[9];
    x_whitespace = 1;
    y_whitespace = 1;
    parent       = NULL;

    cells[1][1] = 0;    
    srand((int)time(0));
    for(int i = 0; i < 8; i++){
        dddd[i].num = rand();  // 随机生成一个数 
		dddd[i].index = i+1;
    }
    for(int i = 0; i < 8; i++){
        for(int j = i + 1; j < 8; j++){
            int tem_num;
            int tem_index;
            if(dddd[i].num > dddd[j].num){
                tem_index = dddd[i].index;
                tem_num = dddd[i].num;
                dddd[i].index = dddd[j].index;
                dddd[i].num = dddd[j].num;
                dddd[j].num = tem_num;
                dddd[j].index = tem_index;
            }
        }
    }
    cells[0][0] = dddd[0].index;
    cells[0][1] = dddd[1].index;
    cells[0][2] = dddd[2].index;
    cells[1][2] = dddd[3].index;
    cells[2][2] = dddd[4].index;
    cells[2][1] = dddd[5].index;
    cells[2][0] = dddd[6].index;
    cells[1][0] = dddd[7].index;
}

