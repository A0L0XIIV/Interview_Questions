/*
* Baran Kaya
* 2020
*/

#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <limits>
#include <algorithm>

#include "BinarySearchTree.h";

using namespace std;

// Function prototypes
template <typename T>
vector<T> getArrayInput();
bool is_digit(string);
void fizzBuzz();
void twoSum();
void maxConsecutiveOnes();
void maxProductofThreeNumbers();
void validParanthesis();
void baseballGame();
void containsDuplicate();
void validAnagram();
void kthLargestElement();
void kPairsWithSmallestSum();
void invertBST();

int main()
{
    // Selection of the question
    int questionSelection = 1;

    while (questionSelection) {
        cout << "This program consits of several interview questions and their solutions/implementations in C++. List of questions given below. Enter 0 to end the program." << endl;
        cout << "Questions list:" << endl;

        cout << "1 - FizzBuzz" << endl;
        cout << "2 - Two Sum" << endl;
        cout << "3 - Max Consecutive Ones" << endl;
        cout << "4 - Max Product of Three Numbers in an array" << endl;
        cout << "5 - Valid Paranthesis" << endl;
        cout << "6 - Baseball Game" << endl;
        cout << "7 - Contains Duplicate" << endl;
        cout << "8 - Valid Anagram" << endl;
        cout << "9 - Kth Largest Element" << endl;
        cout << "10 - K Pairs with Smallest Sum" << endl;
        cout << "11 - Invert a Binary Search Tree" << endl;

        cout << "Select a question: ";
        // Get selection input from the user
        cin >> questionSelection;
        switch (questionSelection)
        {
        case 0:
            cout << "Program ending!" << endl;
            break;
        case 1:
            fizzBuzz();
            break;
        case 2:
            twoSum();
            break;
        case 3:
            maxConsecutiveOnes();
            break;
        case 4:
            maxProductofThreeNumbers();
            break;
        case 5:
            validParanthesis();
            break;
        case 6:
            baseballGame();
            break;
        case 7:
            containsDuplicate();
            break;
        case 8:
            validAnagram();
            break;
        case 9:
            kthLargestElement();
            break;
        case 10:
            kPairsWithSmallestSum();
            break;
        case 11:
            invertBST();
            break;
        default:
            cout << "Please enter a valid input from the question list!" << endl;
            break;
        }
    }
}

template <typename T>
vector<T> getArrayInput() {
    // Get array/vector size from user
    int arrSize = 0;
    cout << "Enter size of the array: ";
    cin >> arrSize;

    // Get array values from user
    vector<T> arr(0);
    T tempInput;
    cout << "Enter the array elements." << endl;
    for (int i = 0; i < arrSize; ++i) {
        cout << to_string(i) + "th: ";
        cin >> tempInput;
        arr.push_back(tempInput);
    }

    return arr;
}

bool is_digits(const string& str){
    return str.find_first_not_of("-0123456789") == string::npos;
    //return all_of(str.begin(), str.end(), ::isdigit); // C++11
}

void fizzBuzz() {
    // Description of the problem
    cout << "Print numbers from 1 to x. If the number is divisible by 3, replace it with \"Fizz\". If it is divisible by 5, replace it with \"Buzz\". If it is divisible by 3 and 5 replace it with \"FizzBuzz\"." <<endl;

    // integer for user input
    int userNumber = 0;
    string printResults = "";

    cout << endl << "- Enter the number for FizzBuzz:";
    cin >> userNumber;

    if (userNumber < 1 || userNumber > INT_MAX)
        cout << "ERROR: Please enter valid number! Between 1 and " + to_string(INT_MAX) << endl;
    else {
        for (int i = 1; i <= userNumber; ++i) {
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

        cout << printResults << endl;
    }
}

void twoSum() {
    // Description of the problem
    cout << "Given an array of integers, return indices of the two numbers such that they add up to a specific target." << endl;

    // Get target integer from user
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
    cout << "Enter 1 for O(n^2) solution, 2 for O(logn) solution." << endl;
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

    // O(logn) solution, sort the array, try to find closest numbers
    else if (solutionSelection == 2) {
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
    // Neither O(n^2) nor O(logn) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void maxConsecutiveOnes() {
    // Description of the problem
    cout << "Given an array of 0s and 1s (binary), return the number of max consecutive ones. For example; [1,1,1,0,1,1] --> return 3." << endl;

    // Get array values from user

    vector<bool> arr = getArrayInput<bool>();
    int arrSize = arr.size();

    // O(n) solution
    int maxOnes = INT_MIN;

    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] == 1) {
            for (int j = i; j < arrSize; ++j) {
                if (arr[j] == 0) {
                    if(maxOnes < j-i)
                        maxOnes = j - i;
                    i = j;
                    break;
                }
            }
        }
    }

    if (maxOnes > 0)
        cout << "# max consecutive ones: " + to_string(maxOnes) << endl;

}

void maxProductofThreeNumbers(){
    // Description of the problem
    cout << "Given an array of integers, print the product of 3 max integers. For example; [1,2,3,4] --> 2*3*4=24" << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(n^3) solution, 2 for O(logn) solution, and 3 for O(n) solution." << endl;
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

    // O(logn) solution, sort the array and multiply max and min
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

        for (int i : arr) {
            // Find 3 maximum
            if (i >= max3) {
                max1 = max2;
                max2 = max3;
                max3 = i;
            }
            else if (i >= max2) {
                max1 = max2;
                max2 = i;
            }
            else if (i >= max1) {
                max1 = i;
            }
            // Find 2 minimum
            if (i <= min1) {
                min2 = min1;
                min1 = i;
            }
            else if (i <= min2) {
                min2 = i;
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

    // Neither O(n^2) nor O(logn) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void validParanthesis() {
    // Description of the problem
    cout << "Given an array of paranthesis check its validness. Every opening parathesis must have one closing paranthesis!" << endl;

    // Get array values from user
    cout << "Array should only consist of ( and ) characters!" << endl;
    vector<char> arr = getArrayInput<char>();
    int arrSize = arr.size();

    // Size of the array is not even, not valid
    if (arrSize % 2 != 0) {
        cout << "Not Valid: Array size is not even." << endl;
    }

    // Use stack for validness
    stack<char> paranthesisStack;

    // Loop over every element in the array
    for (char element : arr) {
        // Opening paranthesis, push something to the stack
        if (element == '(') {
            paranthesisStack.push('x');
        }
        // Closing paranthesis, pop last pushed characters
        else if (element == ')' && !paranthesisStack.empty()) {
            paranthesisStack.pop();
        }
        // Closing paranthesis but stack is empty, error
        else {
            cout << "Not Valid: There is a closing paranthesis without opening paranthesis." << endl;
            break;
        }
    }

    if (paranthesisStack.empty()) {
        cout << "Valid: All paranthesis matched." << endl;
    }
    else {
        cout << "Not Valid: There is/are opening paranthesis that didn't close." << endl;
    }

}

void baseballGame() {
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

    // Loop over the array
    for (string element : arr) {
        // Digit, push to stack
        if (is_digits(element)) {
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

void containsDuplicate(){
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
    // Could add O(logn) solution with sorting and paired (value, unsorted index) vectors
    // O(n) solution, use hash maps
    else if (solutionSelection == 2) {
        map<int, int> hashMap;
        // Loop over all elements
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
    // Neither O(n^2) nor O(logn) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }

}

void validAnagram(){
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
        cout << "Enter 1 for O(logn) sorting solution, 2 for O(n) hash map solution." << endl;
        cin >> solutionSelection;

        // Brute force O(n^2) solution, check two arrays' every pairs, then delete same letters

        // O(logn) solution, sort two strings and check pairs
        if (solutionSelection == 1) {
            // Sort 2 strings
            sort(firstWord.begin(), firstWord.end());
            sort(secondWord.begin(), secondWord.end());
            bool validAnagram = true;
            // Check every index
            for (int i = 0; i < firstWord.size(); ++i) {
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

            // Loop over every letter in the first word
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

            // Second, loop over second word and decrease each letters counter
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
        // Neither O(logn) nor O(n) solution selected
        else {
            cout << "Incorrect solution selection!" << endl;
        }
    }
}

void kthLargestElement(){
    // Description of the problem
    cout << "Find the Kth largest element in the given array." << endl;

    // Get the k
    int k = 0;
    cout << "Enter a value for k: ";
    cin >> k;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    int solutionSelection = 0;
    // Problem has several solutions, choose one
    cout << "Enter 1 for O(nlogn) sorting solution, 2 for O(nlogk) min heap solution." << endl;
    cin >> solutionSelection;

    // O(nlogn) solution, sort the array and get Kth element
    if (solutionSelection == 1) {
        // Sort the array
        sort(arr.begin(), arr.end());

        // Print the result
        cout << "Kth largest element in the given array: " << arr[arrSize - k] << endl;
    
    }
    // O(nlogk) solution, use min heaps
    else if (solutionSelection == 2) {
        // Convert vector array to MIN HEAP with STL priority_queue
        priority_queue <int, vector<int>, greater<int>> minHeap;
        // Loop over array's elements
        for (int element : arr) {
            // Heap only has k elements because we only need kth element, push first k element into heap
            if (minHeap.size() < k) {
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
    // Neither O(nlogn) nor O(nlogk) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }
}

void kPairsWithSmallestSum() {
    // Description of the problem
    cout << "Given 2 different arrays, find the k pairs that have smallest sum value." << endl;
    cout << "For example: u=[1,7,11] and v=[2,4,6], results are= [1,2], [1,4] and [1,6]." << endl;

    // Get the k
    int k = 0;
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
    cout << "Enter 1 for O(n^2*logn) naive solution, 2 for O(n^2*logn) max heap solution." << endl;
    cin >> solutionSelection;

    // Combination array with all sums, size = arr1Size * arr2Size
    vector<pair<int, int>> pairArray;

    // Loop over the first array
    for (int element1 : arr1) {
        // Loop over the second array
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
        for (int i = 0; i < k; ++i) {
            cout << "- [" << pairArray[i].first << ',' << pairArray[i].second << ']' << endl;
        }
    }
    // O(n^2*logn) solution, use k sized max heaps
    else if (solutionSelection == 2) {
        // Create a new max heap with lambda comparison function
        // Heap will only store k min summed pairs
        priority_queue <pair<int, int>, vector<pair<int, int>>, auto(*)(pair<int, int>, pair<int, int>)->bool> maxHeap{
            // Using lambda function to compare pair elements sum
            [](pair<int, int> a, pair<int, int> b)->bool { return (a.first+a.second) < (b.first+b.second); }
        };
        // Loop over pair array
        for (pair<int, int> p : pairArray) {
            // If the heap is empty, push new pairs to heap
            if (maxHeap.size() < k) {
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
        for (int i = 0; i < k; ++i) {
            cout << "- [" << maxHeap.top().first << ',' << maxHeap.top().second << ']' << endl;
            maxHeap.pop();
        }
    }
    // Neither O(n^2*logn) nor O(n^2*logn) solution selected
    else {
        cout << "Incorrect solution selection!" << endl;
    }

}

void invertBST() {
    // Description of the problem
    cout << "Invert the given binary search tree." << endl;

    // Create a new BST
    BST* bst = new BST();

    // Get new node data from user to fill the tree
    while (true) {
        // TO DO
    }

}