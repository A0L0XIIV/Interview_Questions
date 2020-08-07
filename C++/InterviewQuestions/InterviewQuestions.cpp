﻿/*
* Baran Kaya
* 2020
*/

#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <limits>
#include <algorithm>

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

void containsDuplicate(){}

void validAnagram(){}

void kthLargestElement(){}