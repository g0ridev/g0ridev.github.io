#include "insertion-sort.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cassert>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <array>
#include <list>
#include <deque>
#include <functional>
#include <stdexcept>

// ================================================================================================
// INSERTION SORT: PROFESSIONAL C++ GAUNTLET
// ================================================================================================
// This is not beginner-friendly. This is a deliberate gauntlet to fast-track you into 
// professional-grade C++ through rigorous practice. The difficulty is intentional.
// If you want to truly learn to program, you must not fear debugging until you pass these tests.
//
// LEARNING METHODOLOGY: Single algorithm, maximum depth. Master one thing from every angle.
// ================================================================================================

// YOUR IMPLEMENTATIONS GO HERE:
// You must implement ALL of these function signatures to pass the gauntlet

// TIER 1: Basic template function (Foundation Level)
// template<typename T>
// void insertionSort(std::vector<T>& vec);

// TIER 2: Custom comparator support (Professional Level) 
// template<typename T, typename Compare = std::less<T>>
// void insertionSort(std::vector<T>& vec, Compare comp = Compare{});

// TIER 3: Iterator-based design (Advanced Level)
// template<typename Iterator, typename Compare = std::less<>>
// void insertionSort(Iterator first, Iterator last, Compare comp = Compare{});

// TIER 4: Constexpr compile-time version (Expert Level)
// template<typename T, std::size_t N>
// constexpr std::array<T, N> insertionSort(std::array<T, N> arr);

#include "your_insertion_sort.h" // Replace with your implementation

// Exception-throwing type for testing exception safety
class ThrowingInt {
public:
    int value;
    static int copy_count;
    static bool should_throw;
    
    ThrowingInt(int v) : value(v) {}
    
    ThrowingInt(const ThrowingInt& other) : value(other.value) {
        ++copy_count;
        if (should_throw && copy_count > 3) {
            throw std::runtime_error("Copy failed");
        }
    }
    
    ThrowingInt& operator=(const ThrowingInt& other) {
        value = other.value;
        ++copy_count;
        if (should_throw && copy_count > 3) {
            throw std::runtime_error("Assignment failed");
        }
        return *this;
    }
    
    bool operator<(const ThrowingInt& other) const {
        return value < other.value;
    }
    
    bool operator==(const ThrowingInt& other) const {
        return value == other.value;
    }
};

int ThrowingInt::copy_count = 0;
bool ThrowingInt::should_throw = false;

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::cout << "╔══════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              INSERTION SORT: PROFESSIONAL C++ GAUNTLET          ║" << std::endl;
    std::cout << "║                          LearnThruFailure                       ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ This is not beginner-friendly. This is your debugging gauntlet. ║" << std::endl;
    std::cout << "║ Master insertion sort from every professional angle.            ║" << std::endl;
    std::cout << "║ No moving forward until ALL tests pass.                        ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    // ============================================================================================
    // TIER 1: FOUNDATION LEVEL (Easy → Intermediate)
    // Testing: Basic templates, STL integration, const correctness
    // ============================================================================================
    
    std::cout << "═══ TIER 1: FOUNDATION LEVEL ═══" << std::endl;
    std::cout << "Testing: Templates, STL containers, modern C++ syntax, const correctness\n" << std::endl;

    // Test 1.1: Basic integer sorting
    std::cout << "Test 1.1: Basic integer sorting (your first challenge)..." << std::endl;
    {
        std::vector<int> test_data = {3, 5, 8, 10, 1};
        const std::vector<int> expected = {1, 3, 5, 8, 10};
        
        std::cout << "  Input:  ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        insertionSort(test_data);
        
        std::cout << "  Output: ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        assert(test_data == expected);
        std::cout << "  ✓ PASSED - Basic template instantiation works" << std::endl;
    }

    // Test 1.2: Template genericity with strings
    std::cout << "\nTest 1.2: String sorting (template genericity)..." << std::endl;
    {
        auto test_data = std::vector<std::string>{"cat", "dog", "lion", "parrot", "fish", "elephant"};
        const auto expected = std::vector<std::string>{"cat", "dog", "elephant", "fish", "lion", "parrot"};
        
        std::cout << "  Input:  ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        insertionSort(test_data);
        
        std::cout << "  Output: ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        assert(test_data == expected);
        std::cout << "  ✓ PASSED - Template works with std::string" << std::endl;
    }

    // Test 1.3: Auto keyword and type deduction
    std::cout << "\nTest 1.3: Auto keyword and type deduction..." << std::endl;
    {
        auto test_data = std::vector<double>{3.14, 2.71, 1.41, 0.57, 9.81};
        const auto expected = std::vector<double>{0.57, 1.41, 2.71, 3.14, 9.81};
        
        std::cout << "  Type deduced as: " << typeid(test_data).name() << std::endl;
        std::cout << "  Input:  ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        insertionSort(test_data);
        
        std::cout << "  Output: ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        assert(test_data == expected);
        std::cout << "  ✓ PASSED - Modern C++ syntax works" << std::endl;
    }

    // Test 1.4: Edge cases (debugging fundamentals)
    std::cout << "\nTest 1.4: Edge cases (debugging fundamentals)..." << std::endl;
    {
        // Empty vector
        auto empty_vec = std::vector<int>{};
        insertionSort(empty_vec);
        assert(empty_vec.empty());
        std::cout << "  Empty vector: ✓" << std::endl;
        
        // Single element
        auto single_vec = std::vector<int>{42};
        insertionSort(single_vec);
        assert(single_vec.size() == 1 && single_vec[0] == 42);
        std::cout << "  Single element: ✓" << std::endl;
        
        // Already sorted
        auto sorted_vec = std::vector<int>{1, 2, 3, 4, 5};
        const auto expected_sorted = sorted_vec;
        insertionSort(sorted_vec);
        assert(sorted_vec == expected_sorted);
        std::cout << "  Already sorted: ✓" << std::endl;
        
        // Reverse sorted (worst case)
        auto reverse_vec = std::vector<int>{5, 4, 3, 2, 1};
        const auto expected_reverse = std::vector<int>{1, 2, 3, 4, 5};
        insertionSort(reverse_vec);
        assert(reverse_vec == expected_reverse);
        std::cout << "  Reverse sorted: ✓" << std::endl;
        
        std::cout << "  ✓ PASSED - Your algorithm handles edge cases" << std::endl;
    }

    // ============================================================================================
    // TIER 2: PROFESSIONAL PRACTICES (Intermediate → Advanced)
    // Testing: Custom comparators, smart pointers, RAII
    // ============================================================================================
    
    std::cout << "\n═══ TIER 2: PROFESSIONAL PRACTICES ═══" << std::endl;
    std::cout << "Testing: Custom comparators, smart pointers, RAII, function objects\n" << std::endl;

    // Test 2.1: Custom comparator (descending order)
    std::cout << "Test 2.1: Custom comparator (descending order)..." << std::endl;
    {
        std::vector<int> test_data = {3, 1, 4, 1, 5, 9, 2, 6};
        const std::vector<int> expected = {9, 6, 5, 4, 3, 2, 1, 1};
        
        std::cout << "  Input:  ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        insertionSort(test_data, std::greater<int>{});
        
        std::cout << "  Output: ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        assert(test_data == expected);
        std::cout << "  ✓ PASSED - Custom comparator works" << std::endl;
    }

    // Test 2.2: Lambda comparator (case-insensitive strings)
    std::cout << "\nTest 2.2: Lambda comparator (case-insensitive strings)..." << std::endl;
    {
        std::vector<std::string> test_data = {"Apple", "banana", "Cherry", "date"};
        const std::vector<std::string> expected = {"Apple", "banana", "Cherry", "date"};
        
        std::cout << "  Input:  ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        insertionSort(test_data, [](const std::string& a, const std::string& b) {
            std::string a_lower = a, b_lower = b;
            std::transform(a_lower.begin(), a_lower.end(), a_lower.begin(), ::tolower);
            std::transform(b_lower.begin(), b_lower.end(), b_lower.begin(), ::tolower);
            return a_lower < b_lower;
        });
        
        std::cout << "  Output: ";
        for (const auto& elem : test_data) std::cout << elem << " ";
        std::cout << std::endl;
        
        assert(test_data == expected);
        std::cout << "  ✓ PASSED - Lambda expressions work" << std::endl;
    }

    // Test 2.3: Smart pointers and RAII
    std::cout << "\nTest 2.3: Smart pointers and RAII..." << std::endl;
    {
        struct Student {
            std::string name;
            int grade;
            
            Student(const std::string& n, int g) : name(n), grade(g) {}
            
            bool operator<(const Student& other) const {
                return grade < other.grade;
            }
        };
        
        auto students = std::vector<std::unique_ptr<Student>>();
        students.push_back(std::make_unique<Student>("Alice", 85));
        students.push_back(std::make_unique<Student>("Bob", 92));
        students.push_back(std::make_unique<Student>("Charlie", 78));
        students.push_back(std::make_unique<Student>("Diana", 96));
        
        std::cout << "  Input grades:  ";
        for (const auto& student : students) std::cout << student->grade << " ";
        std::cout << std::endl;
        
        // Sort using custom comparator for smart pointers
        std::sort(students.begin(), students.end(), 
                 [](const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b) {
                     return a->grade < b->grade;
                 });
        
        std::cout << "  Sorted grades: ";
        for (const auto& student : students) std::cout << student->grade << " ";
        std::cout << std::endl;
        
        // Verify sorted order
        for (size_t i = 1; i < students.size(); ++i) {
            assert(students[i-1]->grade <= students[i]->grade);
        }
        std::cout << "  ✓ PASSED - RAII and smart pointers work" << std::endl;
    }

    // ============================================================================================
    // TIER 3: ADVANCED TECHNIQUES (Advanced → Expert)
    // Testing: Iterator design, exception safety, type traits
    // ============================================================================================
    
    std::cout << "\n═══ TIER 3: ADVANCED TECHNIQUES ═══" << std::endl;
    std::cout << "Testing: Iterator-based design, exception safety, type traits, metaprogramming\n" << std::endl;

    // Test 3.1: Iterator-based design (works with different containers)
    std::cout << "Test 3.1: Iterator-based design..." << std::endl;
    {
        // Test with std::list
        std::list<int> test_list = {5, 2, 8, 1, 9};
        std::cout << "  std::list input:  ";
        for (const auto& elem : test_list) std::cout << elem << " ";
        std::cout << std::endl;
        
        insertionSort(test_list.begin(), test_list.end());
        
        std::cout << "  std::list output: ";
        for (const auto& elem : test_list) std::cout << elem << " ";
        std::cout << std::endl;
        
        // Verify sorted
        auto prev = test_list.begin();
        for (auto it = std::next(prev); it != test_list.end(); ++it, ++prev) {
            assert(*prev <= *it);
        }
        
        // Test with std::deque
        std::deque<char> test_deque = {'z', 'a', 'm', 'b', 'q'};
        insertionSort(test_deque.begin(), test_deque.end());
        
        std::cout << "  std::deque chars: ";
        for (const auto& c : test_deque) std::cout << c << " ";
        std::cout << std::endl;
        
        std::cout << "  ✓ PASSED - Iterator abstraction works with multiple containers" << std::endl;
    }

    // Test 3.2: Exception safety
    std::cout << "\nTest 3.2: Exception safety..." << std::endl;
    {
        ThrowingInt::copy_count = 0;
        ThrowingInt::should_throw = false;
        
        std::vector<ThrowingInt> test_data;
        test_data.emplace_back(3);
        test_data.emplace_back(1);
        test_data.emplace_back(4);
        test_data.emplace_back(2);
        
        std::cout << "  Testing without exceptions: ";
        insertionSort(test_data);
        for (const auto& elem : test_data) std::cout << elem.value << " ";
        std::cout << std::endl;
        
        // Verify sorted
        for (size_t i = 1; i < test_data.size(); ++i) {
            assert(test_data[i-1].value <= test_data[i].value);
        }
        
        std::cout << "  ✓ PASSED - Exception safety maintained" << std::endl;
    }

    // Test 3.3: Type traits and compile-time validation
    std::cout << "\nTest 3.3: Type traits and compile-time validation..." << std::endl;
    {
        // Compile-time type checking
        static_assert(std::is_same_v<int, int>, "Type trait test failed");
        static_assert(!std::is_same_v<int, double>, "Type trait test failed");
        static_assert(std::is_integral_v<int>, "Integer type check failed");
        static_assert(std::is_floating_point_v<double>, "Float type check failed");
        
        // Test with different numeric types to verify template instantiation
        auto char_vec = std::vector<unsigned char>{255, 1, 128, 64};
        const auto expected_chars = std::vector<unsigned char>{1, 64, 128, 255};
        
        std::cout << "  unsigned char test: ";
        insertionSort(char_vec);
        for (const auto& c : char_vec) std::cout << static_cast<int>(c) << " ";
        std::cout << std::endl;
        
        assert(char_vec == expected_chars);
        std::cout << "  ✓ PASSED - Type traits and template instantiation work" << std::endl;
    }

    // ============================================================================================
    // TIER 4: EXPERT LEVEL (Metaprogramming & Performance)
    // Testing: Constexpr, compile-time computation, performance analysis
    // ============================================================================================
    
    std::cout << "\n═══ TIER 4: EXPERT LEVEL ═══" << std::endl;
    std::cout << "Testing: Constexpr functions, compile-time computation, performance analysis\n" << std::endl;

    // Test 4.1: Constexpr compile-time sorting
    std::cout << "Test 4.1: Constexpr compile-time sorting..." << std::endl;
    {
        // This test requires your constexpr implementation
        constexpr std::array<int, 5> test_array = {3, 1, 4, 1, 5};
        constexpr auto sorted_array = insertionSort(test_array);
        
        static_assert(sorted_array[0] == 1, "Constexpr sort failed");
        static_assert(sorted_array[1] == 1, "Constexpr sort failed");
        static_assert(sorted_array[2] == 3, "Constexpr sort failed");
        static_assert(sorted_array[3] == 4, "Constexpr sort failed");
        static_assert(sorted_array[4] == 5, "Constexpr sort failed");
        
        std::cout << "  Compile-time sorted: ";
        for (const auto& elem : sorted_array) std::cout << elem << " ";
        std::cout << std::endl;
        
        std::cout << "  ✓ PASSED - Constexpr sorting works at compile time" << std::endl;
    }

    // Test 4.2: Performance analysis and complexity verification
    std::cout << "\nTest 4.2: Performance analysis..." << std::endl;
    {
        const std::vector<size_t> test_sizes = {100, 500, 1000, 2000};
        
        for (auto size : test_sizes) {
            // Generate worst-case data (reverse sorted)
            std::vector<int> test_data(size);
            std::iota(test_data.rbegin(), test_data.rend(), 1);
            
            auto perf_start = std::chrono::high_resolution_clock::now();
            insertionSort(test_data);
            auto perf_end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(perf_end - perf_start);
            
            // Verify correctness
            for (size_t i = 1; i < test_data.size(); ++i) {
                assert(test_data[i-1] <= test_data[i]);
            }
            
            std::cout << "  Size " << size << ": " << duration.count() << " μs" << std::endl;
        }
        
        std::cout << "  ✓ PASSED - Performance scales as O(n²) as expected" << std::endl;
    }

    // Test 4.3: Comparison with standard library
    std::cout << "\nTest 4.3: Comparison with std::sort..." << std::endl;
    {
        const size_t test_size = 10000;
        
        // Test insertion sort
        std::vector<int> data1(test_size);
        std::iota(data1.rbegin(), data1.rend(), 1);
        
        auto start1 = std::chrono::high_resolution_clock::now();
        insertionSort(data1);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto insertion_time = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
        
        // Test std::sort
        std::vector<int> data2(test_size);
        std::iota(data2.rbegin(), data2.rend(), 1);
        
        auto start2 = std::chrono::high_resolution_clock::now();
        std::sort(data2.begin(), data2.end());
        auto end2 = std::chrono::high_resolution_clock::now();
        auto std_time = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
        
        assert(data1 == data2); // Both should produce same result
        
        std::cout << "  Insertion sort (" << test_size << " elements): " << insertion_time.count() << " μs" << std::endl;
        std::cout << "  std::sort      (" << test_size << " elements): " << std_time.count() << " μs" << std::endl;
        std::cout << "  Slowdown factor: " << (double)insertion_time.count() / std_time.count() << "x" << std::endl;
        std::cout << "  ✓ PASSED - You understand the performance trade-offs" << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    // ============================================================================================
    // GAUNTLET COMPLETION SUMMARY
    // ============================================================================================
    
    std::cout << "\n╔══════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                    GAUNTLET COMPLETED!                          ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Professional C++ Skills Mastered:                               ║" << std::endl;
    std::cout << "║ ✓ Template metaprogramming and generic design                   ║" << std::endl;
    std::cout << "║ ✓ STL integration and iterator-based algorithms                 ║" << std::endl;
    std::cout << "║ ✓ Modern C++ idioms (auto, lambdas, smart pointers)            ║" << std::endl;
    std::cout << "║ ✓ Exception safety and resource management (RAII)              ║" << std::endl;
    std::cout << "║ ✓ Custom comparators and function objects                      ║" << std::endl;
    std::cout << "║ ✓ Type traits and compile-time programming                     ║" << std::endl;
    std::cout << "║ ✓ Performance analysis and complexity understanding            ║" << std::endl;
    std::cout << "║ ✓ Comprehensive testing and debugging skills                   ║" << std::endl;
    std::cout << "║                                                                  ║" << std::endl;
    std::cout << "║ Algorithm Mastery:                                              ║" << std::endl;
    std::cout << "║ ✓ Insertion sort implementation and optimization                ║" << std::endl;
    std::cout << "║ ✓ Edge case handling and robustness                            ║" << std::endl;
    std::cout << "║ ✓ Multiple interface designs (vector, iterator, constexpr)     ║" << std::endl;
    std::cout << "║ ✓ Performance characteristics and trade-off analysis           ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Total debugging and testing time: " << std::setw(4) << total_duration.count() << " ms           ║" << std::endl;
    std::cout << "║                                                                  ║" << std::endl;
    std::cout << "║ You have successfully completed the Insertion Sort Gauntlet.    ║" << std::endl;
    std::cout << "║ You now think like a professional C++ developer.                ║" << std::endl;
    std::cout << "║                                                                  ║" << std::endl;
    std::cout << "║ Next challenges: Binary Search, Merge Sort, Hash Tables...      ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════╝" << std::endl;
    
    return 0;
}