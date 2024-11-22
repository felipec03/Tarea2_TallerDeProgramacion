// main.cpp
#include "headers/Solver.h"
#include "headers/FileReader.h"

int main() {
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;
    FileReader fr(filename);
    fr.readGraph();
    vector<vector<int>> edges = fr.getGraph();

    Graph graph(edges);
    State s(graph);
    ColoringOperation co;
    int greedyColors = co.greedyColoring(&s);
    co.OptActual = greedyColors;
    cout << "Number of colors in greedy coloring: " << greedyColors << endl;

    State s_bnb(graph);
    co.branchAndBound(&s_bnb);
    cout << "Number of colors in branch and bound: " << co.OptActual << endl;
    co.best->printColor();
    return 0;
}