#include <iostream>
#include <chrono>
#include "stringhash.h"
#include <string.h>
#include <vector>
using namespace std;

// 找到最小不平衡子树的根，对其进行更新
/*
    左旋
        旧根节点为新根节点的左
        新根节点的右为旧根节点的左
    右旋
        旧根节点为新根节点的右子树
        新根节点的右子树(如果存在)为旧根节点的左子树
*/
// AVL树节点结构
struct TNode {
    int key;
    std::string value;
    struct TNode *left;
    struct TNode *right;
    int height;
};


class BST{
public:
    BST():Root(nullptr){}
    void Insert(std::string Key,std::string value){
        int key = BKDRHash(Key.c_str());
        char Res[1024]={0};
        strcpy(Res,value.c_str());
        find(this->Root,key,Res,1);
        Root = insert(Root,key,value);
    }
    void Find(std::string Key,char *buffer){
        int key = BKDRHash(Key.c_str());
        find(this->Root,key,buffer,0);
    }
    void Del(std::vector<string> Str,char *buffer){
        int key;
        int count = 0;
        for(int i = 0;i<Str.size();i++){
            key = BKDRHash(Str[i].c_str());
            DeleteNode(Root,key,&count);
        }
        std::stringstream ss;
        ss << count;
        std::string Res=("(integer)");
        Res+=ss;
        strcpy(buffer,Res.c_str());
    }
private:
    // 获取节点的高度
    int height(struct TNode *N);

    // 获取两个整数中较大的值
    int max(int a, int b);

    // 创建一个新的节点
    struct TNode *newTNode(int key,std::string &value);

    // 右旋操作
    struct TNode *rightRotate(struct TNode *Root);

    // 左旋操作
    struct TNode *leftRotate(struct TNode *Root);

    // 获取平衡因子 左右子树高度相减
    int getBalance(struct TNode *N);

    // 插入节点
    struct TNode *insert(struct TNode *TNode, int key,std::string &value);

    // find的结果会存放到Res中
    void find(struct TNode *Root,int key,char *Res,int flag);

    TNode* minValueNode(TNode* node);
    TNode* DeleteNode(TNode *Root,int value,int *Count);
    TNode* Root;

};