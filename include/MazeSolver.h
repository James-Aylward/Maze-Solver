// Written by James Aylward

#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <queue>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <Graph.h>

class MazeSolver
{
    public:
        MazeSolver(Graph graph);
        std::vector<int> dijkstra();
        std::vector<int> breadth_first_search();
        std::vector<int> greedy_best_first_search();
        std::vector<int> a_star();


    private:
        std::vector<int> _construct_path(int start_id, int finish_id, std::unordered_map<int, int> came_from);

        int _heuristic(int point_a_id, int point_b_id);
        Graph _graph;

};

#endif // BREADTHFIRSTSEARCH_H
