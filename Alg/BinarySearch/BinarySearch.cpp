#include <iostream>

int BinarySearch(int *arr,int size,int val){
    int i=0,j=size-1;
    while(i<=j){
        int mid = (i+j)/2;
        if(val>arr[mid]){
            i = mid+1;
        }
        else if(val<arr[mid]){
            j=mid-1;
        }
        else{
            return mid;
        }
    }
    return -1;
}

int main(){
    int arr[]={1,3,5,7,9,11,13,15,17,19};
    std::cout<<"Index: "<<BinarySearch(arr,sizeof(arr),13)<<std::endl;
}