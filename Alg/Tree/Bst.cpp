#include <iostream>

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
        printf("%d ",T->data);
        OrderTree(T->right);
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

int main(){
    Node *T=nullptr;
    int arr[]={1,9,2,8,3,7,4,6,5,11};
    for(int i = 0;i<sizeof(arr)/sizeof(int);i++){
        CreatTree(&T,arr[i]);
    }
    OrderTree(T);
    printf("\n====================\n");
    T = DeleteNode(T,5);
    T = DeleteNode(T,11);
    OrderTree(T);
    printf("\n");
}