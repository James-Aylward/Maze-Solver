// Written by James Aylward

#include "Maze.h"

#include <iostream>

using namespace std;


Maze::Maze()
{
    // contructor
}


Graph Maze::convert_to_pathfinding_grid()
{
    Graph graph;
    int id_count = 0;

    unordered_map<int, int> above;

    for (int i = 0; i < sizeof(_maze)/sizeof(*_maze); i++)
    {
        int left_id;

        for (int j = 0; j < sizeof(_maze[0])/sizeof(*_maze[0]); j++)
        {
            // Manipulate and check an element

            if (_maze[i][j] != '#')
            {
                vector<int> connection_data;
                pair<int, int> coordinates;

                coordinates.first = i;
                coordinates.second = j;

                // Check if spot to the left is a valid space - make a connection
                if (_get_offset(LEFT, i, j) != '#')
                {
                    connection_data.push_back(left_id);
                    graph.connections[left_id].push_back(id_count);
                }

                // Check if the current space is below another valid space - make a connection and delete the note
                if (above.find(j) != above.end())
                {
                    connection_data.push_back(above[j]);
                    graph.connections[above[j]].push_back(id_count);
                    above.erase(j);
                }

                // If the current space is above another valide space - keep note
                if (_get_offset(DOWN, i, j) != '#')
                {
                    above[j] = id_count;
                }

                // Check if the current spot is the starting position
                if (_maze[i][j] == 'S')
                {
                    graph.start_id = id_count;
                }

                // Check if the current spot is the finishing position
                if (_maze[i][j] == 'F')
                {
                    graph.finish_id = id_count;
                }

                left_id = id_count;
                graph.coordinates[id_count] = coordinates;
                graph.connections[id_count] = connection_data;
                id_count++;
            }

        }
    }

    return graph;
}


char Maze::_get_offset(int offset, int current_row, int current_element)
{
    // Get new coordinates
    if (offset == UP) {current_row--;}
    else if (offset == DOWN) {current_row++;}
    else if (offset == LEFT) {current_element--;}
    else if (offset == RIGHT) {current_element++;}

    // Check if coordinates are valid
    if (current_row < 0 || current_element < 0 || current_element > sizeof(_maze[0]) / sizeof(*_maze[0]) - 1 || current_row > sizeof(_maze) / sizeof(*_maze) - 1)
        return '#';

    // Return element at new coordinates
    return _maze[current_row][current_element];
}
