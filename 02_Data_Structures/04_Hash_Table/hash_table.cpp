#include <iostream> 
#include <vector>
#include <list>
#include <string>

class HashTable {
private:
    static const int SIZE = 10;

    // Each bucket holds a list of key-value pairs
    struct Entry {
        std::string key;
        int value;
    };

    std::vector<std::list<Entry>> table; // Array of lists

    // Simple hash: sum ascii values % size
    int hash(const std::string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % SIZE;
    }

public:
    HashTable() : table(SIZE) {}

    // Add or update
    void put(const std::string& key, int value) {
        int index = hash(key);

        // if key exists, update it
        for (auto& entry: table[index]) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }

        // Key doesn't exist, add it
        table[index].push_back({key, value}); // Enables chaining
    }

    // Find value by key
    int get(const std::string& key) {
        int index = hash(key);

        // Search the list at this index
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        return -1; // Not found
    }

    // See what's in each bucket
    void print() {
        for (int i = 0; i < SIZE; i++) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& entry : table[i]) {
                std::cout << "[" << entry.key << ":" << entry.value << "] ";
            }
            std::cout << "\n";
        }
    }
};


int main() {
    HashTable scores;

    // Insert scores
    scores.put("alice", 95);
    scores.put("bob", 87);
    scores.put("charlie", 92);
    scores.put("alice", 98);  // Update alice

    // Collision
    scores.put("obb", 75);     // Same hash as bob!

    // Lookup
    std::cout << "Alice's score: " << scores.get("alice") << "\n";
    std::cout << "Bob's score: " << scores.get("bob") << "\n";
    std::cout << "David's score: " << scores.get("david") << "\n";  // -1
    
    std::cout << "\nTable contents:\n";
    scores.print();
    
    return 0;
}