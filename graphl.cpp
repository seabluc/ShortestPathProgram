#include "graphl.h"
// ---------------------------------graphl.cpp---------------------------------
// Sean-Luc Ghim CSS343D
// Created 2/07/23
// Date of Last Modification: 2/18/23
// ----------------------------------------------------------------------------
/* Purpose - Implement depth-first search and display graph information. 
*/

// ----------------------------Default Constructor-----------------------------
// Constructs an empty array of nodes.
// Precondition: None.
// Postcondition: Empty array of nodes is created, with size set to 0.
// ----------------------------------------------------------------------------
GraphL::GraphL() {
    for (int i = 1; i < MAXNODES; i++) {
        nodeArray[i].data = nullptr;
        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].visited = false;
    }
    size = 0;
}

// ---------------------------------Destructor---------------------------------
// Deletes and deallocates GraphL object.
// Precondition: None.
// Postcondition: All nodes are deleted/deallocated.
// ----------------------------------------------------------------------------
GraphL::~GraphL() {
    deleteHelper();
}

// ---------------------------------buildGraph---------------------------------
// Builds up graph node information and adjacency list of edges between each
// node reading from a data file.
// Precondition: Input data file must be correctly formatted with valid data.
// Postcondition: Adjacency list is constructed, with approrpiate edges and
// nodes from input file.
// ----------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& file) {
    file >> size; // Size is the first input given, set number of nodes
    string nodeData;
    getline(file, nodeData);
     for (int i = 1; i <= size; i++) {
        getline(file, nodeData);
        NodeData* ins = new NodeData(nodeData);
        nodeArray[i].data = ins;
    }
    int src, dest; 
    while (file >> src >> dest) {
        if (src == 0) { // 0 indicates EOF
            break;
        }
        // Test to see if node is empty.
        if (nodeArray[src].edgeHead == nullptr) {
            // Instantiate head.
            EdgeNode* head = new EdgeNode;
            head->adjGraphNode = dest;
            nodeArray[src].edgeHead = head;
            nodeArray[src].edgeHead->nextEdge = nullptr;
        }
        else {
            // Nodes after head are inserted and pointers are arranged. 
            EdgeNode* ins = new EdgeNode;
            ins->adjGraphNode = dest;
            ins->nextEdge = nodeArray[src].edgeHead;
            nodeArray[src].edgeHead = ins;
        }
    }
}

// --------------------------------displayGraph--------------------------------
// Displays each node information and edge in the graph.
// Precondition: Graph exists.
// Postcondition: Displays all Nodes and their source and destinations.
// ----------------------------------------------------------------------------
void GraphL::displayGraph() {
    cout << "\nGraph:" << endl;
    for (int i = 1; i <= size; i++) {
        cout << "Node " << i << "            " << *(nodeArray[i].data) << endl;
        EdgeNode* crawler = nodeArray[i].edgeHead;
        while (crawler != nullptr) {
            cout << " edge   " << i << "    " << crawler->adjGraphNode << endl;
            crawler = crawler->nextEdge;
        }
    }
}

// ------------------------------depthFirstSearch------------------------------
// Makes a depth-first search and displays each node in a depth-first order.
// Precondition: Graph exists.
// Postcondition: Depth-first order is printed.
// ----------------------------------------------------------------------------
void GraphL::depthFirstSearch() {
    cout << "\nDepth-first ordering:"; 
    for (int n = 1; n <= size; n++) {
        if (!nodeArray[n].visited) {
            dfsHelper(n);
        }
    }
}

// ---------------------------------dfsHelper----------------------------------
// Helper method that traveres the entire list to properly cout all nodes.
// Precondition: None
// Postcondition: Depth-first order is printed.
// ----------------------------------------------------------------------------
void GraphL::dfsHelper(int n) {
    cout << " " << n; // Print first node in DFS.
    nodeArray[n].visited = true;
    EdgeNode* crawler = nodeArray[n].edgeHead; // Begin list traversal
    while (crawler != nullptr) {
        if (!(nodeArray[crawler->adjGraphNode].visited)) {
            dfsHelper(crawler->adjGraphNode);
        }
        crawler = crawler->nextEdge; // Next node
    }
}

// --------------------------------deleteHelper--------------------------------
// Helper method for destructor. Deallocates the entire list.
// Precondition: None
// Postcondition: Array of lists has been properly deallocated/deleted.
// ----------------------------------------------------------------------------
void GraphL::deleteHelper() {
    // Go through array of lists and delete every node.
    for (int i = 1; i <= size; i++) {
        // Deallocation
        nodeArray[i].visited = false;
        delete nodeArray[i].data;
        nodeArray[i].data = nullptr; 
        if (nodeArray[i].edgeHead != nullptr) {
            EdgeNode* rem = nodeArray[i].edgeHead; // Crawler to traverse list
            while (rem != nullptr) {
                // Deallocate all nodes
                nodeArray[i].edgeHead = nodeArray[i].edgeHead->nextEdge;
                delete rem;
                rem = nullptr;
                rem = nodeArray[i].edgeHead; 
            }
        }
    }
}