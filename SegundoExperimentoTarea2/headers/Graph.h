#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Clase que representa un grafo no dirigido no ponderado
class Graph{
    public:
        // Atributos
        unordered_map<int, unordered_set<int>> vertexNeighbors; // vértice -> vecinos
        unordered_map<int, int> vertexColor; // vértice -> colores

        // Métodos
        Graph();
        Graph(vector<vector<int>> edges);
        size_t getNumberOfColors();
        bool canColor(int vertex, int color);
        void printGraph();
};