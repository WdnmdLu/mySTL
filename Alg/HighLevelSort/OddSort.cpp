#include <iostream>
#include <vector>
using namespace std;

void OddSort(int *arr, int Size, int Num) {
    vector<vector<int>> Temp(10);  // 10个桶，用于存放0-9的数字

    for (int i = 1; i <= Num; i++) {  // 按位数进行循环排序
        // 放入桶中
        for (int k = 0; k < Size; k++) {
            int num = arr[k];
            for (int j = 1; j < i; j++) {
                num /= 10;
            }
            int digit = num % 10;
            Temp[digit].push_back(arr[k]);
        }

        // 从桶中取出数据放回原数组
        int index = 0;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < Temp[j].size(); k++) {
                arr[index++] = Temp[j][k];
            }
            Temp[j].clear();  // 清空桶，准备下一轮排序
        }
    }
}

int main() {
    int arr[] = {123, 234, 23, 56, 78, 12, 10, 100};
    int size = sizeof(arr) / sizeof(arr[0]);

    OddSort(arr, size, 3);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}