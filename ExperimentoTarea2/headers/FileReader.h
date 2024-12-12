#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// Clase auxiliar para lectura de archivos
class FileReader {

    // Atributos
    private:
        string filename;
        vector<vector<int>> edges;
        int numVertices;
        int numEdges;
    // Métodos
    public:
        FileReader(string filename);
        void readGraph();
        // En base a una representación de lista de adyacencia, devuelve los 
        // vértices adyacentes a un vértice
        vector<vector<int>> getGraph();
        // Getters
        int getNumVertices();
        int getNumEdges();
};