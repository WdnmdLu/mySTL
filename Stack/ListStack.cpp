#include <iostream>
#include <string.h>
class Stack{
public:
    Stack(){
        head = new Node();
        head->data = 0;
        head->next = nullptr;
    }
    ~Stack(){
        Node* pMove=head->next;
        while(pMove!=nullptr){
            Node *temp = pMove;
            pMove = pMove->next;
            delete(temp);
        }
        delete(head);
    }
    void Push(int val){
        Node *newNode = new Node();
        newNode->data = val;
        newNode->next = head->next;
        head->next = newNode;
    }
    int Pop(){
        if(head->next == nullptr){
            return -1;
        }
        int num = head->next->data;
        Node *temp = head->next;
        head->next = temp->next;
        delete(temp);
        return num;
    }
    void Show(){
        Node *pMove = head->next;
        while(pMove!=nullptr){
            std::cout<<pMove->data<<" ";
            pMove=pMove->next;
        }
        std::cout<<std::endl;
    }
private:
    struct Node{
        Node *next;
        int data;
    };
private:
    Node *head;
};

int main(){
    Stack stack;
    stack.Push(3);
    stack.Push(2);
    stack.Push(1);
    stack.Push(3);
    stack.Push(2);
    stack.Push(1);
    stack.Push(3);
    stack.Pop();
    stack.Pop();
    stack.Push(2);
    stack.Push(1);
    stack.Show();
}