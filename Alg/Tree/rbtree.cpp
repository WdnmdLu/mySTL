#include <iostream>
/*
1.每个节点都有颜色，不是红色就是黑色
2.叶子节点nullptr为黑色
3.root节点一定为黑色
4.不能出现连续红色的节点    父亲为红则孩子一定为黑  如果孩子有红则父亲一定为黑
5.从根节点到任意一个叶节点(nullptr)上，黑色节点的数量一定是一致的
*/
/*
红黑树的插入
1.空树 直接插入 根节点：黑色
2.非空 插入节点 - 叶子节点：红色 
进行调整 父节点肯定为红色，爷节肯定点为黑色
    1.叔为红色  父->黑 叔->黑 爷->红 新插入->红 如果爷为根 直接变为黑色
    2.叔为黑色  父变黑 爷变红 叔还算黑 然后在以爷为根进行右旋
    3.叔为黑色  插在父的右边  先以父节点为根进行左旋 然后变为情况2 接着进行调整即可
*/

struct Node{
    int Color;
    int data;
    Node *left;
    Node *right;
};

class rbTree(){
public:
    void Insert(int Value){

    }

private:
    struct Node *insert(struct Node* root,int value){
        //先往下找到可以插入的位置进行插入
        if(root == nullptr ){
            root = new Node();
            root->data = value;
            root->left = nullptr;
            root->right = nullptr;
            return root;
        }
        if(root->data > value){
            root->left = insert(root->left,value);
        }
        else if(root->data < value){
            root->right = insert(root->right,value);
        }
        else{
            // 找到了相同的值，无法进行插入
            return root;
        }
    }

    // 右旋操作
    struct Node *rightRotate(struct Node *Root) {
        struct Node *newRoot = Root->left;
        struct Node *OldL = newRoot->right;

        // 执行右旋操作
        newRoot->right = Root;
        Root->left = OldL;

        return newRoot;
    }

    // 左旋操作
    struct Node *leftRotate(struct Node *Root) {
        struct Node *newRoot = Root->right;
        struct Node *OldR = newRoot->left;

        // 执行左旋操作
        newRoot->left = Root;
        Root->right = OldR;

        return newRoot;
    }
};

int main(){

}