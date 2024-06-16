#include <iostream>

class Queue{

public:
    Queue(){
        size = 0;
        head = new Node();
        head->next = nullptr;
    }
    ~Queue(){
        Node *pMove = head->next;
        while(pMove != nullptr){
            Node *temp = pMove;
            pMove=pMove->next;
            delete(temp);
        }
    }
    void Push(int val){
        Node *newNode = new Node();
        newNode->next = head->next;
        head->next = newNode;
        newNode->data = val;
        size++;
    }
    int Pop(){
        Node *pMove=head;
        if(size == 0){
            return -1;
        }
        while(pMove->next->next!=nullptr){
            pMove=pMove->next;
        }
        int num = pMove->next->data;
        delete(pMove->next);
        pMove->next=nullptr;
        return num;
    }
    void Show(){
        Node *pMove=head->next;
        while(pMove!= nullptr){
            printf("%d ",pMove->data);
            pMove=pMove->next;
        }
        printf("\n");
    }
private:
    struct Node{
        struct Node *next;
        int data;
    };
private:
    int size;
    Node *head;
};

int main(){
    Queue q;
    q.Push(12);
    q.Push(13);
    q.Push(25);
    q.Show();
    std::cout<<q.Pop()<<std::endl;
    q.Show();
}