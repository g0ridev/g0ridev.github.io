#pragma once

#include <vector>
#include <array>
#include <functional>
#include <iterator>
#include <type_traits>

// ================================================================================================
// INSERTION SORT: PROFESSIONAL C++ GAUNTLET
// Header File - Function Declarations
// ================================================================================================
// 
// This header defines all the function signatures you must implement to pass the gauntlet.
// Each tier represents increasing complexity and professional C++ mastery.
//
// Your mission: Implement ALL of these functions in your solution file.
// The test suite will validate every aspect of your implementations.
// ================================================================================================

namespace insertion_sort {

// ============================================================================================
// TIER 1: FOUNDATION LEVEL
// Basic template function - works with std::vector and any comparable type
// ============================================================================================



void insertionSort(int arr[], int n);

/**
 * Basic insertion sort for std::vector
 * 
 * Requirements:
 * - Template function that works with any type T that supports operator<
 * - Sorts the vector in-place in ascending order
 * - Must handle edge cases: empty vector, single element, already sorted
 * - Time complexity: O(n²), Space complexity: O(1)
 * 
 * @param vec Reference to vector to be sorted (modified in-place)
 */
// template<typename T>
// void insertionSort(std::vector<T>& vec);

// ============================================================================================
// TIER 2: PROFESSIONAL PRACTICES
// Custom comparator support - enables flexible sorting criteria
// ============================================================================================

/**
 * Insertion sort with custom comparator
 * 
 * Requirements:
 * - Template function with default comparator (std::less<T>)
 * - Supports custom comparison functions/lambdas/function objects
 * - Must work with descending order, case-insensitive strings, etc.
 * - Maintains same time/space complexity as basic version
 * 
 * @param vec Reference to vector to be sorted (modified in-place)
 * @param comp Comparison function object (default: std::less<T>{})
 */
// template<typename T, typename Compare = std::less<T>>
// void insertionSort(std::vector<T>& vec, Compare comp = Compare{});

// ============================================================================================
// TIER 3: ADVANCED TECHNIQUES
// Iterator-based design - works with any container, not just std::vector
// ============================================================================================

/**
 * Iterator-based insertion sort with custom comparator
 * 
 * Requirements:
 * - Works with any bidirectional iterator (vector, list, deque, etc.)
 * - Uses std::less<> (transparent comparator) as default
 * - Must handle different iterator categories properly
 * - Should work with both mutable and const iterators appropriately
 * 
 * @param first Iterator to beginning of range
 * @param last Iterator to end of range (one past the last element)
 * @param comp Comparison function object (default: std::less<>{})
 */
// template<typename Iterator, typename Compare = std::less<>>
// void insertionSort(Iterator first, Iterator last, Compare comp = Compare{});

// ============================================================================================
// TIER 4: EXPERT LEVEL
// Constexpr compile-time sorting - computation at compile time
// ============================================================================================

/**
 * Constexpr insertion sort for std::array (compile-time computation)
 * 
 * Requirements:
 * - Must be constexpr (evaluatable at compile time)
 * - Works with std::array of any size
 * - Returns new sorted array (doesn't modify input)
 * - Should work in static_assert contexts
 * - Must maintain same algorithmic complexity
 * 
 * @param arr Input array to be sorted
 * @return New std::array with sorted elements
 */
// template<typename T, std::size_t N>
// constexpr std::array<T, N> insertionSort(std::array<T, N> arr);

/**
 * Constexpr insertion sort with custom comparator
 * 
 * Requirements:
 * - Same as above but with custom comparison function
 * - Comparator must also be constexpr-compatible
 * - Enables compile-time sorting with custom criteria
 * 
 * @param arr Input array to be sorted
 * @param comp Comparison function object (must be constexpr)
 * @return New std::array with sorted elements
 */
// template<typename T, std::size_t N, typename Compare>
// constexpr std::array<T, N> insertionSort(std::array<T, N> arr, Compare comp);

// ============================================================================================
// BONUS CHALLENGES (Optional - for true mastery)
// ============================================================================================

/**
 * BONUS: Exception-safe insertion sort
 * 
 * Provides strong exception safety guarantee:
 * - If any operation throws, the container remains in its original state
 * - No partial modifications or resource leaks
 * - Uses copy-and-swap or similar technique
 */
template<typename T, typename Compare = std::less<T>>
void insertionSortSafe(std::vector<T>& vec, Compare comp = Compare{});

/**
 * BONUS: Range-based insertion sort (C++20 style)
 * 
 * Modern C++ approach using concepts and ranges:
 * - Works with any sortable range
 * - Uses C++20 concepts for type constraints
 * - Integrates with std::ranges ecosystem
 */
// template<typename Range, typename Compare = std::less<>>
// requires std::sortable<std::ranges::iterator_t<Range>, Compare>
// void insertionSort(Range&& range, Compare comp = Compare{});

} // namespace insertion_sort

// ================================================================================================
// IMPLEMENTATION NOTES FOR STUDENTS
// ================================================================================================
//
// DEBUGGING TIPS:
// 1. Start with the basic version (Tier 1) and get it working first
// 2. Test edge cases thoroughly before moving to next tier
// 3. Use static_assert for compile-time validation where possible
// 4. Pay attention to const correctness and reference semantics
// 5. Consider exception safety in all implementations
//
// COMMON PITFALLS:
// - Off-by-one errors in loop bounds
// - Not handling empty containers properly
// - Incorrect iterator advancement
// - Missing const qualifiers
// - Not considering exception safety
//
// ALGORITHM REMINDER:
// Insertion sort builds the sorted portion one element at a time:
// 1. Start with second element (index 1)
// 2. Compare with elements to the left
// 3. Shift larger elements right
// 4. Insert current element in correct position
// 5. Repeat for all remaining elements
//
// PERFORMANCE CHARACTERISTICS:
// - Best case:    O(n)   - already sorted array
// - Average case: O(n²)  - random array
// - Worst case:   O(n²)  - reverse sorted array
// - Space:        O(1)   - in-place sorting
// - Stable:       Yes    - maintains relative order of equal elements
// ================================================================================================