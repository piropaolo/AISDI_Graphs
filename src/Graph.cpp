//
// Created by volterra on 06.01.17.
//

#include <iostream>
#include "Graph.h"

Graph::Graph(char *fileName) {
    v = e = 0;

    file.open(fileName, std::ios::in);
    if (!file.good())   std::cout << "File opening error." << std::endl;
    file >> v;
    for (int i = 0; i < v ; ++i) {
        std::vector<int> row;
        row.push_back(i);
        body.push_back(row);
    }
    int tmp1, tmp2;
    while (file >> tmp1 >> tmp2) {
        body[tmp1].push_back(tmp2);
        if(tmp1 != tmp2)
            body[tmp2].push_back(tmp1);
        ++e;
    }
    file.close();
}

Graph::Graph(const Graph &other) {
    v = other.v;
    e = other.e;
    for (int i = 0; i < v; ++i) {
        std::vector<int> row;
        for (auto it = other.body[i].begin(); it != other.body[i].end(); ++it)
            row.push_back(*it);
        body.push_back(row);
    }
}

Graph &Graph::operator=(const Graph &other) {
    v = other.v;
    e = other.e;
    if (this != &other){
        body.erase(body.begin(), body.end());
    }
    for (int i = 0; i < v; ++i) {
        std::vector<int> row;
        for (auto it = other.body[i].begin(); it != other.body[i].end(); ++it)
            row.push_back(*it);
        body.push_back(row);
    }
    return *this;
}

void Graph::print() {
    for (int i = 0; i < v; ++i) {
        for (auto it = body[i].begin(); it != body[i].end() ; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Number of vertices: " << v << std::endl;
    std::cout << "Number of edges: " << e << std::endl;
}

void Graph::sort() {
    for (int i = 0; i < v ; ++i) {
        std::sort(body[i].begin()+1, body[i].end(), std::less<int>());
    }
    std::sort(body.begin(), body.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] < b[0];
    });
}

void Graph::permutate(std::vector<int> key) {
    for (int i = 0; i < v; ++i) {
        for (auto it = body[i].begin(); it != body[i].end() ; ++it) {
            *it = key[*it];
        }
    }
}
