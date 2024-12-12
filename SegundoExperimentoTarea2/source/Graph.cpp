#include "Graph.h"

// Constructor vacío
Graph::Graph() {
}

// Constructor basado en una lista de arcos
Graph::Graph(vector<vector<int>> edges) {
    for (vector<int> edge : edges) {
        vertexNeighbors[edge[0]].insert(edge[1]);
        vertexNeighbors[edge[1]].insert(edge[0]);
    }
}


// Método que devuelve el número de colores usados en el grafo
size_t Graph::getNumberOfColors() {
    // Se almacenan los colores en un conjunto para evitar repetidos
    unordered_set<int> colors;
    // Iteradores!!!
    for (auto par : vertexColor) {
        colors.insert(par.second);
    }
    // Basta con devolver el tamaño del conjunto
    return colors.size();
}

// Método que verifica si un vértice puede ser coloreado con un color dado
bool Graph::canColor(int vertex, int color) {
    // Se verifica si algún vecino ya tiene el color deseado
    for (int neighbor : vertexNeighbors[vertex]) {
        // Iterador que busca el color del vecino
        auto it = vertexColor.find(neighbor);
        // Si es que se encuentra y es igual al color deseado, se retorna falso
        if (it != vertexColor.end() && it->second == color) {
            return false;
        }
    }
    // Si no se encontró ningún vecino con el color deseado, se retorna verdadero
    return true;
}

// Método que imprime el grafo, estética
void Graph::printGraph() {
    for (auto const& par : vertexNeighbors) {
        cout << par.first << ": ";
        for (int neighbor : par.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}