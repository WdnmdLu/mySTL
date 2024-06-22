#include <iostream>
// 二分搜索递归代码实现

int BinarySearch(int *arr,int Begin,int End,int val){
    if(Begin>End){
        return -1;
    }
    int mid = (Begin+End)/2;
    if(arr[mid] == val){
        return mid;
    }
    else if(arr[mid] > val){
        return BinarySearch(arr,Begin,mid-1,val);
    }
    else{
        return BinarySearch(arr,mid+1,End,val);
    }
}

int main(){
    int arr[]={1,3,5,7,9,11,13,15,17,19};
    std::cout<<"Index: "<<BinarySearch(arr,0,sizeof(arr)-1,15)<<std::endl;
    std::cout<<"Index: "<<BinarySearch(arr,0,sizeof(arr)-1,3)<<std::endl;
    std::cout<<"Index: "<<BinarySearch(arr,0,sizeof(arr)-1,15)<<std::endl;
    std::cout<<"Index: "<<BinarySearch(arr,0,sizeof(arr)-1,19)<<std::endl;
}