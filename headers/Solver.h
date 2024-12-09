#include "State.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>

class ColoringOperation {
public:
    State *best;
    int OptActual;

    ColoringOperation();
    int greedyColoring(State *s);
    int branchAndBound(State *s);

    void bruteForceColoring(State *s);
    bool backtrack(State *s, size_t vertexIndex, int maxColors);

    
    int calculateLowerBound(State *s);
    int selectVertex(State *s);
    std::vector<int> getAvailableColors(State *s, int vertex);
};