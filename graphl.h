#ifndef GRAPHL_H
#define GRAPHL_H
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;
// ----------------------------------graphl.h----------------------------------
// Sean-Luc Ghim CSS343D
// Created 2/07/23
// Date of Last Modification: 2/18/23
// ----------------------------------------------------------------------------
/* Purpose - Header file for depth-first search function. Structs, global 
   variables, and methods are utilized for displaying DFS.
*/

// Global variable
const int MAXNODES = 101; // Max must be 100 and we won't use any indices of 0 

struct EdgeNode;        // Forward reference for the compiler
struct GraphNode {      // Structs used for simplicity, use classes if desired
    EdgeNode* edgeHead; // Head of the list of edges
    NodeData* data;     // Data information about each node
    bool visited;
};
struct EdgeNode {
    int adjGraphNode; // Subscript of the adjacent graph node
    EdgeNode* nextEdge;
};

class GraphL {
public:
    // Constructor and Destructor
    GraphL();
    ~GraphL();
    // Required Methods
    void buildGraph(ifstream& file);
    void displayGraph();
    void depthFirstSearch();
private:
    GraphNode nodeArray[MAXNODES]; // Array of GraphNodes
    int size;
    //Helper function:
    void dfsHelper(int n);
    void deleteHelper();
};
#endif