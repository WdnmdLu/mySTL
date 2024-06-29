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

enum Color { RED, BLACK };

// 红黑树节点的定义
struct Node {
    int data;
    Color color;
    Node *left, *right;
    Node *Parent;
    Node(int data,Node *P=nullptr) : data(data), color(RED), left(nullptr), right(nullptr),Parent(P) {}
};

class rbTree {
public:
    rbTree() : Root(nullptr) {}

    // 插入操作
    void Insert(int value) {
        Node *newNode = new Node(value);
        if (Root == nullptr) {
            Root = newNode;
            Root->color = BLACK;
        } else {
            Node *parent = nullptr;
            Node *current = Root;
            while (current != nullptr) {
                parent = current;
                if (value < current->data)
                    current = current->left;
                else if (value > current->data)
                    current = current->right;
                else {
                    delete newNode;
                    return; // 如果节点已经存在，不重复插入
                }
            }

            // 插入新节点
            newNode->Parent = parent;
            if (value < parent->data)
                parent->left = newNode;
            else
                parent->right = newNode;

            // 进行修复操作
            FixInsert(newNode);
        }
    }

    void OrderTree(){
        InOrderTraversal(Root);
    }
    // 中序遍历以验证树的结构和颜色
    void InOrderTraversal(Node *node) {
        if (node == nullptr) return;
        InOrderTraversal(node->left);
        std::cout << node->data << " ";
        if (node->color == RED)
            std::cout << "(RED) ";
        else
            std::cout << "(BLACK) ";
        InOrderTraversal(node->right);
    }

private:
    Node *Root;

    // 插入后修复红黑树性质
    void FixInsert(Node *node) {
        while (node != Root && node->Parent->color == RED) {
            Node *parent = node->Parent;
            Node *grandparent = parent->Parent;

            if (grandparent->left == parent) { // 父节点是祖父节点的左孩子
                Node *uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1: 叔节点是红色
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    // Case 2: 叔节点是黑色，当前节点是右孩子
                    if (node == parent->right) {
                        node = parent;
                        LeftRotate(node);
                        parent = node->Parent;
                    }

                    // Case 3: 叔节点是黑色，当前节点是左孩子
                    parent->color = BLACK;
                    grandparent->color = RED;
                    RightRotate(grandparent);
                }
            } else { // 父节点是祖父节点的右孩子（对称情况）
                Node *uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1: 叔节点是红色
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    // Case 2: 叔节点是黑色，当前节点是左孩子
                    if (node == parent->left) {
                        node = parent;
                        RightRotate(node);
                        parent = node->Parent;
                    }

                    // Case 3: 叔节点是黑色，当前节点是右孩子
                    parent->color = BLACK;
                    grandparent->color = RED;
                    LeftRotate(grandparent);
                }
            }
        }

        // 根节点颜色始终是黑色
        Root->color = BLACK;
    }

    // 右旋操作
    void RightRotate(Node *pivot) {
        Node *leftChild = pivot->left;
        pivot->left = leftChild->right;
        if (leftChild->right != nullptr)
            leftChild->right->Parent = pivot;
        leftChild->Parent = pivot->Parent;
        if (pivot->Parent == nullptr)
            Root = leftChild;
        else if (pivot == pivot->Parent->right)
            pivot->Parent->right = leftChild;
        else
            pivot->Parent->left = leftChild;
        leftChild->right = pivot;
        pivot->Parent = leftChild;
    }

    // 左旋操作
    void LeftRotate(Node *pivot) {
        Node *rightChild = pivot->right;
        pivot->right = rightChild->left;
        if (rightChild->left != nullptr)
            rightChild->left->Parent = pivot;
        rightChild->Parent = pivot->Parent;
        if (pivot->Parent == nullptr)
            Root = rightChild;
        else if (pivot == pivot->Parent->left)
            pivot->Parent->left = rightChild;
        else
            pivot->Parent->right = rightChild;
        rightChild->left = pivot;
        pivot->Parent = rightChild;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        // 最小值肯定在最左边
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    //删除节点
    //如果是叶子节点直接删除即可
    //如果是非叶子节点，删除之后找到左孩子中最大的那个节点替换上来
    Node* DeleteNode(Node *Root,int value){
        if(Root == nullptr){
            return Root;
        }
        if(Root->data > value){
            Root->left = DeleteNode(Root->left,value);
        }
        else if(Root->data < value){
            Root->right = DeleteNode(Root->right,value);
        }//当前的这个Root就是要删除的节点
        else{
            //如果左孩子为空，直接右孩子来接替当前节点的位置
            if(Root->left == nullptr){
                Node *temp = Root->right;
                delete(Root);
                return temp;
            }//如果右孩子为空，直接左孩子来接替当前节点位置
            if(Root->right == nullptr){
                Node *temp = Root->left;
                delete(Root);
                return temp;
            }
            //存在左右孩子
            //找到右孩子中值最小的那个节点
            Node *temp = minValueNode(Root->right);
            Root->key = temp->key;//更新当前root的值为右孩子中最小的key
            //当前Root->right=删除了右孩子中值为key的那个节点即可
            Root->right = DeleteNode(Root->right, temp->key);
        }
        return Root;
    }
};

int main() {
    rbTree tree;

    // 插入测试数据
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(6);

    // 中序遍历打印结果验证红黑树性质
    std::cout << "Inorder traversal of the Red-Black Tree:" << std::endl;
    tree.OrderTree();
    std::cout << std::endl;

    return 0;
}