#include "headers/Solver.h"

int main() {
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 5}, {1, 6},
        {2, 3}, {2, 6}, {2, 7},
        {3, 4}, {3, 7}, {3, 8},
        {4, 8}, {4, 9},
        {5, 6}, {6, 7}, {7, 8}, {8, 9},
        {5, 10}, {6, 10}, {7, 11}, {8, 11},
        {10, 11}, {10, 12}, {11, 12} 
    };
    Graph graph(edges);
    graph.printGraph();
    State s(graph);
    s.printColor();
    ColoringOperation co;
    int c = co.backtrack(&s);
    cout << "Numero de colores backtrack : " << c << endl;
    co.best->printColor();
    return 0;
}