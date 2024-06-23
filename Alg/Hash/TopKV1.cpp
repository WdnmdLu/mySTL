#include <iostream>

/* 大根堆小根堆求TopK和MinK */
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
// 
void HeapSort(int *arr, int Size) {
    // 先对数组进行大根堆的处理，将值小的元素下沉
    // 当前位置i，左孩子2i+1 右孩子2i+2
    int end = Size - 1;
    for (int i = (end - 1) / 2; i >= 0; i--) {
        //从最后一个非叶节点元素开始进行调整，一直调整到根
        HeapDown(arr, i, Size);
    }
    // 经过上面的调整就保证了非叶节点的值一定大于该节点左右孩子的值

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

// 确保根节点比左右孩子的值都小
void SmallHeapDown(int *arr,int i,int Size){
    int value = arr[i];
    while (i < Size / 2) {
        int child = 2 * i + 1;//左孩子的位置
        // 找到左右孩子中最小的
        if (child + 1 < Size && arr[child + 1] < arr[child]) {
            child = child + 1;
        }
        // 如果孩子有比当前节点值大 将当前节点的值赋为孩子的值
        if (arr[child] < value) {
            arr[i] = arr[child];
            i = child; // 修改i为孩子的位置
        } else {
            break;
        }
    }
    arr[i] = value;
}

void SmallHeapSort(int *arr,int Size){
     // 先对数组进行大根堆的处理，将值小的元素下沉
    // 当前位置i，左孩子2i+1 右孩子2i+2
    int end = Size - 1;
    for (int i = (end - 1) / 2; i >= 0; i--) {
        //从最后一个非叶节点元素开始进行调整，一直调整到根
        SmallHeapDown(arr, i, Size);
    }
    // 经过上面的调整就保证了非叶节点的值一定大于该节点左右孩子的值

    // 堆顶和末尾元素进行交换
    for (int i = end; i > 0; i--) {
        int temp = 0;
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        //堆顶元素下沉到最后
        //堆顶元素为最小值，将最小值下沉到最后
        SmallHeapDown(arr, 0, i);
    }
}

// 求数组中最小的k个数
void MinK(int *arr,int Size){
    int k = 3;
    int len = Size;
    int i;

    for(i = 0;i < k;i++){
        // 对arr的前三个元素进行大根堆的建立
        HeapSort(arr,3);
    }
    // 求前k个最元素
    for(i = k;i < len;i++){
        if(arr[2] < arr[i]){
            continue;
        }
        arr[2] = arr[i];
        HeapSort(arr,3);
    }
    for(i = 0;i < k ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

// 求数组中最大的K个数
void TopK(int *arr,int Size){
    // 取出前k个值中最小的放在堆顶，如果比最小值还大，将最小值移除，放入新元素
    int k = 5;
    int len = Size;
    int i;

    for(i = 0;i < k;i++){
        // 对arr的前三个元素进行大根堆的建立
        SmallHeapSort(arr,3);
    }
    for(i = k;i < len;i++){
        if(arr[2] > arr[i]){
            continue;
        }
        arr[2] = arr[i];
        SmallHeapSort(arr,3);
    }
    for(i = 0;i < k ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

/* 快排分割法求TopK和MinK */
void QuickSort(int *arr, int left, int right) {
    if (left >= right) return;
    int K = 3;
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


int main() {
    int arr[]={11,96,88,48,53,27,44,66,55,110};
    int len = sizeof(arr)/sizeof(int);
    //TopK(arr,len);
    QuickSort(arr,0,sizeof(arr)/sizeof(int)-1);
    for(int i=0;i<sizeof(arr)/sizeof(int);i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}