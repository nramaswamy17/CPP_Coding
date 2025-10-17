#include <iostream>
#include <memory>

// Simple class to demonstrate ownership
class Robot {
    
    public:
        std::string name;

    // Constructor
    Robot(std::string n) : name(n) {
        std::cout << "Robot " << name << " created\n";
    }
    
    // Destructor
    ~Robot() {
        std::cout << "Robot " << name << " destroyed\n";
    }

    void sayHello() {
        std::cout << name << " says: Hello!\n";
    }
};


void example1_basic() {
    std::cout << "\n=== Example 1: Basic Usage ===\n";

    // Create robot managed by unique_ptr
    std::unique_ptr<Robot> robot = std::make_unique<Robot>("Alpha");

    // Use it like a regular pointer with ->
    robot->sayHello();

    std::cout << "About to exit function...\n";


    // Destructor automatically called
}

void example2_manual() {
    std::cout << "\n=== Example 2: Manual Memory (Old Way) ===\n";

    Robot* robot = new Robot("Beta");
    robot->sayHello();

    delete robot; // 

    std::cout << "Exiting function\n";
}

void example3_moving() {
    std::cout << "\n=== Example 3: Moving Ownership ===\n";
    std::unique_ptr<Robot> robot1 = std::make_unique<Robot>("Gamma");
    robot1->sayHello();

    // Transfer ownership from robot1 to robot2
    std::unique_ptr<Robot> robot2 = std::move(robot1);

    // Now robot1 is empty (null)
    if (robot1 == nullptr) {
        std::cout << "robot1 is now empty\n";
    }

    // robot2 now owns the robot
    robot2->sayHello();
    
    std::cout << "About to exit function...\n";
    // robot2 will automatically delete the Robot
}

void example4_scope() {
    std::cout << "\n=== Example 4: Scope ===\n";
    std::unique_ptr<Robot> outer = std::make_unique<Robot>("Outer");
    {
        std::cout << "Entering inner scope\n";
        std::unique_ptr<Robot> inner = std::make_unique<Robot>("Inner");
        inner->sayHello();
        std::cout << "Exiting inner scope...\n";
    } // Inner PTR is destroyed HERE

    std::cout << "Back in outer scope\n";
    outer->sayHello();

    std::cout << "Exiting outer scope...\n";
} // Outer is destoryed HERE

int main() {
    std::cout << "\nProgram started\n";

    example1_basic();
    example2_manual();
    example3_moving();
    example4_scope();

    std::cout << "\nProgram ended\n";
    return 0;
}