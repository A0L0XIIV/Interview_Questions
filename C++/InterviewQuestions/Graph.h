#pragma once

/*
* Baran Kaya
* 2021
*/

#include <iostream>
#include <queue>
#include <stack>
#include <map>

template<class Type>
class GraphNode {
	Type value;
	std::vector<std::shared_ptr<GraphNode>> neighbors;
public:
	// Constructors
	GraphNode() = default;
	GraphNode(Type v) : value(v), neighbors(nullptr) {};
	GraphNode(Type v, std::shared_ptr<BSTNode> nodes) : value(v), neighbors(nodes) {};
	// Functions
	Type getValue() { return value; };
	std::shared_ptr<GraphNode> getNeighbors() { return neighbors; };
	void updateValue(Type v) { value = v; };
	void updateNeighbors(std::shared_ptr<GraphNode> nodes) { neighbors = nodes; };
};

template<class Type>
class Graph {
	std::shared_ptr<GraphNode<Type>> start;
	unsigned short numOfNodes;
	unsigned short numOfEdges;
public:
	// Constructors
	Graph() = default;
	Graph(std::shared_ptr<GraphNode<Type>> startNode) : start(startNode) {};
	Graph(std::vector<Type> vec);
	// Functions
	void printGraph();
	std::shared_ptr<GraphNode<Type>> find(int v, std::shared_ptr<GraphNode<Type>> node);
	void addNode(Type val);
	void addNode(std::shared_ptr<GraphNode<Type>> node);
	void deleteNode(Type val);
	void deleteNode(std::shared_ptr<GraphNode<Type>> node);
	std::shared_ptr<GraphNode<Type>> getHead();
	size_t countNodes(std::shared_ptr<GraphNode<Type>> = start);
	std::shared_ptr<GraphNode<Type>> BreadthFirstSearch();
	std::shared_ptr<GraphNode<Type>> DepthFirstSearch();
};

// BFS
template <class Type>
std::shared_ptr<GraphNode<Type>> Graph<Type>::BreadthFirstSearch() {
	// Queue and explored vector
	std::queue<std::shared_ptr<GraphNode<Type>>> q;
	std::vector<Type> explored;
	std::shared_ptr<GraphNode<Type>> current;
	Type currentValue;
	// Push the first node (head) in queue
	q.push(head);
	// Explore every node until the queue is empty or find the node
	while (!q.empty()) {
		// Get the front element and its value
		current = q.front();
		currentValue = current->getValue();
		// Pop from queue
		q.pop();
		// Search in the vector, if find return it
		if (find(explored.begin(), explored.end(), current->getValue()) != explored.end()) {
			return current;
		}
		// Not find, search next nodes
		else {
			// Add in the explored vector
			explored.push_back(currentValue);
			// Add node's neighbors in queue
			for (auto neighbor : current->getNeighbors()) {
				q.push(neighbor);
			}
		}
	}
	// Could not find the node, return null
	return nullptr;
}

// DFS
template <class Type>
std::shared_ptr<GraphNode<Type>> Graph<Type>::DepthFirstSearch() {
	// Stack and discovered vector
	std::stack<std::shared_ptr<GraphNode<Type>>> s;
	std::vector<Type> discovered;
	std::shared_ptr<GraphNode<Type>> current;
	Type currentValue;
	// Push the first node (head) in stack
	s.push(head);
	// Explore every node until the stack is empty or find the node
	while (!s.empty()) {
		// Get the front element and its value
		current = s.top();
		currentValue = current->getValue();
		// Pop from stack
		s.pop();
		// Search in the vector, if find return it
		if (find(discovered.begin(), discovered.end(), current->getValue()) != discovered.end()) {
			return current;
		}
		// Not find, search next nodes
		else {
			// Add in the discovered vector
			discovered.push_back(currentValue);
			// Add node's neighbors in stack
			for (auto neighbor : current->getNeighbors()) {
				q.push(neighbor);
			}
		}
	}
	// Could not find the node, return null
	return nullptr;
}