#include <iostream>
#include <random>
#include <chrono>

struct Node {
    int Key;
    int Value;
    int flag;
};

// 寻找下一个素数
int SuNum(int value) {
    int i, j;
    int count;
    for (i = value*2 + 1;; i++) {
        count = 0;
        for (j = 2; j < i; j++) {  // 修改此处循环条件为 j < i
            if (i % j == 0) {
                count = 1;
                break;
            }
        }
        if (count == 0) {
            break;
        }
    }
    return i;
}

class unordered_map {
public:
    unordered_map() : Cap(7), Size(0) {
        arr = new Node[Cap]();
        status = Size / Cap;
    }

    ~unordered_map() {
        delete[] arr;
    }

     void Insert(int key_, int value_) {
        // 已经有3/4的位置被填满，需要扩容了
        if (status > 3.0 / 4.0) {
            Expand();
        }

        // 通过哈希函数找到对应位置进行存储
        int index = HashFunction(key_);
        while (arr[index].flag == 1) {  // 使用线性探测法解决冲突
            index = (index + 1) % Cap;
        }
        arr[index].Key = key_;
        arr[index].Value = value_;
        arr[index].flag = 1;
        Size++;
        status = static_cast<double>(Size) / Cap;
    }

    int Find(int Key) {
        int index = HashFunction(Key);
        while (arr[index].flag != 0) {
            if (arr[index].flag == 1 && arr[index].Key == Key) {
                return arr[index].Value;
            }
            // 下一个接着查找
            index = (index + 1) % Cap;
        }
        return -1;  // 未找到对应键值对，返回-1表示失败
    }

    void Delete(int Key) {
        int index = HashFunction(Key);
        while (arr[index].flag != 0) {
            if (arr[index].flag == 1 && arr[index].Key == Key) {
                arr[index].flag = -1;  // 删除标记为-1
                Size--;
                status = static_cast<double>(Size) / Cap;
                return;
            }
            index = (index + 1) % Cap;
        }
    }

private:
    void Expand() {
        // 找到下一个素数
        int next = SuNum(Cap);
        // 将Cap的值设为下一个素数
        Node* newArr = new Node[next]();
        // 通过哈希映射将旧数组中的元素一个个映射到新的元素中去
        for (int i = 0; i < Cap; i++) {
            if (arr[i].flag == 1) {
                // 获取到哈希映射的地址
                int index = HashFunction(arr[i].Key);
                while (newArr[index].flag == 1) {  // 使用线性探测法解决冲突
                    index = (index + 1) % next;
                }
                newArr[index].Key = arr[i].Key;
                newArr[index].Value = arr[i].Value;
                newArr[index].flag = 1;
            }
        }
        delete[] arr;
        arr = newArr;
        Cap = next;
        status = static_cast<double>(Size) / Cap;
    }

    int HashFunction(int key) {
        // 这里简单地将key模Cap作为哈希函数的计算方法
        return key % Cap;
    }

    int Size;
    int Cap;
    Node* arr;
    double status;
};

int main() {
    unordered_map map;
    
    const int NUM_OPERATIONS = 99;  // 操作次数
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, NUM_OPERATIONS);

    auto start = std::chrono::high_resolution_clock::now();

    // 插入操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = distribution(generator);
        printf("%d\n",key);
        int value = distribution(generator);
        map.Insert(key, value);
    }

    // 查找操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = distribution(generator);
        map.Find(key);
    
    }

    // 删除操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = distribution(generator);
        map.Delete(key);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // 输出总用时
    std::cout << "Total time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}