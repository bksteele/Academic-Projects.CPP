// Bianca Steele CSS 343 A
// 4/30/2017
// 5/10/2017
// ----------------------------------------------------------------------------
// Purpose - This is the .h file for the graphm class. The graphm
// class builds a graph with two dimensional arrays. The class includes the 
// following methods: constructor, buildGraph, insertEdge, removeEdge,
// displayAll, and display. The display and displayAll methods also have their
// helper methods, fullPath and pathNames, located at the bottom of the file.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#ifndef GRAPHM
#define GRAPHM
#include "nodedata.h"
#include "limits.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class GraphM {

public:

	// ------------------------------------Constructor-------------------------

	// Constructor:		The default is an empty graph with all distances set to
	//					infinity, all visited to false, and all paths to 0.
	// Preconditions:	None.
	// Postconditions:	A new GraphM is created.

	// ------------------------------------------------------------------------
	GraphM();


	// ------------------------------------buildGraph--------------------------

	// buildGraph:		Builds up graph node information and adjacency matrix
	//					of edges between each node reading from a data file.
	// Preconditions:	None
	// Postconditions:	The GraphM is filled with the information from the
	//					ifstream parameter.

	// ------------------------------------------------------------------------
	void buildGraph(ifstream& input);


	// ------------------------------------insertEdge--------------------------

	// insertEdge:		Inserts an edge into the graph between two given nodes.
	// Preconditions:	The from and to parameters are nodes in the graph, the
	//					weight is a positive int.
	// Postconditions:	The edge is inserted into the graph.

	// ------------------------------------------------------------------------
	void insertEdge(int from, int to, int value);


	// ------------------------------------removeEdge--------------------------

	// removeEdge:		Remove an edge between two given nodes.
	// Preconditions:	The edge exists and is within bounds.
	// Postconditions:	The edge is removed from the graph.

	// ------------------------------------------------------------------------
	void removeEdge(int from, int to);


	// ------------------------------findShortestPath--------------------------

	// findShortestPath:Find the shortest path between every node to every
	//					other node in the graph
	// Preconditions:	None
	// Postconditions:	TableType T is updated with shortest path information

	// ------------------------------------------------------------------------
	void findShortestPath();


	// ------------------------------displayAll--------------------------------

	// displayAll:		Uses couts to demonstrate that the algorithm works
	//					properly
	// Preconditions:	None
	// Postconditions:	The path information for the graph is printed

	// ------------------------------------------------------------------------
	void displayAll();


	// ------------------------------display-----------------------------------

	// display:			Uses couts to display the shortest distance with path
	//					info between the fromNode to toNode.
	// Preconditions:	None
	// Postconditions:	The path information for the fromNode to toNode is 
	//					printed

	// ------------------------------------------------------------------------
	void display(int fromNode, int toNode);



private:

	struct TableType {

		bool visited;          // whether node has been visited

		int dist;              // shortest distance from source known so far

		int path;              // previous node in path of min dist

	};

	static const int MAXNODES = 100;

	NodeData data[MAXNODES];              // data for graph nodes

	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix

	int size;                             // number of nodes in the graph

	TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path


	// ------------------------------fullPath----------------------------------

	// fullPath:		Finds and prints the full path from one node to another
	//					with recursion
	// Preconditions:	None
	// Postconditions:	The path information for the graph is printed

	// ------------------------------------------------------------------------
	void fullPath(int from, int to);


	// ------------------------------pathNames---------------------------------

	// pathNames:		Prints the names of the nodes in the full path from one
	//					node to another with recursion
	// Preconditions:	None
	// Postconditions:	The path information is printed

	// ------------------------------------------------------------------------
	void pathNames(int from, int to);
};
#endif // !GRAPHM