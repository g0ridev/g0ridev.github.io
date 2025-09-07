#include "insertion-sort.h"





void insertion_sort::insertionSort(int arr[],int n){
    for(int idxi = 0; idxi < n; idxi++){
        int key = arr[idxi];
        int idxj = idxi - 1;

        while(idxj >= 0 && arr[idxj] > key){ //5 4<-j 3 2 1 key = 1
            arr[idxj + 1] = arr[idxj];//5 5 3 2 1
            idxj = idxj - 1; //5<-j 5 ....

        }

        arr[idxj + 1] = key; // 1 5 4 3 2 
    }



}

























// template<typename T>
// void insertionSort(std::vector<T>& vec){
    
// }
