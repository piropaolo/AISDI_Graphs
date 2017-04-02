#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include "Graph.h"

bool areEqual(Graph &graph1, Graph &graph2) {
    for (int i = 0; i < graph1.v; ++i) {
        if (graph1.body[i].size() != graph2.body[i].size()) return false;
        for (auto it = graph1.body.begin(), jt = graph2.body.begin(); it != graph1.body.end(); ++it, ++jt) {
            if (*it != *jt) return false;
        }
    }
    return true;
}

bool areValid(Graph &graph1, Graph &graph2, std::vector<int> key) {
    std::vector<int>::iterator nr;

    for (int i = 0; i < graph1.v; ++i) {
        if (graph1.body[i].size() != graph2.body[key[i]].size()) return false;
        if (!std::is_permutation (graph1.body[i].begin()+1, graph1.body[i].end(),
                                 graph2.body[key[i]].begin()+1)) return false;
    }
    return true;
}

bool findIsomorphism(Graph &graph1, Graph &graph2) {
    if (graph1.v != graph2.v || graph1.e != graph2.e)   {
        std::cout << "Nieizomorficzne" << std::endl;
        return false;
    }

    std::vector<int> key;
    for (int i = 0; i < graph1.v ; ++i) {
        key.push_back(i);
    }
    Graph graph3(graph1);

    graph2.sort();
    do {
        graph3 = graph1;
        graph3.permutate(key);
        //graph3.sort();
        if (areValid(graph3, graph2, key)){
            //graph1.print();
            //graph3.print();

            std::cout << "Izomorficzne" << std::endl;
            for (int i = 0; i < key.size() ; ++i) {
                std::cout << i <<" --> "<< key[i] << std::endl;
            }
            return true;
        }
    }   while(std::next_permutation(key.begin(), key.end()));
    std::cout << "Nieizomorficzne" << std::endl;
    return false;

}

int main(int argc, char **argv) {
    if (argc != 3)  {
        std::cout << "Where are the files?" << std::endl;
        return 0;
    }
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Graph graph1(argv[1]);
    Graph graph2(argv[2]);
    findIsomorphism(graph1, graph2);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}