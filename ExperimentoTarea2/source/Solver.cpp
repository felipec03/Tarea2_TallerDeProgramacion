// Solver.cpp
#include "Solver.h"

// Constructor 
Solver::Solver() {
    best = nullptr;
    OptActual = INT_MAX;
}

// Función greedyColoring
int Solver::greedyColoring(State *s){
        while (!s->isAllColored()) {
            // seleccionamos un vertice y lo coloreamos
            int vertex = s->getVertex(); // necesitamos obtener un vértice no coloreado
            // encuentro el primer color disponible que sea factible (no igual al un color de vecinos)
            for (int color : s->uncoloredVertices) {
                if (s->graph.canColor(vertex, color)) {
                    s->pushColorSelectVertex(vertex, color);
                    break; // ya encontramos un color y actualizamos el estado
                }
            }
            // consulto si no se pudo colorear el vertice vertex
            if (!s->isVertexColored(vertex)) { // entonces debo colorearlo con un nuevo color
                int c = s->graph.getNumberOfColors();
                s->pushColorSelectVertex(vertex, c);
                s->uncoloredVertices.insert(c);
            }
            s->printColor();
        }
        best = s; // el mejor estado es el estado actual
        return s->graph.getNumberOfColors(); // retornamos el numero de colores
    }

// Algoritmo maestro, recopila los métodos de la clase Solver
void Solver::branchAndBoundColoring(State *s) {
    // Cómo óptimo inicial, se usa RLF
    OptActual = rlfUpperBound(s); 
    best = new State(*s);

    // Se realiza el backtrack
    s->maxColors = OptActual - 1;
    backtrackBB(s);
}

// Función con toda la lógica del Branch and Bound
bool Solver::backtrackBB(State *s) {

    // CASO BASE:
    // Si se colorearon todos los vértices
    if (s->isAllColored()) {
        // Se obtiene el número de colores utilizados
        size_t usedColors = s->graph.getNumberOfColors();
        // Si es que se utilizó menos colores que el óptimo actual
        if (usedColors < OptActual) {
            // Se considera el nuevo óptimo
            OptActual = usedColors;
            delete best;
            best = new State(*s);
            s->maxColors = OptActual - 1;
        }
        // Se retorna si se utilizó la cantidad máxima de colores
        return usedColors == s->maxColors;
    }

    // Se calcula el límite inferior con heurística de DSatur
    size_t lowerBound = calculateLowerBound(s);
    // Si llega a ser mayor o igual al óptimo actual, se retorna falso
    // Osease, no significa un camino prometedor
    if (lowerBound >= OptActual) {
        return false;
    }

    // Se saca un vértice de la lista de vértices no coloreados
    // Se utiliza la heurística MRV, definida mas abajo
    int vertex = selectVertex(s);

    // Para cada color posible
    for (size_t color = 0; color < s->maxColors; ++color) {
        // Si es posible colorear el vértice con el color
        if (s->graph.canColor(vertex, color)) {
            // Se colorea el vértice
            s->pushColorSelectVertex(vertex, color);
            // Paso recursivo
            if (backtrackBB(s)) {
                s->undoColor(vertex);
                return true;
            }
            s->undoColor(vertex);
        }
    }
    // Si no se pudo colorear el vértice
    return false;
}

// Función que calcula el límite superior con la heurística RLF
int Solver::rlfUpperBound(State *s) {

    // Aprovechamos la estructura de datos de árbol de búsqueda de pb_ds
    int numColors = 0;
    ordered_set uncoloredVertices = s->uncoloredVertices;
    unordered_map<int, int> degrees;

    // Para cada vertice en los vertices no coloreados
    for (int v : uncoloredVertices) {
        // Se calcula el grado de cada vértice
        degrees[v] = s->graph.vertexNeighbors[v].size();
    }

    // Mientras queden vértices por colorear
    while (!uncoloredVertices.empty()) {

        numColors++;
        // Se declara el conjunto máximo independiente
        unordered_set<int> independentSet;

        // Se debe seleccionar el vértice con mayor grado
        // max_element viene de GNU y se le pasa una función lambda
        int vertex = *max_element(uncoloredVertices.begin(), uncoloredVertices.end(),
                                  [&](int a, int b) { return degrees[a] < degrees[b]; });

        // Se colorea el vértice
        independentSet.insert(vertex);
        uncoloredVertices.erase(vertex);

        // Construcción del conjunto independiente
        // Para cada vértice no coloreado
        for (auto it = uncoloredVertices.begin(); it != uncoloredVertices.end();) {
            // Flag para saber si es independiente
            bool isIndependent = true;

            // Para cada vértice en el conjunto independiente
            for (int v : independentSet) {
                // Si el vértice no es independiente
                if (s->graph.vertexNeighbors[v].count(*it)) {
                    // Se marca y se detiene
                    isIndependent = false;
                    break;
                }
            }
            // si se considera independiente
            if (isIndependent) {
                // Se agrega al conjunto independiente
                independentSet.insert(*it);
                it = uncoloredVertices.erase(it);
            } else {
                ++it;
            }
        }

        // Se asignan colores al conjunto independiente
        // Para cada vértice en el conjunto independiente
        for (int v : independentSet) {
            s->graph.vertexColor[v] = numColors;
        }
    }
    return numColors;
}

// Envoltorio para computar el límite inferior
// No es realmente necesario, pero si útil para pruebas modulares.
size_t Solver::calculateLowerBound(State *s) {
    return dsaturLowerBound(s); 
}

// Heurística DSatur para límite inferior
size_t Solver::dsaturLowerBound(State *s) {

    // Se definen los mapas de saturación y colores
    unordered_map<int, int> saturation;
    unordered_map<int, bool> colored;
    
    // Para cada vértice en los vecinos del grafo
    for (const auto& par : s->graph.vertexNeighbors) {
        // Se inicializan los mapas
        saturation[par.first] = 0;
        colored[par.first] = false;
    }

    // Se inicializa el vector de vértices
    std::vector<int> vertices;
    // Para cada vértice en los vecinos del grafo
    for (const auto& par : s->graph.vertexNeighbors) {
        // Se agregan los vértices al vector
        vertices.push_back(par.first);
    }

    int maxColor = -1;

    // Mientras queden vértices por colorear
    while (true) {
        // Se elige el vértice con mayor saturación
        int vertex = -1;
        int maxSat = -1;
        size_t maxDegree = 0;  

        // Para cada vértice
        for (int v : vertices) {
            // Si no está coloreado
            if (!colored[v]) {
                // Criterio: saturación y grado
                // Si la saturación es mayor o igual al máximo, entonces se actualiza
                if (saturation[v] > maxSat || (saturation[v] == maxSat && s->graph.vertexNeighbors[v].size() > maxDegree)) {
                    maxSat = saturation[v];
                    maxDegree = s->graph.vertexNeighbors[v].size();
                    vertex = v;
                }
            }
        }

        // Si no se encontró vértice, se detiene
        if (vertex == -1) break; 

        // Se busca asignar el color más pequeño posible
        unordered_set<int> neighborColors;

        // Para cada vecino del vértice
        for (int neighbor : s->graph.vertexNeighbors[vertex]) {
            // Si se encuentra coloreado
            if (colored[neighbor]) {
                // Se agrega el color al conjunto
                neighborColors.insert(s->graph.vertexColor[neighbor]);
            }
        }


        int color = 0;
        while (neighborColors.count(color)) {
            color++;
        }

        s->graph.vertexColor[vertex] = color;
        colored[vertex] = true;
        maxColor = std::max(maxColor, color);

        // Se actualizan los grados de saturación de los vecinos
        for (int neighbor : s->graph.vertexNeighbors[vertex]) {
            if (!colored[neighbor]) {
                saturation[neighbor] = neighborColors.size();
            }
        }
    }

    return maxColor + 1;
}


// Heurística MRV para seleccionar vértices
// MRV = Minimum Remaining Values
int Solver::selectVertex(State *s) {
    // Seleccionamos los vértices no coloreados con el "dominio mínimo"
    int selectedVertex = -1;
    int minRemainingColors = INT_MAX;

    // Para cada vértice no coloreado
    for (int vertex : s->uncoloredVertices) {
        // Se obtiene la cantidad de colores disponibles
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