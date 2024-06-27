#include <iostream>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

struct Node{
    Node *left;
    Node *right;
    int data;
};
Node* minValueNode(Node* node);

void CreatTree(Node **T,int value){
    if((*T)==nullptr){
        (*T) = (Node*)malloc(sizeof(Node));
        (*T)->data = value;
        (*T)->left = nullptr;
        (*T)->right = nullptr;
        return;
    }
    if((*T)->data > value){
        CreatTree(&((*T)->left),value);
    }
    else{
        CreatTree(&((*T)->right),value);
    }
}

void OrderTree(Node *T){
    if(T!=nullptr){
        OrderTree(T->left);
        //printf("%d ",T->data);
        OrderTree(T->right);
    }
}

void PreOrderTree(Node *T){
    if(T!=nullptr){
        printf("%d ",T->data);
        PreOrderTree(T->left);
        PreOrderTree(T->right);
    }
}

void OnOrderTree(Node *T){
    if(T!=nullptr){
        OnOrderTree(T->left);
        OnOrderTree(T->right);
        //printf("%d ",T->data);
    }
}

Node* DeleteNode(Node *Root,int value){
    if(Root == nullptr){
        return Root;
    }
    if(Root->data > value){
        Root->left = DeleteNode(Root->left,value);
    }
    else if(Root->data < value){
        Root->right = DeleteNode(Root->right,value);
    }
    else{
        if(Root->left == nullptr){
            Node *temp = Root->right;
            delete(Root);
            return temp;
        }
        if(Root->right == nullptr){
            Node *temp = Root->left;
            delete(Root);
            return temp;
        }
        //存在左右孩子
        Node *temp = minValueNode(Root->right);
        Root->data = temp->data;
        Root->right = DeleteNode(Root->right, temp->data);
    }
    return Root;
}
Node* minValueNode(Node* node) {
    Node* current = node;
    // 最小值肯定在最左边
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

int main() {
    Node *T = nullptr;
    const int num_elements = 9999;

    // Generate random numbers
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, num_elements * 10);

    // Insertion timing
    auto start_insert = high_resolution_clock::now();

    for (int i = 0; i < num_elements; ++i) {
        int value = dis(gen);
        CreatTree(&T, value);
    }

    auto stop_insert = high_resolution_clock::now();
    auto duration_insert = duration_cast<microseconds>(stop_insert - start_insert);

    // Traversal timing (Inorder)
    auto start_traverse = high_resolution_clock::now();

    OrderTree(T);  // Traversing without printing for timing purposes

    auto stop_traverse = high_resolution_clock::now();
    auto duration_traverse = duration_cast<microseconds>(stop_traverse - start_traverse);

    cout << "Inserted " << num_elements << " elements\n";
    cout << "Insertion time: " << duration_insert.count() << " microseconds\n";
    cout << "Traversal time: " << duration_traverse.count() << " microseconds\n";

    return 0;
}