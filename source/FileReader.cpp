// FileReader.cpp
#include "FileReader.h"

FileReader::FileReader(string filename) {
    this->filename = filename;
    this->numVertices = 0;
    this->numEdges = 0;
}

void FileReader::readGraph() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    file >> numVertices >> numEdges;
    int u, v;
    while (file >> u >> v) {
        // Adjust indices if your input file uses 1-based indexing
        u--; 
        v--;
        edges.push_back({u, v});
    }
    file.close();
}

vector<vector<int>> FileReader::getGraph() {
    return edges;
}

int FileReader::getNumVertices() {
    return numVertices;
}

int FileReader::getNumEdges() {
    return numEdges;
}