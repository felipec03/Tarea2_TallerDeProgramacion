#include "Solver.h"
#include <climits>

ColoringOperation::ColoringOperation() {
    best = nullptr;
    OptActual = INT_MAX;
}

int ColoringOperation::greedyColoring(State *s) {
    while (!s->isAllColored()) {
        int vertex = s->getVertex();
        for (int color : s->availableColors) {
            if (s->graph.canColor(vertex, color)) {
                s->pushColorSelectVertex(vertex, color);
                break;
            }
        }
        if (!s->isVertexColored(vertex)) {
            int c = s->graph.getNumberOfColors();
            s->pushColorSelectVertex(vertex, c);
            s->availableColors.insert(c);
        }
    }
    best = new State(*s);
    return s->graph.getNumberOfColors();
}

int ColoringOperation::branchAndBound(State *s) {
    if (s->isAllColored()) {
        int numColors = s->graph.getNumberOfColors();
        if (numColors < OptActual) {
            OptActual = numColors;
            delete best;
            best = new State(*s);
        }
        return numColors;
    }

    int LB = calculateLowerBound(s);
    if (LB >= OptActual) {
        return -1;
    }

    int vertex = selectVertex(s);
    vector<int> colors = getAvailableColors(s, vertex);

    for (int color : colors) {
        if (s->graph.canColor(vertex, color)) {
            State *s1 = new State(*s);
            s1->pushColorSelectVertex(vertex, color);
            branchAndBound(s1);
            delete s1;
        }
    }
    return OptActual;
}

// Método sencillo para computar el límite inferior de colores
int ColoringOperation::calculateLowerBound(State *s) {
    
    int maxDegree = 0;
    for (int vertex : s->uncoloredVertices) {
        int degree = s->graph.vertexNeighbors[vertex].size();
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    int lb = s->graph.getNumberOfColors();
    return lb + 1;
}

int ColoringOperation::selectVertex(State *s) {
    int maxDegree = -1;
    int selectedVertex = -1;
    for (int vertex : s->uncoloredVertices) {
        int degree = s->graph.vertexNeighbors[vertex].size();
        if (degree > maxDegree) {
            maxDegree = degree;
            selectedVertex = vertex;
        }
    }
    return selectedVertex;
}

vector<int> ColoringOperation::getAvailableColors(State *s, int vertex) {
    vector<int> colors;
    for (int color : s->availableColors) {
        colors.push_back(color);
    }
    colors.push_back(s->availableColors.size());
    return colors;
}

void ColoringOperation::bruteForceColoring(State *s) {
    int numVertices = s->graph.vertexNeighbors.size();
    for (int k = 1; k <= numVertices; ++k) {
        s->graph.vertexColor.clear();
        s->uncoloredVertices = ordered_set();
        s->coloredVertices = ordered_set();
        for (auto const& par : s->graph.vertexNeighbors) {
            s->uncoloredVertices.insert(par.first);
        }
        if (backtrack(s, 0, k)) {
            OptActual = k;
            best = new State(*s);
            break;
        }
    }
}

bool ColoringOperation::backtrack(State *s, size_t vertexIndex, int maxColors) {
    if (vertexIndex == s->graph.vertexNeighbors.size()) {
        return true;
    }

    int vertex = *std::next(s->uncoloredVertices.begin(), vertexIndex);
    for (int color = 0; color < maxColors; ++color) {
        if (s->graph.canColor(vertex, color)) {
            s->pushColorSelectVertex(vertex, color);
            if (backtrack(s, vertexIndex + 1, maxColors)) {
                return true;
            }
            s->undoColor(vertex);
        }
    }
    return false;
}