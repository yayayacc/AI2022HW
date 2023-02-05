# pragma once

#include<iostream>
#include"classes.h"
using namespace std;

State* State::search(State & p){
    // step1: push the original node
    int level = 0;
    OPEN_TABLE.push_back(&p);

    // step 2-8
    // step2: check whether the open_table is empty
    while(!OPEN_TABLE.empty()){
        // step3: pop the first node in open_table and push it into the closed_table, notated as n
        State* node_tem = OPEN_TABLE.back();
        OPEN_TABLE.pop_back();
        CLOSED_TABLE.push_back(node_tem);

        // step4: judge whether n is the aim node
        if(node_tem->is_aim()){
            return node_tem;
        }

        // step5 and step6: produce children nodes and initialize them
        node_tem->produce_children();



    }

}

bool State::is_aim(){
    if(this->cells[0][0] == 1){
        if(this->cells[0][1] == 2){
            if(this->cells[0][2] == 3){
                if(this->cells[1][0] == 4){
                    if(this->cells[1][2] == 5){
                        if(this->cells[2][0] == 6){
                            if(this->cells[2][1] == 7){
                                if(this->cells[2][2] == 8){
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

void State::produce_children(){
    if(x_whitespace > 0){// it can moves to its left
        State* tem = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace] = tem->cells[x_whitespace - 1][y_whitespace];
        tem->cells[x_whitespace - 1][y_whitespace] = 0;
        tem->x_whitespace--;
        if(!is_in_table(OPEN_TABLE, tem))
    }
    if(y_whitespace > 0){
        State* tem = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace] = tem->cells[x_whitespace][y_whitespace - 1];
        tem->cells[x_whitespace][y_whitespace] = 0;
        tem->y_whitespace--;
        OPEN_TABLE.push_back(tem);
    }
    if(x_whitespace < 2){
        State* tem = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace] = tem->cells[x_whitespace + 1][y_whitespace];
        tem->cells[x_whitespace + 1][y_whitespace] = 0;
        tem->x_whitespace++;
        OPEN_TABLE.push_back(tem);
    }
    if(y_whitespace < 2){
        State* tem = this->produce_single_child();
        tem->cells[x_whitespace][y_whitespace] = tem->cells[x_whitespace][y_whitespace + 1];
        tem->cells[x_whitespace][y_whitespace + 1] = 0;
        tem->y_whitespace++;
        OPEN_TABLE.push_back(tem);
    }
}

State* State::produce_single_child(){
    State* tem = new State(*this);
    tem->depth++;
    tem->parent = this;
    return tem;
}

bool State::is_in_table(vector<State*> table, State* p){
    bool flag1 = false;
    for(vector<State*>::iterator it =  table.begin(); it != table.end(); it++){
        bool flag2 = true;
        for(int i = 0; i < GRID_LENGTH; i++){
            for(int j = 0; j<GRID_LENGTH; j++){
                if((*it)->cells[i][j] != p->cells[i][j]){
                    flag2 = false;
                    break;
                }
            }
        }
        if(flag2){
            flag1 = true;
            break;
        }
    }
    return flag1;
}



