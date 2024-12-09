#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

class State {
    public:
    ordered_set uncoloredVertices;
    ordered_set coloredVertices;
    ordered_set availableColors;
    Graph graph;

    State();
    State(Graph graph);
    int getVertex();
    void pushColorSelectVertex(int vertex, int color);
    bool isVertexColored(int vertex);
    bool isAllColored();
    void printColor();
    void undoColor(int vertex);
    void incrementColor();
};