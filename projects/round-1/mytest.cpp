
#include "insertion-sort.h"

#include <iostream>
#include <cassert>

int main(){


    int array[] = {10,9,8,7,6,5,4,3,2,1}; // not sorted in order.(backwards)

    int n = sizeof(array) / sizeof(array[0]);

    insertion_sort::insertionSort(array, n);
    
    assert( array[0] == 1);

    for(int i = 0; i < n; i++){
        assert(array[i] == i + 1);
    }
































    // template T1;

    // T1 = {3,2,4,5,10};

    // insertionSort(T1);

    // if(T1[0] == 2){}??;
    
    // for(int i = 0; i< T1.size(); i++){
    //     if(T1[i] < T1[i+1]){ 
    //         std::cout << "consistent..." << std::endl; 
    //     }
    //     else{
    //         std::cout << "failure..." << std::endl;
    //     }
    // }





    std::cout << "All tests passed." << std::endl;
}