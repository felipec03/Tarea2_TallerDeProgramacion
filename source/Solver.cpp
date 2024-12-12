// Solver.cpp
#include "Solver.h"
#include <climits>
#include <algorithm>

ColoringOperation::ColoringOperation() {
    best = nullptr;
    OptActual = INT_MAX;
}

int ColoringOperation::greedyColoring(State *s) {
    // Sort vertices by decreasing degree
    vector<int> vertices;
    for (auto const& par : s->graph.vertexNeighbors) {
        vertices.push_back(par.first);
    }
    sort(vertices.begin(), vertices.end(), [&](int a, int b) {
        return s->graph.vertexNeighbors[a].size() > s->graph.vertexNeighbors[b].size();
    });

    for (int vertex : vertices) {
        for (size_t color = 0; color < s->graph.vertexNeighbors.size(); ++color) {
            if (s->graph.canColor(vertex, color)) {
                s->graph.vertexColor[vertex] = color;
                break;
            }
        }
    }
    best = new State(*s);
    return s->graph.getNumberOfColors();
}

size_t ColoringOperation::calculateLowerBound(State *s) {
    size_t maxDegree = 0;
    for (auto const& par : s->graph.vertexNeighbors) {
        size_t degree = par.second.size();
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    return maxDegree + 1;
}

int ColoringOperation::selectVertex(State *s) {
    int selectedVertex = -1;
    int minRemainingColors = INT_MAX;

    for (int vertex : s->uncoloredVertices) {
        int remainingColors = 0;
        for (size_t color = 0; color < s->maxColors; ++color) {
            if (s->graph.canColor(vertex, color)) {
                ++remainingColors;
            }
        }
        if (remainingColors < minRemainingColors) {
            minRemainingColors = remainingColors;
            selectedVertex = vertex;
        }
    }
    return selectedVertex;
}

void ColoringOperation::branchAndBoundColoring(State *s) {
    OptActual = greedyColoring(new State(s->graph));
    best = new State(*s);

    s->maxColors = OptActual - 1;
    backtrackBB(s);
}

bool ColoringOperation::backtrackBB(State *s) {
    if (s->isAllColored()) {
        size_t usedColors = s->graph.getNumberOfColors();
        if (usedColors < OptActual) {
            OptActual = usedColors;
            delete best;
            best = new State(*s);
            s->maxColors = OptActual - 1;
        }
        return usedColors == s->maxColors;
    }

    size_t lowerBound = calculateLowerBound(s);
    if (lowerBound >= OptActual) {
        return false;
    }

    int vertex = selectVertex(s);
    for (size_t color = 0; color < s->maxColors; ++color) {
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