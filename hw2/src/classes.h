#pragma once

#include <iostream>
#include <vector>

using namespace std;

#define GRID_LENGTH 3

class State {
public:
    int    cells[GRID_LENGTH][GRID_LENGTH];
    int    depth;
    int    x_whitespace;
    int    y_whitespace;
    State* parent;

    State(int level) { depth = level; }

    State* search();

    bool is_aim();

    void produce_children();

    State* produce_single_child();

    bool is_in_table(vector<State*> table, State* p);

    void init();
};