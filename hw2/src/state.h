#pragma once

#include <iostream>
#include <vector>

#define GRID_LENGTH 3

class State {
public:
    int    cells[GRID_LENGTH][GRID_LENGTH];
    int    depth;
    int    x_whitespace;
    int    y_whitespace;
    State* parent;

    State(int level) { depth = level; }

    State* search_width_first();
    State* search_depth_first();

    bool is_aim();

    void produce_children();
    void produce_children_depth_first();

    State* produce_single_child();

    bool is_in_table(std::vector<State*> table, State* p);

    void test();
    

    void init();
    void randomly_init();
};