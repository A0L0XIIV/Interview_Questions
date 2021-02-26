/*
* Baran Kaya
* 2020
*/

#include <iostream>
#include <list>
#include <string>

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
	std::shared_ptr<BSTNode<Type>> getLeftChild() { return left; };
	std::shared_ptr<BSTNode<Type>> getRightChild() { return right; };
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
	std::shared_ptr<BSTNode<Type>> find(Type v, std::shared_ptr<BSTNode<Type>> node);
	std::shared_ptr<BSTNode<Type>> findParent(Type v, std::shared_ptr<BSTNode<Type>> node, bool &isLeftChild);
	void addNode(std::shared_ptr<BSTNode<Type>> node);
	bool deleteNode(std::shared_ptr<BSTNode<Type>> node);
	bool deleteNode(Type nodeValue);
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
std::shared_ptr<BSTNode<Type>> BST<Type>::find(Type v, std::shared_ptr<BSTNode<Type>> node) {
	// Reached the null leafs
	if (node == nullptr)
		return nullptr;
	// Get node's value
	Type value = node->getValue();
	// Base case
	if (value == v)
		return node;
	// Check left subtree
	else if (value > v){ // TODO: Add custom comparision for template values
		// Recursion
		return find(v, node->getLeftChild());
	}
	// Check right subtree
	else if (value < v) {
		// Recursion
		return find(v, node->getRightChild());
	}
	// Couldn't find
	return nullptr;
}

template<class Type>
std::shared_ptr<BSTNode<Type>> BST<Type>::findParent(Type v, std::shared_ptr<BSTNode<Type>> node, bool &isLeftChild) {
	// Reached the null leafs
	if (node == nullptr)
		return nullptr;
	// Parent's left child
	if (node->getLeftChild()->getValue() == v) {
		isLeftChild = true;
		return node;
	}
	// Parent's right child
	else if (node->getRightChild()->getValue() == v) {
		isLeftChild = false;
		return node;
	}
	// Check left subtree
	else if (node->getValue() > v) {
		// Recursion
		return findParent(v, node->getLeftChild(), isLeftChild);
	}
	// Check right subtree
	else if (node->getValue() < v) {
		// Recursion
		return findParent(v, node->getRightChild(), isLeftChild);
	}
	// Couldn't find
	return nullptr;
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
bool BST<Type>::deleteNode(std::shared_ptr<BSTNode<Type>> node){
	bool isParentsLeftChild = false;
	// Find the node's parent
	std::shared_ptr<BSTNode<Type>> parentNode = findParent(node->getValue(), root, isParentsLeftChild);
	// 4 case: leaf, w/left child, w/right child, w/both children
	std::shared_ptr<BSTNode<Type>> leftChild = node->getLeftChild();
	std::shared_ptr<BSTNode<Type>> rightChild = node->getRightChild();
	// Case 1: Node has only left subtree/children
	if (leftChild && !rightChild) {
		// Remove the root node, node's parent is empty
		if (!parentNode) {
			root = leftChild;
		}
		// Update the parent's left child pointer to node's left child
		else if (isParentsLeftChild) {
			parentNode->updateLeft(leftChild);
		}
		// Update the parent's right child pointer to node's left child
		else {
			parentNode->updateRight(leftChild);
		}
	}	
	// Case 2: Node has only right subtree/children
	else if (!leftChild && rightChild) {
		// Remove the root node, node's parent is empty
		if (!parentNode) {
			root = rightChild;
		}
		// Update the parent's left child pointer to node's right child
		else if (isParentsLeftChild) {
			parentNode->updateLeft(rightChild);
		}
		// Update the parent's right child pointer to node's right child
		else {
			parentNode->updateRight(rightChild);
		}
	}
	// Case 3: Node has both left and right subtree/children
	else if (leftChild && rightChild) {
		// Update the parent's child pointer to node's right child
		// Right child moves one layer up, find a best spot for left subtree
		// Remove the root node, node's parent is empty
		if (!parentNode) {
			root = rightChild;
		}
		// Update the parent's left child pointer to node's right child
		else if (isParentsLeftChild) {
			parentNode->updateLeft(node->getRightChild());
			// Need to put node's left children/subtree
		}
		// Update the parent's right child pointer to node's right child
		else {
			parentNode->updateRight(node->getRightChild());
			// Need to put node's left children/subtree
		}
		// Current pointer to finding best spot for left subtree, start from parentNode or root
		std::shared_ptr<BSTNode<Type>> current = parentNode ? parentNode : root;
		// Find the best spot for left subtree, until finding a node with empty left node
		while (current->getLeftChild() != nullptr) {
			// Left child is greater than the current node, move right
			if (leftChild > current) {
				current = current->getRightChild();
			}
			// Left child is less than the current node, move left
			else if (leftChild < current) {
				current = current->getLeftChild();
			}
		}
		// Found the best spot for node's left subtree
		current->updateLeft(leftChild);
	}
	// Case 4: Node is a leaf node: doesn't have any children
	else {
		// Remove the root node, node's parent is empty
		if (!parentNode) {
			root = nullptr;
			root.reset();
		}
		// Update the parent's left child pointer to nullptr
		else if (isParentsLeftChild) {
			parentNode.get()->updateLeft(nullptr);
			parentNode.get()->getLeftChild().reset();
		}
		// Update the parent's right child pointer to nullptr
		else {
			parentNode.get()->updateRight(nullptr);
			parentNode.get()->getRightChild().reset();
		}
	}
	return true;
}

template<class Type>
bool BST<Type>::deleteNode(Type nodeValue) {
	// Find the node via value and call the overloaded function
	return deleteNode(find(nodeValue, root));
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
