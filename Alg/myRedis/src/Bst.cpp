#include <iostream>
#include "Bst.h"
// 找到最小不平衡子树的根，对其进行更新
/*
    左旋：
        旧根节点为新根节点的左
        新根节点的右为旧根节点的左
    右旋
        旧根节点为新根节点的右子树
        新根节点的右子树(如果存在)为旧根节点的左子树
*/

// 获取节点的高度
int BST::height(struct TNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// 获取两个整数中较大的值
int BST::max(int a, int b) {
    return (a > b) ? a : b;
}

// 创建一个新的节点
struct TNode* BST::newTNode(int key, std::string &value) {
    struct TNode *TNode = (struct TNode *)malloc(sizeof(struct TNode));
    TNode->key = key;
    TNode->value = value;
    TNode->left = NULL;
    TNode->right = NULL;
    TNode->height = 1; // 新节点的高度为1
    return TNode;
}

// 右旋操作
struct TNode* BST::rightRotate(struct TNode *Root) {
    struct TNode *newRoot = Root->left;
    struct TNode *OldL = newRoot->right;

    // 执行右旋操作
    newRoot->right = Root;
    Root->left = OldL;

    // 更新节点高度
    Root->height = max(height(Root->left), height(Root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// 左旋操作
struct TNode* BST::leftRotate(struct TNode *Root) {
    struct TNode *newRoot = Root->right;
    struct TNode *OldR = newRoot->left;

    // 执行左旋操作
    newRoot->left = Root;
    Root->right = OldR;

    // 更新节点高度
    Root->height = max(height(Root->left), height(Root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// 获取平衡因子 左右子树高度相减
int BST::getBalance(struct TNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// 插入节点
struct TNode* BST::insert(struct TNode *TNode, int key, std::string &value) {
    // 执行标准BST的插入
    if (TNode == NULL)
        return newTNode(key,value);

    if (key < TNode->key)
        TNode->left = insert(TNode->left, key, value);
    else if (key > TNode->key)
        TNode->right = insert(TNode->right, key, value);
    else // 重复的键值不允许插入
        return TNode;

    // 更新节点的高度
    TNode->height = 1 + max(height(TNode->left), height(TNode->right));

    // 获取当前节点的平衡因子
    int balance = getBalance(TNode);

    // 根据不同的不平衡情况分别进行相应的调整即可  LL RR LR RL
    // 如果节点不平衡，进行旋转操作
    // 左子树不平衡的情况  LL
    if (balance > 1 && key < TNode->left->key)
        return rightRotate(TNode);

    // 右子树不平衡的情况 RR
    if (balance < -1 && key > TNode->right->key)
        return leftRotate(TNode);

    // 左右子树都不平衡的情况 LR型
    if (balance > 1 && key > TNode->left->key) {
        TNode->left = leftRotate(TNode->left);
        return rightRotate(TNode);
    }
    // RL型
    if (balance < -1 && key < TNode->right->key) {
        TNode->right = rightRotate(TNode->right);
        return leftRotate(TNode);
    }

    // 返回未修改的节点指针
    return TNode;
}

void find(struct TNode *Root,int key,char *Res){
    if(Root == nullptr){
        strcpy(Res,"False");
        return;
    }
    if(Root->key == key){
        strcpy(Res,Root->value);
        return;
    }
    if(Root->key > key){
        find(Root->left,key,Res);
    }
    else{
        find(Root->right,key,Res);
    }
    return;
}