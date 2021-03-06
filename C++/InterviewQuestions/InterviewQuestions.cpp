﻿/*
* Baran Kaya
* 2020
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctype.h>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <windows.h> // Sleep

#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "StacksWithArray.h"
#include "MultithreadProblems.h"
#include "Graph.h"

using namespace std;

template <typename T>
vector<T> getArrayInput() {
    // Get array/vector size from user
    size_t vecSize = 0;
    cout << "Enter size of the array/list: ";
    cin >> vecSize;
    // Create a new vector
    vector<T> vec(0);
    // Check given size
    if (vecSize != 0) {
        vec.reserve(vecSize);
        T tempInput;
        // Get array values from user
        cout << "Enter the array/list elements." << endl;
        for (unsigned int i = 0; i < vecSize; ++i) {
            cout << to_string(i) + "th: ";
            cin >> tempInput;
            vec.push_back(static_cast<T>(tempInput));
        }
    }
    // Return filled OR empty vector
    return vec;
}

template <typename T>
vector<T> getArrayInput(size_t size) {
    // Create a new vector
    vector<T> vec(0);
    // Check given size
    if (size != 0) {
        T tempInput;
        // Get array values from user
        cout << "Enter the array/list elements." << endl;
        for (unsigned int i = 0; i < size; ++i) {
            cout << to_string(i) + "th: ";
            cin >> tempInput;
            vec.push_back(static_cast<T>(tempInput));
        }
    }
    // Return filled OR empty vector
    return vec;
}

bool IsDigits(const string& str){
    return str.find_first_not_of("-0123456789") == string::npos;
    //return all_of(str.begin(), str.end(), ::isdigit); // C++11
}

void FizzBuzz() {
    // Description of the problem
    cout << "Print numbers from 1 to x. If the number is divisible by 3, replace it with \"Fizz\". If it is divisible by 5, replace it with \"Buzz\". If it is divisible by 3 and 5 replace it with \"FizzBuzz\"." <<endl;

    // Variables
    unsigned int userNumber = 0;
    string printResults = "";

    // Get user input
    cout << endl << "- Enter the number for FizzBuzz:";
    cin >> userNumber;

    // Input validity
    if (userNumber < 1 || userNumber > INT_MAX)
        cout << "ERROR: Please enter valid number! Between 1 and " + to_string(INT_MAX) << endl;
    else {
        // FizzBuzz operation
        for (unsigned int i = 1; i <= userNumber; ++i) {
            // Number is power of 3, print Fizz
            if (i % 3 == 0 && i % 5 == 0)
                printResults += "FizzBuzz";
            else if (i % 3 == 0)
                printResults += "Fizz";
            else if (i % 5 == 0)
                printResults += "Buzz";
            else
                printResults += to_string(i);
            printResults += '\n';
        }
        // Print the result
        cout << printResults << endl;
    }
}

void TwoSum() {
    // Description of the problem
    cout << "Given an array of integers, return indices of the two numbers such that they add up to a specific target." << endl;

    // Get the target integer from user
    cout << "Please enter the target number: ";
    int targetNumber = 0;
    cin >> targetNumber;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    // Result indexes
    int firstIndex = -1, secondIndex = -1;
    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(n^2) solution, 2 for O(n*logn) solution." << endl;
    cin >> solutionSelection;

    // O(n^2) solution, check each pair's sum in the array
    if (solutionSelection == 1) {
        // Check if array has more than 2 elements
        if (arr.size() >= 2) {
            for (int i = 0; i < arrSize; ++i) {
                for (int j = 0; j < arrSize; ++j) {
                    if (i != j && (arr[i] + arr[j] == targetNumber)) {
                        firstIndex = i;
                        secondIndex = j;
                    }
                }
            }
            // Print result index
            if (firstIndex != -1 && secondIndex != -1)
                cout << "First index: " + to_string(firstIndex) + ", second index: " + to_string(secondIndex) << endl;
            else
                cout << "Couldn't find the numbers." << endl;
        }
    }

    // O(n*logn) solution, sort the array, try to find closest numbers
    else if (solutionSelection == 2) {
        // Check if array has more than 2 elements
        if (arrSize >= 2) {
            // Pair vector for not sorted array's indexes and sorted array's values
            vector<pair<int, int>> sortedArray(0);
            for (int i = 0; i < arrSize; ++i) {
                pair<int, int> tempPair(arr[i], i);
                sortedArray.push_back(tempPair);
            }
            // Sort the pair vector
            sort(sortedArray.begin(), sortedArray.end());
            // Sum first and last elements, if it's equals to target finish, if it's bigger than the target last-1, else first+1
            bool foundIndexes = false;
            int firstIndex = 0;
            int lastIndex = arrSize - 1;
            // Sum last and the first elements, change big and small index values according to their sums
            while (firstIndex < lastIndex) {
                // Sum of two equals to target, print the unsorted array's indexes (pair's second elements)
                if (sortedArray[firstIndex].first + sortedArray[lastIndex].first == targetNumber) {
                    cout << "First index: " + to_string(sortedArray[firstIndex].second) + ", second index: " + to_string(sortedArray[lastIndex].second) << endl;
                    foundIndexes = true;
                    break;
                }
                // Sum is greater than the target so, decrease the bigger element (decrease larger index)
                else if (sortedArray[firstIndex].first + sortedArray[lastIndex].first > targetNumber)
                    lastIndex--;
                // Sum is smaller than the target so, increase the small element (increase smaller index)
                else
                    firstIndex++;
            }
            // Couln't find the correct numbers
            if (!foundIndexes)
                cout << "Couldn't find the numbers." << endl;
        }
    }
    // Neither O(n^2) nor O(n*logn) solutions selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void MaxConsecutiveOnes() {
    // Description of the problem
    cout << "Given an array of 0s and 1s (binary), return the number of max consecutive ones. For example; [1,1,1,0,1,1] --> return 3." << endl;

    // Get array values from user
    vector<bool> arr = getArrayInput<bool>();
    int arrSize = arr.size();

    // O(n) solution
    int maxOnes = 0;

    // Loop through the vector
    for (int i = 0; i < arrSize; ++i) {
        // If find a 1
        if (arr[i] == 1) {
            // Move until reaching a 0
            for (int j = i; j < arrSize; ++j) {
                // Reached 0
                if (arr[j] == 0) {
                    // Update the max value
                    if(maxOnes < j-i)
                        maxOnes = j - i;
                    // Checked the previous indexes, move i to j's position
                    i = j;
                    // Break the inner loop
                    break;
                }
            }
        }
    }

    if (maxOnes > 0)
        cout << "# max consecutive ones: " + to_string(maxOnes) << endl;
    else
        cout << "There aren't any 1 in the array." << endl;

}

void MaxProductofThreeNumbers(){
    // Description of the problem
    cout << "Given an array of integers, print the product of 3 max integers. For example; [1,2,3,4] --> 2*3*4=24" << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(n^3) solution, 2 for O(n*logn) solution, and 3 for O(n) solution." << endl;
    cin >> solutionSelection;

    // O(n^3) solution, check every three elements sum in the array
    if (solutionSelection == 1) {
        int maxProduct = INT_MIN;
        // 3 loops
        for (int i : arr) {
            for (int j : arr) {
                for (int k : arr) {
                    // Do not multiply same integers
                    if (i != j && j != k && i != k) {
                        // If the multipication result bigger than the max, update the max value
                        if (i * j * k > maxProduct)
                            maxProduct = i * j * k;
                    }
                }
            }
        }
        // Print result
        cout << "Product of max 3: " + to_string(maxProduct) << endl;
    }

    // O(n*logn) solution, sort the array and multiply max and min
    if (solutionSelection == 2) {
        // Sort the array
        sort(arr.begin(), arr.end());
        // Non-negative integers
        int max1 = arr[arrSize - 1] * arr[arrSize - 2] * arr[arrSize - 3];
        // Negative integers
        int max2 = arr[arrSize - 1] * arr[0] * arr[1];
        // Print the result
        if(max1 > max2)
            cout << "Product of max 3: " + to_string(max1) << endl;
        else
            cout << "Product of max 3: " + to_string(max2) << endl;
    }

    // O(n) solution, while traversing in the array find max1, max2, max3, min1 and min2. Max product is either max1*max2*max3 or min1*min2*max3
    if (solutionSelection == 3) {
        // 3 max and 2 min integers
        int max1 = INT_MIN;
        int max2 = INT_MIN;
        int max3 = INT_MIN;
        int min1 = INT_MAX;
        int min2 = INT_MAX;

        for (int item : arr) {
            // Find 3 maximum
            if (item >= max3) {
                max1 = max2;
                max2 = max3;
                max3 = item;
            }
            else if (item >= max2) {
                max1 = max2;
                max2 = item;
            }
            else if (item >= max1) {
                max1 = item;
            }
            // Find 2 minimum
            if (item <= min1) {
                min2 = min1;
                min1 = item;
            }
            else if (item <= min2) {
                min2 = item;
            }
        }
        // Non-negative integers
        int result1 = max1 * max2 * max3;
        // Negative integers
        int result2 = min1 * min2 * max3;
        // Print the result
        if (result1 > result2)
            cout << "Product of max 3: " + to_string(result1) << endl;
        else
            cout << "Product of max 3: " + to_string(result2) << endl;
    }

    // Neither O(n^3), O(n*logn) nor O(n) solutions selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void ValidParantheses() {
    // Description of the problem
    cout << "Given an array of parantheses check its validness. Every opening paratheses must have one closing parantheses!" << endl;

    // Get array values from user
    cout << "Array should only consist of ( and ) characters!" << endl;
    vector<char> arr = getArrayInput<char>();
    int arrSize = arr.size();

    // Size of the array is not even, not valid
    if (arrSize % 2 != 0) {
        cout << "Not Valid: Array size is not even." << endl;
    }

    // Use stack for validness
    stack<char> paranthesesStack;

    // Loop through every element in the array
    for (char element : arr) {
        // Opening parantheses, push something to the stack
        if (element == '(') {
            paranthesesStack.push('x');
        }
        // Closing parantheses, pop last pushed characters
        else if (element == ')' && !paranthesesStack.empty()) {
            paranthesesStack.pop();
        }
        // Closing parantheses but stack is empty, error
        else {
            cout << "Not Valid: There is a closing parantheses without opening parantheses." << endl;
            break;
        }
    }

    // Empty stack: valid: Every opening parantheses has closing ones
    if (paranthesesStack.empty()) {
        cout << "Valid: All parantheses matched." << endl;
    }
    // Non-empty stack: not valid
    else {
        cout << "Not Valid: There is/are opening parantheses that didn't close." << endl;
    }

}

void BaseballGame() {
    // Description of the problem
    cout << "Calculate the final score of the baseball game. Given the array of characters: integers are the points, D doubles the previous point, C cancels the previous point and + sums last two points." << endl;
    cout << "[5,2,C,D,+] --> 5+2=7 --> C: 2 canceled=5 --> D: 5*2=10 : total=5+10=15 --> +: 5+10=15 total=5+10+15=30" << endl;

    // Get array values from user
    vector<string> arr = getArrayInput<string>();
    int arrSize = arr.size();

    // Result
    int total = 0;

    // Use stack for easier calculation
    stack<int> pointStack;

    // Loop through the array
    for (string element : arr) {
        // Digit, push to stack
        if (IsDigits(element)) {
            pointStack.push(stoi(element));
        }
        // D: double the previous
        else if (element == "D" || element == "d") {
            // Convert char to int
            int lastElement = pointStack.top();
            // Double it
            lastElement *= 2;
            // Push to stack
            pointStack.push(lastElement);
        }
        // C: cancel the previous
        else if (element == "C" || element == "c") {
            // Pop the last element
            pointStack.pop();
        }
        // +: sum the previous two
        else if (element == "+") {
            // Get the top element
            int lastElement1 = pointStack.top();
            // Pop the top element
            pointStack.pop();
            // Get the second top element
            int lastElement2 = pointStack.top();
            // Sum these two elements
            int sum = lastElement1 + lastElement2;
            // Push the previous top to stack
            pointStack.push(lastElement1);
            // Push the sum result to stack
            pointStack.push(sum);
        }
        // None: error
        else {
            cout << "Error: Invalid character in the array (" << element << "), finishing the function." << endl;
            break;
        }
    }

    // Find the total
    while (!pointStack.empty()) {
        // Get the top from stack and add to the total
        total += pointStack.top();
        // Pop it
        pointStack.pop();
    }

    cout << "Total: " << total << endl;
}

void ContainsDuplicate(){
    // Description of the problem
    cout << "Find the duplicates in the given array with k index difference." << endl;
    cout << "[2,4,1,1,3,2,5,6] and k=2. 2's index difference is larger than k=2 so only return 1 as a result." << endl;

    // Get k value from user
    cout << "Enter the value of the k, index difference:";
    int k = 0;
    cin >> k;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    vector<int> results;
    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(n*k) brute force solution, 2 for O(n) hash table solution." << endl;
    cin >> solutionSelection;

    // O(n*k) solution, check each pairs in the array
    if (solutionSelection == 1) {
        // First loop, all elements in the array
        for (int i = 0; i < arrSize; ++i) {
            // Second loop for finding duplicates, k times
            for (int j = i+1; j-i <= k && j < arrSize; ++j) {
                // Duplicate check
                if (arr[i] == arr[j]) {
                    results.push_back(arr[i]);
                }
            }
        }
        // Print the result
        if (results.empty()) {
            cout << "Couldn't find any duplicates in the given array with k=" << k << " index difference." << endl;
        }
        else {
            cout << "Found " << results.size() << " different duplicates." << endl;
        }
    }
    // Could add O(n*logn) solution with sorting and paired (value, unsorted index) vectors

    // O(n) solution, use hash maps
    else if (solutionSelection == 2) {
        map<int, int> hashMap;
        // Loop through all elements
        for (int i = 0; i < arrSize; ++i) {
            // Check if there is an element in the hashMap, if not insert it
            if (hashMap.find(arr[i]) == hashMap.end()) {
                // Map keys are array values, map values are array indexes
                hashMap[arr[i]] =  i;
            }
            // Element's values is already in the map, and |previous index - current index| is smaller than the k, add it into results list
            else if (hashMap.find(arr[i]) != hashMap.end() && abs(hashMap[arr[i]] - i) <= k) {
                results.push_back(arr[i]);
                // Update the hash map for possible duplicates
                hashMap[arr[i]] = i;
            }
        }
        // Print the result
        if (results.empty()) {
            cout << "Couldn't find any duplicates in the given array with k=" << k << " index difference." << endl;
        }
        else {
            cout << "Found " << results.size() << " different duplicates." << endl;
        }
    }
    // Neither O(n*k) nor O(n) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }

}

void ValidAnagram(){
    // Description of the problem
    cout << "Check if the given 2 words are anagrams or not (containts the same letters)." << endl;
    cout << "Example: anagram and nagaram are anagrams but cat and rat are not." << endl;

    // Get two strings from user
    cout << "Enter the first string: ";
    string firstWord = "";
    cin >> firstWord;
    cout << "Enter the second string: ";
    string secondWord = "";
    cin >> secondWord;

    // Check their sizes
    if (firstWord.size() != secondWord.size()) {
        cout << "Size of the two words are different, they aren't anagrams." << endl;
    }
    // Sizes are equal
    else {
        // Problem has several solutions, choose one
        int solutionSelection = 0;
        cout << "Enter 1 for O(n*logn) sorting solution, 2 for O(n) hash map solution." << endl;
        cin >> solutionSelection;

        // Brute force O(n^2) solution, check two arrays' every pairs, then delete same letters

        // O(n*logn) solution, sort two strings and check pairs
        if (solutionSelection == 1) {
            // Sort 2 strings
            sort(firstWord.begin(), firstWord.end());
            sort(secondWord.begin(), secondWord.end());
            bool validAnagram = true;
            const size_t firstSize = firstWord.size();
            // Check every index
            for (unsigned int i = 0; i < firstSize; ++i) {
                if (firstWord[i] != secondWord[i]) {
                    cout << "Not Anagram: These two words are not anagrams. (" << firstWord << "-" << secondWord << ")" << endl;
                    validAnagram = false;
                    break;
                }
            }
            if (validAnagram)
                cout << "Anagram: These two words are anagrams. (" << firstWord << "-" << secondWord << ")" << endl;
        }

        // O(n) solution, use hash map for each letter, increase counters for the first word, decrease the same letters for the second word, if all 0 they are anagrams
        else if (solutionSelection == 2) {
            map<char, int> letterMap;
            bool validAnagram = true;

            // Loop through every letter in the first word
            for (char c : firstWord) {
                // First add each letter in the map
                if (letterMap.find(c) == letterMap.end()) {
                    letterMap[c] = 1;
                }
                // Update their counter everytime when encounter the same letter
                else if (letterMap.find(c) != letterMap.end()) {
                    letterMap[c] += 1;
                }
            }

            // Second, loop through second word and decrease each letters counter
            for (char c : secondWord) {
                // First add each letter in the map
                if (letterMap.find(c) == letterMap.end()) {
                    validAnagram = false;
                }
                // Update (decrease) their counter everytime when encounter the same letter
                else if (letterMap.find(c) != letterMap.end() && letterMap[c] > 0) {
                    letterMap[c] -= 1;
                }
            }

            // Check hash map, if all letters' counter is 0 they are anagram, if not not anagram
            for (auto itr = letterMap.begin(); itr != letterMap.end(); ++itr) {
                if (itr->second != 0)
                    validAnagram = false;
            }
            // Print result
            if(validAnagram){
                cout << "Anagram: These two words are anagrams. (" << firstWord << "-" << secondWord << ")" << endl;
            }
            else {
                cout << "Not Anagram: These two words are not anagrams. (" << firstWord << "-" << secondWord << ")" << endl;
            }
        }
        // Neither O(n*logn) nor O(n) solution selected
        else {
            cout << "Incorrect solution selection!" << endl;
        }
    }
}

void KthLargestElement(){
    // Description of the problem
    cout << "Find the Kth largest element in the given array." << endl;

    // Get the k
    unsigned int k = 0;
    cout << "Enter a value for k: ";
    cin >> k;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(n*logn) sorting solution, 2 for O(n*logk) min heap solution." << endl;
    cin >> solutionSelection;

    // O(n*logn) solution, sort the array and get Kth element
    if (solutionSelection == 1) {
        // Sort the array
        sort(arr.begin(), arr.end());

        // Print the result
        cout << "Kth largest element in the given array: " << arr[arrSize - k] << endl;
    
    }
    // O(n*logk) solution, use min heaps
    else if (solutionSelection == 2) {
        // Convert vector array to MIN HEAP with STL priority_queue
        priority_queue <int, vector<int>, greater<int>> minHeap;
        // Loop through array's elements
        for (int element : arr) {
            const size_t minHeapSize = minHeap.size();
            // Heap only has k elements because we only need kth element, push first k element into heap
            if (minHeapSize < k) {
                minHeap.push(element);
            }
            // After heap is full, change the elements if they are greater than the heap's min
            else if (minHeap.top() < element) {
                // Pop smaller element
                minHeap.pop();
                // Push new greater element to heap
                minHeap.push(element);
            }
        }
        // Print the result
        cout << "Kth largest element in the given array: " << minHeap.top() << endl;
    }
    // Neither O(n*logn) nor O(n*logk) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void KPairsWithSmallestSum() {
    // Description of the problem
    cout << "Given 2 different arrays, find the k pairs that have smallest sum value." << endl;
    cout << "For example: u=[1,7,11] and v=[2,4,6], results are= [1,2], [1,4] and [1,6]." << endl;

    // Get the k
    unsigned int k = 0;
    cout << "Enter a value for k: ";
    cin >> k;

    // Get array values from user
    cout << "First Array:" << endl;
    vector<int> arr1 = getArrayInput<int>();
    int arr1Size = arr1.size();

    // Get array values from user
    cout << "Second Array:" << endl;
    vector<int> arr2 = getArrayInput<int>();
    int arr2Size = arr2.size();

    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(n^2*logn) naive solution, 2 for O(n^2*logk) max heap solution." << endl;
    cin >> solutionSelection;

    // Combination array with all sums, size = arr1Size * arr2Size
    vector<pair<int, int>> pairArray;

    // Loop through the first array
    for (int element1 : arr1) {
        // Loop through the second array
        for (int element2 : arr2) {
            // Temporary pair for pushing elements into the vector
            pair<int, int> tempPair(element1, element2);
            pairArray.push_back(tempPair);
        }
    }

    // O(n^2*logn) solution, combine all possible combinations, sort the array and get Kth element
    if (solutionSelection == 1) {
        // Sort the pairArray and get first k elements, use pair's sum for sort comparasion
        sort(pairArray.begin(), pairArray.end(),
            [](const pair<int,int>& a, const pair<int, int>& b) -> bool
            {
                return (a.first + a.second) < (b.first + b.second);
            });
        // Print the results
        cout << "The smallest sum pairs are: " << endl;
        for (unsigned int i = 0; i < k; ++i) {
            cout << "- [" << pairArray[i].first << ',' << pairArray[i].second << ']' << endl;
        }
    }
    // O(n^2*logk) solution, use k sized max heaps
    else if (solutionSelection == 2) {
        // Create a new max heap with lambda comparison function

        // Heap will only store k min summed pairs
        priority_queue <pair<int, int>, vector<pair<int, int>>, auto(*)(pair<int, int>, pair<int, int>)->bool> maxHeap{
            // Using lambda function to compare pair elements sum
            [](pair<int, int> a, pair<int, int> b)->bool { return (a.first+a.second) < (b.first+b.second); }
        };
        // Loop through pair array
        for (pair<int, int> p : pairArray) {
            const size_t maxHeapSize = maxHeap.size();
            // If the heap is empty, push new pairs to heap
            if (maxHeapSize < k) {
                maxHeap.push(p);
            }
            // Heap is full, change elements if their sum is less than the max in the heap
            else if ((p.first + p.second) < (maxHeap.top().first + maxHeap.top().second) ) {
                // Pop the max sum pair
                maxHeap.pop();
                // Put the smaller summed pair in heap
                maxHeap.push(p);
            }
        }
        // Print the results
        cout << "The smallest sum pairs are: " << endl;
        for (unsigned int i = 0; i < k; ++i) {
            cout << "- [" << maxHeap.top().first << ',' << maxHeap.top().second << ']' << endl;
            maxHeap.pop();
        }
    }
    // Neither O(n^2*logn) nor O(n^2*logk) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }

}

void InvertBST(std::shared_ptr<BSTNode<int>> node) {
    // Base case
    if (node == nullptr)
        return;
    // Swap left and right children
    auto temp = std::shared_ptr<BSTNode<int>> (node->getLeftChild());
    node->updateLeft(node->getRightChild());
    node->updateRight(temp);
    // Call left child subtree
    if (node->getLeftChild() != nullptr) {
        InvertBST(node->getLeftChild());
    }
    // Call right child subtree
    if (node->getRightChild() != nullptr) {
        InvertBST(node->getRightChild());
    }
}

void InvertBSTCaller() {
    // Description of the problem
    cout << "Invert the given binary (search) tree." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));

    cout << endl << "Before invertion print tree: ";
    bst->printTree();

    // Call invert function with root node
    InvertBST(bst->getRoot());

    cout << endl << "After invertion print tree: ";
    bst->printTree();
}

void InsertionSort() {
    // Description of the problem
    cout << "Insertion sort algoritm. Create a new array and it will print the sorted result." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();
    int i, key;

    // First loop, start from the second element
    for (int j = 1; j < arrSize; ++j) {
        // Get second element's value
        key = arr[j];
        // Previous index
        i = j - 1;
        // Loop previous elements and change their location if they are bigger
        while (i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        // change key's position if its smaller
        arr[i + 1] = key;
    }

    cout << "Sorted array: ";
    // Print sorted array
    for (int element : arr) {
        cout << element << " - ";
    }
}

void Merge(vector<int>& array, int p, int q, int r) {
    // Size of 2 arrays
    int n1 = (q - p) + 1;
    int n2 = (r - q);
    int i, j;
    // Create 2 new arrays
    vector<int> Left(n1);
    vector<int> Right(n2);
    // Fill the arrays
    for (i = 0; i < n1; ++i) {
        Left[i] = array[p + i];
    }
    for (j = 0; j < n2; ++j) {
        Right[j] = array[q + j + 1];
    }
    // Put max int at the end of the arrays
    Left.push_back(INT_MAX);
    Right.push_back(INT_MAX);
    // Reset indexes
    i = 0, j = 0;
    // Merge left and right arrays
    for (int k = p; k <= r; ++k) {
        if (Left[i] <= Right[j]) {
            array[k] = Left[i];
            i++;
        }
        else {
            array[k] = Right[j];
            j++;
        }
    }
}

void MergeSort(vector<int>& array, int p, int r) {
    if (p < r) {
        // Middle element.s index
        int q = static_cast<int> (ceil((p + r) / 2));
        // Recusrion for first and second halves
        MergeSort(array, p, q);
        MergeSort(array, q + 1, r);
        // Merge 2 halves
        Merge(array, p, q, r);
    }
}

void MergeSortCaller() {
    // Description of the problem
    cout << "Merge sort algoritm. Create a new array and it will print the sorted result." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    // Sorted array
    MergeSort(arr, 0, arrSize-1);

    cout << "Sorted array: ";
    // Print sorted array
    for (int element : arr) {
        cout << element << " - ";
    }
}

void HeapSort() {
    // Description of the problem
    cout << "Heap sort algoritm. Create a new array and it will print the sorted result." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    // Instead of custom Heapify function, I used C++ STL make_heap function
    make_heap(arr.begin(), arr.end());

    // Remove the max element from heap and call make_heap again
    for (int i = arrSize - 1; i > 0; i--)
    {
        // Move max element to the end
        swap(arr[0], arr[i]);

        // Call make_heap (heapify) for remaining heap (beginning to last - i)
        make_heap(arr.begin(), arr.begin() + i);
    }

    cout << "Sorted array: ";
    // Print sorted array
    for (int element : arr) {
        cout << element << " - ";
    }
}

void QuickSortCaller() {
    // Description of the problem
    cout << "Quick sort algoritm. Create a new array and it will print the sorted result." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    // Sorted array
    //QuickSort(arr, 0, arrSize - 1);

    cout << "Sorted array: ";
    // Print sorted array
    for (int element : arr) {
        cout << element << " - ";
    }
}

void QuickSort() { } // TODO

void BinarySearch() {
    // Description of the problem
    cout << "Binary search algorithm. Create a new array, select value for search. It will show the search results." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();
    cout << "Enter a value to search in the array: ";
    int searchValue = 0;
    cin >> searchValue;
    bool found = false;

    // Create a new array with unsorted array's indexes
    vector<pair<int, int>> indexArray;
    for (int i = 0; i < arrSize; ++i) {
        pair<int, int> indexPair(arr[i], i);
        indexArray.push_back(indexPair);
    }

    // Sort the index array with the first value of the pair
    sort(indexArray.begin(), indexArray.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) -> bool
        {
            return a.first < b.first;
        });

    // Find the middle element
    int midIndex = arrSize / 2;

    // Vector iterators for subset operations
    auto first = indexArray.begin();
    auto last = indexArray.end();

    while (!indexArray.empty()) {
        // Update the size variable
        arrSize = indexArray.size();
        midIndex = arrSize / 2;
        // Check middle element's value
        if (indexArray[midIndex].first == searchValue) {
            cout << "Found the value in index " << indexArray[midIndex].second << endl;
            found = true;
            break;
        }
        // Middle is bigger than the value, search the upper half
        else if (indexArray[midIndex].first > searchValue) {
            first = indexArray.begin();
            last = indexArray.begin() + midIndex;
            vector<pair<int, int>> temp(first, last);
            indexArray = temp;
        }
        // Middle is smaller than the value, search the lower half
        else {
            first = indexArray.begin() + midIndex + 1;
            last = indexArray.end();
            vector<pair<int, int>> temp(first, last);
            indexArray = temp;
        }
    }

    if (!found)
        cout << "Couldn't find the " << searchValue << " in the array." << endl;
}

void BreadthFirstSearch() {
    // Description of the problem
    cout << "Breadth First Search algorithm. Create a new Binary Search Tree, select value for search. It will show the search results." << endl;

    // Get array and search value from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();
    cout << "Enter a value to search in the array: ";
    int searchValue = 0;
    cin >> searchValue;
    bool found = false;

    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));
    // Array for storing node's discovered state (NOT NECESSARY FOR BST)
    vector<bool> discovered(arrSize, false);
    // Queue for BFS operations
    queue<std::shared_ptr<BSTNode<int>>> q;
    q.push(bst->getRoot());
    std::shared_ptr<BSTNode<int>> temp = nullptr;

    while (!q.empty()) {
        // Print the front and pop it from queue
        temp = q.front();
        cout << " - " << temp->getValue();
        q.pop();

        // Find check
        if (temp->getValue() == searchValue)
            found = true; // Can stop here but BFS will print all tree elements

        // Push popped one's children in queue
        if (temp->getLeftChild() != nullptr)
            q.push(temp->getLeftChild());
        if (temp->getRightChild() != nullptr)
            q.push(temp->getRightChild());
    }

    if (found)
        cout << endl << "Found " << searchValue << " in the Binary Search Tree." << endl;
    else
        cout << endl << "Could not find " << searchValue << " in the Binary Search Tree." << endl;
}

void DepthFirstSearch() {
    // Description of the problem
    cout << "Depth First Search algorithm. Create a new Binary Search Tree, select value for search. It will show the search results." << endl;

    // Get array and search value from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();
    cout << "Enter a value to search in the array: ";
    int searchValue = 0;
    cin >> searchValue;
    bool found = false;

    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));
    // Array for storing node's explored state (NOT NECESSARY FOR BST)
    vector<bool> explored(arrSize, false);
    // Stack for DFS operations
    stack<std::shared_ptr<BSTNode<int>>> s;
    s.push(bst->getRoot());
    std::shared_ptr<BSTNode<int>> temp = nullptr;

    while (!s.empty()) {
        // Print the top and pop it from stack
        temp = s.top();
        cout << " - " << temp->getValue();
        s.pop();

        // Find check
        if (temp->getValue() == searchValue)
            found = true; // Can stop here but DFS will print all tree elements

        // Push popped one's children in queue
        if (temp->getLeftChild() != nullptr)
            s.push(temp->getLeftChild());
        if (temp->getRightChild() != nullptr)
            s.push(temp->getRightChild());
    }

    if (found)
        cout << endl << "Found " << searchValue << " in the Binary Search Tree." << endl;
    else
        cout << endl << "Could not find " << searchValue << " in the Binary Search Tree."  << endl;
}

void UniqueCharacters() {    
    // Description of the problem
    cout << "Check if the given string has unique characters or not." << endl;

    // Get string from user
    string testString;
    cout << endl << "- Enter a string:";
    cin >> testString;

    // Check string's size
    if (testString.size() == 0) {
        cout << "String is empty." << endl;
    }
    // String is not empty
    else {
        // Problem has several solutions, choose one
        int solutionSelection = 0;
        cout << "Enter 1 for O(n^2) loop solution, 2 for O(n) hash map solution." << endl;
        cin >> solutionSelection;
        bool isUnique = true;

        // Sort force O(n logn) solution, sort the string charaters, check every characters neighbors

        // O(n^2) nested loops solution, compare every pair in the array
        if (solutionSelection == 1) {
            const int strSize = testString.size();

            for (int i = 0; i < strSize; ++i) {
                for (int j = i+1; j < strSize; ++j) {
                    if (testString[i] == testString[j]) {
                        isUnique = false;
                        break;
                    }
                }
                // If string has non-unique charaters, break both of the loops
                if (!isUnique) { break; }
            }

            if (isUnique)
                cout << testString << "'s all characters are unique." << endl << endl;
            else
                cout << testString << " has non-unique characters." << endl << endl;
        }
        // O(n) solution, put each character into the hash table/stl set
        else if (solutionSelection == 2) {
            set<char> charSet;
            // Loop through the string
            for (char c : testString) {
                // If set contains the same value, uniqueness break
                if (charSet.insert(c).second == false) {
                    isUnique = false;
                    break;
                }
            }
            // Print result
            if (isUnique)
                cout << testString << "'s all characters are unique." << endl << endl;
            else
                cout << testString << " has non-unique characters." << endl << endl;
        }        
        // Neither O(n^2) nor O(n) solution selected
        else {
            cout << "Incorrect solution selection!" << endl;
        }
    }

    return;
};

void URLify() {
    // Description of the problem
    cout << "Change space \" \" characters to \"%20\" in a given string." << endl;

    cout << "ERROR: Currently not working do to the input function" << endl;
    return;
    
    // Get string from user
    string urlString;
    cout << endl << "- Enter a string: ";
    //cin >> noskipws >> urlString; // Doesn't work! 
    getline(cin, urlString, '\n');  // TODO: Doesn't work, fix it!

    // Check string's size
    if (urlString.size() == 0) {
        cout << "String is empty." << endl;
    }
    else {
        int oldSize = urlString.size();
        int newSize = oldSize;
        // Calculate the new string's size by using existing space count * 2 --> ' ' to '%20' --> +2 char for each ' '
        for (char c : urlString) {
            if (c == ' ')
                newSize += 2;
        }
        // New string and reserve
        string newString;
        newString.reserve(newSize);
        cout << "oldSize: " << oldSize << " newSize: " << newSize << endl;
        for (int o = oldSize - 1, n = newSize - 1; o >= 0; --o) {
            if (urlString[o] == ' ') {
                newString[n] = '0';
                newString[--n] = '2';
                newString[--n] = '%';
            }
            else {
                newString[n] = urlString[o];
            }
            --n;
        }

        cout << "New URL string: " << newString << " created from: " << urlString << endl << endl;
    }

    return;
};

void OneEditDistance() {
    // Description of the problem
    cout << "Check if given 2 string are in one edit distance (add/remove/change) or not." << endl;

    // Get strings from user
    string firstString;
    string secondString;
    cout << endl << "- Enter the first string: ";
    cin >> firstString;
    cout << endl << "- Enter the second string: ";
    cin >> secondString;

    const size_t firstSize = firstString.size();
    const size_t secondSize = secondString.size();
    int sizeDifference = firstSize - secondSize;
    bool hasOneDifference = true;
    bool different = false;

    // Check string's size
    if ( abs(sizeDifference) > 1) {
        hasOneDifference = false;
    }
    else {
        // Problem has several solutions, choose one
        int solutionSelection = 0;
        cout << "Enter 1 for O(n) neighbor check solution, 2 for O(n) hash map solution." << endl;
        cin >> solutionSelection;

        // Sort force O(n*logn) solution, sort the string charaters, check every characters neighbors

        // O(n) check neighbors solution, check pairs: NOTE: Its not a perfect solution, it has some flaws
        if (solutionSelection == 1) {
            const int shorterSize = firstSize < secondSize ? firstSize : secondSize;

            for (int i = 0, j = 0; i < shorterSize && j < shorterSize; ++i, ++j) {
                if (firstString[i] == secondString[j]) {
                    continue;
                }
                else {
                    // Second difference
                    if (different) {
                        hasOneDifference = false;
                        break;
                    }
                    // i - ple vs j - pale
                    else if (firstString[i] == secondString[j+1]) {
                        different = true;
                        ++j;
                    }
                    // i - palse vs j - pale
                    else if (firstString[i+1] == secondString[j]) {
                        different = true;
                        ++i;
                    }
                    // Last character, different is false so its true
                    else {
                        break;
                    }
                }
            }

        }
        // O(n) solution, put each character into the hash table/stl map
        else if (solutionSelection == 2) {
            map<char, int> charCounter;
            int nonZeroCount = 0;

            for (char c : firstString) {
                // If map contains the same value, increase its value
                if (charCounter.find(c) != charCounter.end()) {
                    charCounter[c]++;
                }
                // If not add it and make its value 1
                else {
                    charCounter[c] = 1;
                    ++nonZeroCount;
                }
            }

            for (char c : secondString) {
                // If set contains the same value, uniqueness break
                if (charCounter.find(c) != charCounter.end()) {
                    if(--charCounter[c] == 0)
                        --nonZeroCount;
                }
                // Second difference, break the loop
                else if (different) {
                    hasOneDifference = false;
                    break;
                }
                // First difference
                else {
                    different = true;
                }
            }

            if(nonZeroCount > 1)
                hasOneDifference = false;
        }
        // Neither O(n) nor O(n) solution selected
        else {
            cout << "Incorrect solution selection!" << endl;
            return;
        }
    }

    if (hasOneDifference)
        cout << firstString << " and " << secondString << " difference is <1 edit distance." << endl << endl;
    else
        cout << firstString << " and " << secondString << " difference is greater than 1 edit distance." << endl << endl;

    return;
};

void StringCompression() {
    // Description of the problem
    cout << "Compress the given string. If result is longer, return original. Ex: aaabbbbbcca --> a3b5c2a1" << endl;

    // Get strings from user
    string compressed, uncompressed;;
    cout << endl << "- Enter a string to compress: ";
    cin >> uncompressed;

    int counter = 0;
    char previousChar = uncompressed[0];
    const size_t uncSize = uncompressed.size();
    // Loop through the string
    for (char c : uncompressed) {
        if (previousChar == c) {
            ++counter;
        }
        else {
            compressed += (previousChar + to_string(counter));
            // Reset counter
            counter = 1;
            // Update previous
            previousChar = c;
        }
    }
    // Last character
    compressed += (previousChar + to_string(counter));
    const size_t cSize = compressed.size();
    // Print result
    if (uncSize > cSize) {
        cout << "Compressed: " << compressed << endl << endl;
    }
    else {
        cout << "Uncompressed: " << uncompressed <<  " Compressed is longer: " << compressed << endl << endl;
    }
    return;
};

void StringRotation() {
    // Description of the problem
    cout << "Check if given 2 string are in one edit distance (add/remove/change) or not." << endl;

    // Get strings from user
    string firstString;
    string secondString;
    cout << endl << "- Enter the first string: ";
    cin >> firstString;
    cout << endl << "- Enter the second string: ";
    cin >> secondString;

    const size_t firstSize = firstString.size();
    const size_t secondSize = secondString.size();
    // Size check
    if (firstSize != secondSize) {
        cout << "Two strings' sizes are different, they cannot be rotation." << endl << endl;
    }
    else {
        // Concat itself so that "waterwater" we can check if it contains "terwa"
        firstString += firstString;
        // Check if it is a substring of it or not
        size_t pos = firstString.find(secondString);
        // Couldn't find in it
        if (pos == string::npos) {
            cout << firstString << " is not a rotation of the " << secondString << endl << endl;
        }
        else {
            cout << firstString << " is a (" << pos << ") rotation of the " << secondString << endl << endl;
        }
    }

    return;
};

void ZeroMatrix() {
    // Description of the problem
    cout << "Change all row and column values to Zero if the cell's value is Zero in the given matrix." << endl;

    unsigned short rowCount = 0, columnCount = 0;
    cout << endl << "- Enter row count: ";
    cin >> rowCount;
    cout << endl << "- Enter column count: ";
    cin >> columnCount;

    vector<vector<int>> matrix;
    vector<bool> changeToZeroRow(rowCount, false);
    vector<bool> changeToZeroCol(columnCount, false);

    for (int i = 0; i < rowCount; ++i) {
        // Get array values from user
        vector<int> arr = getArrayInput<int>(columnCount);
        // Put new vector/array in the matrix
        matrix.push_back(arr);
    }

    // Print
    cout << "Matrix Before: " << endl;
    for (int i = 0; i < rowCount; ++i) {
        for (int val : matrix[i]) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Solution
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            if (matrix[i][j] == 0) {
                // Update boolean arrays
                changeToZeroRow[i] = true;
                changeToZeroCol[j] = true;
            }
        }
    }
    // Update rows and columns to zero
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            if (changeToZeroRow[i] || changeToZeroCol[j]) {
                matrix[i][j] = 0;
            }
        }
    }

    // Print
    cout << "Matrix After: " << endl;
    for (int i = 0; i < rowCount; ++i) {
        for (int val : matrix[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
    return;
};

void LinkedListRemoveDuplicates() {
    // Description of the problem
    cout << "Remove duplicates in a given linked list." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a LinkedList from a vector
    auto ll = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(arr));
    //std::shared_ptr<LinkedList<int>> ll = new LinkedList<int>(arr);

    cout << endl << "LinkedList: ";
    ll->printLinkedList();

    set<int> uniqueValues;
    std::shared_ptr<Node<int>> current = ll->head;
    std::shared_ptr<Node<int>> previous = nullptr;

    while(current){
        // Check current node's value bu adding in set
        if (uniqueValues.insert(current->getValue()).second == false) { 
            // Same value already exist in the set, remove the current
            // Set previous node's next to current's next
            previous->setNext(current->getNext());
            // Delete current node
            //delete current.get(); // Deleting a node doesn't necessary w/ smart pointer
            // Update current node
            current = previous->getNext();
        }
        else {
            // Update previous
            previous = current;
            // Move forward
            current = current->getNext();
        }
    }

    cout << endl << "After removing the duplicates" << endl << "LinkedList: ";
    ll->printLinkedList();

    return;
};

void LinkedListKthLast() {
    // Description of the problem
    cout << "Get the Kth Last element of the linked list." << endl;

    // Get the k
    unsigned short k = 0;
    cout << "K (Kth last element): ";
    cin >> k;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a LinkedList from a vector
    auto ll = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(arr));

    cout << endl << "LinkedList: ";
    ll->printLinkedList();

    std::shared_ptr<Node<int>> slow = ll->head;
    std::shared_ptr<Node<int>> fast = ll->head;
    unsigned short size = 0;

    while (fast != nullptr && fast->getNext() != nullptr) {
        // Increment the size twice
        size += 2;
        // Move slow pointer once
        slow = slow->getNext();
        // Move fast pointer twice
        fast = fast->getNext()->getNext();
    }

    // If the fast is not null, increment size once more
    if (fast) {
        ++size;
    }

    if (k >= size) {
        cout << "K's value cannot be greater or equal to the size of the linked list. K: " << k << " Size: " << size << endl << endl;
    }
    else {
        cout << "Kth node's value: " << ll->getKthNode(size - k)->getValue() << " Size of the LinkedList: " << size << endl << endl;
    }

    return;
};

void SumWithLinkedList() {
    // Description of the problem
    cout << "Sum 2 integers as a Linked List. (Intergers are reversed in LL)" << endl;

    // Get numbers from user
    int first = 0, second = 0;
    cout << endl << "Enter the first number: ";
    cin >> first;
    cout << endl << "Enter the second number: ";
    cin >> second;
    // Number vectors
    vector<int> firstNumVec;
    vector<int> secondNumVec;
    // Generate vectors from numbers
    while (first > 10) {
        firstNumVec.push_back(first % 10);
        first /= 10;
    }
    firstNumVec.push_back(first);
    while (second > 10) {
        secondNumVec.push_back(second % 10);
        second /= 10;
    }
    secondNumVec.push_back(second);
    // Create LinkedLists from vectors
    auto firstNum = std::shared_ptr<LinkedList<int>> (new LinkedList<int>(firstNumVec));
    auto secondNum = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(secondNumVec));
    auto result = std::shared_ptr<LinkedList<int>>(new LinkedList<int>());
    // Print
    cout << endl << "First LinkedList: ";
    firstNum->printLinkedList();
    cout << endl << "Second LinkedList: ";
    secondNum->printLinkedList();
    // Calculate sum operations
    std::shared_ptr<Node<int>> firstPointer = firstNum->head;
    std::shared_ptr<Node<int>> secondPointer = secondNum->head;
    std::shared_ptr<Node<int>> prev = nullptr;
    int carry = 0;
    int sum = 0;
    // Traverse
    while (firstPointer || secondPointer) {
        // Calculate sum
        // Second integer's digits over, only add first integer's digits
        if (firstPointer && !secondPointer) {
            sum = firstPointer->getValue() + carry;
        }
        // First integer's digits over, only add second integer's digits
        else if (secondPointer && !firstPointer) {
            sum = secondPointer->getValue() + carry;
        }
        else {
            sum = firstPointer->getValue() + secondPointer->getValue() + carry;
        }

        // >10, update carry
        if (sum >= 10) {
            carry = sum / 10;
            sum %= 10;
        }
        else {
            carry = 0; // Reset
        }
        // Create a new node
        auto temp = std::shared_ptr<Node<int>> (new Node<int>(sum));
        // If prev is not null, update prev's next
        if (prev) {
            prev->setNext(temp);
        }
        // Update the prev pointer
        prev = temp;
        // If result linked list's head is null, assign first node
        if (!(result->head))
            result->head = temp;
        // Move 2 pointers
        if(firstPointer)
            firstPointer = firstPointer->getNext();
        if (secondPointer)
            secondPointer = secondPointer->getNext();
    }
    // Lastly check carry, if not zero add to the tail (prev)
    if (carry != 0)
        prev->setValue(prev->getValue() + carry);
    // Print result Linked List
    cout << endl << "Result LinkedList: ";
    result->printLinkedList();
}

void LinkedListPalindrom() {    
    // Description of the problem
    cout << "Checks if the given Linked List is palindrom or not." << endl;

    // Get array values from user
    cout << endl << "Enter only one character (letter or number)." << endl;
    vector<char> arr = getArrayInput<char>();
    // Create a LinkedList from a vector
    auto ll = std::shared_ptr<LinkedList<char>>(new LinkedList<char>(arr));

    // Reverse it, compare the first halves
    // Find mid and tail, move from mid kth times
    // Put first half into stack and compare with last half
    std::shared_ptr<Node<char>> fast = ll->head;
    std::shared_ptr<Node<char>> slow = ll->head;
    stack<char> firstHalf;
    bool result = true;
    // Traverse insede the ll
    while (fast && fast->getNext()) {
        // Put slow's values in stack
        firstHalf.push(slow->getValue());
        // Move pointers
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }
    // If length of the ll is odd, move slow once, no need to use middle node
    if (fast) {
        slow = slow->getNext();
    }
    // Pop everything from the stack while comparing
    while (!firstHalf.empty()) {
        if (firstHalf.top() != slow->getValue()) {
            result = false;
            break;
        }
        else {
            slow = slow->getNext(); // Move slow
            firstHalf.pop(); // Pop from stack
        }
    }
    // Print result
    ll->printLinkedList();
    if (result) {
        cout << endl << "Linked List is palindrome." << endl;
    }
    else {
        cout << endl << "Linked List is NOT palindrome." << endl;
    }
}

void LinkedListIntersection() {
    // If the last nodes are the same
    // To find intersection chop of larger list's first x nodes and compare others
    // 1->2->3->4  vs  5->3->4 chop of first list first node so that they can be same length and compare each node
    // Description of the problem
    cout << "Checks if the given 2 Linked Lists intersect with each other." << endl;

    // Select 1 or 2
    int selection = 0;
    cout << endl << "Enter 1 for Linked-List with intersection, 2 for w/o." << endl;
    cin >> selection;
    // Create an empty LinkedList
    std::shared_ptr<LinkedList<int>> ll1 = nullptr;
    std::shared_ptr<LinkedList<int>> ll2 = nullptr;

    // Has Intersection
    if (selection == 1) {
        // First Linked-List 5 -> 2 -> 1 -> 7 -> 8 -> 13 -> 10 -> 3
        auto last = std::shared_ptr<Node<int>> (new Node<int> (3));
        auto seventh = std::shared_ptr<Node<int>> (new Node<int>(10, last));
        auto sixth = std::shared_ptr<Node<int>> (new Node<int>(13, seventh));
        auto fifth = std::shared_ptr<Node<int>> (new Node<int>(8, sixth));
        auto fourth = std::shared_ptr<Node<int>> (new Node<int>(7, fifth));
        auto third = std::shared_ptr<Node<int>> (new Node<int>(1, fourth));
        auto second = std::shared_ptr<Node<int>> (new Node<int>(2, third));
        auto first = std::shared_ptr<Node<int>> (new Node<int>(3, second));
        // Create a linked list

        ll1 = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(first));
        // Second Linked-List 6 -> 4 -> 8 -> 13 -> 10 -> 3
        auto second_2 = std::shared_ptr<Node<int>> (new Node<int>(4, fifth));
        auto first_2 = std::shared_ptr<Node<int>> (new Node<int>(6, second_2));
        // Create a linked list
        ll2 = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(first_2));
    }
    // Doesn't Have Intersection
    else if (selection == 2) {
        // First Linked-List 5 -> 2 -> 1 -> 7 -> 8 -> 13 -> 10 -> 3
        auto last = std::shared_ptr<Node<int>> (new Node<int>(3));
        auto seventh = std::shared_ptr<Node<int>> (new Node<int>(10, last));
        auto sixth = std::shared_ptr<Node<int>> (new Node<int>(13, seventh));
        auto fifth = std::shared_ptr<Node<int>> (new Node<int>(8, sixth));
        auto fourth = std::shared_ptr<Node<int>> (new Node<int>(7, fifth));
        auto third = std::shared_ptr<Node<int>> (new Node<int>(1, fourth));
        auto second = std::shared_ptr<Node<int>> (new Node<int>(2, third));
        auto first = std::shared_ptr<Node<int>> (new Node<int>(3, second));
        // Create a linked list
        ll1 = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(first));

        // Second Linked-List 6 -> 4 -> 12 -> 15 -> 9
        auto last_2 = std::shared_ptr<Node<int>> (new Node<int>(9));
        auto fourth_2 = std::shared_ptr<Node<int>> (new Node<int>(15, last_2));
        auto third_2 = std::shared_ptr<Node<int>> (new Node<int>(12, fourth_2));
        auto second_2 = std::shared_ptr<Node<int>> (new Node<int>(4, third_2));
        auto first_2 = std::shared_ptr<Node<int>> (new Node<int>(6, second_2));
        // Create a linked list
        ll2 = std::shared_ptr<LinkedList<int>>(new LinkedList<int>(first_2));
    }
    // Incorrect selection
    else {
        cout << "Incorrect selection!" << endl;
        return;
    }

    // Solution: If the tails of the 2 LL is the same, they have an intersect
    std::shared_ptr<Node<int>> traverse1 = ll1->head;
    std::shared_ptr<Node<int>> traverse2 = ll2->head;
    // Find 2 lists sizes
    size_t size1 = 0;
    size_t size2 = 0;
    // Move 2 pointers until they reached the end
    while (traverse1->getNext()) {
        traverse1 = traverse1->getNext();
        ++size1;
    }
    while (traverse2->getNext()) {
        traverse2 = traverse2->getNext();
        ++size2;
    }
    // Print both Linked-Lists
    ll1->printLinkedList();
    ll2->printLinkedList();
    // Compare 2 pointers
    if (traverse1 == traverse2) {
        cout << "2 Linked-Lists have an intersection." << endl;
    }
    else {
        cout << "2 Linked-Lists don't have an intersection." << endl;
        return;
    }

    // Find intersection node
    traverse1 = ll1->head;  // Reset traverse pointers
    traverse2 = ll2->head;
    // Find the longer one and move its pointer by size difference
    size_t sizeDifference = size1 - size2; // Use abs for normal cases, in this case s1 is greater than s2
    if (size1 > size2) {
        while (sizeDifference) {
            traverse1 = traverse1->getNext();
            --sizeDifference;
        }
    }
    else if (size1 < size2) {
        while (sizeDifference) {
            traverse2 = traverse2->getNext();
            --sizeDifference;
        }
    }
    // Move 2 pointers simulteniously, if they reached the same node, we found the intersection
    while (traverse1->getNext() && traverse2->getNext()) {
        // Check intersection node
        if (traverse1 == traverse2) {
            cout << "Intersection node is: " << traverse1->getValue() << endl;
            break;
        }
        else {
            traverse1 = traverse1->getNext();
            traverse2 = traverse2->getNext();
        }
    }
    return;
}

void LinkedListLoopDetection() {
    // Description of the problem
    cout << "Checks if the given Linked List has a loop or not." << endl;

    // Get array values from user
    cout << endl << "Enter unique inputs, except one for loop creation." << endl;
    vector<string> arr = getArrayInput<string>();
    // Create a LinkedList from a vector
    set<string> uniqueCheck;
    std::shared_ptr<Node<string>> prev = nullptr;
    auto ll = std::shared_ptr<LinkedList<string>> (new LinkedList<string>());
    // Create new linked list with loop
    for (string element : arr) {
        // Put in set: First time and its unique
        if (uniqueCheck.insert(element).second != false) {
            // Create a new node
            auto temp = std::shared_ptr<Node<string>> (new Node<string>(element));
            // Update prev's next
            if (prev) {
                prev->setNext(temp);
            }
            // First node, update LL's head
            else {
                ll->head = temp;
            }
            // Update prev
            prev = temp;
        }
        // Same value, connect last node's (prev) to given valued node
        else {
            // Find the node in the LL
            std::shared_ptr<Node<string>> loopStart = ll->head;
            while (loopStart && loopStart->getValue() != element) {
                loopStart = loopStart->getNext();
            }
            // Found it or nullptr
            prev->setNext(loopStart);
        }
    }
    // Solution
    std::shared_ptr<Node<string>> fast = ll->head;
    std::shared_ptr<Node<string>> slow = ll->head;
    // Move pointers until they met or reached the end
    while (fast && fast->getNext()) {
        fast = fast->getNext()->getNext();
        slow = slow->getNext();
        // After moving from head, check
        if (fast == slow)
            break;
    }

    if (fast == nullptr || fast->getNext() == nullptr) {
        cout << endl << "Linked List does NOT contain a loop." << endl;
        return;
    }

    // Find the loop start
    // Fast moved 2x faster, when they meet restart slow ptr to head
    // Slow: head, Fast: last meet position
    // When both of them moves only once they will meet at the loop start
    slow = ll->head;
    // Move both fast and slow only 1 node
    while (fast && fast->getNext()) {
        fast = fast->getNext();
        slow = slow->getNext();
        // After moving from head, check
        if (fast == slow)
            break;
    }

    cout << endl << "Linked List contains a loop. Loop start: " << fast->getValue() << endl;
    return;
}

void ThreeStacksWithOneArray() {
    // Description of the problem
    cout << "3 Stacks implementation with 1 Array. Stack sizes are static and the same in this one." << endl;

    size_t stackSize = 0;
    cout << endl << "Enter stacks (all 3 of them are the same) size: ";
    cin >> stackSize;

    // Create instance of the data structure w/ vector
    auto threeStacks = std::shared_ptr<StacksWithArray<int>>(new StacksWithArray<int>(stackSize));
    unsigned int choice = 1;
    int value = 0;
    unsigned int stackIndex = 0;

    while (choice != 0) {
        cout << endl << "0-Exit, 1-Top, 2-Push, 3-Pop, 4-isEmpty: ";
        cin >> choice;
        if (choice == 0) { 
            cout << "Exiting the question..." << endl;
            break; 
        }
        // Stack operaiton seleciton
        switch (choice) {
            case 0:
                break;
            case 1: // TOP
                cout << endl << "Choose a stack to get top (0, 1, 2):";
                cin >> stackIndex;
                if(threeStacks->top(stackIndex))
                    cout << "Top: " << threeStacks->top(stackIndex) << endl;
                else
                    cout << "Stack is empty!" << endl;
                threeStacks->printStack(stackIndex);
                break;
            case 2: // PUSH
                cout << endl << "Choose a stack to push (0, 1, 2):";
                cin >> stackIndex;
                cout << "Enter a number to push:";
                cin >> value;
                if (threeStacks->push(stackIndex, value))
                    cout << "Succesfully pushed!" << endl;
                else
                    cout << "Push failed, stack is full!" << endl;
                cout << "After push operation:" << endl;
                threeStacks->printStack(stackIndex);
                break;
            case 3: // POP
                cout << endl << "Choose a stack to pop (0, 1, 2):";
                cin >> stackIndex;
                if (threeStacks->pop(stackIndex))
                    cout << "Succesfully poped!" << endl;
                else
                    cout << "Pop failed, stack is empty!" << endl;
                cout << "After pop operation:" << endl;
                threeStacks->printStack(stackIndex);
                break;
            case 4: // EMPTY
                cout << endl << "Choose a stack to check emptiness (0, 1, 2):";
                cin >> stackIndex;
                if (threeStacks->isEmpty(stackIndex))
                    cout << "Stack is empty" << endl;
                else
                    cout << "Stack is not empty" << endl;
                threeStacks->printStack(stackIndex);
                break;
            default:
                cout << "Wrong operation selection, try again." << endl;
                break;
        }
    }
    return;
}

void StackWithMinMax() {
    // Description of the problem
    cout << "Stack with min and max values." << endl; 
    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for stack w/ custom data structure , 2 for additional stacks for min/max: ";
    cin >> solutionSelection;

    // Store value, min and max in the array
    int* node = new int[3]{ 0, 0, 0 };
    int value = 0;
    int min = 100; // Could use INT_MIN & INT_MAX
    int max = -100;

    // 1. Store min/max below in the each node/element
    if (solutionSelection == 1) {
        stack<int*> s;
        unsigned int choice = 1;
        while (choice != 0) {
            cout << endl << "0-Exit, 1-Top, 2-Push, 3-Pop: ";
            cin >> choice;
            if (choice == 0) {
                cout << "Exiting the question..." << endl;
                break;
            }
            // Stack operaiton seleciton
            switch (choice) {
            case 0:
                break;
            case 1: // TOP
                cout << "TOP" << endl;
                if (s.empty())
                    cout << "Stack is empty." << endl;
                else
                    cout << "Value: " << s.top()[0] << " Min: " << s.top()[1] << " Max: " << s.top()[2] << endl;
                break;
            case 2: // PUSH
                cout << "PUSH" << endl;
                cout << "Enter a number to push:";
                cin >> value;
                // Get top node's min and max
                if (!s.empty()) {
                    min = s.top()[1];
                    max = s.top()[2];
                }
                // Update min and max
                if (value < min)
                    min = value;
                if (value > max)
                    max = value;
                // Create new array
                node = new int[3]{ value, min, max };
                s.push(node);
                cout << "Pushed!" << endl;
                break;
            case 3: // POP
                cout << "POP" << endl;
                if (s.empty())
                    cout << "Stack is empty." << endl;
                else {
                    s.pop();
                    cout << "Poped!" << endl;
                }
                break;
            default:
                cout << "Wrong operation selection, try again." << endl;
                break;
            }
        }
    }
    // 2. Store min/max in the another stack    
    else if (solutionSelection == 2) {
        stack<int> mins;
        stack<int> maxs;
        stack<int> s;
        unsigned int choice = 1;
        while (choice != 0) {
            cout << endl << "0-Exit, 1-Top, 2-Push, 3-Pop: ";
            cin >> choice;
            if (choice == 0) {
                cout << "Exiting the question..." << endl;
                break;
            }
            // Stack operaiton seleciton
            switch (choice) {
            case 0:
                break;
            case 1: // TOP
                cout << "TOP" << endl;
                if (s.empty())
                    cout << "Stack is empty." << endl;
                else
                    cout << "Value: " << s.top() << " Min: " << mins.top() << " Max: " << maxs.top() << endl;
                break;
            case 2: // PUSH
                cout << "PUSH" << endl;
                cout << "Enter a number to push:";
                cin >> value;
                // Update min and max stacks
                if (mins.empty() || value < mins.top())
                    mins.push(value);
                if (maxs.empty() || value > maxs.top())
                    maxs.push(value);
                // Push in stack
                s.push(value);
                cout << "Pushed!" << endl;
                break;
            case 3: // POP
                cout << "POP" << endl;
                if (s.empty())
                    cout << "Stack is empty." << endl;
                else {
                    // Update min and max stacks
                    if (!mins.empty() && s.top() == mins.top())
                        mins.pop();
                    if (!maxs.empty() && value == maxs.top())
                        maxs.pop();
                    // Pop from stack
                    s.pop();
                    cout << "Poped!" << endl;
                }
                break;
            default:
                cout << "Wrong operation selection, try again." << endl;
                break;
            }
        }
    }
    // Incorrect solution selection
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void StackWithCapacity() {
    // Description of the problem
    cout << "Stack with capacity. If the current stack is full, it creates a new one." << endl;

    size_t stackCapacity = 0;
    cout << endl << "Enter stack capacity: ";
    cin >> stackCapacity;
    
    // Vector to hold all the stacks
    vector<stack<int>*> stackVec;
    // Push empty stack
    stackVec.push_back(new stack<int>);
    // Stack index
    unsigned int currentStack = 0;
    int value = 0;
    unsigned int choice = 1;
    while (choice != 0) {
        cout << endl << "0-Exit, 1-Top, 2-Push, 3-Pop: "; // TODO: PopAt w/ stackVec index and stack index, put NULL and while poping clear
        cin >> choice;
        if (choice == 0) {
            cout << "Exiting the question..." << endl;
            break;
        }
        // Stack operaiton seleciton
        switch (choice) {
        case 0:
            break;
        case 1: // TOP
            cout << "TOP" << endl;
            if (stackVec[currentStack]->empty())
                cout << "Stack is empty." << endl;
            else
                cout << "Value: " << stackVec[currentStack]->top() << endl;
            break;
        case 2: // PUSH
            cout << "PUSH" << endl;
            cout << "Enter a number to push:";
            cin >> value;
            // Check current stack's capacity
            if (stackVec[currentStack]->size() == stackCapacity) {
                // Create a new stack
                stack<int>* newStack = new stack<int>;
                newStack->push(value);
                // Push new stack in stackVec
                stackVec.push_back(newStack);
                // Increment the currentStack index
                ++currentStack;
                cout << "Pushed in a new stack!" << endl;
            }
            else {
                // Push into current stack
                stackVec[currentStack]->push(value);
                cout << "Pushed!" << endl;
            }
            break;
        case 3: // POP
            cout << "POP" << endl;
            if (stackVec[currentStack]->size() == 1) {
                // Pop from stack
                stackVec[currentStack]->pop();
                // Do not delete the first stack, but delete others
                if (currentStack != 0) {
                    // Delete the pointer
                    delete stackVec.back();
                    // Pop the last stack
                    stackVec.pop_back();
                    // Decrement the currentStack index
                    --currentStack;
                    cout << "Poped and deleted a stack!" << endl;
                }
                else
                    cout << "Poped!" << endl;
            }
            else if (currentStack == 0 && stackVec[currentStack]->size() == 0)
                cout << "Stack is empty." << endl;
            else {
                stackVec[currentStack]->pop();
                cout << "Poped!" << endl;
            }
            break;
        default:
            cout << "Wrong operation selection, try again." << endl;
            break;
        }
    }
}

void ReverseStacks(stack<int>& forwardStack, stack<int>& backwardStack) {
    // Pop from the forward until it's empty
    while (!forwardStack.empty()) {
        // Push forward's top element into backward
        backwardStack.push(forwardStack.top());
        // Pop it
        forwardStack.pop();
    }
}

void QueueWithTwoStacks() {
    // Description of the problem
    cout << "Queue data structure that implemented with 2 stacks." << endl;

    // Declare 2 stacks
    stack<int> forwardStack;
    stack<int> backwardStack;
    bool isForwardUpToDate = true;

    int value = 0;
    unsigned int choice = 1;
    while (choice != 0) {
        cout << endl << "0-Exit, 1-Front, 2-Back, 3-Push back, 4-Pop front: ";
        cin >> choice;
        if (choice == 0) {
            cout << "Exiting the question..." << endl;
            break;
        }
        // Stack operaiton seleciton
        switch (choice) {
        case 0:
            break;
        case 1: // FRONT
            cout << "FRONT" << endl;
            if (isForwardUpToDate) {
                if (forwardStack.empty()) {
                    cout << "Queue is empty." << endl;
                    break;
                }
                else {
                    ReverseStacks(forwardStack, backwardStack);
                    isForwardUpToDate = false;
                }
            }
            else if (backwardStack.empty()) {
                cout << "Queue is empty." << endl;
                break;
            }
            // Print front element's value
            cout << "Value: " << backwardStack.top() << endl;
            break;
        case 2: // BACK
            cout << "BACK" << endl;
            if (!isForwardUpToDate) {
                if (backwardStack.empty()) {
                    cout << "Queue is empty." << endl;
                    break;
                }
                else {
                    ReverseStacks(backwardStack, forwardStack);
                    isForwardUpToDate = true;
                }
            }
            else if (forwardStack.empty()) {
                cout << "Queue is empty." << endl;
                break;
            }
            // Print back element's value
            cout << "Value: " << forwardStack.top() << endl;
            break;
        case 3: // PUSH BACK
            cout << "PUSH BACK" << endl;
            cout << "Enter a number to push back:";
            cin >> value;
            // Check forward's up to date
            if (!isForwardUpToDate) {
                ReverseStacks(backwardStack, forwardStack);
                isForwardUpToDate = true;
            }
            forwardStack.push(value);
            cout << "Pushed!" << endl;
            break;
        case 4: // Pop front
            cout << "POP FRONT" << endl;
            if (isForwardUpToDate) {
                if (forwardStack.empty()) {
                    cout << "Queue is empty." << endl;
                    break;
                }
                else {
                    ReverseStacks(forwardStack, backwardStack);
                    isForwardUpToDate = false;
                }
            }
            else if (backwardStack.empty()) {
                cout << "Queue is empty." << endl;
                break;
            }
            // Print front element's value and then pop it
            cout << "Value: " << backwardStack.top() << " poped from front." << endl;
            backwardStack.pop();
            break;
        default:
            cout << "Wrong operation selection, try again." << endl;
            break;
        }
    }
}

void StackSorting() {
    // Description of the problem
    cout << "Sort stack only with 1 additional stack." << endl;

    // Declare 2 stacks
    stack<int> s;
    stack<int> sExtra;
    // Push 5 integers in s
    cout << "Initial stack: 5->1->9->2->13" << endl;
    s.push(5);
    s.push(1);
    s.push(9);
    s.push(2);
    s.push(13);
    // 2 Integers for operatins
    int current = 0;
    unsigned int counter = 0;

    while (!s.empty()) {
        // Get the top of the s and pop it
        current = s.top();
        s.pop();
        // If sExtra is not empty and the top element is greater than the current value, pop it and push in s
        while (!sExtra.empty() && current < sExtra.top()) {
            s.push(sExtra.top());
            sExtra.pop();
            ++counter; // Increment counter so we can get the sExtra elements back
        }
        // Top of the sExtra is smaller than the current value, push it in sExtra
        sExtra.push(current);
        // Transfer back the counter amonth of elements back to sExtra
        while (counter > 0 && !s.empty()) {
            sExtra.push(s.top());
            s.pop();
            --counter;
        }

    }
    // sExtra is reversed sorted: min in the bottom, max in the top. Print elements while popping
    while (!sExtra.empty()) {
        cout << sExtra.top() << endl;
        sExtra.pop();
    }
    return;
}

void LongestCommonSubsequence() {}

void GraphPathCheck() {}

std::shared_ptr<BSTNode<int>> SortedArrayToMinimalBST(vector<int> &nums, int begin, int end) {
    // List is empty
    if (begin > end)
        return nullptr;

    // Find the middle index
    int middle = begin + ((end - begin) / 2);

    // Create new tree node from the middle element
    auto root = std::shared_ptr<BSTNode<int>>(new BSTNode<int>(nums[middle]));

    root.get()->updateLeft(SortedArrayToMinimalBST(nums, begin, middle - 1));
    root.get()->updateRight(SortedArrayToMinimalBST(nums, middle + 1, end));

    // Return the root of the tree
    return root;
}

void SortedArrayToMinimalBST() {
    // Description of the problem
    cout << "Create a minimal depth Binary Search Tree from a sorted array." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Sort the user input array
    sort(arr.begin(), arr.end());

    // Create a BST from sorted array
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(SortedArrayToMinimalBST(arr, 0, arr.size() - 1)));

    cout << endl << "Binary Search Tree: ";
    bst->printTree();
}

void BSTToDepthLinkedList() {
    // Description of the problem
    cout << "Create linked list w/ same depth nodes in BST" << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));

    cout << endl << "Tree: ";
    bst->printTree();

    std::vector<std::list<std::shared_ptr<BSTNode<int>>>> result;
    bst->depthNodesToLinkedList(bst->getRoot(), 1, result);

    for (auto item : result) {
        cout << "Linked List Items: ";
        for (auto node : item) {
            cout << node.get()->getValue() << ", ";
        }
        cout << endl;
    }
}

int IsBalancedBTDepth(std::shared_ptr<BSTNode<int>> root) {
    // Leaf node, return 0
    if (root == nullptr) {
        return 0;
    }
    // Get left and right subtrees' depths
    int left = IsBalancedBTDepth(root.get()->getLeftChild());
    int right = IsBalancedBTDepth(root.get()->getRightChild());
    // If two subtrees' depth difference is greater than 1, return negative number as depth value
    if (abs(left - right) > 1) {
        return -32767; // SHRT_MIN
    }
    // Depth is correct and subtree is balanced, return max depth + 1 (node's depth)
    return max(left, right) + 1;
}

void IsBTBalanced() {
    // Description of the problem
    cout << "Check if the given Binary Tree is balanced or not." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));

    cout << endl << "Tree: ";
    bst->printTree();
    // Get left and right subtrees' depth
    int left = IsBalancedBTDepth(bst->getRoot()->getLeftChild());
    int right = IsBalancedBTDepth(bst->getRoot()->getRightChild());
    int depthDifference = abs(left - right);

    if (left < 0 || right < 0) {
        cout << "BT is NOT balanced." << endl;
    }
    else if (depthDifference <= 1 && depthDifference < 32767) {
        cout << "BT is balanced." << endl;
    }
    else {
        cout << "BT is NOT balanced." << endl;
    }
}

bool IsBST(std::shared_ptr<BSTNode<int>> root, long min, long max) {
    // Null check
    if (root == nullptr)
        return true;
    // Node parameters
    int value = root.get()->getValue();
    std::shared_ptr<BSTNode<int>> leftChild = root.get()->getLeftChild();
    std::shared_ptr<BSTNode<int>> rightChild = root.get()->getRightChild();

    if (value <= min || value >= max) {
        cout << value << endl;
        return false;
    }

    // Left child check recursive calls
    if (leftChild != nullptr && !IsBST(leftChild, min, value)) {
        return false;
    }
    // Right child check
    if (rightChild != nullptr && !IsBST(rightChild, value, max)) {
        return false;
    }

    // Finally return true
    return true;
}

void ValidateBST() {
    // Description of the problem
    cout << "Check if the given Binary Search Tree is valid or not." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));

    cout << endl << "Tree: ";
    bst->printTree();

    long min = LONG_MIN;
    long max = LONG_MAX;
    if (IsBST(bst->getRoot(), min, max)) {
        cout << "BST is valid" << endl;
    }
    else {
        cout << "BST is NOT valid" << endl;
    }
}

bool BTFirstCommonAncestor(std::shared_ptr<BSTNode<int>> node, const int &node1, const int &node2, std::shared_ptr<BSTNode<int>>& ancestor) {
    // Base case for leafs/null
    if (node == nullptr) return false;

    bool isNode1 = false;
    bool isNode2 = false;
    bool isInLeftSubtree = false;
    bool isInRightSubtree = false;

    // First node
    if (node->getValue() == node1) {
        isNode1 = true;
    }
    // Second node
    else if (node->getValue() == node2) {
        isNode2 = true;
    }

    // Recursive calls for left and right subtrees
    isInLeftSubtree = BTFirstCommonAncestor(node->getLeftChild(), node1, node2, ancestor);
    isInRightSubtree = BTFirstCommonAncestor(node->getRightChild(), node1, node2, ancestor);

    // Found the ancestor
    if ((isInLeftSubtree && isInRightSubtree)                       // Left and right subtrees return true, ancestor is current
        || (isNode1 && (isInLeftSubtree || isInRightSubtree))       /* Node is one of them and either left or right subtree is true */
        || (isNode2 && (isInLeftSubtree || isInRightSubtree))) {    /* so current node is the ancestor */
        ancestor = node;
        return false;   // Found the ancestor, return false to prior calls for not confusing
    }
    // Only 1 of the 4 conditions is true, return true to prior calls
    else if (isNode1 || isNode2 || isInLeftSubtree || isInRightSubtree) {
        return true;
    }
    // None of the conditions are true, return false
    else {
        return false;
    }
}

void BTFirstCommonAncestor() {
    // Description of the problem
    cout << "Find the first common ancestor of the given 2 nodes in the binary tree." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));

    // Get 2 nodes
    int node1, node2;
    cout << "Node 1: ";
    cin >> node1;
    cout << "Node 2: ";
    cin >> node2;

    cout << endl << "Tree: ";
    bst->printTree();

    std::shared_ptr<BSTNode<int>> ancestor = nullptr;
    BTFirstCommonAncestor(bst->getRoot(), node1, node2, ancestor);

    // Print the results
    if (ancestor) {
        cout << "First common ancestor of " << node1 << " and " << node2 <<" is: " << ancestor->getValue() << endl;
    }
    else {
        cout << "These 2 nodes are not have a common ancestor, maybe one of them is not in the tree." << endl;
    }
    return;
}

bool IsTreeMatch(std::shared_ptr<BSTNode<int>> root1, std::shared_ptr<BSTNode<int>> root2) {
    // One of them reached a leaf, XOR
    if (root1 == nullptr ^ root2 == nullptr) {
        return false;
    }
    // Both reached the leaves at the same time
    else if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    // Call left children, right children and check the current nodes values
    else if (IsTreeMatch(root1->getLeftChild(), root2->getLeftChild())
        && IsTreeMatch(root1->getRightChild(), root2->getRightChild())
        && root1->getValue() == root2->getValue()
        ) {
        return true;
    }
    else {
        return false;
    }
}

bool IsSubTree(std::shared_ptr<BSTNode<int>> root1, std::shared_ptr<BSTNode<int>> root2) {
    // Reached the leaves
    if (root1 == nullptr) {
        return false;
    }
    // Call match function if the current node is equal to second tree's root
    if (root1->getValue() == root2->getValue() && IsTreeMatch(root1, root2)) {
        return true;
    }
    // Call left and right children
    if (IsSubTree(root1->getLeftChild(), root2)) return true;
    if (IsSubTree(root1->getRightChild(), root2)) return true;
    // No matches, return false
    return false;
}

void IsSubTree() {
    // Description of the problem
    cout << "Is tree B is subtree of the tree A?" << endl;
    short solutionSelection = 0;

    // Tree 1
    cout << "Larger tree:" << endl;
    // Get array values from user
    vector<int> arr1 = getArrayInput<int>();
    // Create a BST from the vector
    auto bst1 = std::shared_ptr<BST<int>>(new BST<int>(arr1));

    // Tree 2
    cout << "Smaller/sub tree:" << endl;
    // Get array values from user
    vector<int> arr2 = getArrayInput<int>();
    // Create a BST from the vector
    auto bst2 = std::shared_ptr<BST<int>>(new BST<int>(arr2));

    // Size comparison
    if (arr1.size() < arr2.size()) {
        cout << "Second/sub tree is larger than the first one, is not subtree." << endl;
        return;
    }

    // Problem has several solutions, choose one
    cout << "Enter 1 for preorder substring solution, 2 for recursive traversal solution: ";
    cin >> solutionSelection;

    // 1. Get 2 trees' preorder traverse strings and check for substring
    if (solutionSelection == 1) {
        cout << "If the smaller tree's preorder is in the larger tree's preorder, it is subtree." << endl;
        cout << endl << "Large Tree: ";
        bst1->printPreorder(bst1->getRoot());
        cout << endl << "Small Tree: ";
        bst2->printPreorder(bst2->getRoot());
        // Search the substring --> Need to implement preorder that return a string, current one just prints
        /*size_t found = str.find(str2);
        if (found != std::string::npos)
            cout << "Subtree" << endl;
        else
            cout << "Not subtree" << endl;*/
    }
    /* Traverse inside the large tree and if the node is equal to small tree's
    * root node, call a matchTree function which compares all nodes until the leaves.*/
    else if (solutionSelection == 2) {
        // Call the recursive function
        if (IsSubTree(bst1->getRoot(), bst2->getRoot())) {
            cout << "Yes, second tree is subtree of the first one." << endl;
        }
        else {
            cout << "No, second tree is NOT subtree of the first one." << endl;
        }
    }
    // Incorrect solution selection
    else {
        cout << "Incorrect solution selection!" << endl;
    }
    return;
}

void RandomNodeInBST() {
    // Description of the problem
    cout << "Select a random node in given binary (search) tree." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    auto bst = std::shared_ptr<BST<int>>(new BST<int>(arr));

    cout << endl << "Tree: ";
    bst->printTree();

    cout << endl << "Random Node: " << bst->randomNode(bst->getRoot()).get()->getValue();
    cout << endl << "Random Node: " << bst->randomNode(bst->getRoot()).get()->getValue();
    cout << endl << "Random Node: " << bst->randomNode(bst->getRoot()).get()->getValue();
}

void ThreeStepStairs() {}

void TowersOfHanoi() {}

void AllCombinationOfParanthesis() {}

void MergeTwoSortedArrays() {}

int Fibonacci(int input, int n, vector<int>& numbers) {
    // Fibonacci with memoization
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (numbers[n] > 0) {
        return numbers[n];
    }
    numbers[n] = Fibonacci(input, n - 1, numbers) + Fibonacci(input, n - 2, numbers);
    return numbers[n];
}

int Fibonacci(int n) {
    // Fibonacci with tabulation
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    vector<int> dp(n+1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

void Fibonacci() {
    // Description of the problem
    cout << "Fibonacci" << endl;

    // Get user input
    int input;
    cin >> input;

    vector<int> numbers(input+1, 0);
    cout << "Fibonacci with memoization: " << Fibonacci(input, input, numbers) << endl;
    for (auto i : numbers)
        std::cout << i << ' ';
    cout << endl << "Fibonacci with tabulation: " << Fibonacci(input) << endl;
}

void ConsumerProducerCaller() {
    // Description of the problem
    std::cout << "Consumer-Producer multithread problem." << std::endl;

    std::vector<char> cVec;
    int solutionSelection = 0;
    unsigned short duration;
    // Problem has several solutions, choose one
    std::cout << "Enter 1 mutex  solution, 2 for semaphore solution (Requires C++20)." << std::endl;
    std::cin >> solutionSelection;
    // Thread runtime duration
    std::cout << "Enter a number of seconds which threads going to run (e.g. 10s): " << std::endl;
    std::cin >> duration;

    // Mutex solution
    if (solutionSelection == 1) {
        // Consumer-Producer w/ Mutex
        ConsumerProducer(true, duration);
    }
    // Semaphore solution
    else if (solutionSelection == 2) {
        // Consumer-Producer w/ Semaphore
        ConsumerProducer(false, duration);
    }
    // Neither Mutex nor Semaphore solution selected
    else {
        std::cout << "Incorrect solution selection!" << std::endl;
    }
    return;
}

void BarberCustomerCaller() {
    // Description of the problem
    std::cout << "Barber-Customer multithread problem." << std::endl;

    unsigned short duration;
    // Thread runtime duration
    std::cout << "Enter a number of seconds which threads going to run (min 15s): " << std::endl;
    std::cin >> duration;
    // 15s check
    if (duration < 15) duration = 15;

    BarberCustomer(duration);
    return;
}

int main()
{
    // Selection of the question
    int questionSelection = 3000;

    while (questionSelection) {
        // Show this menu after 3 seconds so that user can see problem's result for 3 sec
        if (questionSelection != 3000) { Sleep(3000); }

        cout << "This program consits of several interview questions and their solutions/implementations in C++. List of questions given below. Enter 0 to end the program." << endl;
        cout << "Questions list:" << endl
            << "1 - FizzBuzz" << endl
            << "2 - Two Sum" << endl
            << "3 - Max Consecutive Ones" << endl
            << "4 - Max Product of Three Numbers in an array" << endl
            << "5 - Valid Paranthesis" << endl
            << "6 - Baseball Game" << endl
            << "7 - Contains Duplicate" << endl
            << "8 - Valid Anagram" << endl
            << "9 - Kth Largest Element" << endl
            << "10 - K Pairs with Smallest Sum" << endl
            << "11 - Invert a Binary Search Tree" << endl
            << "12 - Insertion Sort" << endl
            << "13 - Merge Sort" << endl
            << "14 - Heap Sort" << endl
            << "15 - Quick Sort" << endl
            << "16 - Binary Search" << endl
            << "17 - Breadth First Search" << endl
            << "18 - Depth First Search" << endl
            << "19 - Check characters uniqueness in a string" << endl
            << "20 - URLify: convert spaces to %20 in a string" << endl
            << "21 - One edit distance between 2 strings" << endl
            << "22 - String Compression" << endl
            << "23 - String Rotation check: battle vs ttleba" << endl
            << "24 - Zero Matrix: Change rows and columns to 0 if cell is 0" << endl
            << "25 - LinkedList: Remove Duplications in LinkedList" << endl
            << "26 - LinkedList: Kth last element in the LinkedList" << endl
            << "27 - LinkedList: Sum 2 integers as linked lists" << endl
            << "28 - LinkedList is palindrome check" << endl
            << "29 - 2 LinkedLists intersection (not value) check" << endl
            << "30 - LinkedList loop detection" << endl
            << "31 - 3 Stacks with 1 array" << endl
            << "32 - Stacks that shows min/max" << endl
            << "33 - Stacs with capacity (Creates new stacks when exceeds)" << endl
            << "34 - Queue with 2 Stacks" << endl
            << "35 - Stack Sort with only 1 additional Stack" << endl
            << "36 - Longest common subsequence of the 2 strings" << endl
            << "37 - Given 2 nodes in the graph, check if there is a path between them" << endl
            << "38 - Sorted array to minimal depth BST" << endl
            << "39 - BST: create Linked Lists with the same depth nodes" << endl
            << "40 - BT is balanced or not" << endl
            << "41 - BST Validation" << endl
            << "42 - BT: Find the first common ancestor of the 2 nodes in BT" << endl
            << "43 - Given 2 trees, check if one of them is subtree of the other" << endl
            << "44 - Random node selection in BST w/ even probability" << endl
            << "45 - All combinations of three (1 or 2 or ) step stairs climbing" << endl
            << "46 - Towers of Hanoi (3 towers, N disks)" << endl
            << "47 - All combination of paranthesis" << endl
            << "48 - Merge 2 sorted arrays" << endl
            << "49 - Fibonacci" << endl
            << "50 - Multithreaded Producer-Consumer" << endl
            << "51 - Multithreaded Barber-Customer" << endl;

        cout << "Select a question: ";

        // Get selection input from the user
        cin >> questionSelection;

        switch (questionSelection)
        {
        case 0:
            cout << "Program ending!" << endl;
            break;
        case 1:
            FizzBuzz();
            break;
        case 2:
            TwoSum();
            break;
        case 3:
            MaxConsecutiveOnes();
            break;
        case 4:
            MaxProductofThreeNumbers();
            break;
        case 5:
            ValidParantheses();
            break;
        case 6:
            BaseballGame();
            break;
        case 7:
            ContainsDuplicate();
            break;
        case 8:
            ValidAnagram();
            break;
        case 9:
            KthLargestElement();
            break;
        case 10:
            KPairsWithSmallestSum();
            break;
        case 11:
            InvertBSTCaller();
            break;
        case 12:
            InsertionSort();
            break;
        case 13:
            MergeSortCaller();
            break;
        case 14:
            HeapSort();
            break;
        case 15:
            QuickSortCaller();
            break;
        case 16:
            BinarySearch();
            break;
        case 17:
            BreadthFirstSearch();
            break;
        case 18:
            DepthFirstSearch();
            break;
        case 19:
            UniqueCharacters();
            break;
        case 20:
            URLify();
            break;
        case 21:
            OneEditDistance();
            break;
        case 22:
            StringCompression();
            break;
        case 23:
            StringRotation();
            break;
        case 24:
            ZeroMatrix();
            break;
        case 25:
            LinkedListRemoveDuplicates();
            break;
        case 26:
            LinkedListKthLast();
            break;
        case 27:
            SumWithLinkedList();
            break;
        case 28:
            LinkedListPalindrom();
            break;
        case 29:
            LinkedListIntersection();
            break;
        case 30:
            LinkedListLoopDetection();
            break;
        case 31:
            ThreeStacksWithOneArray();
            break;
        case 32:
            StackWithMinMax();
            break;
        case 33:
            StackWithCapacity();
            break;
        case 34:
            QueueWithTwoStacks();
            break;
        case 35:
            StackSorting();
            break;
        case 36:
            LongestCommonSubsequence();
            break;
        case 37:
            GraphPathCheck();
            break;
        case 38:
            SortedArrayToMinimalBST();
            break;
        case 39:
            BSTToDepthLinkedList();
            break;
        case 40:
            IsBTBalanced();
            break;
        case 41:
            ValidateBST();
            break;
        case 42:
            BTFirstCommonAncestor();
            break;
        case 43:
            IsSubTree();
            break;
        case 44:
            RandomNodeInBST();
            break;
        case 45:
            ThreeStepStairs();
            break;
        case 46:
            TowersOfHanoi();
            break;
        case 47:
            AllCombinationOfParanthesis();
            break;
        case 48:
            MergeTwoSortedArrays();
            break;
        case 49:
            Fibonacci();
            break;
        case 50:
            ConsumerProducerCaller();
            break;
        case 51:
            BarberCustomerCaller();
            break;
        default:
            cout << "Please enter a valid input from the question list!" << endl;
            break;
        }
    }
}