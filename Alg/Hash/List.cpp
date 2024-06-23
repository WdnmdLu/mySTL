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
        status = static_cast<double>(Size) / Cap;
    }

    ~unordered_map() {
        for (int i = 0; i < Cap; ++i) {
            Node* current = arr[i].head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
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
            pMove = arr[index].head;
        } else {
            while (pMove->next != nullptr) {
                pMove = pMove->next;
            }
            pMove->next = new Node();
            pMove = pMove->next;
        }
        pMove->Key = Key;
        pMove->Value = value;
        pMove->next = nullptr;
        arr[index].Curr++;
        Size++;
        status = static_cast<double>(Size) / Cap;
    }
    int Delete(int Key){
        int index = HashFunction(Key);
        if(arr[index].Curr == 0){
            return -1;
        }
        Node *pMove = arr[index].head;
        while (pMove->next != nullptr)
        {
            if(pMove->next->Key == Key){
                Node *temp = pMove->next;
                pMove->next = pMove->next->next;
                delete(temp);
                arr[index].Curr--;
                Size--;
                status = static_cast<double>(Size) / Cap;
                return 0;
            }
            pMove=pMove->next;
        }
        return -1;
    }
    int Find(int Key){
        int index = HashFunction(Key);
        if(arr[index].Curr == 0){
            printf("Curr == 0\n");
            return -1;
        }
        Node *pMove = arr[index].head->next;
        while (pMove != nullptr)
        {
            if(pMove->Key == Key){
                return pMove->Value;
            }
            pMove=pMove->next;
        }
        printf("Can't Find\n");
        return -1;
    }

private:
    void Expand() {
        int next = SuNum(Cap);
        List* newArr = new List[next]();
        List* tempArr = arr;
        int tempCap = Cap;
        Cap = next;
        arr = newArr;
        for (int i = 0; i < tempCap; i++) {
            if(tempArr[i].Curr == 0){
                continue;
            }
            Node *pMove = tempArr[i].head->next;
            while (pMove != nullptr)
            {
                Node *temp = pMove;
                pMove = pMove->next;
                Insert(temp->Key,temp->Value);
                delete(temp);
            }
            delete(tempArr[i].head);
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

int main(){
    unordered_map map;
    
    const int NUM_OPERATIONS = 11;  // 操作次数
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, NUM_OPERATIONS);

    auto start = std::chrono::high_resolution_clock::now();
    printf("Begin\n");
    // 插入操作
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int key = distribution(generator);
        int value = distribution(generator);
        map.Insert(key, value);
        printf("%d   %d\n",key,map.Find(key));
    }
    printf("Insert Ok\n");

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
    printf("Delete Ok\n");

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // 输出总用时
    std::cout << "Total time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}