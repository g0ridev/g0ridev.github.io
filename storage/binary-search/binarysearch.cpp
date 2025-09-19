#include <iostream>
#include <vector>
using namespace std;



int binarysearch(vector<int> arr,int k){

    int left = 0;
    int right = arr.size() - 1;

    while(left<=right){
        int mid = left + (right - left)/2;
        if(arr[mid] == k){
            std::cout << " mid value matches k at idx: " << mid << " with mid value: "<< arr[mid] << std::endl;
            return mid;
        }
        if(arr[mid] < k){
            std::cout << " mid value < k value at idx: " << mid << " with mid value: "<< arr[mid] << std::endl;

            left = mid + 1;
            std::cout << " left idx now: " << left<< ", left value: "<< left << std::endl;


        }
        else{
            std::cout << " mid value > k value at idx: " << mid << " with mid value: "<< arr[mid] << std::endl;

            right = mid - 1;
            std::cout << " right idx now: " << right<< ", right value: "<< right << std::endl;

        }
    }
    return -1;
}



int main(){
    // make data flow visible to you.


    // case there is matching value.
    vector<int> arr = {1,2,3,4,5,6,7,8,9,10};
    int key = 5;
    
    int result = binarysearch(arr,key);
    
    

    std::cout << "key was "<< key<< ", and found idx of matching value found in array: " << result << std::endl;
    
    //case  there is no matching value.
    if(result == -1){
        std::cout << "no matching value.";
    }
}



