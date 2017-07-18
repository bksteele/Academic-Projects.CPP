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

#include <string> 
#include <iostream> 
#include <fstream> 
#include <algorithm>
#include "nodedata.h"
#include "bintree.h"
using namespace std;


// ------------------------------------Constructor-----------------------------

// Constructor:		The default is a tree with only a NULL root.
// Preconditions:	None.
// Postconditions:	A new BinTree is created with only a NULL root.

// ----------------------------------------------------------------------------
BinTree::BinTree()
{
	//Root is set to NULL, no other actions needed
	root = NULL;
}


// -------------------------------Copy Constructor-----------------------------

// Copy Constructor:	Makes a copy of a BinTree
// Preconditions:		None.
// Postconditions:		A new BinTree is created with the values as the
//						parameter BinTree.

// ----------------------------------------------------------------------------
BinTree::BinTree(const BinTree & input)
{
	root = NULL;
	//recursive helper is called
	copyTreeHelper(input.root, root);
}


// -------------------------------Destructor-----------------------------------

// Destructor:		Empties and deletes calling BinTree
// Preconditions:	None
// Postconditions:	The BinTree is deleted after calling makeEmpty()

// ----------------------------------------------------------------------------
BinTree:: ~BinTree()
{
	//Call to makeEmpty()
	makeEmpty();
}


// ------------------------------------isEmpty---------------------------------

// isEmpty:			Tells if BinTree is empty or not
// Preconditions:	None.
// Postconditions:	Returns true if tree is empty, otherwise false

// ----------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
	//If the root is NULL, the tree is empty
	return root == NULL;
}


// -------------------------- makeEmpty ---------------------------------------

// makeEmpty:		Calls helper function that emptpies the BinTree
// Preconditions:	Calling BinTree isn't empty
// Postconditions:	BinTree is deleted

// ----------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	//If the BinTree is not empty, the makeEmptyHelper() is called
	if (!isEmpty())
	{
		makeEmptyHelper(root);
	}
	root = NULL;
}


// -------------------------- operator= ---------------------------------------

// operator==:		Makes the left operand equal to the right
// Preconditions:	None
// Postconditions:	The left operand is emptied, and then made a deep copy of
//					the right

// ----------------------------------------------------------------------------
BinTree& BinTree:: operator=(const BinTree & input)
{
	if (*this != input)
	{
		//Left operand is emptied if needed
		if (!isEmpty())
		{
			makeEmptyHelper(root);
		}
		root = NULL;
		//Right operand is copied to left
		copyTreeHelper(input.root, root);
	}
	//Copy is returned
	return *this;
}


// -------------------------- operator== --------------------------------------

// operator==:		Tells if the operands are equal
// Preconditions:	None
// Postconditions:	After the trees are compared leaf by leaf, their equality
//					is returned

// ----------------------------------------------------------------------------
bool BinTree:: operator==(const BinTree & input) const
{
	//Check to make sure both BinTrees aren't NULL
	if (root == NULL && input.root == NULL)
	{
		return true;
	}
	//Helper method is called to recursively check equality
	else
	{
		return equalityHelper(root, input.root);
	}
}


// -------------------------- operator!= --------------------------------------

// operator!=:		Tells if the operands are not equal
// Preconditions:	None
// Postconditions:	Opposite of operator== is returned

// ----------------------------------------------------------------------------
bool BinTree:: operator!=(const BinTree & input) const
{
	return !(*this == input);
}


// ------------------------------ insert --------------------------------------

// insert:			Inserts a new node into a BinTree
// Preconditions:	The node does not already exist in the BinTree
// Postconditions:	The new node is inserted in the BinTree based on its value.
//					A repeat node is not inserted and false is returned.

// ----------------------------------------------------------------------------
bool BinTree::insert(NodeData* input)
{
	//Check for a NULL parameter
	if (input == NULL) {
		return false;
	}
	//Helper function is called to recursively insert the parameter
	return insertHelper(input, root);
}


// ------------------------------ retrieve ------------------------------------

// retrieve:		Retrieves an existing node in a BinTree
// Preconditions:	The node exist in the BinTree
// Postconditions:	The node is found in the BinTree based on its value.
//					A node not inserted in the tree returns false.

// ----------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData & data, NodeData* & retVal) const
{
	//Base case for an empty tree
	if (isEmpty())
	{
		return false;
	}
	//If not empty, the recursive retrieveHelper is called and its result is
	//returned
	return retrieveHelper(data, retVal, root);
}


// ------------------------------ getHeight -----------------------------------

// getHeight:		Calculates the height of a node
// Preconditions:	The node exists in the BinTree
// Postconditions:	The node is found in the BinTree based on its value and
//					its height is returned.
//					A node not inserted in the tree returns as 0.

// ----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData & data) const
{
	//Base case for an empty tree
	if (isEmpty())
	{
		return 0;
	}
	Node* temp = root;
	Node* found = NULL;
	//Recursive findNode that first finds the node's position
	findNode(temp, found, data);
	//If the node was found recursive heightHelper is called and returned
	if (found != NULL)
	{
		return heightHelper(found);
	}
	//If the node wasn't found, zero is returned
	if (found == NULL)
	{
		return 0;
	}
}


// ------------------------------ bstreeToArray -------------------------------

// bstreeToArray:	Fills an array with the leaves of the tree
// Preconditions:	None
// Postconditions:	The tree is traversed inorder. As the method goes, leaves
//					are removed from the tree and added to the array. 

// ----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* data[])
{
	if (!isEmpty())
	{
		int i = 0;
		//recursive toArrayHelper is called
		toArrayHelper(data, root, i);
		//Tree is emptied
		makeEmptyHelper(root);
		//root is set to NULL
		root = NULL;
	}

}


// ------------------------------ arrayToBSTree -------------------------------

// arrayToBSTree:	Fills a tree with the elements of an array
// Preconditions:	None
// Postconditions:	The tree is traversed inorder. As the method goes, leaves
//					are added to the tree from the array. The array
//					elements are set to NULL. 

// ----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* data[])
{
	//Counter for number of array elements
	int size = 0;
	while (data[size+1] != NULL) {
		size++;
	}
	//Recursive helper is called to insert the elements into the tree
	toTreeHelper(data, 0, size);
}


// ------------------------------ operator<< ----------------------------------

// operator<<:		Prints the BinTree inorder
// Preconditions:	None
// Postconditions:	After calling inorderHelper to recursively traverse the
//					BinTree, the tree is printed inorder(left, root, right).

// ----------------------------------------------------------------------------
ostream& operator<<(std::ostream& os, const BinTree& data)
{
	//inorderHelper is called to recursively add to os
	data.inorderHelper(os, data.root);
	os << endl;
	return os;
}

void BinTree::inorderHelper(ostream& os, const Node* input) const
{
	//Base case for an empty node
	if (input == NULL)
	{
		return;
	}
	//Tree is recursively traversed in order (left, root, right)
	inorderHelper(os, input->left);
	os << *input->data << " ";
	inorderHelper(os, input->right);
}


//---------------------------- Sideways ---------------------------------------

// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.

// ----------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const
{
	if (current != NULL)
	{
		level++;
		sideways(current->right, level);
		// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}
		cout << *current->data << endl;
		// display information of object
		sideways(current->left, level);

	}
}


// -------------------------- makeEmptyHelper ---------------------------------

// makeEmptyHelper:	Recursively emptpies tree for makeEmpty
// Preconditions:	A non-NULL BinTree* is passed as a parameter
// Postconditions:	Recursively deletes every node in the BinTree

// ----------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node* subTree)
{
	//Check to see if current * is NULL
	if (subTree != NULL)
	{
		//Recursive call for children
		makeEmptyHelper(subTree->left);
		makeEmptyHelper(subTree->right);
		//Delete current leaf
		delete subTree;
	}
}


// -------------------------- copyTreeHelper ----------------------------------

// copyTreeHelper:	Recursively copies a tree for the copy constructor
// Preconditions:	A non-NULL BinTree* is passed as a parameter
// Postconditions:	Recursively copies every node in the BinTree

// ----------------------------------------------------------------------------
void BinTree::copyTreeHelper(const Node* input, Node* & newNode)
{
	newNode = NULL;

	//Copy tree nodes for preorder traversal after checking for an empty tree
	if (input != NULL)
	{
		//Copy node
		newNode = new Node;
		newNode->data = input->data;
		copyTreeHelper(input->left, newNode->left);
		copyTreeHelper(input->right, newNode->right);
	}
}


// -------------------------- insertHelper ------------------------------------

// insertHelper:	Recursively traverses a tree and inserts a node
// Preconditions:	A non-NULL NodeData* is passed as a parameter
// Postconditions:	Recursively traverses a tree and inserts a node. Repeat
//					nodes are not inserted.

// ----------------------------------------------------------------------------
bool BinTree::insertHelper(NodeData* input, Node* & current)
{
	//If node is empty, insert here
	if (current == NULL)
	{
		current = new Node;
		current->data = input;
		current->left = NULL;
		current->right = NULL;
		return true;
	}
	//If node is a repeat, return false for failed insert
	if (*current->data == *input) {
		return false;
	}
	//Recursive calls to traverse the BinTree
	else
	{
		//If value is less, it goes left
		if (*input < *current->data)
		{
			insertHelper(input, current->left);
		}
		//If value is more, it goes right
		else if (*input > *current->data)
		{
			insertHelper(input, current->right);
		}
	}
}


// -------------------------- equalityHelper ----------------------------------

// equalityHelper:	Recursively checks a tree for equality of nodes
// Preconditions:	None
// Postconditions:	Recursively checks a tree for equality of nodes and returns
//					result as a bool to overridden ==operator

// ----------------------------------------------------------------------------
bool BinTree::equalityHelper(const Node * tree1, const Node * tree2) const
{
	//Base case for if both nodes are NULL
	if (tree1 == NULL && tree2 == NULL)
	{
		return true;
	}
	//Base cases for if only one node is NULL
	else if (tree1 == NULL && tree2 != NULL)
	{
		return false;
	}
	else if (tree1 != NULL && tree2 == NULL)
	{
		return false;
	}
	//Base case for if nodes are unequal
	else if (*tree1->data != *tree2->data)
	{
		return false;
	}
	//Recursive calls for children if both nodes are equal and not NULL
	equalityHelper(tree1->left, tree2->left);
	equalityHelper(tree1->right, tree2->right);
}


// ------------------------------ retrieveHelper ------------------------------

// retrieveHelper:	Helps retrieve an existing node in a BinTree
// Preconditions:	The node exists in the BinTree
// Postconditions:	The node is found in the BinTree based on its value after
//					the tree is recursively traversed.
//					A node not inserted in the tree returns false.

// ----------------------------------------------------------------------------
bool BinTree::retrieveHelper(const NodeData & data, NodeData* & retVal,
	Node* current) const
{
	//Base case for a value not in the tree
	if (current == NULL)
	{
		return false;
	}
	//Base case for a found value
	if (data == *current->data)
	{
		retVal = current->data;
		return true;
	}
	//Recursive calls to traverse the BinTree
	else
	{
		//If value is less, it goes left
		if (data < *current->data)
		{
			retrieveHelper(data, retVal, current->left);
		}
		//If value is more, it goes right
		else if (data > *current->data)
		{
			retrieveHelper(data, retVal, current->right);
		}
	}
}


// ------------------------------ heightHelper --------------------------------

// heightHelper:	Helper method that recursively calculates the height of a
//					node
// Preconditions:	The node exists in the BinTree
// Postconditions:	The node is found in the BinTree based on its value and
//					its height is returned.
//					A node not inserted in the tree returns as 0.

// ----------------------------------------------------------------------------
int BinTree::heightHelper(const Node* current) const
{
	//Base case for a NULL node
	if (current->left == NULL && current->right == NULL)
	{
		return 1;
	}
	int l = 1;
	int r = 1;
	//Check and call for the left
	if (current->left != NULL)
	{
		l = 1 + heightHelper(current->left);
	}
	//check and call for the right
	if (current->right != NULL)
	{
		r = 1 + heightHelper(current->right);
	}
	//max height is returned
	return max(l,r);
}


// ------------------------------ findNode -----------------------------------

// findNode:		Checks for the existence of a node and returns it as a
//					pointer
// Preconditions:	None
// Postconditions:	The node is found in the BinTree based on its value and
//					a pointer to it is returned.

// ----------------------------------------------------------------------------
void BinTree::findNode(Node* & current, Node* & final, const NodeData & data) const
{
	//Base case for a value not in the tree
	if (current == NULL)
	{
		return;
	}
	//Base case for a found value
	if (data == *current->data)
	{
		final = new Node;
		final = current;
		return;
	}
	//Recursive calls to traverse the BinTree
	else
	{
		findNode(current->left, final, data);
		findNode(current->right, final, data);
	}
}


// ------------------------------ toArrayHelper -------------------------------

// toArrayHelper:	Fills an array with the leaves of the tree
// Preconditions:	None
// Postconditions:	The tree is recursively traversed inorder. As the method 
//					goes, leaves from the tree are added to the array. 

// ----------------------------------------------------------------------------
void BinTree::toArrayHelper(NodeData* data[], Node* current, int & i)
{
	//Base case for an empty node
	if (current == NULL)
	{
		return;
	}
	//Tree is recursively traversed in order (left, root, right)
	toArrayHelper(data, current->left, i);
	data[i] = current->data;
	i++;
	toArrayHelper(data, current->right, i);
}


// ------------------------------ toTreeHelper -------------------------------

// toTreeHelper:	Recursively fills a tree with the elements of an array
// Preconditions:	None
// Postconditions:	The array is traversed inorder. As the method goes, leaves
//					are added to the tree from the array. The array
//					elements are set to NULL. 

// ----------------------------------------------------------------------------
void BinTree::toTreeHelper(NodeData* data[], int low, int high)
{
	//Base case for when the parameters get out of bounds
	if (low > high)
	{
		return;
	}
	//check to make sure current location isn't NULL before inserting
	//and setting to NULL
	if (data[((low + high) / 2)] != NULL)
	{
		insert(data[((low + high) / 2)]);
		data[((low + high) / 2)] = NULL;
	}
	//Recursive calls
	toTreeHelper(data, low, ((low + high) / 2) - 1);
	toTreeHelper(data, ((low + high) / 2) + 1, high);
}


//------------------------- displaySideways -----------------------------------

//Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.

// ----------------------------------------------------------------------------
void BinTree::displaySideways() const
{
	sideways(root, 0);
}
