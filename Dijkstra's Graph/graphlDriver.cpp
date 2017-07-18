// Bianca Steele CSS 343 A
// 5/10/2017
// 5/10/2017
// ----------------------------------------------------------------------------
// Purpose - This is the test driver the graphl class. It builds off the 
// lab3.cpp tests and further tests the functions of the graphM class.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
using namespace std;

int main() {

	//lab3.cpp section two used for testing below
	ifstream infile2("data32.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the depth-first search ordering

	for (;;) {
		//Constructor test
		GraphL G;
		
		//build test
		G.buildGraph(infile2);
	
		if (infile2.eof())
		break;
		//display test
		G.displayGraph();

		//depth first test
		G.depthFirstSearch();    // find and display depth-first ordering to cout
		
		}

		cout << endl;
		system("PAUSE");
		return 0;
	}
