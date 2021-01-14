#pragma once

/*
* Baran Kaya
* 2020
*/

#include <iostream>

template<class Type>
class StacksWithArray {
	size_t stackSize;
	size_t numOfStacks;
	Type* stacks;
	unsigned short* topIndexes;
public:
	// Constructors
	StacksWithArray();
	StacksWithArray(size_t newStackSize);
	StacksWithArray(size_t newStackSize, size_t newNumOfStacks);
	// Functions
	Type top(unsigned short stackIndex);
	bool pop(unsigned short stackIndex);
	bool push(unsigned short stackIndex, Type value);
	bool isEmpty(unsigned short stackIndex);
	void printStacks();
	void printStack(unsigned short stackIndex);
};

// Constructors
template<class Type>
StacksWithArray<Type>::StacksWithArray() {
	stackSize = 3;		// Default is 3
	numOfStacks = 3;	// Default is 3
	stacks = new Type[stackSize * numOfStacks];
	std::fill(stacks, stacks + (stackSize * numOfStacks), NULL); // Fill with NULLs
	topIndexes = new unsigned short[numOfStacks];
	for (unsigned int i = 0; i < numOfStacks; ++i) { // Fill topIndexes with bottom index of the each stack
		topIndexes[i] = ((i + 1) * stackSize) - 1;
	}
}

template<class Type>
StacksWithArray<Type>::StacksWithArray(size_t newStackSize) {
	stackSize = newStackSize;
	numOfStacks = 3; // Default is 3
	stacks = new Type[stackSize * numOfStacks];
	std::fill(stacks, stacks + (stackSize * numOfStacks), NULL); // Fill with NULLs
	topIndexes = new unsigned short[numOfStacks];
	for (unsigned int i = 0; i < numOfStacks; ++i) { // Fill topIndexes with bottom index of the each stack
		topIndexes[i] = ((i + 1) * stackSize) - 1;
	}
}

template<class Type>
StacksWithArray<Type>::StacksWithArray(size_t newStackSize, size_t newNumOfStacks) {
	stackSize = newStackSize;
	numOfStacks = newNumOfStacks;
	stacks = new Type[stackSize * numOfStacks];
	std::fill(stacks, stacks + (stackSize * numOfStacks), NULL); // Fill with NULLs
	topIndexes = new unsigned short[numOfStacks];
	for (unsigned int i = 0; i < numOfStacks; ++i) { // Fill topIndexes with bottom index of the each stack
		topIndexes[i] = ((i+1) * stackSize) - 1;
	}
}

// Functions
template<class Type>
Type StacksWithArray<Type>::top(unsigned short stackIndex) {
	if (topIndexes[stackIndex]) // is not NULL
		return stacks[topIndexes[stackIndex]];
	else
		return NULL;
}

template<class Type>
bool StacksWithArray<Type>::pop(unsigned short stackIndex) {
	// Check if the stack is empty or not
	if (isEmpty(stackIndex)) {
		return false;
	}
	// Find index of the top element
	unsigned short index = topIndexes[stackIndex];
	// Change it to NULL
	stacks[index] = NULL;
	// Top index didn't reach at the end of the stack (not the last element in the stack)
	if (topIndexes[stackIndex] != ((stackIndex + 1) * stackSize) - 1)
		// Update the top index of the stack
		topIndexes[stackIndex] += 1;
	return true;
}

template<class Type>
bool StacksWithArray<Type>::push(unsigned short stackIndex, Type value) {
	// Find index of the top element
	unsigned short index = topIndexes[stackIndex];
	// Check capactity of the stack, if full return false
	if (index && index == stackIndex * stackSize)
		return false;
	// Push in stack
	if(stacks[index] == NULL) // First value, stack is empty
		stacks[index] = value;
	else {
		stacks[index - 1] = value;
		// Update the top index of the stack
		topIndexes[stackIndex] -= 1;
	}
}

template<class Type>
bool StacksWithArray<Type>::isEmpty(unsigned short stackIndex) {
	// Find index of the top element
	unsigned short index = topIndexes[stackIndex];
	// If the top index is equal to (stackIndex+1) * stackSize, it means its empty
	// Or could check stacks[topIndexes[stackIndex]] is empty or not, if its empty stack is empty as well
	if (index && index == ((stackIndex + 1) * stackSize) - 1 && stacks[index] == NULL)
		return true;
	else
		return false;
}

template<class Type>
void StacksWithArray<Type>::printStacks() {
	size_t arraySize = stackSize * numOfStacks;
	// Loop over the array
	for (int i = 0; i < arraySize; ++i) {
		// Put new line between each stack
		if (i % stackSize == 0)
			std::cout << std::endl;
		// Print values
		std::cout << i / stackSize << "th Stack's " << i % stackSize << "th element: " << stacks[i] << std::endl;
	}
	std::cout << std::endl;
}

template<class Type>
void StacksWithArray<Type>::printStack(unsigned short stackIndex) {
	// Find index of the top element
	//unsigned short firstIndex = topIndexes[stackIndex]; // Prints only non-empty elements in the stack
	unsigned short firstIndex = stackIndex * stackSize;
	unsigned short lastIndex = ((stackIndex + 1) * stackSize) - 1; // Next stack's first element - 1 --> current stack's bottom
	size_t arraySize = stackSize * numOfStacks;
	// Loop over the array
	for (int i = firstIndex; i <= lastIndex; ++i) {
		std::cout << stackIndex << "th Stack's " << i % stackSize << "th element: " << stacks[i] << std::endl;
	}
	std::cout << std::endl;
}