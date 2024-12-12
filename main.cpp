// main.cpp
#include "headers/Solver.h"
#include "headers/FileReader.h"
#include <chrono>

using namespace std;

int main() {
    // Lectura del archivo
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;
    FileReader fr(filename);
    fr.readGraph();
    vector<vector<int>> edges = fr.getGraph();

    // Creación del grafo y el estado
    Graph graph(edges);
    State s(graph);
    ColoringOperation co;
    
    // Solución por Branch and Bound
    auto start = std::chrono::system_clock::now();

    co.branchAndBoundColoring(&s);
    cout << "Aproximación de Número Cromático con Branch and Bound: " << co.OptActual << endl;
    co.best->printColor();
    
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<float,std::milli> duration = end - start;

    cout << "Se demoró: " << duration.count() << "[s]"<< endl;

    getchar();

    return 0;
}