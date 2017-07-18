// Bianca Steele CSS 343 A
// 4/30/2017
// 5/10/2017
// ----------------------------------------------------------------------------
// Purpose - This is the test driver the graphm and graphl classes. It builds 
// off the lab3.cpp tests and further tests the class functions.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphm.h"
using namespace std;

int main() {

	//lab3.cpp section one used for intial testing below along with added
	//student testing
	ifstream infile1("data31.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes
	for (;;) {
		GraphM G;
		G.buildGraph(infile1);
		if (infile1.eof())
			break;


		//tests for inserting edges

		//test for inserting a new, valid edge
		G.insertEdge(1, 4, 5);
		//test for inserting an edge from a node to itself
		G.insertEdge(1, 1, 14);
		//test for inserting an edge with a distance of 0
		G.insertEdge(1, 4, 0);
		//tests for inserting an edge a node outside of the size bounds
		G.insertEdge(1, 6, 10);
		G.insertEdge(-3, 4, 10);

		//tests for removing edges

		//test for removing a valid edge
		G.removeEdge(1, 4);
		//test for removing an edge from a node to itself
		G.removeEdge(1, 1);
		//test for removing an edge outside of the size bounds
		G.removeEdge(0, 4);
		G.removeEdge(1, 7);
		G.removeEdge(-5, 5);

		G.findShortestPath();

		G.displayAll();              // display shortest distance, path to cout
		G.display(3, 1);              // display path from node 3 to 1 to cout
		G.display(1, 2);
		G.display(1, 4);

		//Extra tests for display

		//test for display of a node going to itself
		G.display(1, 1);
		//test for displaying nodes that don't have a pah
		G.display(5, 1);
		//tests for displaying nodes that are out of bounds
		G.display(-1, 6);
		G.display(1, 8);

		system("PAUSE");
	}
	return 0;
}
