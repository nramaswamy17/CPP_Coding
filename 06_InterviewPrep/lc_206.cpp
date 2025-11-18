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