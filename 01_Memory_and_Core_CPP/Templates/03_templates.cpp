#include <iostream>
#include <string>

int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

double maxDouble(double a, double b) {
    return (a > b) ? a : b; 
}

// With template - one function for all types
template <typename T>
T maximum(T a, T b)  {
    return (a > b) ? a : b;
}

void example1_function_template() {
    std::cout << "\n=== Example 1: Function Template ===\n";
    
    // Compiler generates maximum<int> automatically
    std::cout << "Max of 10 and 20: " << maximum(10, 20) << "\n";
    
    // Compiler generates maximum<double> automatically
    std::cout << "Max of 3.5 and 2.1: " << maximum(3.5, 2.1) << "\n";
    
    // Works with strings too!
    std::cout << "Max of 'apple' and 'zebra': " << maximum(std::string("apple"), std::string("zebra")) << "\n";
    
    // You can explicitly specify the type
    std::cout << "Max (explicit): " << maximum<int>(5, 8) << "\n";
}

template <typename T>
class Container {
    private:
        T* data;
        size_t size;
    public:

    Container(size_t s): size(s) {
        data = new T[size];
        std::cout << "[Container<T>] Created container of size " << size << "\n";
    }

    ~Container() {
        delete[] data;
        std::cout << "[Container<T>] Destroyed container\n";
    }

    void set(size_t index, T value) {
        if (index < size) {
            data[index] = value;
        }
    }

    // get value at index
    T get(size_t index) const {
        if (index < size) {
            return data[index];
        }
        return T();
    }

    // Print all elements
    void print() const {
        std::cout << "Container: [";
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    size_t getSize() const { 
        return size; 
    }
};

void example2_class_template() {
    std::cout << "\n=== Example 2: Class Template ===\n";

    // Container of integers
    Container<int> intContainer(5);
    for (size_t i = 0; i < intContainer.getSize(); i++) {
        intContainer.set(i, i * 10);
    }
    intContainer.print();

    // Container of doubles
    Container<double> doubleContainer(3);
    doubleContainer.set(0, 3.14);
    doubleContainer.set(1, 2.71);
    doubleContainer.set(2, 1.41);
    doubleContainer.print();
    
    // Container of strings
    Container<std::string> stringContainer(3);
    stringContainer.set(0, "Hello");
    stringContainer.set(1, "World");
    stringContainer.set(2, "!");
    stringContainer.print();

}

int main() {
    example1_function_template();
    example2_class_template();
    
    std::cout << "\n=== Program Ending ===\n";
    return 0;
}