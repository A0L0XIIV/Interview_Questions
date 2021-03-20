#pragma once

/*
* Baran Kaya
* 2021
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

template<class Type>
class GraphNode {
	Type value;
	std::vector<std::shared_ptr<GraphNode<Type>>> neighbors;
public:
	// Constructors
	GraphNode() = default;
	GraphNode(Type v) : value(v) {};
	GraphNode(Type v, std::vector<std::shared_ptr<GraphNode<Type>>> nodes) : value(v), neighbors(nodes) {};
	// Functions
	Type GetValue() { return value; };
	std::vector<std::shared_ptr<GraphNode<Type>>> GetNeighbors() { return neighbors; };
	void UpdateValue(Type v) { value = v; };
	void UpdateNeighbors(std::shared_ptr<GraphNode<Type>> nodes) { neighbors = nodes; };
	void AddNeighbor(std::shared_ptr<GraphNode<Type>> neighbor) { neighbors.push_back(neighbor); };
	void RemoveNeighbor(std::shared_ptr<GraphNode<Type>> neighbor);
};

template<class Type>
class Graph {
	std::shared_ptr<GraphNode<Type>> start;
	size_t numOfNodes;
	size_t numOfEdges;
public:
	// Constructors
	Graph() = default;
	Graph(std::shared_ptr<GraphNode<Type>> startNode) : start(startNode), numOfNodes(0), numOfEdges(0) {};
	//Graph(std::vector<Type> vec);
	// Functions
	void PrintGraph();
	void AddNode(Type val, std::vector<Type> neighbors = {});
	void DeleteNode(Type val);
	std::shared_ptr<GraphNode<Type>> GetStart() { return start; };
	size_t GetNumOfNodes() { return numOfNodes; };
	size_t GetNumOfEdges() { return numOfEdges; };
	std::string BreadthFirstSearch();
	std::shared_ptr<GraphNode<Type>> BreadthFirstSearch(Type searchValue);
	std::shared_ptr<GraphNode<Type>> DepthFirstSearch(Type searchValue);
};

// Node Functions

template <class Type>
void GraphNode<Type>::RemoveNeighbor(std::shared_ptr<GraphNode<Type>> neighborNode) { 
	// Find in the vector
	auto iterator = find(neighbors.begin(), neighbors.end(), neighborNode);
	// If found, remove it
	if (iterator != neighbors.end()) {
		neighbors.erase(iterator);
	}
};

// Graph Functionss
template <class Type>
void Graph<Type>::PrintGraph() {
	if (!start) return;
	std::cout << "Graph: " << BreadthFirstSearch() << std::endl;
	return;
}

template <class Type>
void Graph<Type>::AddNode(Type val, std::vector<Type> neighbors) {
	// Find neighbor nodes with values and store them in the vector
	std::vector<std::shared_ptr<GraphNode<Type>>> neighborNodes;
	for (auto n : neighbors) {
		auto tempNode = BreadthFirstSearch(n);
		if (tempNode != nullptr) {
			neighborNodes.push_back(tempNode);
		}
	}
	// Create a new node with the new value and neighbor nodes vector
	std::shared_ptr<GraphNode<Type>> node(new GraphNode<Type>(val, neighborNodes));
	// Update/add neighbor nodes' neighbor vector
	for (auto n : neighborNodes) {
		n->AddNeighbor(node);
	}
	// Start node update
	if (!start) {
		start = node;
	}
	// Update the counter variables, count again
	BreadthFirstSearch();
	// Return
	return;
}

template <class Type>
void Graph<Type>::DeleteNode(Type val) {
	// Find the node with given value
	std::shared_ptr<GraphNode<Type>> nodeToDelete = DepthFirstSearch(val);
	std::vector<std::shared_ptr<GraphNode<Type>>> nodeToDeleteNeighbors = nodeToDelete->GetNeighbors();
	// Go nodeToDelete's neighbors and delete the pointer to nodeToDelete in them
	for (auto neighborNode : nodeToDeleteNeighbors) {
		// Update neighbor nodes' vector -remove from them-
		neighborNode->RemoveNeighbor(nodeToDelete);
	}
	// If the nodeToDelete is the start node, change it to its first neighbor
	if (nodeToDelete == start) {
		// Has neighbors
		if (!nodeToDeleteNeighbors.empty())
			start = nodeToDelete->GetNeighbors().at(0);
		// Only node in the graph
		else
			start.reset(); // TODO: It empties the shared_ptr and makes its address 0x0000000, make start normal ptr
	}
	// Update the counter variables, count again
	BreadthFirstSearch();
	// Return its value
	return;
}

// BFS for counting nodes/edges and printing the graph
template <class Type>
std::string Graph<Type>::BreadthFirstSearch() {
	// If the graph is empty -no start node- finish
	if (!start) return nullptr;
	// String result for printing
	std::string result = "";
	// Reset number variables
	numOfNodes = 0;
	numOfEdges = 0;
	// Queue and explored vector
	std::queue<std::shared_ptr<GraphNode<Type>>> q;
	std::vector<Type> explored;
	std::shared_ptr<GraphNode<Type>> current;
	// Push the first node (start) in queue
	q.push(start);
	// Explore every node until the queue is empty or find the node
	while (!q.empty()) {
		// Get the front element and its value
		current = q.front();
		// Pop from queue
		q.pop();
		// Search in the vector, if find it has been explored continue, if not push into queue
		if (find(explored.begin(), explored.end(), current->GetValue()) == explored.end()) {
			// Increase the number variables
			++numOfNodes;
			numOfEdges += current->GetNeighbors().size();
			// Concat to the result
			result = result + " - " + std::to_string(current->GetValue());
			// Add in the explored vector
			explored.push_back(current->GetValue());
			// Add node's neighbors in queue
			for (auto neighbor : current->GetNeighbors()) {
				q.push(neighbor);
			}
		}
	}
	// Every edge counted twice because of pairs, divedi it by 2
	numOfEdges /= 2;
	// Return printable string
	return result;
}

// BFS
template <class Type>
std::shared_ptr<GraphNode<Type>> Graph<Type>::BreadthFirstSearch(Type searchValue) {
	// If the graph is empty -no start node- finish
	if (!start) return nullptr;
	// Queue and explored vector
	std::queue<std::shared_ptr<GraphNode<Type>>> q;
	std::vector<Type> explored;
	std::shared_ptr<GraphNode<Type>> current;
	Type currentValue;
	// Push the first node (start) in queue
	q.push(start);
	// Explore every node until the queue is empty or find the node
	while (!q.empty()) {
		// Get the front element and its value
		current = q.front();
		currentValue = current->GetValue();
		// Find the node, return
		if (currentValue == searchValue) {
			return current;
		}
		// Pop from queue
		q.pop();
		// Search in the vector, if find it has been explored continue, if not push into queue
		if (find(explored.begin(), explored.end(), current->GetValue()) == explored.end()) {
			// Add in the explored vector
			explored.push_back(currentValue);
			// Add node's neighbors in queue
			for (auto neighbor : current->GetNeighbors()) {
				q.push(neighbor);
			}
		}
	}
	// Could not find the node, return null
	return nullptr;
}

// DFS
template <class Type>
std::shared_ptr<GraphNode<Type>> Graph<Type>::DepthFirstSearch(Type searchValue) {
	// If the graph is empty -no start node- finish
	if (!start) return nullptr;
	// Stack and discovered vector
	std::stack<std::shared_ptr<GraphNode<Type>>> s;
	std::vector<Type> discovered;
	std::shared_ptr<GraphNode<Type>> current;
	Type currentValue;
	// Push the first node (start) in stack
	s.push(start);
	// Explore every node until the stack is empty or find the node
	while (!s.empty()) {
		// Get the front element and its value
		current = s.top();
		currentValue = current->GetValue();
		// Find the node, return
		if (currentValue == searchValue) {
			return current;
		}
		// Pop from stack
		s.pop();
		// Search in the vector, if find it has been discovered continue, if not push into stack
		if (find(discovered.begin(), discovered.end(), current->GetValue()) == discovered.end()) {
			// Add in the discovered vector
			discovered.push_back(currentValue);
			// Add node's neighbors in stack
			for (auto neighbor : current->GetNeighbors()) {
				s.push(neighbor);
			}
		}
	}
	// Could not find the node, return null
	return nullptr;
}