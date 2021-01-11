/*
* Baran Kaya
* 2020
*/

#include <iostream>

template<class Type>
class BSTNode{
	Type value;
	BSTNode* left;
	BSTNode* right;
public:
	// Constructors
	BSTNode() = default;
	BSTNode(Type v) { value = v; left = nullptr; right = nullptr; };
	BSTNode(Type v, BSTNode* l, BSTNode* r) { value = v; left = l; right = r; };
	// Functions
	Type getValue() { return value; };
	BSTNode* getLeftChild() { return left; };
	BSTNode* getRightChild() { return right; };
	void updateValue(Type v) { value = v; };
	void updateLeft(BSTNode* l) { left = l; };
	void updateRight(BSTNode* r) { right = r; };
};

template<class Type>
class BST {
	BSTNode<Type>* root;
	unsigned short numOfNodes;
	unsigned short depth;
public:
	// Constructors
	BST() = default;
	BST(BSTNode<Type>* rootNode) { root = rootNode; };
	BST(std::vector<Type> array);
	// Functions
	void printTree();
	void printPreorder(BSTNode<Type>* node);
	void printInorder(BSTNode<Type>* node);
	void printPostorder(BSTNode<Type>* node);
	BSTNode<Type>* find(int v, BSTNode<Type>* node);
	void addNode(BSTNode<Type>* node);
	void deleteNode(BSTNode<Type>* node);
	int calculateDepth(BSTNode<Type>* node);
	BSTNode<Type>* getRoot();
};

// Constructor
template<class Type>
BST<Type>::BST(std::vector<Type> array) {
	// Create BST from an array
	// Loop over the array and fill the BST, Start from 1 because 0 is root
	for (Type element : array) {
		BSTNode<Type>* node = new BSTNode<Type>(element);
		BST<Type>::addNode(node);
	}
}

// Functions
template<class Type>
BSTNode<Type>* BST<Type>::getRoot() {
	return this->root;
}

template<class Type>
void BST<Type>::printTree() {
	std::cout << std::endl << "Preorder: " << std::endl;
	printPreorder(this->root);
	std::cout << std::endl << "Inorder: " << std::endl;
	printInorder(this->root);
	std::cout << std::endl << "Postorder: " << std::endl;
	printPostorder(this->root);
	std::cout << std::endl;
}

template<class Type>
void BST<Type>::printPreorder(BSTNode<Type>* node) {
	if (node == nullptr)
		return;
	std::cout << " - " << node->getValue();
	printPreorder(node->getLeftChild());
	printPreorder(node->getRightChild());
}

template<class Type>
void BST<Type>::printInorder(BSTNode<Type>* node) {
	if (node == nullptr)
		return;
	printInorder(node->getLeftChild());
	std::cout << " - " << node->getValue();
	printInorder(node->getRightChild());
}

template<class Type>
void BST<Type>::printPostorder(BSTNode<Type>* node) {
	if (node == nullptr)
		return;
	printPostorder(node->getLeftChild());
	printPostorder(node->getRightChild());
	std::cout << " - " << node->getValue();
}

template<class Type>
BSTNode<Type>* BST<Type>::find(int v, BSTNode<Type>* node) {
	// Base case
	if (node->getValue() == v)
		return node;
	// Reached the null leafs
	else if (node == nullptr)
		return nullptr;
	else if (node->getValue() > v){ // TODO: Add custom comparision for template values
		// Recursion
		find(v, node->getLeftChild());
	}
	else if (node->getValue() < v) {
		// Recursion
		find(v, node->getRightChild());
	}
}

template<class Type>
void BST<Type>::addNode(BSTNode<Type>* node) {
	BSTNode<Type>* newNode = new BSTNode<Type>(node->getValue(), node->getLeftChild(), node->getRightChild());
	// Check root of the tree
	if (this->root != nullptr) {
		bool isLeft = false;
		BSTNode<Type>* traversal = this->root;
		BSTNode<Type>* previousTraversal = traversal;
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

template<class Type>
void BST<Type>::deleteNode(BSTNode<Type>* node){
	// TO DO: 4 case: leaf, w/left child, w/right child, w/both children
}

template<class Type>
int BST<Type>::calculateDepth(BSTNode<Type>* node) {
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