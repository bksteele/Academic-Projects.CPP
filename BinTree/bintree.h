// --------------------------BinTree Class-------------------------------------
// Bianca Steele CSS 343 A
// 4/10/2017
// 4/21/2017
// ----------------------------------------------------------------------------
// Purpose - This is the .h file for the BinTree class. The BinTree
// class is a binary search tree for strings. Each node stores a string
// value for each leaf of the tree. Smaller values go to the left and larger
// values go to the right. A value of "$$" signals the end of the tree. The
// class includes the following methods: isEmpty, makeEmpty, insert, retrieve
// getHeight, bstreeToArray, and arrayToBSTree. Each of these methods also has
// its own helper methods, located at the bottom of the file. The following 
// operators have also been overridden: ==, !=, =, and <<.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#ifndef BINTREE_H 
#define BINTREE_H 
#include <string> 
#include <iostream> 
#include <fstream> 
#include "nodedata.h"
using namespace std;

class BinTree
{

	friend ostream& operator<<(ostream& os, const BinTree & data);


public:

	// ------------------------------------Constructor-------------------------

	// Constructor:		The default is a tree with only a NULL root.
	// Preconditions:	None.
	// Postconditions:	A new BinTree is created with only a NULL root.

	// ------------------------------------------------------------------------
	BinTree();

	// -------------------------------Copy Constructor-------------------------

	// Copy Constructor:	Makes a copy of a BinTree
	// Preconditions:		None.
	// Postconditions:		A new BinTree is created with the values as the
	//						parameter BinTree.

	// ------------------------------------------------------------------------
	BinTree(const BinTree & input);


	// -------------------------------Destructor-------------------------------

	// Destructor:		Empties and deletes calling BinTree
	// Preconditions:	None
	// Postconditions:	The BinTree is deleted after calling makeEmpty()

	// ------------------------------------------------------------------------
	~BinTree();


	// ------------------------------------isEmpty-----------------------------

	// isEmpty:			Tells if BinTree is empty or not
	// Preconditions:	None.
	// Postconditions:	Returns true if tree is empty, otherwise false

	// ------------------------------------------------------------------------
	bool isEmpty() const;


	// -------------------------- makeEmpty -----------------------------------

	// makeEmpty:		Calls helper function that emptpies the BinTree
	// Preconditions:	Calling BinTree isn't empty
	// Postconditions:	BinTree is deleted

	// ------------------------------------------------------------------------
	void makeEmpty();


	// -------------------------- operator= -----------------------------------

	// operator==:		Makes the left operand equal to the right
	// Preconditions:	None
	// Postconditions:	The left operand is emptied, and then made a deep copy
	//					of the right

	// ------------------------------------------------------------------------
	BinTree& operator=(const BinTree & input);


	// -------------------------- operator== ----------------------------------

	// operator==:		Tells if the operands are equal
	// Preconditions:	None
	// Postconditions:	After the trees are compared leaf by leaf, their
	//					equality is returned

	// ------------------------------------------------------------------------
	bool operator==(const BinTree & input) const;


	// -------------------------- operator!= ----------------------------------

	// operator!=:		Tells if the operands are not equal
	// Preconditions:	None
	// Postconditions:	Opposite of operator== is returned

	// ------------------------------------------------------------------------
	bool operator!=(const BinTree & input) const;


	// ------------------------------ insert ----------------------------------

	// insert:			Inserts a new node into a BinTree
	// Preconditions:	The node does not already exist in the BinTree
	// Postconditions:	The new node is inserted in the BinTree based on its
	//					value. A repeat node is not inserted and false is 
	//					returned.

	// ------------------------------------------------------------------------
	bool insert(NodeData* input);


	// ------------------------------ retrieve --------------------------------

	// retrieve:		Retrieves an existing node in a BinTree
	// Preconditions:	The node exists in the BinTree
	// Postconditions:	The node is found in the BinTree based on its value.
	//					A node not inserted in the tree returns false.

	// ------------------------------------------------------------------------
	bool retrieve(const NodeData & data, NodeData* & retVal) const;


	// ------------------------------ getHeight -------------------------------

	// getHeight:		Calculates the height of a node
	// Preconditions:	The node exists in the BinTree
	// Postconditions:	The node is found in the BinTree based on its value and
	//					its height is returned.
	//					A node not inserted in the tree returns as 0.

	// ------------------------------------------------------------------------
	int getHeight(const NodeData & data) const;


	// ------------------------------ bstreeToArray ---------------------------

	// bstreeToArray:	Fills an array with the leaves of the tree
	// Preconditions:	None
	// Postconditions:	The tree is traversed inorder. As the method goes, 
	//					leaves are removed from the tree and added to the array

	// ------------------------------------------------------------------------
	void bstreeToArray(NodeData* data[]);


	// ------------------------------ arrayToBSTree ---------------------------

	// arrayToBSTree:	Fills a tree with the elements of an array
	// Preconditions:	None
	// Postconditions:	The tree is traversed inorder. As the method goes, 
	//					leaves are added to the tree from the array. The array
	//					elements are set to NULL. 

	// ------------------------------------------------------------------------
	void arrayToBSTree(NodeData* data[]);


	//------------------------- displaySideways -----------------------------------

	//Displays a binary tree as though you are viewing it from the side;
	// hard coded displaying to standard output.
	// Preconditions: NONE
	// Postconditions: BinTree remains unchanged.

	// ----------------------------------------------------------------------------
	void displaySideways() const;


private:
	struct Node {
		NodeData* data;
		// pointer to data object 
		Node* left;
		// left subtree pointer 
		Node* right;
		// right subtree pointer
	};
	Node* root;
	// root of the tree
	// utility functions 



	void inorderHelper(ostream& os, const Node* input) const;


	//---------------------------- Sideways -----------------------------------

	// Helper method for displaySideways
	// Preconditions: NONE
	// Postconditions: BinTree remains unchanged.
	// ------------------------------------------------------------------------

	void sideways(Node* current, int level) const;


	// -------------------------- makeEmptyHelper -----------------------------

	// makeEmptyHelper:	Recursively emptpies tree for makeEmpty
	// Preconditions:	A non-NULL BinTree* is passed as a parameter
	// Postconditions:	Recursively deletes every node in the BinTree

	// ------------------------------------------------------------------------
	void makeEmptyHelper(Node* subTree);


	// -------------------------- copyTreeHelper ------------------------------

	// copyTreeHelper:	Recursively copies a tree for the copy constructor
	// Preconditions:	A non-NULL BinTree* is passed as a parameter
	// Postconditions:	Recursively copies every node in the BinTree

	// ------------------------------------------------------------------------
	void copyTreeHelper(const Node* input, Node* & newNode);


	// -------------------------- insertHelper --------------------------------

	// insertHelper:	Recursively traverses a tree and inserts a node
	// Preconditions:	A non-NULL NodeData* is passed as a parameter
	// Postconditions:	Recursively traverses a tree and inserts a node. Repeat
	//					nodes are not inserted.

	// ------------------------------------------------------------------------
	bool insertHelper(NodeData* input, Node* & current);


	// -------------------------- equalityHelper ------------------------------

	// equalityHelper:	Recursively checks a tree for equality of nodes
	// Preconditions:	None
	// Postconditions:	Recursively checks a tree for equality of nodes and 
	//					returns result as a bool to overridden ==operator

	// ------------------------------------------------------------------------
	bool equalityHelper(const Node * tree1, const Node * tree2) const;


	// ------------------------------ retrieveHelper --------------------------

	// retrieveHelper:	Helps retrieve an existing node in a BinTree
	// Preconditions:	The node exists in the BinTree
	// Postconditions:	The node is found in the BinTree based on its value 
	//					after the tree is recursively traversed.
	//					A node not inserted in the tree returns false.

	// ------------------------------------------------------------------------
	bool retrieveHelper(const NodeData & data, NodeData* & retVal,
		Node* current) const;


	// ------------------------------ heightHelper ----------------------------

	// heightHelper:	Helper method that recursively calculates the height of
	//					a node
	// Preconditions:	The node exists in the BinTree
	// Postconditions:	The node is found in the BinTree based on its value and
	//					its height is returned.
	//					A node not inserted in the tree returns as 0.

	// ------------------------------------------------------------------------
	int heightHelper(const Node* current) const;


	// ------------------------------ toArrayHelper ---------------------------

	// toArrayHelper:	Fills an array with the leaves of the tree
	// Preconditions:	None
	// Postconditions:	The tree is recursively traversed inorder. As the 
	//					method goes, leaves from the tree are added to the
	//					array.

	// ------------------------------------------------------------------------
	void toArrayHelper(NodeData* data[], Node* current, int & i);


	// ------------------------------ toTreeHelper ----------------------------

	// toTreeHelper:	Recursively fills a tree with the elements of an array
	// Preconditions:	None
	// Postconditions:	The array is traversed inorder. As the method goes, 
	//					leaves are added to the tree from the array. The array
	//					elements are set to NULL. 

	// ------------------------------------------------------------------------
	void toTreeHelper(NodeData* data[], int low, int high);


	// ------------------------------ findNode --------------------------------

	// findNode:		Checks for the existence of a node and returns it as a
	//					pointer
	// Preconditions:	None
	// Postconditions:	The node is found in the BinTree based on its value and
	//					a pointer to it is returned.

	// ------------------------------------------------------------------------
	void findNode(Node* & current, Node* & final, const NodeData & data) const;

};
#endif
