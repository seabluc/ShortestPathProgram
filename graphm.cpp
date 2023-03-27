#include "graphm.h"
// ---------------------------------graphm.cpp---------------------------------
// Sean-Luc Ghim CSS343D
// Created 2/07/23
// Date of Last Modification: 2/17/23
// ----------------------------------------------------------------------------
/* Purpose - Implement Dijsktra's shortest path algorithm. The program will
   read a data file consisting of many lines and find the lowest cost paths and
   and path from every node to every other node. Another display routine will
   output one path in detail.
*/

// ----------------------------Default Constructor-----------------------------
// Data member T is initialized to set all dist to infinity, sets all visited
// to false, and sets all path to 0.
// Precondition: None.
// Postcondition: Empty graph is constructed, with all visited set to false, 
// path set to 0, and all dists set to INFINITY.
// ----------------------------------------------------------------------------
GraphM::GraphM() {
    // Array of data initialized to ""
    for (int i = 1; i < MAXNODESm; i++) {
        data[i] = NodeData();
    }
    for (int i = 1; i < MAXNODESm; i++) {
        for (int j = 1; j < MAXNODESm; j++) {
            C[i][j] = INFINITY;
            T[i][j].dist = INFINITY;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
    size = 0;
}

// ---------------------------------buildGraph---------------------------------
// Builds up graph node information and adjacency matrix of edges between each
// node reading from a data file.
// Precondition: Input data file must be correctly formatted with valid data.
// Postcondition: Adjacency matrix is constructed, with approrpiate edges and
// nodes from input file.
// ----------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& file) {
    file >> size; // Size is the first input given, set number of nodes
    string nodeData; 
    getline(file, nodeData);
    for (int i = 1; i <= size; ++i) {
        data[i].setData(file); // Name each node
    }
    int src, dest, weight; 
    while (file >> src >> dest >> weight) {
        if (src == 0) { // 0 indicates EOF
            break;
        }
        C[src][dest] = weight;
    }
}

// ---------------------------------insertEdge---------------------------------
// Inserts an edge into the graph between src and dest.
// Precondition: Nodes must exist within graph.
// Postcondition: New edge between two vertices has been added into the graph.
// ----------------------------------------------------------------------------
bool GraphM::insertEdge(int src, int dest, int weight) {
    if ((src <= size) && dest <= size) { // Check if Nodes within scope
        if ((src != 0) && (dest != 0)) { // Check if Nodes are valid
            C[src][dest] = weight; // Node inserted
            return true;
        }
    }
    return false;
}

// ---------------------------------removeEdge---------------------------------
// Removes an edge into the graph between src and dest.
// Precondition: Nodes must exist within graph.
// Postcondition: Edge between two vertices has been removed from the graph.
// ----------------------------------------------------------------------------
bool GraphM::removeEdge(int src, int dest) {
    if ((src <= size) && (dest <= size)) { // Check if within scope
        if ((src != 0) && (dest != 0)) { // Check if valid
            // Node "removed"
            C[src][dest] = INFINITY; 
            T[src][dest].dist = INFINITY;
            T[src][dest].path = 0;
            T[src][dest].visited = false;
            return true;
        }
    }
    return false;
}

// ------------------------------findShortestPath------------------------------
// Find the shortest path between every node to every other node in the graph 
// via Dijsktra's Algorithm
// Precondition: Graph must not be empty
// Postcondition: New edge between two vertices has been added into the graph.
// ----------------------------------------------------------------------------
void GraphM::findShortestPath() {
    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
        T[source][source].visited = true;
         int min, v;
        for (int i = 1; i <= size; i++) {
            if (C[source][i] != INFINITY) {
                T[source][i].dist = C[source][i];
                T[source][i].path = source;
            }
        }
        do {
            min = INFINITY;
            v = 0;
            // Search adjacent vertexes to find the shortest distance.
            for (int j = 1; j <= size; j++) {
                if (!T[source][j].visited && (C[source][j] < min)) {
                    min = C[source][j];
                    v = j;
                }
            }
            // Case to end search
            if (v == 0) {
                break;
            }
            // Vertex visited, continue checking all other vertexes. 
            T[source][v].visited = true; 
            for (int w = 1; w <= size; ++w) {
                if ((T[source][w].visited) || 
                (C[v][w] == INFINITY) || (v == w)) {
                    continue;
                }
                if (T[source][w].dist > T[source][v].dist + C[v][w]) {
                    T[source][w].dist = T[source][v].dist + C[v][w];
                    T[source][w].path = v;
                }
            }
        }
        while (v != 0);
    }
}

// ----------------------------------display-----------------------------------
// Uses "cout's" to display the shortest diatance with path info between the
// src to dest.
// Precondition: Node must exist.
// Postcondition: Vertex's name, source, destination, and path are printed.
// ----------------------------------------------------------------------------
void GraphM::display(int src, int dest) {
    // Test if nodes are valid. If not, cout proper format
    if ((src > size || src < 0) || (src > size || dest < 0)) {
        cout <<
        "        " << src << "        " << dest << "        ---" << endl;
        return;
    }
    // Begin couting the source, destination, distance, path, and vertex's name
    cout << "        " << src << "        " << dest;
    if (T[src][dest].dist != INFINITY) { 
        cout << "        " << T[src][dest].dist << "        ";
        findPath(src, dest); // Retrieve path
        cout << endl;
        findData(src, dest); // Retrieve name of vertex
    }
    else {
        cout << "        ---" << endl; // DNE
    }
}

// ---------------------------------displayAll---------------------------------
// Uses "cout's" to demonstrate that the algorithm works properly.
// Precondition: None
// Postcondition: Name of every vertice with their adjacent neighbors along with
// weight/distance and shortest path are given with the expected format. 
// ----------------------------------------------------------------------------
void GraphM::displayAll() {
    cout << // Cout header
    "Description        From_node        To_node        Distance        Path" 
    << endl;
    for (int source = 1; source <= size; source++) {
        // Cout string name of node
        cout << data[source] << endl;
        for (int dest = 1; dest <= size; dest++) {
            // Cout the source and destination of vertex
            if (T[source][dest].dist != 0) {
                cout << "                         " << source << 
                "               " << dest;

                // Cout distance, or --- if dist is set to INFINITY
                if (T[source][dest].dist != INFINITY) {
                    cout << "            " << T[source][dest].dist << 
                    "             ";
                    findPath(source, dest); // Cout path via backtrack
                    cout << endl;
                }
                else {
                    cout << "            ---" << endl;
                }
            }
        }
    }
}

// ----------------------------------findData----------------------------------
// Helper function to find data for display() method.
// Precondition: None
// Postcondition: Cout's the selected node's name.
// ----------------------------------------------------------------------------
void GraphM::findData(int src, int dest) {
    if (T[src][dest].dist == INFINITY) {
        return;
    }
    else if (src == dest) {
        cout << data[dest] << endl;
        return;
    }
    int pathData = dest;
    findData(src, dest = T[src][dest].path);
    cout << data[pathData] << endl;
}

// ----------------------------------findPath----------------------------------
// Helper function to find path for both display methods. 
// Precondition: None
// Postcondition: Cout's the shortest path. 
// ----------------------------------------------------------------------------
void GraphM::findPath(int src, int dest) {
    if (T[src][dest].dist == INFINITY) {
        return;
    }
    else if (src == dest) {
        cout << dest << " ";
        return;
    }
    int pathData = dest;
    findPath(src, dest = T[src][dest].path);
    cout << pathData << " ";
}