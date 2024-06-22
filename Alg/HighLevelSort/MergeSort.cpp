#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// 合并两个有序的子数组
void Merge(int *arr, int Begin, int mid, int End) {
    int n1 = mid - Begin + 1;
    int n2 = End - mid;

    // 创建临时数组来存放两个子数组
    std::vector<int> left(n1);
    std::vector<int> right(n2);

    // 将数据复制到临时数组
    for (int i = 0; i < n1; ++i)
        left[i] = arr[Begin + i];
    for (int i = 0; i < n2; ++i)
        right[i] = arr[mid + 1 + i];

    // 合并临时数组到原数组
    int i = 0, j = 0, k = Begin;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        } else {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    // 复制剩余的元素（如果有的话）
    while (i < n1) {
        arr[k] = left[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = right[j];
        ++j;
        ++k;
    }
}

// 归并排序的递归函数
void MergeSort(int *arr, int Begin, int End) {
    // 先划分
    if (Begin >= End) {
        return;
    }

    int mid = (Begin + End) / 2;
    MergeSort(arr, Begin, mid);
    MergeSort(arr, mid + 1, End);

    // 排序 Begin mid End
    Merge(arr, Begin, mid, End);
}

int main() {
    const int size = 1000;
    int arr[size];

    // 使用当前时间作为随机数种子
    std::srand(std::time(0));

    // 生成1000个随机数
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand();
    }

    // 对数组进行归并排序
    MergeSort(arr, 0, size - 1);

    // 打印排序后的数组
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}