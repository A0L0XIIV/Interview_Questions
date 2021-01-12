/*
* Baran Kaya
* 2020
*/

//#include <iostream> Coming from .h files
#include <algorithm>
#include <cstdlib>
#include <ctype.h>
#include <limits>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <windows.h> // Sleep

#include "BinarySearchTree.h"
#include "LinkedList.h"

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
void invertBSTCaller();
void insertionSort();
void mergeSort(vector<int> & array, int p, int r);
void merge(vector<int> & array, int p, int q, int r);
void mergeSortCaller();
void heapSort();
void quickSort();
void quickSortCaller();
void binarySearch();
void breadthFirstSearch();
void depthFirstSearch();
void UniqueCharacters();
void URLify();
void OneEditDistance();
void StringCompression();
void ZeroMatrix();
void StringRotation();
void LinkedListRemoveDuplicates();
void LinkedListKthLast();

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
        << "23 - Zero Matrix: Change row and column to zero" << endl
        << "24 - String Rotation check: battle vs ttleba" << endl
        << "25 - Remove Duplications in LinkedList" << endl
        << "26 - Kth last element in the LinkedList" << endl;

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
            invertBSTCaller();
            break;
        case 12:
            insertionSort();
            break;
        case 13:
            mergeSortCaller();
            break;
        case 14:
            heapSort();
            break;
        case 15:
            quickSortCaller();
            break;
        case 16:
            binarySearch();
            break;
        case 17:
            breadthFirstSearch();
            break;
        case 18:
            depthFirstSearch();
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
            ZeroMatrix();
            break;
        case 24:
            StringRotation();
            break;
        case 25:
            LinkedListRemoveDuplicates();
            break;
        case 26:
            LinkedListKthLast();
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

void invertBST(BSTNode<int>* node) {
    // Base case
    if (node == nullptr)
        return;
    // Swap left and right children
    BSTNode<int>* temp = node->getLeftChild();
    node->updateLeft(node->getRightChild());
    node->updateRight(temp);
    // Call left child
    if (node->getLeftChild() != nullptr) {
        invertBST(node->getLeftChild());
    }
    // Call right child
    if (node->getRightChild() != nullptr) {
        invertBST(node->getRightChild());
    }
}

void invertBSTCaller() {
    // Description of the problem
    // Inverting BST instead of BT is not logical but I only coded BST implementation, so I inverted BST.
    cout << "Invert the given binary (search) tree." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a BST from the vector
    BST<int>* bst = new BST<int>(arr);

    cout << endl << "Before invertion print tree: ";
    bst->printTree();

    invertBST(bst->getRoot());

    cout << endl << "After invertion print tree: ";
    bst->printTree();
}

void insertionSort() { 
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

void mergeSortCaller() {
    // Description of the problem
    cout << "Merge sort algoritm. Create a new array and it will print the sorted result." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    // Sorted array
    mergeSort(arr, 0, arrSize-1);

    cout << "Sorted array: ";
    // Print sorted array
    for (int element : arr) {
        cout << element << " - ";
    }
}

void mergeSort(vector<int> & array, int p, int r) {
    if (p < r) {
        // Middle element.s index
        int q = ceil((p + r) / 2);
        // Recusrion for first and second halves
        mergeSort(array, p, q);
        mergeSort(array, q + 1, r);
        // Merge 2 halves
        merge(array, p, q, r);
    }
}

void merge(vector<int> & array, int p, int q, int r) {
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

void heapSort() {
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

void quickSortCaller() {
    // Description of the problem
    cout << "Quick sort algoritm. Create a new array and it will print the sorted result." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();

    // Sorted array
    //quickSort(arr, 0, arrSize - 1);

    cout << "Sorted array: ";
    // Print sorted array
    for (int element : arr) {
        cout << element << " - ";
    }
}

void quickSort() { }

void binarySearch() {
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

void breadthFirstSearch() {
    // Description of the problem
    cout << "Breadth First Search algorithm. Create a new Binary Search Tree, select value for search. It will show the search results." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();
    cout << "Enter a value to search in the array: ";
    int searchValue = 0;
    cin >> searchValue;
    bool found = false;

    // Create a BST from the vector
    BST<int>* bst = new BST<int>(arr);
    // Array for storing node's discovered state (NOT NECESSARY FOR BST)
    vector<bool> discovered(arrSize, false);
    // Queue for BFS operations
    queue<BSTNode<int>*> q;
    q.push(bst->getRoot());
    BSTNode<int>* temp = nullptr;

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

void depthFirstSearch() {
    // Description of the problem
    cout << "Depth First Search algorithm. Create a new Binary Search Tree, select value for search. It will show the search results." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    int arrSize = arr.size();
    cout << "Enter a value to search in the array: ";
    int searchValue = 0;
    cin >> searchValue;
    bool found = false;

    // Create a BST from the vector
    BST<int>* bst = new BST<int>(arr);
    // Array for storing node's explored state (NOT NECESSARY FOR BST)
    vector<bool> explored(arrSize, false);
    // Stack for DFS operations
    stack<BSTNode<int>*> s;
    s.push(bst->getRoot());
    BSTNode<int>* temp = nullptr;

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

        // O(n^2) loop solution, sort two strings and check pairs
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

            for (char c : testString) {
                // If set contains the same value, uniqueness break
                if (charSet.insert(c).second == false) {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                cout << testString << "'s all characters are unique." << endl << endl;
            else
                cout << testString << " has non-unique characters." << endl << endl;
        }        
        // Neither O(logn) nor O(n) solution selected
        else {
            cout << "Incorrect solution selection!" << endl;
        }

        return;
    }
};

void URLify() {
    // Description of the problem
    cout << "Change space \" \" characters to \"%20\" in a given string." << endl;
    
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
                newString[n] == urlString[o];
            }
            --n;
        }

        cout << "New URL string: " << newString << " created from: " << urlString << endl << endl;
    }

    return;
};

void OneEditDistance() {

};

void StringCompression() {};

void ZeroMatrix() {};

void StringRotation() {};

void LinkedListRemoveDuplicates() {
    // Description of the problem
    cout << "Remove duplicates in a given linked list." << endl;

    // Get array values from user
    vector<int> arr = getArrayInput<int>();
    // Create a LinkedList from a vector
    LinkedList<int>* ll = new LinkedList<int>(arr);

    cout << endl << "LinkedList: ";
    ll->printLinkedList();

    set<int> uniqueValues;
    Node<int>* current = ll->head;
    Node<int>* previous = nullptr;

    while(current){
        // Check current node's value bu adding in set
        if (uniqueValues.insert(current->getValue()).second == false) { 
            // Same value already exist in the set, remove the current
            // Set previous node's next to current's next
            previous->setNext(current->getNext());
            // Delete current node
            delete current;
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
    LinkedList<int>* ll = new LinkedList<int>(arr);

    cout << endl << "LinkedList: ";
    ll->printLinkedList();

    Node<int>* slow = ll->head;
    Node<int>* fast = ll->head;
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
