/*
* Baran Kaya
* 2020
*/

#include <iostream>

class BSTNode{
	int value;
	BSTNode* left;
	BSTNode* right;
public:
	// Constructors
	BSTNode();
	BSTNode(int v);
	BSTNode(int v, BSTNode* l, BSTNode* r);
	// Functions
	int getValue();
	BSTNode* getLeftChild();
	BSTNode* getRightChild();
	void updateValue(int v);
	void updateLeft(BSTNode* l);
	void updateRight(BSTNode* r);
};

// Constructors
BSTNode::BSTNode() {
	this->value = 0;
	this->left = nullptr;
	this->right = nullptr;
}

BSTNode::BSTNode(int v) {
	this->value = v;
	this->left = nullptr;
	this->right = nullptr;
}

BSTNode::BSTNode(int v, BSTNode* l, BSTNode* r) {
	this->value = v;
	this->left = l;
	this->right = r;
}

// Functions
int BSTNode::getValue() {
	return this->value;
}

BSTNode* BSTNode::getLeftChild() {
	return this->left;
}

BSTNode* BSTNode::getRightChild() {
	return this->right;
}

void BSTNode::updateValue(int v) {
	this->value = v;
}

void BSTNode::updateLeft(BSTNode* l) {
	this->left = l;
}

void BSTNode::updateRight(BSTNode* r) {
	this->right = r;
}



class BST {
	BSTNode* root;
	unsigned short numOfNodes;
	unsigned short depth;
public:
	// Constructors
	BST();
	BST(BSTNode* rootNode);
	BST(std::vector<int> array);
	// Functions
	void printTree();
	void printPreorder(BSTNode* node);
	void printInorder(BSTNode* node);
	void printPostorder(BSTNode* node);
	BSTNode* find(int v, BSTNode* node);
	void addNode(BSTNode* node);
	void deleteNode(BSTNode* node);
	int calculateDepth(BSTNode* node);
	BSTNode* getRoot();
};

// Constructors
BST::BST() {
	this->root = nullptr;
	this->numOfNodes = 0;
	this->depth = 0;
}

BST::BST(BSTNode* rootNode) {
	this->root = rootNode;
	this->numOfNodes = 1;
	this->depth = 1;
}

BST::BST(std::vector<int> array) {
	// Create BST from an array
	// Loop over the array and fill the BST, Start from 1 because 0 is root
	for (int num : array) {
		BSTNode* node = new BSTNode(num);
		BST::addNode(node);
	}
}

// Functions
BSTNode* BST::getRoot() {
	return this->root;
}

void BST::printTree() {
	std::cout << std::endl << "Preorder: " << std::endl;
	printPreorder(this->root);
	std::cout << std::endl << "Inorder: " << std::endl;
	printInorder(this->root);
	std::cout << std::endl << "Postorder: " << std::endl;
	printPostorder(this->root);
	std::cout << std::endl;
}

void BST::printPreorder(BSTNode* node) {
	if (node == nullptr)
		return;
	std::cout << " - " << node->getValue();
	printPreorder(node->getLeftChild());
	printPreorder(node->getRightChild());
}
void BST::printInorder(BSTNode* node) {
	if (node == nullptr)
		return;
	printInorder(node->getLeftChild());
	std::cout << " - " << node->getValue();
	printInorder(node->getRightChild());
}
void BST::printPostorder(BSTNode* node) {
	if (node == nullptr)
		return;
	printPostorder(node->getLeftChild());
	printPostorder(node->getRightChild());
	std::cout << " - " << node->getValue();
}

BSTNode* BST::find(int v, BSTNode * node) {
	// Base case
	if (node->getValue() == v)
		return node;
	// Reached the null leafs
	else if (node == nullptr)
		return nullptr;
	else if (node->getValue() > v){
		// Recursion
		find(v, node->getLeftChild());
	}
	else if (node->getValue() < v) {
		// Recursion
		find(v, node->getRightChild());
	}
}

void BST::addNode(BSTNode* node) {
	BSTNode* newNode = new BSTNode(node->getValue(), node->getLeftChild(), node->getRightChild());
	// Check root of the tree
	if (this->root != nullptr) {
		bool isLeft = false;
		BSTNode* traversal = this->root;
		BSTNode* previousTraversal = traversal;
		// Loop over the tree
		while (traversal != nullptr){
			if (traversal->getValue() > node->getValue()) {
				traversal = traversal->getLeftChild();
				isLeft = true;
			}
			else if (traversal->getValue() < node->getValue()) {
				traversal = traversal->getRightChild();
				isLeft = false;
			}
			// Update the previous traversal
			if (traversal != nullptr)
				previousTraversal = traversal;
			else if (isLeft)
				previousTraversal->updateLeft(newNode);
			else
				previousTraversal->updateRight(newNode);
		}
	}
	// Root is empty, add new to as a root
	else {
		this->root = newNode;
	}
	// Update the depth of the tree
	this->depth = this->calculateDepth(this->root);
}

void BST::deleteNode(BSTNode* node){
	// TO DO: 4 case: leaf, w/left child, w/right child, w/both children
}

int BST::calculateDepth(BSTNode* node) {
	if (node == nullptr)
		return 0;
	else {
		// Call left subtree
		int leftDepth = calculateDepth(node->getLeftChild());
		// Call right subtree
		int rightDepth = calculateDepth(node->getRightChild());
		if (leftDepth > rightDepth)
			return leftDepth + 1;
		else
			return rightDepth + 1;
	}
}