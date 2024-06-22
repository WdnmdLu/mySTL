#include <iostream>
#include <cstdlib>  // 用于 std::rand 和 std::srand
#include <ctime>    // 用于 std::time

void QuickSort(int *arr, int left, int right) {
    if (left >= right) return;
    
    int i = left, j = right;
    int pivot = arr[(left + right) / 2]; // 选择中间元素作为基准值

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    QuickSort(arr, left, j);
    QuickSort(arr, i, right);
}

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


int main() {
    const int size = 99999;
    int arr[size];

    // 使用当前时间作为随机数种子
    std::srand(std::time(0));

    // 生成1000个随机数
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand();
    }

    // 对数组进行快速排序
    BubbleSort(arr, sizeof(arr)/4);

    // 打印排序后的数组
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}