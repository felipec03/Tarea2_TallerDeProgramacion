#include "State.h"
#include <climits>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
// Utilización de Policy Based Data Structures de GNU, importante.
using namespace __gnu_pbds;

// Clase que apunta a resolver el problema de coloreo de grafos
// Prácticamente, la única clase necesaria
class Solver {
    public:
        State *best;
        size_t OptActual;

        Solver();
        int greedyColoring(State *s);
        int greedyUpperBound(State* s);

        int maxCliqueLowerBound(State* s);
        int rlfUpperBound(State *s);
        int selectVertexMRV(State* s);
        void branchAndBoundColoring(State *s);
        bool backtrackBB(State *s);

        int selectVertexByDegree(State* s);

};;
