#include "Solver.h"

ColoringOperation::ColoringOperation() {
    best = nullptr;
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
        s->printColor();
    }
    best = s;
    return s->graph.getNumberOfColors();
}

int ColoringOperation::backtrack(State *s) {
    if (s->isAllColored()) {
        if (best == nullptr || 
            s->graph.getNumberOfColors() < best->graph.getNumberOfColors()) {
            best = s;
        }
        return best->graph.getNumberOfColors();
    } else {
        int vertex = s->getVertex();
        s->incrementColor();
        for(int color : s->availableColors) {
            if (s->graph.canColor(vertex, color)) {
                State *s1 = new State(*s);
                s1->pushColorSelectVertex(vertex, color);
                backtrack(s1);
            }
        }
        return best->graph.getNumberOfColors();
    }
}