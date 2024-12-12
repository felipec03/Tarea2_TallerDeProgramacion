// Solver.cpp
#include "Solver.h"

// Constructor
Solver::Solver() {
    best = nullptr;
    OptActual = INT_MAX;
}

// Function to compute upper bound using greedy coloring
int Solver::greedyUpperBound(State* s) {
    State tempState(*s);
    int colorsUsed = greedyColoring(&tempState);
    return colorsUsed;
}

// Function to compute lower bound using MaxClique heuristic
int Solver::maxCliqueLowerBound(State* s) {
    // Implement a simple heuristic to find a clique
    int maxCliqueSize = 1;
    for (int vertex : s->uncoloredVertices) {
        int cliqueSize = 1;
        for (int neighbor : s->graph.vertexNeighbors[vertex]) {
            if (s->uncoloredVertices.find(neighbor) != s->uncoloredVertices.end()) {
                cliqueSize++;
            }
        }
        if (cliqueSize > maxCliqueSize) {
            maxCliqueSize = cliqueSize;
        }
    }
    return maxCliqueSize;
}

// Main branch and bound coloring function
void Solver::branchAndBoundColoring(State* s) {
    // Use greedy coloring to get initial upper bound
    OptActual = greedyUpperBound(s);
    if (best != nullptr) {
        delete best;
    }
    best = new State(*s);

    // Start backtracking
    backtrackBB(s);
}

// Backtracking function
bool Solver::backtrackBB(State* s) {
    // If all vertices are colored
    if (s->isAllColored()) {
        size_t usedColors = s->graph.getNumberOfColors();
        if (usedColors < OptActual) {
            OptActual = usedColors;
            delete best;
            best = new State(*s);
        }
        return usedColors == s->maxColors;
    }

    // Calculate lower bound
    int lowerBound = maxCliqueLowerBound(s);
    if (static_cast<size_t>(lowerBound) >= OptActual) {
        return false;
    }

    // Select vertex to color
    int vertex = selectVertexMRV(s);

    // Try all possible colors up to OptActual - 1
    for (int color = 0; static_cast<size_t>(color) < OptActual; ++color) {
        if (s->graph.canColor(vertex, color)) {
            s->pushColorSelectVertex(vertex, color);
            if (backtrackBB(s)) {
                s->undoColor(vertex);
                return true;
            }
            s->undoColor(vertex);
        }
    }
    return false;
}

// Function to select the next vertex to color using MRV heuristic
int Solver::selectVertexMRV(State* s) {
    int selectedVertex = -1;
    int minRemainingValues = INT_MAX;
    for (int vertex : s->uncoloredVertices) {
        // Count the number of available colors
        int availableColors = 0;
        for (int color = 0; static_cast<size_t>(color) < OptActual; ++color) {
            if (s->graph.canColor(vertex, color)) {
                availableColors++;
            }
        }
        if (availableColors < minRemainingValues) {
            minRemainingValues = availableColors;
            selectedVertex = vertex;
        }
    }
    return selectedVertex;
}

// Greedy coloring function
int Solver::greedyColoring(State* s) {
    while (!s->isAllColored()) {
        int vertex = selectVertexByDegree(s);
        std::unordered_set<int> neighborColors;
        for (int neighbor : s->graph.vertexNeighbors[vertex]) {
            if (s->isVertexColored(neighbor)) {
                neighborColors.insert(s->graph.vertexColor[neighbor]);
            }
        }
        int color = 0;
        while (neighborColors.count(color)) {
            color++;
        }
        s->pushColorSelectVertex(vertex, color);
    }
    return s->graph.getNumberOfColors();
}

// Function to select vertex by highest degree
int Solver::selectVertexByDegree(State* s) {
    int selectedVertex = -1;
    size_t maxDegree = 0;
    for (int vertex : s->uncoloredVertices) {
        size_t degree = s->graph.vertexNeighbors[vertex].size();
        if (degree > maxDegree) {
            maxDegree = degree;
            selectedVertex = vertex;
        }
    }
    return selectedVertex;
}