// FileReader.h
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class FileReader {
private:
    string filename;
    vector<vector<int>> edges;
    int numVertices;
    int numEdges;
public:
    FileReader(string filename);
    void readGraph();
    vector<vector<int>> getGraph();
    int getNumVertices();
    int getNumEdges();
};