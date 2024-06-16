#include <iostream>

class Node{
public:
    Node(int Data = 0):data(Data),next(nullptr){}
    int data;
    Node *next;
};

class list{
public:
    list(){
        head = new Node();
        tail = nullptr;
        size = 0;
    }
    ~list(){
        while(head->next!=nullptr){
            Node *pMove = head->next;
            delete(head);
            head = pMove;
        }
    }
    //删除链表中所有data == val 的节点
    void DeleteAll(int val){
        if(size == 0){
            return;
        }
        Node *pMove = head;
        while(pMove->next != nullptr){
            if(pMove->next->data == val){
                Node *temp = pMove->next;
                pMove->next = temp->next;
                delete(temp);
                continue;
            }
            pMove=pMove->next;
        }
        tail = pMove;
    }
    void insertByHead(int data){
        size++;
        Node *newNode = new Node(data);
        if(head->next == nullptr){
            tail = newNode;
        }
        newNode->next = head->next;
        head->next = newNode;
        
    }
    void insertByTail(int data){
        Node *newNode = new Node(data);
        size++;
        if(head->next == nullptr){
            tail = newNode;
            head->next = newNode;
            newNode->next = nullptr;
            return;
        }
        tail->next = newNode;
        tail = newNode;
        
    }
    void Show(){
        Node *pMove=head->next;
        while (pMove!=nullptr)
        {
            printf("%d ",pMove->data);
            pMove=pMove->next;
        }
        printf("\n");
    }

    int PopFront(){
        if(size == 0){
            return -1;
        }
        size--;
        Node *p;
        p=head->next;
        head->next = p->next;
        int num = p->data;
        delete(p);
        return num;
    }

    int PopBack(){
        if(size == 0){
            return -1;
        }
        Node *pMove = head;
        while(pMove->next != tail){
            pMove=pMove->next;
        }
        int num = tail->data;
        delete(tail);
        pMove->next=nullptr;
        tail = pMove;
        return num;
    }

    void ReverseList(){
        Node *p,*q;
        p=head->next;
        q=head->next;
        head->next = nullptr;
        while(q!=nullptr){
            p=q;
            q=q->next;
            p->next = head->next;
            head->next = p;
        }
    }
    //倒数第k个节点
    void PopKNode(int val){
        if(val > size){
            return;
        }
        ReverseList();
        Node *pMove = head;
        for(int i=0;i<val;i++){
            pMove = pMove->next;
        }
        printf("K: %d\n",pMove->data);
        ReverseList();
        return;
    }
private:
    Node *head;
    Node *tail;
    int size;
};

int main(){
    list L;
    L.insertByHead(1);
    L.insertByHead(2);
    L.insertByHead(3);
    L.Show();
    L.insertByTail(4);
    L.insertByTail(3);
    L.insertByTail(5);
    L.insertByTail(3);
    L.insertByTail(6);
    L.Show();
    L.DeletePopK(3);
    printf("111\n");
    L.Show();
    L.insertByTail(3);
    L.Show();
    L.PopKNode(5);
    L.ReverseList();
    L.Show();
    L.DeleteAll(3);
    L.Show();
    printf("PopFront:%d\n",L.PopFront());
    L.Show();
    printf("PopBack:%d\n",L.PopBack());
    L.Show();


    
}