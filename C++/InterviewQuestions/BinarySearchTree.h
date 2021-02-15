/*
* Baran Kaya
* 2020
*/

#include <iostream>
#include <list>

template<class Type>
class BSTNode{
	Type value;
	std::shared_ptr<BSTNode> left;
	std::shared_ptr<BSTNode> right;
public:
	// Constructors
	BSTNode() = default;
	BSTNode(Type v) : value (v), left(nullptr), right(nullptr) {};
	BSTNode(Type v, std::shared_ptr<BSTNode> l, std::shared_ptr<BSTNode> r) : value(v), left(l), right(r) {};
	// Functions
	Type getValue() { return value; };
	std::shared_ptr<BSTNode> getLeftChild() { return left; };
	std::shared_ptr<BSTNode> getRightChild() { return right; };
	void updateValue(Type v) { value = v; };
	void updateLeft(std::shared_ptr<BSTNode> l) { left = l; };
	void updateRight(std::shared_ptr<BSTNode> r) { right = r; };
};

template<class Type>
class BST {
	std::shared_ptr<BSTNode<Type>> root;
	unsigned short numOfNodes;
	unsigned short depth;
public:
	// Constructors
	BST() = default;
	BST(std::shared_ptr<BSTNode<Type>> rootNode) : root(rootNode) {};
	BST(std::vector<Type> vec);
	// Functions
	void printTree();
	void printPreorder(std::shared_ptr<BSTNode<Type>> node);
	void printInorder(std::shared_ptr<BSTNode<Type>> node);
	void printPostorder(std::shared_ptr<BSTNode<Type>> node);
	std::shared_ptr<BSTNode<Type>> find(int v, std::shared_ptr<BSTNode<Type>> node);
	void addNode(std::shared_ptr<BSTNode<Type>> node);
	void deleteNode(std::shared_ptr<BSTNode<Type>> node);
	int calculateDepth(std::shared_ptr<BSTNode<Type>> node);
	std::shared_ptr<BSTNode<Type>> getRoot();
	std::shared_ptr<BSTNode<Type>> randomNode(std::shared_ptr<BSTNode<Type>> node);
	size_t countNodes(std::shared_ptr<BSTNode<Type>> = root);
	void depthNodesToLinkedList(std::shared_ptr<BSTNode<Type>> node, size_t depth, std::vector<std::list<std::shared_ptr<BSTNode<Type>>>> &result);
};

// Constructor
template<class Type>
BST<Type>::BST(std::vector<Type> vec) : BST() {
	// Check vector's emptiness
	if (!vec.empty()) {
		// Create a BST from a vector
		for (Type element : vec) {
			auto node = std::shared_ptr<BSTNode<int>> (new BSTNode<Type>(element));
			BST<Type>::addNode(node);
		}
	}
}

// Functions
template<class Type>
std::shared_ptr<BSTNode<Type>> BST<Type>::getRoot() {
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
void BST<Type>::printPreorder(std::shared_ptr<BSTNode<Type>> node) {
	if (node == nullptr)
		return;
	std::cout << " - " << node->getValue();
	printPreorder(node->getLeftChild());
	printPreorder(node->getRightChild());
}

template<class Type>
void BST<Type>::printInorder(std::shared_ptr<BSTNode<Type>> node) {
	if (node == nullptr)
		return;
	printInorder(node->getLeftChild());
	std::cout << " - " << node->getValue();
	printInorder(node->getRightChild());
}

template<class Type>
void BST<Type>::printPostorder(std::shared_ptr<BSTNode<Type>> node) {
	if (node == nullptr)
		return;
	printPostorder(node->getLeftChild());
	printPostorder(node->getRightChild());
	std::cout << " - " << node->getValue();
}

template<class Type>
std::shared_ptr<BSTNode<Type>> BST<Type>::find(int v, std::shared_ptr<BSTNode<Type>> node) {
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
void BST<Type>::addNode(std::shared_ptr<BSTNode<Type>> node) {
	auto newNode = std::shared_ptr<BSTNode<Type>> (new BSTNode<Type>(node->getValue(), node->getLeftChild(), node->getRightChild()));
	// Check root of the tree
	if (this->root != nullptr) {
		bool isLeft = false;
		std::shared_ptr<BSTNode<Type>> traversal = this->root;
		std::shared_ptr<BSTNode<Type>> previousTraversal = traversal;
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
void BST<Type>::deleteNode(std::shared_ptr<BSTNode<Type>> node){
	// TO DO: 4 case: leaf, w/left child, w/right child, w/both children
}

template<class Type>
int BST<Type>::calculateDepth(std::shared_ptr<BSTNode<Type>> node) {
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

template<class Type>
std::shared_ptr<BSTNode<Type>> BST<Type>::randomNode(std::shared_ptr<BSTNode<Type>> node) {
	// Left and right subtree node count for the current node
	size_t leftCount = countNodes(node->getLeftChild());
	size_t rightCount = countNodes(node->getRightChild());
	// Leaf node, doesn't have any branches, return it
	if (leftCount == 0 && rightCount == 0) {
		return node;
	}
	// Random number for selecting: current node, left subtree or right subtree (+1 is node itself)
	unsigned int randomSelection = rand() % (leftCount + rightCount + 1);
	// If random number is 0, return the current node (0)
	if (randomSelection == 0) {
		return node;
	}
	// Call left subtree recursively (1 to leftCount)
	else if (randomSelection > 0 && randomSelection <= leftCount) {
		return randomNode(node->getLeftChild());
	}
	// Call right subtree recursively (leftCount+1 to nodeCount)
	else {
		return randomNode(node->getRightChild());
	}
}

template<class Type>
size_t BST<Type>::countNodes(std::shared_ptr<BSTNode<Type>> root) {
	// Reached the leaves
	if (root == nullptr) {
		return 0;
	}
	// Call for left and right subtrees, +1 is node itself
	return countNodes(root->getLeftChild()) + countNodes(root->getRightChild()) + 1;
}

template<class Type>
inline void BST<Type>::depthNodesToLinkedList(std::shared_ptr<BSTNode<Type>> node, size_t depth, std::vector<std::list<std::shared_ptr<BSTNode<Type>>>> &result)
{
	if (node == nullptr) {
		return;
	}
	// Create a new linked list for each depth
	if (result.size() < depth) {
		result.push_back(std::list<std::shared_ptr<BSTNode<Type>>>());
	}
	// Push back node in linked list
	result[depth-1].push_back(node);
	// Call left and right subtree nodes
	depthNodesToLinkedList(node->getLeftChild(), depth + 1, result);
	depthNodesToLinkedList(node->getRightChild(), depth + 1, result);
	// Final return
	return;
}
