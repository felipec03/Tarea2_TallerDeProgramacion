// State.cpp
#include "State.h"

// Constructor
State::State(Graph graph) {
    this->graph = graph;
    for (auto const& par : graph.vertexNeighbors) {
        uncoloredVertices.insert(par.first);
    }
    maxColors = graph.vertexNeighbors.size();
}

// Obtenemos el vértice a colorear
int State::getVertex(){
    auto it = uncoloredVertices.begin();
    if (it == uncoloredVertices.end()) {
        return -1;
    }
    return *it;
}

// Coloreamos un vértice
void State::pushColorSelectVertex(int vertex, int color) {
    // Se almacena el color del vértice
    graph.vertexColor[vertex] = color;
    coloredVertices.insert(vertex);
    uncoloredVertices.erase(vertex);
}

// Se verifica si un vértice ya fue coloreado
bool State::isVertexColored(int vertex) {
    return coloredVertices.find(vertex) != coloredVertices.end();
}

// Se verifica si todos los vértices ya fueron coloreados
bool State::isAllColored() {
    return uncoloredVertices.size() == 0;
}

// Se imprime el color de los vértices
void State::printColor() {
    for (auto const& par : graph.vertexColor) {
        cout << par.first << " -> " << par.second << " ";
    }
    cout << endl;
}

// Método para devolverse en la decisión de colorear un vértice
void State::undoColor(int vertex) {
    graph.vertexColor.erase(vertex);
    coloredVertices.erase(vertex);
    uncoloredVertices.insert(vertex);
}