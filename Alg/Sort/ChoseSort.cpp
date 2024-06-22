#include <iostream>

void ChoseSearch(int *arr,int Size){
    int i=0,j=Size-1;
    int min,index;
    for(i=0;i<Size-1;i++){
        min = arr[i];
        index = i;
        for(j=i+1;j<Size;j++){
            if(arr[j]<min){
                min = arr[j];
                index = j;
            }
        }
        if(i!=index){
            arr[index] = arr[i];
            arr[i] = min;
        }
    }
}

int main(){
    int arr[]={1,9,2,8,3,7,4,6,5,10,23,21,45,17,25,11,29,18,26,20};
    ChoseSearch(arr,sizeof(arr)/4);
    for(int i=0;i<sizeof(arr)/4;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}