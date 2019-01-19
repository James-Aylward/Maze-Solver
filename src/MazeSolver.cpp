// Written by James Aylward

#include "MAZESOLVER.h"

using namespace std;

MazeSolver::MazeSolver(Graph graph)
{
    _graph = graph;
}


vector<int> MazeSolver::dijkstra()
{
    priority_queue<pair<int, int>> frontier;
    pair<int, int> j;
    j.first = _graph.start_id; // id
    j.second = 0; // priority
    frontier.push(j);

    unordered_map<int, int> came_from;
    unordered_map<int, int> cost_so_far;

    came_from[_graph.start_id] = -1;
    cost_so_far[_graph.start_id] = 0;

    while (!frontier.empty())
    {
        pair<int, int> current = frontier.top();
        frontier.pop();

        if (current.first == _graph.finish_id)
            break;

        vector<int> current_connections = _graph.connections[current.first];
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it)
        {
            // CHANGE 1 TO THE WEIGHTED VALUE
            int new_cost = cost_so_far[current.first] + 1;

            if(cost_so_far.find(*it) == cost_so_far.end() || new_cost < cost_so_far[*it])
            {
                cost_so_far[*it] = new_cost;
                int priority = new_cost;
                pair<int, int> j;
                j.first = *it;
                j.second = priority;
                frontier.push(j);
                came_from[*it] = current.first;
            }
        }
    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from);
}


vector<int> MazeSolver::breadth_first_search()
{
    queue<int> frontier;
    frontier.push(_graph.start_id);

    unordered_map<int, int> came_from;
    came_from[_graph.start_id] = -1;

    while(!frontier.empty())
    {
        int current = frontier.front();
        frontier.pop();

        if (current == _graph.finish_id)
            break;

        vector<int> current_connections = _graph.connections[current];
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it)
        {
            if(came_from.find(*it) == came_from.end())
            {
                frontier.push(*it);
                came_from[*it] = current;
            }
        }

    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from);
}


vector<int> MazeSolver::greedy_best_first_search()
{
    priority_queue<pair<int, int>> frontier;
    pair<int, int> j;
    j.first = _graph.start_id; // id
    j.second = 0; // priority
    frontier.push(j);

    unordered_map<int, int> came_from;
    came_from[_graph.start_id] = -1;

    while (!frontier.empty())
    {
        pair<int, int> current = frontier.top();
        frontier.pop();

        if (current.first == _graph.finish_id)
            break;

        vector<int> current_connections = _graph.connections[current.first];
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it)
        {
            if(came_from.find(*it) == came_from.end())
            {
                int priority = _heuristic(_graph.finish_id, *it);
                pair<int, int> j;
                j.first = *it;
                j.second = priority;
                frontier.push(j);
                came_from[*it] = current.first;
            }
        }
    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from);
}


vector<int> MazeSolver::a_star()
{
    priority_queue<pair<int, int>> frontier;
    pair<int, int> j;
    j.first = _graph.start_id; // id
    j.second = 0; // priority
    frontier.push(j);

    unordered_map<int, int> came_from;
    unordered_map<int, int> cost_so_far;

    came_from[_graph.start_id] = -1;
    cost_so_far[_graph.start_id] = 0;

    while (!frontier.empty())
    {
        pair<int, int> current = frontier.top();
        frontier.pop();

        if (current.first == _graph.finish_id)
            break;

        vector<int> current_connections = _graph.connections[current.first];
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it)
        {
            // CHANGE 1 TO THE WEIGHTED VALUE
            int new_cost = cost_so_far[current.first] + 1;

            if(cost_so_far.find(*it) == cost_so_far.end() || new_cost < cost_so_far[*it])
            {
                cost_so_far[*it] = new_cost;
                int priority = new_cost + _heuristic(_graph.finish_id, *it);
                pair<int, int> j;
                j.first = *it;
                j.second = priority;
                frontier.push(j);
                came_from[*it] = current.first;
            }
        }
    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from);
}


vector<int> MazeSolver::_construct_path(int start_id, int finish_id, unordered_map<int, int> came_from)
{
    // Reconstruct path
    int current = finish_id;
    vector<int> path;

    while(current != start_id)
    {
        path.push_back(current);
        current = came_from[current];
    }

    path.push_back(start_id);

    return path;
}


int MazeSolver::_heuristic(int point_a_id, int point_b_id)
{
    pair<int, int> point_a = _graph.coordinates[point_a_id];
    pair<int, int> point_b = _graph.coordinates[point_b_id];


    return abs(point_a.first - point_b.first) + abs(point_a.second - point_b.second);
}
