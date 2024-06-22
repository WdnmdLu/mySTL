#include <iostream>

#include <iostream>

class Queue {
public:
    Queue(int Size = 10) : size(Size), front(0), back(0) {
        array = new int[Size]();
    }

    ~Queue() {
        delete[] array;
    }

    void Push(int val) {
        if (IsFull()) {
            std::cout << "Queue is full. Cannot push element." << std::endl;
            return;
        }
        array[back] = val;
        back = (back + 1) % size;
    }

    void Pop() {
        if (IsEmpty()) {
            std::cout << "Queue is empty. Cannot pop element." << std::endl;
            return;
        }
        front = (front + 1) % size;
    }

    int Front() {
        if (IsEmpty()) {
            std::cout << "Queue is empty. No front element." << std::endl;
            return -1; // Assuming -1 represents an invalid value
        }
        return array[front];
    }

    bool IsEmpty() {
        return front == back;
    }

    bool IsFull() {
        return (back + 1) % size == front;
    }

private:
    int front, back;
    int size;
    int* array;
};

int main(){

}