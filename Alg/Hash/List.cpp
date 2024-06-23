#include <iostream>
#include <random>
#include <chrono>

struct Node{
    int Key;
    int Value;
    Node *next;
};

struct List{
    Node *head;
    int Curr=0;
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

class unordered_map{
public:
    unordered_map():Cap(7),Size(0){
        arr = new List[Cap]();
        status = Size / Cap;
    }

    ~unordered_map() {
        Node *pMove;
        Node *next;
        for(int i = 0;i<Cap ; i++){
            if(arr[i].Curr == 0){
                continue;
            }
            next = arr[i].head->next;
            pMove = arr[i].head;
            while(next != nullptr){
                delete(pMove);
                pMove = next;
                next = next->next;
            }
            delete(pMove);
        }
        delete[] arr;
    }

    void Insert(int Key, int value) {
        if (status > 3.0 / 4.0) {
            Expand();
        }
        int index = HashFunction(Key);
        Node* pMove = arr[index].head;
        if (arr[index].Curr == 0) {
            arr[index].head = new Node();
            arr[index].head->Key = Key;
            arr[index].head->Value = value;
            arr[index].head->next = nullptr;
            Size++;
            status = Size/Cap;
        } 
        else {
            while (pMove->next != nullptr) {
                pMove = pMove->next;
            }
            Node *temp = new Node();
            temp->Key = Key;
            temp->Value = value;
            temp->next = nullptr;
            pMove->next = temp;
        }
        arr[index].Curr++;

    }
    int Delete(int Key){
        int index = HashFunction(Key);
        // 该key没有存储过
        if(arr[index].Curr == 0){
            return -1;
        }
        Node *pMove = arr[index].head;
        if(pMove->Key == Key){
            pMove = pMove->next;
            delete(arr[index].head);
            arr[index].head = pMove;
            arr[index].Curr--;
            if(arr[index].Curr == 0){
                Size--;
                status = Size/Cap;
            }
            return 1;
        }
        Node *pre = arr[index].head;
        pMove = pMove->next;
        while (pMove != nullptr)
        {
            if(pMove->Key == Key){
                pre->next = pMove->next;
                delete(pMove);
                arr[index].Curr--;
                return 1;
            }
            pMove = pMove->next;
            pre = pre->next;
        }
        return -1;
    }
    int Find(int Key){
        // 该key从来没被映射过
        int index = HashFunction(Key);
        if(arr[index].Curr == 0){
            return -1;
        }
        Node *pMove = arr[index].head;
        while(pMove != nullptr){
            if(pMove->Key == Key){
                return pMove->Value;
            }
            pMove = pMove->next;
        }
        return -1;
    }

private:
    void Expand() {
        int next = SuNum(Cap);
        int tempCap = Cap;
        Cap = next;
        List *newArr = new List[next]();
        List *tempArr = arr;
        arr = newArr;
        for(int i = 0;i<tempCap;i++){
            if(tempArr[i].Curr == 0){
                continue;
            }
            Node *pMove = tempArr[i].head;
            Node *next = pMove->next;
            while (next != nullptr)
            {
                delete(pMove);
                pMove = next;
                next = next->next;
            }
            delete(pMove);
            
        }
        delete[] tempArr;
    }

    int HashFunction(int key) {
        return key % Cap;
    }

    int Size;
    int Cap;
    List* arr;
    double status;
};

int main() {
    unordered_map map;

    const int NUM_OPERATIONS = 99999999;  // 操作次数
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, NUM_OPERATIONS);

    auto start_insert = std::chrono::high_resolution_clock::now();

    // 插入操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = i;
        int value = distribution(generator);
        map.Insert(key, value);
    }

    auto end_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_insert = end_insert - start_insert;

    auto start_find = std::chrono::high_resolution_clock::now();

    // 查找操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = i;
        map.Find(key);
    }

    auto end_find = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_find = end_find - start_find;

    auto start_delete = std::chrono::high_resolution_clock::now();

    // 删除操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = i;
        map.Delete(key);
    }

    auto end_delete = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_delete = end_delete - start_delete;

    // 输出总用时
    std::cout << "Insert time: " << elapsed_insert.count() << " seconds" << std::endl;
    std::cout << "Find time: " << elapsed_find.count() << " seconds" << std::endl;
    std::cout << "Delete time: " << elapsed_delete.count() << " seconds" << std::endl;

    return 0;
}