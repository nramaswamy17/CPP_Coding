/*
Given:
- head (ptr to head of linked list)

Task: 
- Determine if a cycle exists (reference from node in the list back to the list again)

Idea: 
- Iterate through list, for each node check if itself can be reached from its next node. (SLOW but O(c) space)
- Iterate through linked list, store memory locations of each node in a map. Check each new node against the map (FAST but O(n) space)
- Same as last one but use unordered set since we don't actually care about any values
- Use 2 pointers, one going faster and the other going slower. If they ever meet then you know there's a cycle. (FAST AND O(c) space)


Pseudocode

struct Node
    int data
    Node* next

    Node(int val)
        data = val
        next = nullptr

bool isCycle (head)
    define set (unordered set) of type Node*

    Node* current = head
    while current is not null
        if (current is in set) 
            return True
        add current to set
        current = current->next
    return False


*/

#include <unordered_set>
#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Uses O(n) space
bool isCycle_set(Node* head) {
    Node* current = head;
    unordered_set<Node*> set;

    while(current != nullptr) {
        if(set.find(current) != set.end()) {
            return true;
        }
        set.insert(current);
        current = current->next;
    }
    return false;
}

// Uses O(c) space
bool isCycle_ptr(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }
    return false;
}

int main() {

    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = head->next; // cycles back to 2

    cout << isCycle_ptr(head) << endl;

    return 0;
}