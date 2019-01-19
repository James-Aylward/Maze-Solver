// Written by James Aylward

#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>

class Graph
{
    public:
        std::unordered_map<int, std::vector<int>> connections;
        std::unordered_map<int, std::pair<int, int>> coordinates;

        int start_id;
        int finish_id;


        void print_data()
        {
            std::cout << "\n\nCOORDINATES:\n";
            for (std::unordered_map<int, std::pair<int, int>>::iterator it = coordinates.begin(); it != coordinates.end(); it++ )
            {
                std::cout << it->first << ": ";

                std::cout << it->second.first << " " << it->second.second << "\n";
            }


            std::cout << "\n\nCONNECTIONS:\n";
            for (std::unordered_map<int, std::vector<int>>::iterator it = connections.begin(); it != connections.end(); it++ )
            {
                std::cout << it->first << ": ";

                std::vector<int> test = it->second;
                for(std::vector<int>::iterator it = test.begin(); it != test.end(); ++it)
                {
                    std::cout << *it << " ";
                }

                std::cout << "\n";

            }

            std::cout << "\nSTART ID: " << start_id << "\nEND ID: " << finish_id << std::endl;
        }
};

#endif // GRAPH_H
