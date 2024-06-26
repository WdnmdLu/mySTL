#include "unordered_map.h"

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

int stringToInt(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return -1; // 如果字符串中包含非数字字符，返回-1
        }
    }

    try {
        return std::stoi(str); // 尝试将字符串转换为整数
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1; // 如果转换过程中出现异常，返回-1
    }
}

bool checkArguments(std::istringstream& iss, int expectedArgs, std::vector<std::string>& args) {
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args.size() == expectedArgs;
}



unordered_map::unordered_map():Cap(7),Size(0){
    arr = new List[Cap]();
    status = Size / Cap;
}

unordered_map::~unordered_map() {
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

void unordered_map::Insert(std::string Key, std::string value) {
    // 先find这个值是否在，如果不在则可以插入，如果在就修改value
    if(ChangValue(Key,value)){
        return;
    };
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
int unordered_map::Delete(std::string Key){
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
const char* unordered_map::Find(std::string Key){
    // 该key从来没被映射过
    int index = HashFunction(Key);
    if(arr[index].Curr == 0){
        return nullptr;
    }
    Node *pMove = arr[index].head;
    while(pMove != nullptr){
        if(pMove->Key == Key){
            return pMove->Value.c_str();
        }
        pMove = pMove->next;
    }
    return nullptr;
}
bool unordered_map::ChangValue(std::string Key,std::string value){
    // 该key从来没被映射过
    int index = HashFunction(Key);
    if(arr[index].Curr == 0){
        return false;
    }
    Node *pMove = arr[index].head;
    while(pMove != nullptr){
        if(pMove->Key == Key){
            pMove->Value = value;
            return true;
        }
        pMove = pMove->next;
    }
    return false;
}
void unordered_map::Expand() {
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

int unordered_map::HashFunction(std::string key) {
    return BKDRHash(key.c_str()) % Cap;
}