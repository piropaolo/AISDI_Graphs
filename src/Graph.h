//
// Created by volterra on 06.01.17.
//

#ifndef GRAFY_GRAPH_H
#define GRAFY_GRAPH_H

#include <fstream>
#include <vector>
#include <algorithm>

class Graph {
public:
    Graph(char *fileName);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    void print();
    void sort();
    void permutate(std::vector<int> key);
    int v, e;
    std::vector<std::vector<int>> body;

private:
    std::fstream file;
    char *fileName;
};


#endif //GRAFY_GRAPH_H
