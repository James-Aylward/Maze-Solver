// Written by James Aylward


#include <iostream>
#include <vector>

#include <Maze.h>
#include <Graph.h>
#include <MazeSolver.h>

using namespace std;


int main()
{
    Maze m;
    Graph g = m.convert_to_pathfinding_grid();


    MazeSolver ms(g);
    vector<int> path = ms.breadth_first_search();
    vector<int> path2 = ms.dijkstra();
    vector<int> path3 = ms.greedy_best_first_search();
    vector<int> path4 = ms.a_star();


    g.print_data();

    cout << "\nPath from b: ";
    for(vector<int>::iterator it = path.begin(); it != path.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << "\nPath from d: ";
    for(vector<int>::iterator it = path2.begin(); it != path2.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << "\nPath from g: ";
    for(vector<int>::iterator it = path3.begin(); it != path3.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << "\nPath from a: ";
    for(vector<int>::iterator it = path4.begin(); it != path4.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << "\n";

}

