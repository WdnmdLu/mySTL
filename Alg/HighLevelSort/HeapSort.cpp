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

class PriorityQueue {
public:
    PriorityQueue(int cap = 20) : Cap(cap), Size(0) {
        arr = new int[Cap]();
    }

    ~PriorityQueue() {
        delete[] arr;
    }

    void Push(int val) {
        if (Size == Cap) {
            expand();
        }
        
        // 将新元素放到数组末尾
        arr[Size] = val;
        Size++;

        // 进行堆化操作，使得新元素符合大根堆的性质
        HeapUp();
    }

    int Top() {
        if (Size == 0) {
            std::cerr << "PriorityQueue is empty\n";
            return -1; // 可以根据实际情况返回错误值或者抛出异常
        }
        return arr[0];
    }

    void Pop() {
        if (Size == 0) {
            std::cerr << "PriorityQueue is empty\n";
            return;
        }

        // 将堆顶元素与最后一个元素交换
        arr[0] = arr[Size - 1];
        Size--;

        // 对堆顶元素进行向下调整，以维持大根堆性质
        HeapDown(0);
    }

    bool Empty() {
        return Size == 0;
    }

private:
    int Cap;
    int Size;
    int *arr;

    void HeapUp() {
        int idx = Size - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (arr[parent] < arr[idx]) {
                // 如果父节点值小于当前节点值，则交换它们
                std::swap(arr[parent], arr[idx]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    void HeapDown(int idx) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        // 找到当前节点与其左右孩子中的最大值
        if (left < Size && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < Size && arr[right] > arr[largest]) {
            largest = right;
        }

        // 如果最大值不是当前节点，则交换并继续向下调整
        if (largest != idx) {
            std::swap(arr[idx], arr[largest]);
            HeapDown(largest);
        }
    }

    void expand() {
        Cap *= 2;
        int *newArr = new int[Cap]();
        for (int i = 0; i < Size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
};

int main() {
    PriorityQueue pq;

    pq.Push(3);
    pq.Push(2);
    pq.Push(15);

    std::cout << "Top element: " << pq.Top() << "\n";

    pq.Pop();

    std::cout << "Top element after pop: " << pq.Top() << "\n";

    return 0;
}