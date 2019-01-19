// Written by James Aylward

#ifndef MAZE_H
#define MAZE_H

#include <Graph.h>
#include <unordered_map>

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3



class Maze
{
    public:
        Maze();

        Graph convert_to_pathfinding_grid();
        Graph convert_to_weighted_graph();

    private:
        /*
        S = Start
        F = Finish
        # = Wall
        *//*
        char _maze[4][3] = {{'S', '#', ' '},
                           {' ', ' ', ' '},
                           {' ', '#', ' '},
                           {'#', '#', 'F'}};*/

        char _maze[10][10] = {

            {'S', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' '},
            {'#', ' ', '#', ' ', '#', ' ', ' ', '#', '#', ' '},
            {' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'#', ' ', '#', ' ', '#', '#', ' ', ' ', '#', ' '},
            {' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#'},
            {' ', '#', ' ', ' ', '#', '#', '#', ' ', '#', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' '},
            {' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' '},
            {' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', 'F'},


        };

        char _get_offset(int offset, int current_row, int current_element);

};

#endif // MAZE_H
