// Bianca Steele CSS 343 A
// 5/7/2017
// 5/11/2017
// ----------------------------------------------------------------------------
// Purpose - This is the .cpp file for the graphl class. The graphl
// class is the class makes a graph using an adjacency list with an array.
// It includes the following methods: a constructor, destructor, buildgraph,
// displayGraph, and depthFirstSearch. The class also has one private helper 
// method, depthHelper, located at the bottom of the file.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include "graphl.h"
#include "limits.h"
#include <algorithm>

// ------------------------------------Constructor-------------------------

// Constructor:		The default is an empty graph with all distances set to
//					infinity, all visited to false, and all paths to 0.
// Preconditions:	None.
// Postconditions:	A new GraphL is created.

// ------------------------------------------------------------------------
GraphL::GraphL()
{
	size = 0;

	//for loop to create all of the nodes array variables
	for (int i = 0; i < MAXNODES; i++)
	{
		nodes[i].edgeHead = NULL;
		nodes[i].data = NULL;
		nodes[i].visited = false;
	}
}


// ------------------------------------Destructor------------------------------

// Destructor:		Deletes a GraphL object
// Preconditions:	None.
// Postconditions:	The GraphL object is emptied and deleted.

// ----------------------------------------------------------------------------
GraphL::~GraphL()
{
	for (int i = 0; i <= size; i++)
	{
		delete nodes[i].data;

		//check to make sure there's not an edgeHead
		if (nodes[i].edgeHead != NULL)
		{
			EdgeNode *temp = nodes[i].edgeHead;

			//if any Edgenodes exist, they're cycled through and deleted
			while (nodes[i].edgeHead != NULL)
			{
				nodes[i].edgeHead = nodes[i].edgeHead->nextEdge;
				delete temp;
				temp = nodes[i].edgeHead;
			}
			delete temp;
		}
	}
}


// ------------------------------------buildGraph--------------------------

// buildGraph:		Builds up graph node information and adjacency list of
//					edges between each node reading from a data file.
// Preconditions:	None
// Postconditions:	The GraphL is filled with the information from the
//					ifstream parameter.

// ------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& input)
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

	//Size is set to the first line
	ss.str(s);
	ss >> size;
	ss.clear();
	if (size <= 0)
	{
		return;
	}

	//For loop to iterate through the location names and set them to Nodes
	for (int i = 0; i < size; i++)
	{
		string temp;
		getline(input, temp);
		NodeData* tNode = new NodeData(temp);
		nodes[i + 1].data = tNode;
	}

	//While the file continues, the remaining lines are read and set as paths
	while (true)
	{
		//Strings for the nodes before they're converted to ints
		string node1;
		string node2;
		input >> node1;
		input >> node2;

		//Ints for the nodes after conversion
		int from;
		int to;

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

		//Catch for the end of the data set
		if (from == 0 && to == 0)
		{
			getline(input, s);
			break;
		}
		if (from > 0 && from <= size)
		{
			if (to > 0 && to <= size)
			{
				//Edge is not first node inserted into adjacency list
				EdgeNode *temp = new EdgeNode;
				temp->adjGraphNode = to;
				//the edgeHead is slid over to make room for the new node
				temp->nextEdge = nodes[from].edgeHead;
				nodes[from].edgeHead = temp;
			}
		}

		//Next line is read for while loop
		getline(input, s);
	}
}


// ------------------------------displayGraph----------------------------------

// displayGraph:	Displays each node information and edge in the graph
// Preconditions:	None
// Postconditions:	The path information for the graph is printed

// ----------------------------------------------------------------------------
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;

	//for loop to cycle through the array of nodes
	for (int i = 1; i <= size; i++)
	{
		cout << "Node " << i << "      " << *nodes[i].data << endl;

		//temp EdgeNode * to cycle through and print the EdgeNodes
		EdgeNode* temp = nodes[i].edgeHead;

		while (temp != NULL)
		{
			cout << "Edge " << i << "  " << temp->adjGraphNode << endl;
			temp = temp->nextEdge;
		}

		cout << endl;
	}
}


// ------------------------------depthFirstSearch--------------------------------

// depthFirstSearch:Makes a depth-first search and displays each node in 
//					depth-first order
// Preconditions:	None
// Postconditions:	The path information for the graph is printed

// ------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{

	//check for an empty list
	if (size == 0)
	{
		cout << "Empty list." << endl;
		return;
	}

	cout << "Depth-first ordering: ";

	//for loop to cycle through the array
	for (int i = 1; i <= size; i++)
	{
		if (nodes[i].visited == false)
		{
			//DFS helper method is called to print the nodes
			depthHelper(i);
		}
	}
	cout << endl;
}


// ------------------------------depthHelper--------------------------------

// depthHelper:		Helper method for depth-first search recursively calls
//					to find the depth-first order
// Preconditions:	None
// Postconditions:	The path information for the graph is printed in DFO

// ------------------------------------------------------------------------
void GraphL::depthHelper(int current)
{
	//print the current node and mark it visited
	cout << current << " ";
	nodes[current].visited = true;

	//temp EdgeNode to find the adjacent node
	EdgeNode* temp = nodes[current].edgeHead;

	while (temp != NULL)
	{
		//check to see if adjacent node has been visited
		if (nodes[temp->adjGraphNode].visited == false)
		{
			//recursive call
			depthHelper(temp->adjGraphNode);
		}

		//temp is moved down
		temp = temp->nextEdge;
	}
}