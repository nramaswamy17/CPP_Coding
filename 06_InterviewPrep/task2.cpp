/*
Given: 
- Array A of size N 

Task:
- Return the smallest positive integer that is NOT in A

Constraints:
- A contains only integers

Idea:
- Can use for loop and check for each whether it's in A
    - O(n^2) time, O(1) space
- Add values of A to a set then use for loop and count up, chcking if in list
    -  O(n) time, O(n) space

Potential issues:
- What if size(A) is 0


Pseudocode:

int Solution(A)
    define set
    for i in range (len(A))
        set.insert(A[i])
    for i = 1 in range(len(A))
        if i is NOT in set
            return i
    return i + 1

main
    A = values
    int val = Solution(A)
    print(val)
*/

#include <vector>
#include <iostream>
#include <unordered_set>
#include <gtest/gtest.h>
using namespace std;

int Solution(vector<int>& A) {
    if (A.size() == 0) {
        return 1;
    }
    // Add elements of A to set
    unordered_set<int> set;
    for (int i = 0; i < A.size(); i++) {
        set.insert(A[i]);
    }

    // Check if A elements are in the set
    int i = 0;
    for (i = 1; i < A.size(); i++) {
        if (set.find(i) == set.end()) {
            // if i is NOT in the set
            return i;
        }
    }
    return i + 1;
}



int main() {
    vector<int> A = {1, 3, 6, 4, 5, 2};
    cout << Solution(A) << endl;
    return 0;
}