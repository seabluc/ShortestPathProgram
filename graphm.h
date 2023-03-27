#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include <fstream> // Read from file
#include <string>
#include <limits> // To set all dist to infinity
#include "nodedata.h"
using namespace std;
// ----------------------------------graphm.h----------------------------------
// Sean-Luc Ghim CSS343D
// Created 2/07/23
// Date of Last Modification: 2/17/23
// ----------------------------------------------------------------------------
/* Purpose - Header file for Dijsktra's algorithm. Structs, global variables,
   and methods are utilized for achieving and displaying the shortest path.
*/

// Global variables
const int INFINITY = numeric_limits<int>::max(); // "Infinity"
const int MAXNODESm = 101; // Max must be 100 and we won't use any indices of 0

struct TableType { 
    bool visited;   // Whether node has been visited
    int dist;       // Shortest distance from source known so far
    int path;       // Previous node in path of min dist
};

class GraphM {
public:
    GraphM(); // Constructor
    // Required methods
    void buildGraph(ifstream& file);
    bool insertEdge(int src, int dest, int weight);
    bool removeEdge(int src, int dest);
    void findShortestPath();
    void display(int src, int dest);
    void displayAll();
private:
    NodeData data[MAXNODESm];            // Data for graph nodes
    int C[MAXNODESm][MAXNODESm];          // Cost array, the adjacency matrix
    int size;                           // Number of nodes in the graph
    TableType T[MAXNODESm][MAXNODESm];    // Stores visited, distance, path
    // Helper functions
    void findPath(int src, int dest);
    void findData(int src, int dest);
};
#endif