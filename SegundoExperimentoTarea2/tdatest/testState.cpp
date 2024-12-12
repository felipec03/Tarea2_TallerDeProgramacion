#include "State.h"

int main(){
    // Se hacen los arcos del grafo
    vector<vector<int>> edges = {
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3},
        {2, 3},
        {2, 4},
        {3, 4},
        {3, 5},
        {4, 5}
    };

    // Se crea el grafo
    Graph graph(edges);

    // Se crea un estado inicial
    State state(graph);

    int vertice = state.getVertex();
    cout << vertice << endl;

    

    return 0;
}