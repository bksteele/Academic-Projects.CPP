// Bianca Steele CSS 343 A
// 5/7/2017
// 5/11/2017
// ----------------------------------------------------------------------------
// Purpose - This is the .h file for the graphl class. The graphl
// class is the class makes a graph using an adjacency list with an array.
// It includes the following methods: a constructor, destructor, buildgraph,
// displayGraph, and depthFirstSearch. The class also has one private helper 
// method, depthHelper, located at the bottom of the file.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#ifndef GRAPHL
#define GRAPHL
#include "nodedata.h"
#include "limits.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class GraphL {

public:

	// ------------------------------------Constructor-------------------------

	// Constructor:		The default is an empty graph with all distances set to
	//					infinity, all visited to false, and all paths to 0.
	// Preconditions:	None.
	// Postconditions:	A new GraphL is created.

	// ------------------------------------------------------------------------
	GraphL();


	// ------------------------------------Destructor--------------------------

	// Destructor:		Deletes a GraphL object
	// Preconditions:	None.
	// Postconditions:	The GraphL object is emptied and deleted.

	// ------------------------------------------------------------------------
	~GraphL();


	// ------------------------------------buildGraph--------------------------

	// buildGraph:		Builds up graph node information and adjacency list of
	//					edges between each node reading from a data file.
	// Preconditions:	None
	// Postconditions:	The GraphL is filled with the information from the
	//					ifstream parameter.

	// ------------------------------------------------------------------------
	void buildGraph(ifstream& input);


	// ------------------------------displayGraph--------------------------------

	// displayGraph:	Displays each node information and edge in the graph
	// Preconditions:	None
	// Postconditions:	The path information for the graph is printed

	// ------------------------------------------------------------------------
	void displayGraph();


	// ------------------------------depthFirstSearch--------------------------------

	// depthFirstSearch:Makes a depth-first search and displays each node in 
	//					depth-first order
	// Preconditions:	None
	// Postconditions:	The path information for the graph is printed

	// ------------------------------------------------------------------------
	void depthFirstSearch();

private:

	static const int MAXNODES = 100;

	int size;

	struct EdgeNode;      // forward reference for the compiler

	struct GraphNode {    // structs used for simplicity, use classes if desired

		EdgeNode* edgeHead; // head of the list of edges

		NodeData* data;     // data information about each node

		bool visited;

	};

	struct EdgeNode {

		int adjGraphNode;  // subscript of the adjacent graph node

		EdgeNode* nextEdge;

	};

	GraphNode nodes[MAXNODES];// array of GraphNodes


	// ------------------------------depthHelper--------------------------------

	// depthHelper:		Helper method for depth-first search recursively calls
	//					to find the depth-first order
	// Preconditions:	None
	// Postconditions:	The path information for the graph is printed in DFO

	// ------------------------------------------------------------------------
	void depthHelper(int current);

};
#endif // !GRAPHL