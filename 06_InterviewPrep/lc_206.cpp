/*
Given: 
- The head of a singly linked list

Task:
- Reverse the list and return the reversed list

Constraints:
- The number of nodes in the list is in range [0,5000]
- -5000 < Node.val < 5000

Idea:
- Take each pointer and reverse its direction and make the tail the new head
    (1) => (2) => (3)
    (1) <= (2) <= (3)
*/

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

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;

    while(curr != nullptr) {
        Node* next = curr->next;

        curr->next = prev; // points to previous now
        prev = curr; // move prev now to current ptr
        curr = next; // move current ptr to next to reset the state
    }

    return prev;
}

int main () {

    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    head = reverseList(head);

    cout << head->data<< " " << head->next->data << " " << head->next->next->data;

    return 0;
}