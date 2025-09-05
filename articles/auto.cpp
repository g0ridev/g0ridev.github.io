#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;

    Node(int value) : data{value}, next{nullptr} {}
};

int main() {
    auto head = std::make_unique<Node>(1);
    head->next = std::make_unique<Node>(2);
    head->next->next = std::make_unique<Node>(3);

    // Traverse
    Node* current = head.get();
    while (current) {
        std::cout << current->data << " ";
        current = current->next.get();
    }
    std::cout << "\n";
}


#include <iostream>
#include <memory>

struct Node {
    int value;
    std::shared_ptr<Node> next;
    Node(int v) : value{v}, next{nullptr} {
        std::cout << "Node " << value << " created\n";
    }
    ~Node() {
        std::cout << "Node " << value << " destroyed\n";
    }
};

int main() {
    auto n1 = std::make_shared<Node>(1);
    auto n2 = std::make_shared<Node>(2);
    n1->next = n2;  // n2 now has 2 references: n2 variable and n1->next
    
    std::cout << "n1 ref count: " << n1.use_count() << std::endl;  // 1
    std::cout << "n2 ref count: " << n2.use_count() << std::endl;  // 2
    
    std::cout << "\n--- Destroying n1 ---\n";
    n1.reset();  // ✅ Proper way to "destroy" shared_ptr
    // or: n1 = nullptr;
    
    // n1 is now null, but Node(1) still exists because n2->next points to it
    if (n1 != nullptr) {
        std::cout << "n1 still exists: " << n1->value << std::endl;
    } else {
        std::cout << "n1 is null\n";
    }
    
    // n2 still exists and is accessible
    if (n2 != nullptr) {
        std::cout << "n2 still exists: " << n2->value << std::endl;
        std::cout << "n2 ref count: " << n2.use_count() << std::endl;  // Still 1
    }
    
    std::cout << "\n--- Destroying n2 ---\n";
    n2.reset();  // Now Node(2) will be destroyed
    
    std::cout << "\n--- End of main ---\n";
    // Node(1) will be destroyed here when n1->next goes out of scope
}


#include <iostream>
#include <vector>
#include <optional>
#include <chrono>
#include <fstream>

// Sources I used:
// https://codelucky.com/cpp-best-practices/
// https://www.learncpp.com/

int main() {
    // ## 1. Initialization styles
    int a = 5;      // copy initialization
    int b(5);       // direct initialization
    int c{5};       // list (uniform) initialization
    
    // 👉 Professional tip: prefer {} because it prevents narrowing conversions
    // int x{3.14}; // ❌ compile error, prevents narrowing
    int y = 3.14;    // ✅ compiles but silently truncates to 3

    std::cout << "a=" << a << " b=" << b << " c=" << c << " y=" << y << "\n";


    // ## 2. Use auto to reduce boilerplate
    std::vector<int> vec{1,2,3};
    auto it = vec.begin(); // cleaner than std::vector<int>::iterator
    std::cout << "First element: " << *it << "\n";


    // ## 3. Prefer smart pointers over raw pointers
    auto ptr = std::make_unique<int>(42);
    std::cout << "Smart pointer value: " << *ptr << "\n";


    // ## 4. Use optional instead of magic numbers
    auto findIndex = [](const std::string& s) -> std::optional<int> {
        if (s.empty()) return std::nullopt;
        return 0;
    };

    if (auto idx = findIndex("hello")) {
        std::cout << "Found index: " << *idx << "\n";
    }


    // ## 5. Timing with chrono
    auto start = std::chrono::steady_clock::now();
    for (volatile int i=0; i<1000000; ++i); // dummy work
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed ms: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
              << " ms\n";


    // ## 6. RAII (fstream auto-closes the file)
    {
        std::ofstream out{"data.txt"};
        out << "Hello RAII!\n";
    } // file automatically closed here
}


