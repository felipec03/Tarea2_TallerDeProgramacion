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
    Solver co;
    
    // Inicio cronómetro
    auto start = std::chrono::system_clock::now();

    // Solución por Branch and Bound
    co.branchAndBoundColoring(&s);
    cout << "Aproximación de Número Cromático con Branch and Bound: " << co.OptActual << endl;

    cout << "Secuencia de colores: " << endl;
    co.best->printColor();
    
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<float,std::milli> duration = end - start;

    cout << "Se demoró: " << duration.count() << "[ms]"<< endl;

    getchar();

    return 0;
}