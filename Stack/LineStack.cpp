//顺序栈
#include <iostream>
#include <string.h>
class Stack{
public:
    Stack(int cap=1):Cap(cap),size(0){
        stack = new int[cap]();
    }
    ~Stack(){
        delete[] stack;
    }
    void Push(int val){
        if(size == Cap){
            expand(size*2);
        }
        stack[size] = val; 
        size++;
    }
    int Pop(){
        if(size == 0){
            return -1;
        }
        int num = stack[size-1];
        size--;
        return num;
    }
    void Show(){
        for(int i=size-1;i>=0;i--){
            std::cout<<stack[i]<<" ";
        }
        std::cout<<std::endl;
    }
private:
    void expand(int num){
        int *newStack = new int[num]();
        for(int i=0;i<size;i++){
            newStack[i] = stack[i];
        }
        delete[] stack;
        stack = newStack;
        Cap = num;
    }

private:
    int *stack;
    int size;
    int Cap;
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
    stack.Push(2);
    stack.Push(1);
    stack.Show();
}