#include "State.h"

State::State(Graph graph) {
    this->graph = graph;
    for (auto const& par : graph.vertexNeighbors) {
        uncoloredVertices.insert(par.first);
    }
}

int State::getVertex(){
    auto it = uncoloredVertices.begin();
    if (it == uncoloredVertices.end()) {
        return -1;
    }
    return *it;
}

void State::pushColorSelectVertex(int vertex, int color) {
    graph.vertexColor[vertex] = color;
    coloredVertices.insert(vertex);
    uncoloredVertices.erase(vertex);
}

bool State::isVertexColored(int vertex) {
    return coloredVertices.find(vertex) != coloredVertices.end();
}

bool State::isAllColored() {
    return uncoloredVertices.size() == 0;
}

void State::printColor() {
    for (auto const& par : graph.vertexColor) {
        cout << par.first << "->" << par.second << " ";
    }
    cout << endl;
}

void State::incrementColor() {
    int c = graph.getNumberOfColors();
    availableColors.insert(c);
}