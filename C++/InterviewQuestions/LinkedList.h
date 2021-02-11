#pragma once

/*
* Baran Kaya
* 2021
*/

#include <iostream>

template<class Type>
class Node {
	Type value;
	std::shared_ptr<Node<Type>> next;
	std::shared_ptr<Node<Type>> previous;

public:
	// Constructors
	Node() = default;
	Node(Type val) : value(val), next(nullptr), previous(nullptr) {};
	Node(Type val, std::shared_ptr<Node<Type>> n) : value(val), next(n), previous(nullptr) {};
	Node(Type val, std::shared_ptr<Node<Type>> n, std::shared_ptr<Node<Type>> p) : value(val), next(n), previous(p) {};
	// Functions
	Type getValue() { return value; };
	void setValue(Type newValue) { value = newValue; };
	std::shared_ptr<Node<Type>> getNext() { return next; };
	void setNext(std::shared_ptr<Node<Type>> newNext) { next = newNext; };
	std::shared_ptr<Node<Type>> getPrevious() { return previous; };
	void setPrevious(std::shared_ptr<Node<Type>> newPrevious) { previous = newPrevious; };
};

template<class Type>
class LinkedList {
public:
	std::shared_ptr<Node<Type>> head;
	// Constructors
	LinkedList() = default;
	LinkedList(std::shared_ptr<Node<Type>> h) : head (h) {};
	LinkedList(std::vector<Type> arr);
	// Functions
	void printLinkedList();
	std::shared_ptr<Node<Type>> getKthNode(int k);
};

template<class Type>
class DoubleLinkedList : public LinkedList<Type> {
public:
	std::shared_ptr<Node<Type>> tail;
	// Constructors
	DoubleLinkedList() = default;
	DoubleLinkedList(std::shared_ptr<Node<Type>> h, std::shared_ptr<Node<Type>> t) : LinkedList<Type>(h) { tail = t; }; // Call LL's cons. for head
	DoubleLinkedList(std::vector<Type> arr);
};

// Constructor with vector
template<class Type>
LinkedList<Type>::LinkedList(std::vector<Type> vec) : LinkedList() {
	// Check vector's emptiness
	if (!vec.empty()) {
		// Head node
		head = std::shared_ptr<Node<Type>> (new Node<Type>(vec[0]));
		// Erase the first element from the vector
		vec.erase(vec.begin());
		// For holding previous nodes
		std::shared_ptr<Node<Type>> prev = head;

		for (Type element : vec) {
			// Create a new node
			auto newNode = std::shared_ptr<Node<Type>> (new Node<Type>(element));
			// Set previous node's next pointer
			prev->setNext(newNode);
			// Update previous pointer
			prev = newNode;
		}
	}
}

template<class Type>
DoubleLinkedList<Type>::DoubleLinkedList(std::vector<Type> arr) : LinkedList(arr) {
	// After creating a normal LinkedList with its ctor, update each nodes' previous ptr
	std::shared_ptr<Node<Type>> current = this->head;
	std::shared_ptr<Node<Type>> prev = nullptr;

	// Update each node's previous pointer
	while (current) {
		// Update each node's previous pointer
		current->setPrevious(prev);
		// Update the previous
		prev = current;
		// Move current forward
		current = current->getNext();
	}

	// Update the tail ptr
	tail = prev;
}

// Print function
template<class Type>
void LinkedList<Type>::printLinkedList() {
	std::shared_ptr<Node<Type>> current = head;

	while (current) {
		// Print node's value
		std::cout << current->getValue() << "->";
		// Move forward
		current = current->getNext();
	}
	// Print Null at the end
	std::cout << "NULL" << std::endl;

	return;
};

// Get Kth Node Function
template<class Type>
std::shared_ptr<Node<Type>> LinkedList<Type>::getKthNode(int k) {
	std::shared_ptr<Node<Type>> current = head;

	while (k > 0 && current) {
		// Decrement k
		--k;
		// Move pointer
		current = current->getNext();
	}

	return current;
}