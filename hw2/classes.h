#pragma once

#include<vector>
#include<iostream>

using namespace std;


# define GRID_LENGTH 3


vector<State*> OPEN_TABLE;
vector<State*> CLOSED_TABLE;

bool flag = false;


class State{
    int cells[GRID_LENGTH][GRID_LENGTH];
    int depth;
    int x_whitespace;
    int y_whitespace;
    State* parent;
    

    State(int d = 0, int x = 1, int y = 1, State* par = NULL){
        depth = d; 
        x_whitespace = x; 
        y_whitespace = y; 
        parent = par;
    }


    State* search(State & p);

    bool is_aim();

    void produce_children();

    State* produce_single_child();

    bool is_in_table(vector<State*> table, State* p);
};