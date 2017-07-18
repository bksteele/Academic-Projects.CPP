// Bianca Steele CSS 343 A
// 4/30/2017
// 5/10/2017
// ----------------------------------------------------------------------------
// Purpose - This is the .cpp file for the graphm class. The graphm
// class builds a graph with two dimensional arrays. The class includes the 
// following methods: constructor, buildGraph, insertEdge, removeEdge,
// displayAll, and display. The display and displayAll methods also have their
// helper methods, fullPath and pathNames, located at the bottom of the file.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include "graphm.h"
#include "limits.h"
#include <algorithm>

// ------------------------------------Constructor-----------------------------

// Constructor:		The default is an empty graph with all distances set to
//					infinity, all visited to false, and all paths to 0.
// Preconditions:	None.
// Postconditions:	A new GraphM is created.

// ----------------------------------------------------------------------------
GraphM::GraphM()
{
	size = 0;
	//Nested for loops to cycle through C and T
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//All of T's variables are set to defaults
			T[i][j].dist = INT_MAX;
			T[i][j].visited = false;
			T[i][j].path = 0;
			//If i == j, the adjacency matrix value is 0
			if (i == j)
			{
				C[i][j] = 0;
			}
			//Else, the matrix value is infinity
			else
			{
				C[i][j] = INT_MAX;
			}
		}
	}
}


// ------------------------------------buildGraph------------------------------

// buildGraph:		Builds up graph node information and adjacency matrix
//					of edges between each node reading from a data file.
// Preconditions:	None
// Postconditions:	The GraphM is filled with the information from the
//					ifstream parameter.

// ----------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& input)
{
	string s;
	stringstream ss;
	//First line of input file is read
	getline(input, s);

	//If the file is empty, function ends
	if (s == "")
	{
		return;
	}

	ss.str(s);
	ss >> size;
	ss.clear();
	if (size <= 0)
	{
		return;
	}
	//Size is set to the first line

	//For loop to iterate through the location names and set them to Nodes
	for (int i = 0; i < size; i++)
	{
		NodeData temp;
		temp.setData(input);
		data[i + 1] = temp;
	}

	//While the file continues, the remaining lines are read and set as paths
	while (true)
	{
		//Strings for the nodes and weight before they're converted to ints
		string node1;
		string node2;
		string weight;
		input >> node1;
		input >> node2;
		input >> weight;

		//Ints for the nodes after conversion
		int from;
		int to;
		int value;

		//Stringstream to read the values and convert them to ints
		//From node
		stringstream ss;
		ss.str(node1);
		ss >> from;
		ss.clear();

		//To node
		ss.str(node2);
		ss >> to;
		ss.clear();

		//Weight value
		ss.str(weight);
		ss >> value;
		ss.clear();

		//Catch for the end of the data set
		if (from == 0 && to == 0 && value == 0)
		{
			getline(input, s);
			break;
		}

		//Edge is inserted into graph
		insertEdge(from, to, value);

		//Next line is read for while loop
		getline(input, s);
	}
}

// ------------------------------------insertEdge------------------------------

// insertEdge:		Inserts an edge into the graph between two given nodes.
// Preconditions:	The from and to parameters are nodes in the graph, the
//					weight is a positive int.
// Postconditions:	The edge is inserted into the graph.

// ----------------------------------------------------------------------------
void GraphM::insertEdge(int from, int to, int value)
{
	//catch to make sure the path is between two different nodes
	if (from == to)
	{
		return;
	}
	//catch to make sure that from node is within size bounds
	if (from <= 0 || from > size)
	{
		return;
	}
	//catch to make sure that to node is within size bounds
	if (to <= 0 || to > size)
	{
		return;
	}
	//catch to make sure that the weight is greater than 0
	if (value <= 0)
	{
		return;
	}
	//if all catches are passed, adjacency matrix is set
	else {
		C[from][to] = value;
	}
}


// ------------------------------------removeEdge------------------------------

// removeEdge:		Remove an edge between two given nodes.
// Preconditions:	The edge exists and is within bounds.
// Postconditions:	The edge is removed from the graph.

// ----------------------------------------------------------------------------
void GraphM::removeEdge(int from, int to)
{
	//Catch for an out of bounds from node
	if (from <= 0 || from > size)
	{
		return;
	}
	//Catch for an out of bounds to node
	if (to <= 0 || to > size)
	{
		return;
	}
	//Catch for an edge that doesn't exist
	if (to == from)
	{
		C[from][to] = 0;
		return;
	}
	//Else, the edge is set to infinity
	else
	{
		C[from][to] = INT_MAX;
	}
}


// ------------------------------findShortestPath------------------------------

// findShortestPath:find the shortest path between every node to every
//					other node in the graph
// Preconditions:	None
// Postconditions:	TableType T is updated with shortest path information

// ----------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	//outer for loop for the source
	for (int source = 1; source <= size; source++)
	{
		//inner for loop makes sure every node is checked
		for (int all = 1; all <= size; all++)
		{
			T[source][source].dist = 0;
			int v = 0;
			int min = INT_MAX;
			//find v
			for (int j = 1; j <= size; j++)
			{
				//v has to be unvisited and a valid/shorter path
				if (T[source][j].visited == false && C[source][j] < min)
				{
					v = j;
					min = C[source][j];
				}
			}
			//V is now visited
			T[source][v].visited = true;

			//find neighbors of v
			for (int w = 1; w <= size; w++)
			{
				//catch for unvisited nodes that are valid paths
				if (T[source][w].visited != true && C[v][w] != INT_MAX
					&& v != w)
				{
					//if the new path is shorter, the node is updated
					if (T[source][w].dist > T[source][v].dist + C[v][w])
					{
						T[source][w].dist = T[source][v].dist + C[v][w];
						T[source][w].path = v;

					}
				}
			}
		}
	}
}


// ------------------------------displayAll------------------------------------

// displayAll:		Uses couts to demonstrate that the algorithm works
//					properly
// Preconditions:	None
// Postconditions:	The path information for the graph is printed

// ----------------------------------------------------------------------------
void GraphM::displayAll()
{
	cout << endl << "Description" << setw(20) << "From" << setw(10) << "To" <<
		setw(15) << "Dijkstra's" << setw(7) << "Path" << endl;

	//loops to print out the nodes and paths
	//first loop is the from node
	for (int i = 1; i <= size; i++)
	{
		cout << data[i] << endl;

		//second loop is the to node
		for (int j = 1; j <= size; j++)
		{
			//if there are nodes to go to and i!=j, they're printed
			if (T[i][j].dist != 0)
			{
				//first section
				cout << setw(31) << i << setw(10) << j;

				//if the path doesn't exist, placeholder is printed
				if (T[i][j].dist == INT_MAX)
				{
					cout << setw(10) << "---";
				}
				//if the path does exist, it's printed
				else
				{
					//shortest distance is printed
					cout << setw(10) << T[i][j].dist << setw(12);
					//fullPath is called to find the full path of to/from
					fullPath(i, j);
				}
				cout << endl;
			}
		}
	}
	cout << endl;
}


// ------------------------------display---------------------------------------

// display:			Uses couts to display the shortest distance with path
//					info between the fromNode to toNode.
// Preconditions:	None
// Postconditions:	The path information for the fromNode to toNode is printed

// ----------------------------------------------------------------------------
void GraphM::display(int fromNode, int toNode)
{
	//Catch for an out of bounds from node
	if (fromNode <= 0 || fromNode > size)
	{
		cout << "Invalid start node." << endl << endl;
		return;
	}
	//Catch for an out of bounds to node
	if (toNode <= 0 || toNode > size)
	{
		cout << "Invalid end node." << endl << endl;
		return;
	}
	//catch for a path that doesn't exist
	if (T[fromNode][toNode].dist == INT_MAX)
	{
		cout << "Invalid start and end combination." << endl << endl;
		return;
	}
	//Printout of a path that does exist
	cout << fromNode << setw(5) << toNode << setw(5) << T[fromNode][toNode].dist;
	cout << setw(10);
	//fullPath is called to get the path nodes
	fullPath(fromNode, toNode);
	cout << endl;
	//pathNames is called to print out the names of the nodes in the path
	pathNames(fromNode, toNode);
	cout << endl << endl;
}


// ------------------------------fullPath--------------------------------------

// fullPath:		Finds and prints the full path from one node to another
//					with recursion
// Preconditions:	None
// Postconditions:	The path information for the graph is printed

// ----------------------------------------------------------------------------
void GraphM::fullPath(int from, int to)
{
	//base case for no path
	if (T[from][to].dist == INT_MAX)
	{
		return;
	}

	//base case for end of the path
	else if (from == to)
	{
		cout << to << " ";
		return;
	}

	//recursive call with the to variable adjusted
	fullPath(from, (T[from][to].path));

	//final path step printed
	cout << to << " ";
}


// ------------------------------pathNames---------------------------------

// pathNames:		Prints the names of the nodes in the full path from one
//					node to another with recursion
// Preconditions:	None
// Postconditions:	The path information is printed

// ------------------------------------------------------------------------
void GraphM::pathNames(int from, int to)
{
	//base case for no path
	if (T[from][to].dist == INT_MAX)
	{
		return;
	}

	//base case for end of the path
	else if (from == to)
	{
		cout << data[to] << endl;
		return;
	}

	//recursive call with the to variable adjusted
	pathNames(from, (T[from][to].path));

	//final path step printed
	cout << data[to] << endl;
}