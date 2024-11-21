#include <iostream>
#include <string>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

class Graph{
    public:
    gp_hash_table<int, ordered_set> vertexNeighbors; // vertex -> neighbors
    gp_hash_table<int, int> vertexColor; // vertex -> color

    Graph();
    Graph(vector<vector<int>> edges);
    int getNumberOfColors();
    bool canColor(int vertex, int color);
    void printGraph();
};