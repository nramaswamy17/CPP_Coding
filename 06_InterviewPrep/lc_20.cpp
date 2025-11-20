/*
Given:
- String s containing characters 
    - '(', ')', '{', '}', '[' and ']'

Task:
- Determine if the string is valid

Constraints:
- Every bracket must be closed by the same type of bracket
- Open bracket must be closed in the correct order
- Every close bracket has a corresponding open bracket of the same type

Idea:
- Could use two-pointer system. 
- Could use a map but this does not resolve the order issue. 
    - Use a queue also? 
- Can we break this into open and close type?

- Okay what we should use here is a queue. 
    - the queue will maintain order of operations
    - we also store the close version of the open bracket

Case:
    if I have a close bracket and it does not match the queue's top close equivalent, return false. 

OOps, this should be a STACK not QUEUE

Pseudocode:

isValidParentheses(string s) 
    if s.size <= 1
        return false
    define stack st
    define set open
    define set close
    define map open_close
    map open and close to correct symbols

    for char c in s
        if st.size == 0
            if c is type open
                st.push(c)
            else
                return false
        else
            if c is type open 
                st.push(c)
            else
                open_symbol = st.front()
                st.pop()
                if c and open_symbol do not match
                    return false
    if st.size() > 0
        return false
    return true

*/

#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

bool isValidParentheses(string s) {
    if (s.size() <= 1) {
        return false;
    }
    stack<char> st;
    unordered_set<char> open = {'(', '{', '['};
    unordered_set<char> close = {')', '}', ']'};
    unordered_map<char,char> map = {{'{','}'},
                                    {'(',')'},
                                    {'[',']'}};
    
    for (char c : s) {
        
        if (open.find(c) != open.end()) {
            // if type open
            st.push(c);
            cout << "PUSH: " << c << endl;
        } else {
            // if type close
            if (st.size() == 0) {
                // if stack is empty
                cout << "Stack is empty and " << c << " is type close, returning false" << endl;
                return false;
            }
            cout << "POP: " << c << endl;
            char open_symbol = st.top();
            st.pop();
            if (map[open_symbol] != c) {
                cout << "Open symbol does not match close " << map[open_symbol] << ", " << c << endl;
                return false;
            }
        }
    }
    if (st.size() > 0) {
        return false;
    }
    return true;
}

int main() {
    string s = "([)]";
    //s = "()[]{}";
    cout << isValidParentheses(s) << endl;
    return 0;
}