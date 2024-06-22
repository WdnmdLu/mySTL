#include <iostream>

void InsertSort(int *arr,int size){
    int i,j;
    for(i = 1;i<size;i++){
        int val = arr[i];
        for(j = i-1;j>=0;j--){
            if(arr[j] <=val){
                break;
            }
            arr[j+1] = arr[j];
        }
        arr[j+1] = val;
    }
}

void HillSort(int *arr, int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main(){
    int arr[]={1,9,2,8,3,7,4,6,5,10,23,21,45,17,25,11,29,18,26,20};
    int len = sizeof(arr)/4;
    HillSort(arr,len);
    for(int i=0;i<len;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}