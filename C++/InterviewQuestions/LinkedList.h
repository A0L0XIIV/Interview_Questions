#pragma once

/*
* Baran Kaya
* 2021
*/

template<class Type>
class Node {
	Type value;
	Node<Type>* next;
	Node<Type>* previous;

public:
	// Constructors
	Node() = default;
	Node(Type val) { value = val; };
	Node(Type val, Node<Type>* n) { value = val; next = n; };
	Node(Type val, Node<Type>* n, Node<Type>* p) { value = val; next = n; previous = p; };
	// Functions
	Type getValue() { return value; };
	void setValue(Type newValue) { value = newValue; };
	Node* getNext() { return next; };
	void setNext(Node<Type>* newNext) { next = newNext; };
	Node* getPrevious() { return previous; };
	void setPrevious(Node<Type>* newPrevious) { previous = newPrevious; };
};

template<class Type>
class LinkedList {
public:
	Node<Type>* head;
	// Constructors
	LinkedList() = default;
	LinkedList(Node<Type>* h) { head = h; };
	LinkedList(std::vector<Type> arr);
};

template<class Type>
class DoubleLinkedList : public LinkedList<Type> {
public:
	Node<Type>* tail;
	// Constructors
	DoubleLinkedList() = default;
	DoubleLinkedList(Node<Type>* h, Node<Type>* t) : LinkedList<Type>(h) { tail = t; }; // Call LL's cons. for head
	DoubleLinkedList(std::vector<Type> arr);
};

// Constructor with vector
template<class Type>
LinkedList<Type>::LinkedList(std::vector<Type> arr) {
	// Head node
	Node<Type>* head = new Node<Type>(arr[0]);
	// Erase the first element from the vector
	arr.erase(arr.begin());
	// For holding previous nodes
	Node<Type>* previous = head;

	for (Type element : arr) {
		// Create a new node
		Node<Type>* newNode = new Node<Type>(element);
		// Set previous node's next pointer
		previous->setNext(newNode);
		// Update previous pointer
		previous = newNode;
	}

	// Set last node's next pointer
	previous->setNext(nullptr);

	// Return newly created linked list with head node
	return LinkedList<Type>(head);
}

template<class Type>
DoubleLinkedList<Type>::DoubleLinkedList(std::vector<Type> arr) {
	// Call parent class's constructor
	LinkedList<Type> ll = new LinkedList<Type>(arr);
	// Get its head node
	Node<Type> head = ll.head;
	// For holding current nodes
	Node<Type>* current = head;
	// For holding previous nodes
	Node<Type>* previous = nullptr;

	// Update each node's tail pointer
	while (current) {
		// Update each node's previous pointer
		current->setPrevious(previous);
		// Update the previous
		previous = current;
		// Move current forward
		current = current->getNext();
	}

	// Return newly created double linked list with head and the tail nodes
	return DoubleLinkedList<Type>(head, previous);
}