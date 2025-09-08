# Master Insertion Sort: Round 1 - Foundation

*Learn the fundamentals of insertion sort through hands-on implementation*

---

## 🎯 What You'll Learn

In this first round, you'll implement the basic insertion sort algorithm from scratch. We'll focus on:

- Understanding how insertion sort works conceptually
- Implementing the core algorithm step-by-step
- Visualizing the sorting process with debug output
- Building good coding habits with proper function structure

**Difficulty Level**: 🟢 **Beginner**  
**Time Estimate**: 15-20 minutes  
**Prerequisites**: Basic C++ knowledge (loops, arrays, functions)

---

## 📋 The Challenge

You need to implement insertion sort for a fixed array of integers: `[64, 34, 25, 12, 22]`

Your implementation should:
1. Sort the array in ascending order
2. Print each step of the sorting process
3. Show the final sorted result

---

## 🧠 How Insertion Sort Works

Think of insertion sort like organizing a hand of playing cards:

1. **Start with the second card** (first card is already "sorted")
2. **Compare it with cards to the left**
3. **Slide cards right** to make space
4. **Insert the card** in the correct position
5. **Repeat** for each remaining card

### Visual Example:
```
Initial:  [64, 34, 25, 12, 22]
Step 1:   [34, 64, 25, 12, 22]  // Insert 34
Step 2:   [25, 34, 64, 12, 22]  // Insert 25  
Step 3:   [12, 25, 34, 64, 22]  // Insert 12
Step 4:   [12, 22, 25, 34, 64]  // Insert 22
```

---

## 💻 Get Started

### 📁 Download the Starter Code

**[📥 Get Round 1 Files](C:\Users\bucki\Downloads\g0ridev.github.io\projects\round-1)**

```bash
# Clone the repository
git clone https://github.com/g0ridev/g0ridev.github.io.git

# Navigate to Round 1
cd g0ridev.github.io/projects/round-1

# Compile and run
g++ main.cpp -o insertion_sort
./insertion_sort
```

### 📂 Project Structure
```
round-1/
├── main.cpp           # Your main implementation file
├── insertion_sort.h   # Header file with function declarations
├── test.cpp          # Test cases (bonus)
└── README.md         # Additional instructions
```

---

## 🔍 Step-by-Step Implementation Guide

### Step 1: Understand the Function Signature

```cpp
void insertionSort(vector<int>& arr) {
    // Your implementation goes here
}
```

**Key Points:**
- Takes a `vector<int>&` (reference to modify original array)
- Returns `void` (modifies array in-place)
- Should sort in ascending order

### Step 2: The Core Algorithm

Here's the insertion sort logic broken down:

```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    // Start from second element (index 1)
    for (int i = 1; i < n; i++) {
        
        // Current element to insert
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        // Insert key at correct position
        arr[j + 1] = key;
    }
}
```

### Step 3: Add Debug Output

To visualize what's happening, add print statements:

```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    cout << "Starting insertion sort..." << endl;
    printArray(arr, "Initial array");
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        cout << "\nStep " << i << ": Inserting " << key << endl;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        
        printArray(arr, "After step " + to_string(i));
    }
}
```

---

## 🎯 Your Mission

1. **Open `main.cpp`** and find the `insertionSort()` function
2. **Implement the algorithm** using the guide above
3. **Add debug output** to see each step
4. **Compile and test** with the provided array
5. **Verify** your output matches the expected result

### Expected Output:
```
Starting insertion sort...
Initial array: [64, 34, 25, 12, 22]

Step 1: Inserting 34
After step 1: [34, 64, 25, 12, 22]

Step 2: Inserting 25  
After step 2: [25, 34, 64, 12, 22]

Step 3: Inserting 12
After step 3: [12, 25, 34, 64, 22]

Step 4: Inserting 22
After step 4: [12, 22, 25, 34, 64]

Final sorted array: [12, 22, 25, 34, 64]
```

---

## 🧪 Testing Your Solution

Run the test cases to verify your implementation:

```bash
# Compile with test file
g++ test.cpp -o test_insertion_sort

# Run tests
./test_insertion_sort
```

The tests will check:
- ✅ Correctly sorted output
- ✅ Handling of duplicate elements  
- ✅ Edge cases (empty array, single element)

---

## 💡 Common Mistakes to Avoid

1. **Starting from index 0** instead of 1
   - First element is already "sorted"
   
2. **Forgetting boundary checks**
   - Always check `j >= 0` in the while loop
   
3. **Not updating j correctly**
   - Remember to decrement: `j = j - 1`

4. **Placing key in wrong position**
   - Insert at `arr[j + 1] = key`, not `arr[j]`

---

## 🚀 Ready for More?

Once you've mastered Round 1, move on to:

**[Round 2: Dynamic Input & Validation →](../round-2/)**

In Round 2, you'll enhance your insertion sort to handle:
- User input for array size and elements
- Input validation and error handling  
- Different data types and edge cases

---

## 📚 Additional Resources

- [Insertion Sort Visualization](https://visualgo.net/en/sorting)
- [Big O Notation Explained](https://www.bigocheatsheet.com/)
- [C++ Vector Reference](https://cplusplus.com/reference/vector/vector/)

---

**Questions? Issues?** [Open an issue on GitHub](https://github.com/g0ridev/g0ridev.github.io/issues) or reach out!

---

*Happy coding! 🎉*