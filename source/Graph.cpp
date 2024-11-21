#include "Graph.h"

Graph::Graph() {
}

Graph::Graph(vector<vector<int>> edges) {
    for (vector<int> edge : edges) {
        vertexNeighbors[edge[0]].insert(edge[1]);
        vertexNeighbors[edge[1]].insert(edge[0]);
    }
}

int Graph::getNumberOfColors() {
    ordered_set colors;
    for (auto par : vertexColor) {
        colors.insert(par.second);
    }
    return colors.size();
}

bool Graph::canColor(int vertex, int color) {
    for (int neighbor : vertexNeighbors[vertex]) {
        if (vertexColor.find(neighbor) != vertexColor.end() && 
            vertexColor[neighbor] == color) {
            return false;
        }
    }
    return true;
}

void Graph::printGraph() {
    for (auto const& par : vertexNeighbors) {
        cout << par.first << ": ";
        for (int neighbor : par.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}