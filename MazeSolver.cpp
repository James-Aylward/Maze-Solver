// Written by James Aylward

#include "MAZESOLVER.h"

using namespace std;

MazeSolver::MazeSolver(Graph graph)
{
    _graph = graph;
}


vector<int> MazeSolver::dijkstra()
{
    priority_queue<Pair> frontier;
    Pair j(_graph.start_id, 0); // first is id, second is priority
    frontier.push(j);

    unordered_map<int, int> came_from; // store where each id came from
    unordered_map<int, int> cost_so_far; // will store the cost so far at each id

    came_from[_graph.start_id] = -1; // since this is the start, it didn't come from anything
    cost_so_far[_graph.start_id] = 0; // cost so far starts at 0

    while (!frontier.empty())
    {
        Pair current = frontier.top(); // grab highest priority id
        frontier.pop();

        if (current.first == _graph.finish_id) // if it's the finish, we exit and construct path
            break;

        vector<int> current_connections = _graph.connections[current.first]; // grab connections for current id
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it) // loop through connetions
        {
            // CHANGE 1 TO THE WEIGHTED VALUE
            int new_cost = cost_so_far[current.first] + 1; // calculate the new cost so far

            if(cost_so_far.find(*it) == cost_so_far.end() || new_cost < cost_so_far[*it]) // checks if id is on the frontier (hasn't been checked yet)
            {
                cost_so_far[*it] = new_cost; // assign new cost
                Pair j(*it, new_cost);
                frontier.push(j);
                came_from[*it] = current.first; // continue path
            }
        }
    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from); // make the path and return it
}


vector<int> MazeSolver::breadth_first_search()
{
    queue<int> frontier;
    frontier.push(_graph.start_id);

    unordered_map<int, int> came_from; // store where each id came from
    came_from[_graph.start_id] = -1; // since this is the start, it didn't come from anything

    while(!frontier.empty())
    {
        int current = frontier.front(); // grab the next id to search
        frontier.pop();

        if (current == _graph.finish_id) // if it's the finish, we exit and construct path
            break;

        vector<int> current_connections = _graph.connections[current]; // grab connections for current id
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it) // loop through connetions
        {
            if(came_from.find(*it) == came_from.end()) // checks if id is on the frontier (hasn't been checked yet)
            {
                frontier.push(*it); // add to the frontier
                came_from[*it] = current; // continue path
            }
        }

    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from); // make the path and return it
}


vector<int> MazeSolver::greedy_best_first_search()
{
    priority_queue<Pair> frontier;
    Pair j(_graph.start_id, 0); // first is id, second is priority
    frontier.push(j);

    unordered_map<int, int> came_from; // store where each id came from
    came_from[_graph.start_id] = -1; // since this is the start, it didn't come from anything

    while (!frontier.empty())
    {
        Pair current = frontier.top(); // grab highest priority id
        frontier.pop();

        if (current.first == _graph.finish_id) // if it's the finish, we exit and construct path
            break;

        vector<int> current_connections = _graph.connections[current.first]; // grab connections for current id
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it) // loop through connetions
        {
            if(came_from.find(*it) == came_from.end()) // checks if id is on the frontier (hasn't been checked yet)
            {
                int priority = _heuristic(_graph.finish_id, *it); // estimate distance from current to finish, make this priority
                Pair j(*it, priority);
                frontier.push(j);
                came_from[*it] = current.first; // continue path
            }
        }
    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from); // make the path and return it
}


vector<int> MazeSolver::a_star()
{
    priority_queue<Pair> frontier;
    Pair j(_graph.start_id, 0); // first is id, second is priority
    frontier.push(j);

    unordered_map<int, int> came_from; // store where each id came from
    unordered_map<int, int> cost_so_far; // will store the cost so far at each id

    came_from[_graph.start_id] = -1; // since this is the start, it didn't come from anything
    cost_so_far[_graph.start_id] = 0; // cost so far is 0

    while (!frontier.empty())
    {
        Pair current = frontier.top(); // grab highest priority id
        frontier.pop();

        if (current.first == _graph.finish_id) // if it's the finish, we exit and construct path
            break;

        vector<int> current_connections = _graph.connections[current.first]; // grab connections for current id
        for(vector<int>::iterator it = current_connections.begin(); it != current_connections.end(); ++it) // loop through connetions
        {
            // CHANGE 1 TO THE WEIGHTED VALUE
            int new_cost = cost_so_far[current.first] + 1; // calculate the new cost so far

            if(cost_so_far.find(*it) == cost_so_far.end() || new_cost < cost_so_far[*it]) // checks if id is on the frontier (hasn't been checked yet)
            {
                cost_so_far[*it] = new_cost; // assign new cost
                int priority = new_cost + _heuristic(_graph.finish_id, *it); // estimate distance from current to finish, make this priority
                Pair j(*it, priority);
                frontier.push(j);
                came_from[*it] = current.first; // continue path
            }
        }
    }

    return _construct_path(_graph.start_id, _graph.finish_id, came_from); // make the path and return it
}


vector<int> MazeSolver::_construct_path(int start_id, int finish_id, unordered_map<int, int> came_from)
{
    // Reconstruct path
    int current = finish_id; // start at finish
    vector<int> path;

    while(current != start_id) // while not at start
    {
        path.push_back(current); // push current into vector
        current = came_from[current]; // find the id preceding current and assign it to current
    }

    path.push_back(start_id);

    return path;
}


int MazeSolver::_heuristic(int point_a_id, int point_b_id) // heuristic function to estimate distance between two points
{
    pair<int, int> point_a = _graph.coordinates[point_a_id];
    pair<int, int> point_b = _graph.coordinates[point_b_id];


    return abs(point_a.first - point_b.first) + abs(point_a.second - point_b.second);
}
