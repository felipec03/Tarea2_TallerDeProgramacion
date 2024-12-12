// Graph.h
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph{
    public:
    unordered_map<int, unordered_set<int>> vertexNeighbors; // vertex -> neighbors
    unordered_map<int, int> vertexColor; // vertex -> color

    Graph();
    Graph(vector<vector<int>> edges);
    size_t getNumberOfColors();
    bool canColor(int vertex, int color);
    void printGraph();
};