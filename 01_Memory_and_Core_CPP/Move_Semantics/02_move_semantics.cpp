// Move semantics - instead of copying data, "steal it" from objects we don't need anymore
#include <iostream>
#include <vector>
#include <cstring>

// Simple dynamic array class to demonstrate move semantics
class DynamicArray {
    private:
        int* data;
        size_t size;

    public:
    // Constructor
    DynamicArray(size_t s) : size(s) {
        data = new int[size];
        std::cout << "[CONSTRUCTOR] Created array of size " << size << "\n";

        // fill with values
        for (size_t i = 0; i < size; i++) {
            data[i] = i * 10;
        }
    }

    ~DynamicArray() {
        if (data != nullptr) {
            std::cout << "[DESTRUCTOR] Deleting array of size " << size << "\n";
            delete[] data;
        }
    }

    // Copy constructor - makes a full copy (SLOW for large data)
    DynamicArray(const DynamicArray& other) : size(other.size) {
        std::cout << "[COPY CONSTRUCTOR] Copying array of size " << size << "\n";
        data = new int[size];

        // copy all elements
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    DynamicArray(DynamicArray&& other) noexcept : size(other.size) {
        std::cout << "[MOVE CONSTRUCTOR] Moving array of size " << size << "\n";

        // Steal the data pointer
        data = other.data;

        // Leave the other obj in valid but empty state
        other.data = nullptr;
        other.size = 0;
    }
    
    // Copy - makes full copy
    DynamicArray& operator = (const DynamicArray& other) {
        std::cout << "[COPY ASSIGNMENT] Copying array of size " << other.size << "\n";
        
        // delete old data
        if (this != &other) { // if we are not looking at ourseleves
            delete[] data;
        
            // copy new data
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Move - steals data
    DynamicArray& operator = (DynamicArray&& other) noexcept {
        std::cout << "[MOVE ASSIGNMENT] Moving array of size " << other.size << "\n";
        
        if (this != &other) { // if we are not looking at ourseleves
            // Clean up old data
            delete[] data;

            // Steal data
            data = other.data;
            size = other.size;

            // Leave other in valid state
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void print() const {
        std::cout << "Array [size=" << size << "]: ";
        for (size_t i = 0; i < size && i < 5; i++) {  // Print first 5 elements
            std::cout << data[i] << " ";
        }
        if (size > 5) std::cout << "...";
        std::cout << "\n";
    }
};

void example1_copy_vs_move() {
    std::cout << "\n=== Example 1: Copy vs Move ===\n";

    DynamicArray arr1(5);
    arr1.print();

    // Copy - slow
    std::cout << "\nMaking a copy:\n";
    DynamicArray arr2 = arr1;
    arr2.print();

    // Move - fast
    std::cout << "\nMoving:\n";
    DynamicArray arr3 = std::move(arr1);
    arr3.print();

    std::cout << "\nNote: arr1 is now empty after move\n";
}

DynamicArray createLargeArray() {
    DynamicArray temp(1000);
    std::cout << "Returning from function...\n";
    return temp; // Compiler automatically runs Move to the destination array
}

void example2_return_value() {
    std::cout << "\n=== Example 2: Returning from Function ===\n";
    DynamicArray result = createLargeArray();
    std::cout << "Got result\n";
}

void example3_containers() {
    std::cout << "\n=== Example 3: Moving in Vectors ===\n";
    
    std::vector<DynamicArray> vec;

    std::cout << "Creating array:\n";
    DynamicArray arr(3);

    std::cout << "\nPushing without move (copy):\n";
    //vec.push_back(arr);

    std::cout << "Pushing with move:\n";
    vec.push_back(std::move(arr)); // Moves instead of copy
    
    
    std::cout << "\nVector now owns the array\n";
}

// Example 4: When NOT to use move
void example4_when_not_to_move() {
    std::cout << "\n=== Example 4: When NOT to Use Move ===\n";
    
    DynamicArray arr(3);
    arr.print();
    
    // DON'T do this - you still need arr later!
    // DynamicArray arr2 = std::move(arr);  
    // arr.print();  // DANGER - arr is now empty!
    
    // DO this - copy when you need both
    DynamicArray arr2 = arr;  // Copy
    std::cout << "Original: ";
    arr.print();
    std::cout << "Copy: ";
    arr2.print();
}

int main() {
    example1_copy_vs_move();
    example2_return_value();
    example3_containers();
    example4_when_not_to_move();
    
    std::cout << "\n=== Program Ending ===\n";
    return 0;
}