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
    co.bruteForceColoring(&s);
    cout << "Chromatic number found by brute-force: " << co.OptActual << endl;
    co.best->printColor();

    co.greedyColoring(&s);
    cout << "Chromatic number found by greedy: " << co.OptActual << endl;
    co.best->printColor(); 
    
    return 0;
}