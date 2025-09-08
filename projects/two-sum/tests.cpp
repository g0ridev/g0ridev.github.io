#include "two-sum.h"
#include <iostream>
#include <cassert>

void runTests() {
    Solution sol;

    // Test case 1
    {
        std::vector<int> nums = {2,7,11,15};
        int target = 9;
        std::vector<int> result = sol.twoSum(nums, target);
        assert((result == std::vector<int>{0,1} || result == std::vector<int>{1,0}));
    }

    // Test case 2
    {
        std::vector<int> nums = {3,2,4};
        int target = 6;
        std::vector<int> result = sol.twoSum(nums, target);
        assert((result == std::vector<int>{1,2} || result == std::vector<int>{2,1}));
    }

    // Test case 3
    {
        std::vector<int> nums = {3,3};
        int target = 6;
        std::vector<int> result = sol.twoSum(nums, target);
        assert((result == std::vector<int>{0,1} || result == std::vector<int>{1,0}));
    }
}

int main() {
    runTests();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
