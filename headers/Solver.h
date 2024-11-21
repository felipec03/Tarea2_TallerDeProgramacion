#include "State.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>

class ColoringOperation {
    public:
        State *best;

        ColoringOperation();
        int greedyColoring(State *s);
        int backtrack(State *s);
};