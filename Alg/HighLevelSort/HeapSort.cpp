#include <iostream>

// 堆中元素下沉
void HeapDown(int *arr, int i, int Size) {
    int value = arr[i];
    while (i < Size / 2) {
        int child = 2 * i + 1;
        if (child + 1 < Size && arr[child + 1] > arr[child]) {
            child = child + 1;
        }
        // 如果孩子有比当前节点值大 将当前节点的值赋为孩子的值
        if (arr[child] > value) {
            arr[i] = arr[child];
            i = child; // 修改i为孩子的位置
        } else {
            break;
        }
    }
    arr[i] = value;
}

void HeapSort(int *arr, int Size) {
    //先对数组进行大根堆的处理，将值小的元素下沉
    // 当前位置i，左孩子2i+1 右孩子2i+2
    int end = Size - 1;
    for (int i = (end - 1) / 2; i >= 0; i--) {
        //从最后一个非叶节点元素开始进行调整，一直调整到根
        HeapDown(arr, i, Size);
    }

    // 堆顶和末尾元素进行交换
    for (int i = end; i > 0; i--) {
        int temp = 0;
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        //堆顶元素下沉到最
        HeapDown(arr, 0, i);
    }
}

int main() {
    int arr[] = {1, 9, 2, 8, 3, 7, 4, 6, 5, 10};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    HeapSort(arr, arrSize);
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}