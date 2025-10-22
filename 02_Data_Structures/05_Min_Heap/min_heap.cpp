#include <iostream>
#include <vector>

class MinHeap {
private:
    std::vector<int> heap;
    
    // Get parent index
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Get left child index
    int left_child(int i ) {
        return 2 * i + 1;
    }

    // Get right child index
    int right_child(int i ) {
        return 2 * i + 2;
    }

    // Move element up until heap property satisfied
    void heapify_up(int index) {
        while (index > 0 && heap[index] < heap[parent(index)]) {
            // Swap with parent
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    // Move element down until heap property satisfied
    void heapify_down(int index) {
        int size = heap.size();

        while (true) {
            int smallest = index;
            int left = left_child(index);
            int right = right_child(index);

            // Find smallest among node and its children
            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }

            // if node is smallest we're done
            if (smallest == index) {
                break;
            }

            // otherwise swap and continue
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }

    }

public:
    // Insert new element
    void push(int value) {
        heap.push_back(value);
        heapify_up(heap.size() - 1);
    }

    // Get minimmum (peek dont remove)
    int top() const {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Remove and return minimmum
    int pop() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        int min_value = heap[0];

        // Move last element to root
        heap[0] = heap.back();
        heap.pop_back();

        // Restore heap property
        if (!heap.empty()) {
            heapify_down(0);
        }
        return min_value;
    }

    int size() const {
        return heap.size();
    }

    bool empty() const {
        return heap.empty();
    }

    // Debug: print array representation
    void print() const {
        std::cout << "Heap: [";
        for (size_t i = 0; i < heap.size(); i++) {
            std::cout << heap[i];
            if (i < heap.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

int main() {
    MinHeap heap;

    // Insert
    heap.push(15);
    heap.push(10);
    heap.push(20);
    heap.push(8);
    heap.push(3);
    heap.push(12);

    heap.print();
    std::cout << "Min: " << heap.top() << "\n\n";

    // Remove elements in sorted order
    std::cout << "Popping all elements:\n";
    while (!heap.empty()) {
        std::cout << heap.pop() << " ";
    }
    std::cout << "\n";
    
    return 0;
}