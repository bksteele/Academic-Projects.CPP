#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	BinTree tree1;
	
	NodeData notND("n");
	NodeData andND("a");
	NodeData sssND("s");
	NodeData ttttND("tttt");
	NodeData oooND("ooo");
	NodeData yND("y");
	NodeData eND("e");
	NodeData mND("m");
	NodeData tND("t");

	NodeData* temp1 = new NodeData(notND);
	NodeData* temp2 = new NodeData(andND);
	NodeData* temp3 = new NodeData(sssND);
	//Insert tests
	tree1.insert(temp1);
	tree1.insert(temp2);
	tree1.insert(temp3);
	//Copy Constructor test with filled, balanced tree
	BinTree tree2(tree1);
	NodeData* temp4 = new NodeData(yND);
	tree2.insert(temp4);
	//Copy Constructor test with filled, unbalanced tree
	BinTree tree3(tree2);
	BinTree tree4;
	//Copy Constructor with empty tree
	BinTree tree5(tree4);
	bool test = false;
	//==Operator test for two empty trees
	if (tree5 == tree4) {
		test = true;
	}
	cout << "Tree 5 == Tree 4 : " << test << endl;
	//!=Operator test for two empty trees
	test = false;
	bool test4 = false;
	if (tree4 != tree5) {
		test4 = true;
	}
	cout << "Tree 5 != Tree 4 : " << test4 << endl;
	bool test2 = false;
	//==Operator test for two filled trees
	if (tree2 == tree3) {
		test2 = true;
	}
	cout << "Tree 2 == Tree 3 : " << test2 << endl;
	//!=Operator test for two different trees
	bool test3 = false;
	if (tree2 != tree5) {
		test3 = true;
	}
	cout << "Tree 2 != Tree 5 : " << test3 << endl;
	//!=Operator test for two equal trees
	test4 = false;
	if (tree2 != tree3) {
		test4 = true;
	}
	cout << "Tree 2 != Tree 3 : " << test4 << endl;
	//Operator = test for an empty tree
	BinTree tree6;
	tree6 = tree2;
	//operator = test for a filled tree
	tree6 = tree4;
	//Test for getHeight when node is at root
	cout << "Tree 2 level of n: " << tree2.getHeight(notND) << endl;
	//Test for getHeight when node is in middle of tree
	cout << "Tree 2 level of s: " << tree2.getHeight(sssND) << endl;
	//Test for getHeight when node is at the bottom of an unbalanced tree
	cout << "Tree 2 level of y: " << tree2.getHeight(yND) << endl;
	//Test for getHeight when node doesn't exist in tree
	cout << "Tree 1 level of y: " << tree1.getHeight(yND) << endl;
	NodeData * rTest = new NodeData();
	//Test for retrieve when node doesn't exist
	tree1.retrieve(yND, rTest);
	//Test for retrieve when node is at root
	tree2.retrieve(notND, rTest);
	//Test for retrieve when node is at a leaf
	tree2.retrieve(yND, rTest);
	//Test for bstreeToArray
	NodeData* arr1[5];
	arr1[4] = NULL;
	tree2.bstreeToArray(arr1);
	//Test for arrayToBSTree
	BinTree tree8;
	tree8.arrayToBSTree(arr1);
	//Aside from these tests, the full driver file provided by
	//Professor Kim was also checked
}
