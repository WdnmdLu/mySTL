#include <iostream>

void BubbleSort(int *arr,int Size){
    int i,j;
    int temp=0;
    for(i=0;i<Size-1;i++){
        for(j=0;j<Size-i-1;j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    int arr[]={1,9,2,8,3,7,4,6,5,10};
    int len = sizeof(arr)/4;
    BubbleSort(arr,len);
    for(int i=0;i<len;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}