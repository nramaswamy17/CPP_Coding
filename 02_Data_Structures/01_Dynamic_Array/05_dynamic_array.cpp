#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class DynamicArray {
    private:
        T* data; // pointer to array on heap
        size_t capacity; // total allocated space
        size_t size; // number of elements currently stored
    public:

    // Constructor 
    DynamicArray() : data(nullptr), capacity(0), size(0) {
        std::cout << "[CONSTRUCTOR] Created empty array\n";
    }

    ~DynamicArray() {
        delete[] data;
        std::cout << "[DESTRUCTOR] Destroyed array\n";
    }

    // Copy constructor
    DynamicArray(const DynamicArray& other) : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; i++){
            data[i] = other.data[i];
        }
        std::cout << "[COPY] Copied array\n";
    }

    // Copy assignment
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != other) {
            delete[] data; 

            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];

            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Add element to end (most important method!)
    void push_back(const T& value) {
        if (size >= capacity) {
            // Need to resize!
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2; // double each time  to make fewer resize calls
            resize(newCapacity);
        }

        data[size] = value;
        size++;
    }

    // Remove last element
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    // Access element at index
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // Safe access with bounds checking
    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Get current size
    size_t getSize() const {
        return size;
    }

    // Get current capacity
    size_t getCapacity() const {
        return capacity;
    }

    // Check if empty
    bool empty() const {
        return size == 0;
    }

    // clear all elements
    void clear() {
        size = 0;
    }

    // Print array
    void print() const {
        std::cout << "Array [size=" << size << ", capacity=" << capacity << "]: ";
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }

    private:
        // Resize internal array
        void resize(size_t newCapacity) {
            std::cout << " [RESIZE] " << capacity << " -> " << newCapacity << "\n";

            // Allocate new larger array
            T* newData = new T[newCapacity];
        
            // Copy existing elements
            for (size_t i = 0; i < size; i++){
                newData[i] = data[i];
            }
        
            // delete old array
            delete[] data;

            // Update to new array
            data = newData;
            capacity = newCapacity;
        }
};


void example1_basic_usage() {
    std::cout << "\n=== Example 1: Basic Usage ===\n";

    DynamicArray<int> arr;

    std::cout << "\nAdding elements:\n";

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.print();

    std::cout << "\nAccessing elements:\n";
    std::cout << "arr[0] = " << arr[0] << "\n";
    std::cout << "arr[1] = " << arr[1] << "\n";
    
    std::cout << "\nModifying element:\n";
    arr[1] = 99;
    arr.print();

}

void example4_operations() {
    std::cout << "\n=== Example 4: Various Operations ===\n";
    
    DynamicArray<int> arr;

    std::cout << "Is empty? " << (arr.empty() ? "yes" : "no") << "\n";
    
    arr.push_back(5);
    arr.push_back(10);
    arr.push_back(15);
    arr.print();

    std::cout << "\nPopping the last element:\n";
    arr.pop_back();
    arr.print();

    std::cout << "\nClearing array:\n";
    arr.clear();
    arr.print();
    std::cout << "Is empty? " << (arr.empty() ? "yes" : "no") << "\n";
}

void example5_comparison_with_vector() {
    std::cout << "\n=== Example 5: How It Compares to std::vector ===\n";

    // My implementation
    DynamicArray<int> myArray;
    myArray.push_back(1);
    myArray.push_back(2);
    myArray.push_back(3);

    std::cout << "My array: ";
    myArray.print();

    // std::vector
    std::vector<int> stdVector;
    stdVector.push_back(1);
    stdVector.push_back(2);
    stdVector.push_back(3);

    std::cout << "std::vector: ";
    for (int val : stdVector) {
        std::cout << val << " ";
    }
    std::cout << "\n";

}

int main() {
    example1_basic_usage(); 
    example4_operations();
    example5_comparison_with_vector();
    
    std::cout << "\n=== Program Ending ===\n";
    return 0;
}