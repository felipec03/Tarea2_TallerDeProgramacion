#include "Graph.h"

int main(){
    // Se crea un vector que representa los arcos del grafo
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}};
    // Se crea un grafo con un constructor
    Graph g(edges);
    
    // Se imprime el grafo
    g.printGraph();

    return 0;
}