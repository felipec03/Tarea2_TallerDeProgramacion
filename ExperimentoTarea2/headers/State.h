// Estado de decisión
// Se utilizarán dos conjuntos ordenados de la librería pb_ds de GNU para almacenar los vértices coloreados y no coloreados.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;
using namespace __gnu_pbds;

// Se debe definir
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// Clase estado, se utilizará como un snapshot de un estado de decisión
class State {
    public:
        // Atributos
        // Vertices no coloreados
        ordered_set uncoloredVertices;
        // Vertices ya coloreados
        ordered_set coloredVertices;
        // Grafo
        Graph graph;
        // Cantidad máxima de colores de un estado en particular
        size_t maxColors;

        // Métodos
        State();
        State(Graph graph);
        int getVertex();
        void pushColorSelectVertex(int vertex, int color);
        bool isVertexColored(int vertex);
        bool isAllColored();
        void printColor();
        void undoColor(int vertex);
};