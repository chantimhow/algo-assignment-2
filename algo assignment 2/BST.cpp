#include <cstddef>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#include "BTNode.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::display(int order,int source){
	if(root==NULL) return false;
	switch(order){
		case 1:
		switch(source){
			case 1:
				inOrderPrint();
				break;

			case 2:
				InorderOutfile();
				break;
			
		}
		break;
		case 2:
		switch(source){
			case 1:
				reverseInorderPrint();
				break;
			case 2:
				reverseInorderOutfile();
				break;
		}

	}
	return true;
}


void BST::reverseInorderPrint(){
	if(root == NULL) return;
	reverseInorderPrint2(root);
	return;


}
void BST::reverseInorderPrint2(BTNode *cur){
	if(cur == NULL) return;
	reverseInorderPrint2(cur->right);
	cur->item.print(cout);
	reverseInorderPrint2(cur->left);
}

void BST::InorderOutfile(){
	if (root == NULL) return;// handle special case
	else {
		ofstream outfile;
		outfile.open("student_info.txt", ios::app);
		if (!outfile.is_open()) {
			cout << "file is not open";
			return;
		}
		InorderOufile2(root,outfile);// do normal process
		outfile.close();
	}
}

void BST::InorderOufile2(BTNode *cur,ofstream &outfile){
	if (cur == NULL) {
		return;
	}
	
	InorderOufile2(cur->left,outfile);
	cur->item.print(outfile);
	InorderOufile2(cur->right,outfile);

}
void BST::reverseInorderOutfile(){
	if (root == NULL) return;// handle special case
	else {
		ofstream outfile;
		outfile.open("student_info.txt", ios::app);
		if (!outfile.is_open()) {
			cout << "file is not open";
			return;
		}
		reverseInorderOufile2(root, outfile);
		outfile.close();
	}

}
void BST::reverseInorderOufile2(BTNode *cur,ofstream &outfile){

	if (cur == NULL) {
		return;
	}
	reverseInorderOufile2(cur->right,outfile);
	cur->item.print(outfile);
	reverseInorderOufile2(cur->left,outfile);

}
bool BST::CloneSubtree(BST t1,type item){
	BTNode *cur;
	if (t1.empty()) {
		cout << "the original BST is empty!" << endl;
		return false;
	}
	if(root == NULL){
		cur = t1.findnode(t1.root,item);
		if (cur == NULL) {
			cout << "cannot find id " << item.id << endl;
			return false;
		}
		cloneNode(cur);
		cout << "Original Binary Search Tree:" << endl;
		cout << "____________________________" << endl;
		t1.preOrderPrint();
		cout << "Cloned Binary Search Tree:" << endl;
		cout << "____________________________" << endl;
		preOrderPrint();
		return true;
	}
	else {
		cout << "Subtree is not empty for cloning!";
		return false;
	}
	



}
BTNode* BST::findnode(BTNode *cur,type item){
	if(cur==NULL)return NULL;
	if (cur->item.compare2(item)){
		return cur;
	}
	else if(cur->item.compare1(item)){
		findnode(cur->left,item);
	}
	else findnode(cur->right,item);
}
void BST::cloneNode(BTNode *cur){
	if (cur == NULL) return;
	insert(cur->item);
	cloneNode(cur->left);
	cloneNode(cur->right);
}
//deepest nodes
int BST::height(BTNode* cur) {
	if (cur == NULL) return 0;
	return 1 + max(height(cur->left), height(cur->right));
}

void BST::printLevel(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 1) {
		cout << cur->item.getID() << " ";  // only print Student ID
	}
	else {
		printLevel(cur->left, level - 1);
		printLevel(cur->right, level - 1);
	}
}
bool BST::deepestNodes() {
	if (root == NULL) return false;  // empty tree

	int h = height(root);
	cout << "Deepest nodes (Student IDs): ";
	printLevel(root, h);
	cout << endl;
	return true;
}

bool BST::printLevelNodes()
{
	if (root == NULL)
	{
		cout << "There is nothing in the tree! \n ";
		return false;
	}

	int lvl = 1, currLvlNode = 1, nextLvlNode = 0;
	Queue p;

	p.enqueue(root); //create a queue to store the tree root.

	if (p.empty())
	{
		cout << "The tree is empty!\n";
		return false;

	}

	while (!p.empty())
	{
		cout << "Level " << lvl << " nodes: ";

		for (int i = 0; i < currLvlNode; i++)
		{
			BTNode* cur;
			p.dequeue(cur); //take out the node and record it to cur.

			cout << cur->item.id;

			if (i < currLvlNode - 1)
				cout << " ";

			if (cur->left != NULL)
			{
				p.enqueue(cur->left);
				nextLvlNode++;       // count how many node at next lvl.
			}
			if (cur->right != NULL)
			{
				p.enqueue(cur->right);
				nextLvlNode++;
			}
		}

		lvl++;
		currLvlNode = nextLvlNode;
		nextLvlNode = 0;
		cout << endl;
	}
	return true;
}






bool BST::printPath()
{
	if (root == NULL)
	{
		cout << "There is nothing in the tree! \n ";
		return false;
	}
	cout << "Below are all the external paths for the tree: \n\n";
	type path[100];
	printPathRecurs(root, path, 0);
	return true;

}

void BST::printPathRecurs(BTNode* cur, type path[], int depth)
{

	path[depth] = cur->item;


	//find leaf node and print it when there is no more leaf node.
	if (cur->left == NULL && cur->right == NULL)
	{
		for (int i = 0; i <= depth; i++)
		{
			cout << path[i].id;
			if (i < depth)
			{
				cout << " "; //empty space between the student id.
			}
		}
		cout << endl;
	}
	else
	{
		//recursive function to get all the leaf node.
		if (cur->left != NULL)
			printPathRecurs(cur->left, path, depth + 1);
		if (cur->right != NULL)
			printPathRecurs(cur->right, path, depth + 1);

	}

}

bool BST::find(int id) {
	BTNode* current = root;
	while (current != nullptr) {
		if (id == current->item.id) return true;
		else if (id < current->item.id)
			current = current->left;
		else
			current = current->right;
	}
	return false;
}










