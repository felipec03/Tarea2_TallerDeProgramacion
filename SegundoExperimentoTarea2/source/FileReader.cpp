// FileReader.cpp
#include "FileReader.h"

// Constructor genérico
FileReader::FileReader(string filename) {
    this->filename = filename;
    this->numVertices = 0;
    this->numEdges = 0;
}


// Función útil: Lee el grafo presentado en archivo de texto
void FileReader::readGraph() {
    // Se usa fstream
    ifstream file(filename);
    // Si no se puede abrir el archivo, se imprime un mensaje de error
    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    // Se lee el número de vértices y aristas
    file >> numVertices >> numEdges;
    int u, v;
    while (file >> u >> v) {
        // Se hace un ajuste a los índices
        // En caso de que los vértices estén indexados desde 1
        u--; 
        v--;
        edges.push_back({u, v});
    }
    // Buena práctica: cerrar el archivo
    file.close();
}

// Getters, fome.
vector<vector<int>> FileReader::getGraph() {
    return edges;
}

int FileReader::getNumVertices() {
    return numVertices;
}

int FileReader::getNumEdges() {
    return numEdges;
}