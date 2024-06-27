#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
// 找到最小不平衡子树的根，对其进行更新
/*
    左旋：
        旧根节点为新根节点的左
        新根节点的右为旧根节点的左
    右旋
        旧根节点为新根节点的右子树
        新根节点的右子树(如果存在)为旧根节点的左子树
*/
// AVL树节点结构
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// 获取节点的高度
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// 获取两个整数中较大的值
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 创建一个新的节点
struct Node *newNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // 新节点的高度为1
    return node;
}

// 右旋操作
struct Node *rightRotate(struct Node *Root) {
    struct Node *newRoot = Root->left;
    struct Node *OldL = newRoot->right;

    // 执行右旋操作
    newRoot->right = Root;
    Root->left = OldL;

    // 更新节点高度
    Root->height = max(height(Root->left), height(Root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// 左旋操作
struct Node *leftRotate(struct Node *Root) {
    struct Node *newRoot = Root->right;
    struct Node *OldR = newRoot->left;

    // 执行左旋操作
    newRoot->left = Root;
    Root->right = OldR;

    // 更新节点高度
    Root->height = max(height(Root->left), height(Root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// 获取平衡因子 左右子树高度相减
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// 插入节点
struct Node *insert(struct Node *node, int key) {
    // 执行标准BST的插入
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // 重复的键值不允许插入
        return node;

    // 更新节点的高度
    node->height = 1 + max(height(node->left), height(node->right));

    // 获取当前节点的平衡因子
    int balance = getBalance(node);

    // 根据不同的不平衡情况分别进行相应的调整即可  LL RR LR RL
    // 如果节点不平衡，进行旋转操作
    // 左子树不平衡的情况  LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // 右子树不平衡的情况 RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // 左右子树都不平衡的情况 LR型
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL型
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 返回未修改的节点指针
    return node;
}

// 中序遍历AVL树
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        //printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    auto start_insert = high_resolution_clock::now();

    // 插入1到1000
    for (int i = 1; i <= 9999; ++i) {
        root = insert(root, i);
    }

    auto stop_insert = high_resolution_clock::now();
    auto duration_insert = duration_cast<milliseconds>(stop_insert - start_insert);

    cout << "Insertion time for 1000 nodes: " << duration_insert.count() << " milliseconds" << endl;

    // 清空控制台
    system("cls");

    auto start_inorder = high_resolution_clock::now();

    // 中序遍历
    cout << "Inorder traversal of the AVL tree:\n";
    inorder(root);
    cout << endl;

    auto stop_inorder = high_resolution_clock::now();
    auto duration_inorder = duration_cast<milliseconds>(stop_inorder - start_inorder);

    cout << "Inorder traversal time: " << duration_inorder.count() << " milliseconds" << endl;

    return 0;
}