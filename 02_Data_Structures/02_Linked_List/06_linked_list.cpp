#include <iostream>

// Node structure - building block
template <typename T>
struct Node {
    T data;
    Node* next;

    // Constructor
    Node(const T& value) : data(value), next(nullptr) {
        std::cout << "  [NODE CREATED]  " << data << "\n";
    }

    // Destructor
    ~Node() {
        std::cout << "  [NODE DELETED]  " << data << "\n";
    }
};

// Singly linked list
template <typename T>
class LinkedList {
private:
    Node<T>* head; // Pointer to first node
    Node<T>* tail; // Pointer to last node (for push_back)
    size_t size;
public:

    // Constructor
    LinkedList() : head(nullptr), tail(nullptr), size(0) {
        std::cout << "[CONSTRUCTOR] Created empty linked list\n";
    }
    
    // Destructor - must delete all nodes!
    ~LinkedList() {
        std::cout << "[DESTRUCTOR] Deleting linked list...\n";
        clear();
    }

    // Add element to front O(1)
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if(head == nullptr) {
            // Empty list
            head = tail = newNode;
        }
        else {
            // Add to front
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    // Add element to back - O(1) with tail pointer
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (tail == nullptr) {
            // Empty list
            head = tail = newNode;
        } else {
            // Add to end
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // remove from front - O(1)
    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node<T>* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr; // list is empty
        }

        delete temp; // remove ptr to prevent leak
        size--;
    }

    void insert(size_t index, const T& value) {
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index >= size) {
            push_back(value);
            return;
        }

        // Find node before insertion point
        Node<T>* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        // Insert new node
        Node<T>* newNode = new Node<T>(value);
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    void remove(size_t index) {
        if (index >= size || head == nullptr) {
            return;
        }

        if (index == 0) {
            pop_front();
            return;
        }

        // Find node before deletion point
        Node<T>* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        // Delete node
        Node<T>* temp = current->next;
        current->next = temp->next;

        if (temp == tail) {
            tail = current;
        }

        delete temp;
        size--;
    }

    // Access element at index O(n)
    T& at(size_t index) {
        Node<T>* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Get first element
    T& front() {
        return head->data;
    }

    // Get last element
    T& back() {
        return tail->data;
    }

    // Get size
    size_t getSize() const {
        return size;
    }

    // Check if empty
    bool empty() const {
        return head == nullptr;
    }

    // Clear all nodes
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    // Print list
    void print() const {
        std::cout << "List [size=" << size << "]: ";
        Node<T>* current = head;
        while(current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << "\n";
    }
    
    // Print with memory addresses (helpful for understanding)
    void printDetailed() const {
        std::cout << "List [size=" << size << "]:\n";
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            std::cout << "  [" << index << "] data=" << current->data 
                      << ", next=" << current->next << "\n";
            current = current->next;
            index++;
        }
    }
};

void example1_basic_operations() {
    std::cout << "\n=== Example 1: Basic Operations ===\n";

    LinkedList<int> list;
    std::cout << "\nPushing to back:\n";
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.print();

    std::cout << "\nPushing to front:\n";
    list.push_front(5);
    list.print();

    std::cout << "\nAccessing elements:\n";
    std::cout << "Front: " << list.front() << "\n";
    std::cout << "Back: " << list.back() << "\n";
    std::cout << "At index 2: " << list.at(2) << "\n";

}

void example2_insertion_deletion() {
    std::cout << "\n=== Example 2: Insertion & Deletion ===\n";
    
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(40);
    list.push_back(50);
    
    std::cout << "Original list:\n";
    list.print();
    
    std::cout << "\nInserting 30 at index 2:\n";
    list.insert(2, 30);
    list.print();
    
    std::cout << "\nRemoving element at index 1:\n";
    list.remove(1);
    list.print();
    
    std::cout << "\nPopping from front:\n";
    list.pop_front();
    list.print();
}

void example4_memory_visualization() {
    std::cout << "\n=== Example 4: Memory Visualization ===\n";
    
    LinkedList<int> list;
    list.push_back(100);
    list.push_back(200);
    list.push_back(300);
    
    std::cout << "\nDetailed view (see memory addresses):\n";
    list.printDetailed();
    
}

int main() {
    example1_basic_operations();
    example2_insertion_deletion();
    example4_memory_visualization();
    
    std::cout << "\n=== Program Ending ===\n";
    return 0;
}