#include <iostream>
#include <pthread.h>
#include <SDL.h>
class Queue{
public:
    Queue(int Cap = 2){
        Capacity = Cap;
        size = 0;
        head = (Node*)malloc(sizeof(Node));
        head->next = NULL;
        head->data = NULL;
        curr = head;
        tail = head;
        int i;
        // 建立Capacity个新的节点
        for(i = 0; i < Capacity ; i++){
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->next = head->next;
            head->next = newNode;
            if(i == 0){
                tail= newNode;
            }
        }
        i=0;
        Node *pMove = head->next;
        while(pMove != NULL){
            pMove = pMove->next;
            i++;
        }
        printf("%d   %d\n",i,Capacity);

        pthread_mutex_init(&Mut,NULL);
        pthread_cond_init(&Cond,NULL);
    }
    ~Queue(){ 
        Node *pMove = head->next;
        Node *temp;
        while(pMove != NULL){
            temp = pMove;
            pMove = pMove->next;
            free(temp->data);
            free(temp);
        }
    }
    //放入
    void Push(void *data){
        pthread_mutex_lock(&Mut);
        // 先判断当前的Size和Capacity是否相同
        if(size == Capacity){
            expand();
        }
        curr = curr->next;
        curr->data = data;
        size++;
        pthread_mutex_unlock(&Mut);
    }
    // 队头的数据出队
    void Pop(){
        pthread_mutex_lock(&Mut);
        if(size == 0){
            return;
        }
        Node *temp = head->next;
        if(size == 1){
            curr = head;
            head->next = NULL;
            free(temp->data);
            free(temp);
        }
        else{
            head->next = temp->next;
            free(temp->data);
            free(temp);
        }
        size--;
        pthread_mutex_unlock(&Mut);
    }
    // 获取到队头的数据
    void *Front(){
        if(size > 0){
            return head->next->data;
        }
        return NULL;
    }
    // 进行二倍扩容
    void expand(){
        for(int i = 0; i < Capacity ; i++){
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        Capacity *= 2;
    }

    int GetSize(){
        return size;
    }

    int GetCap(){
        return Capacity;
    }
    
private:
    struct Node{
        struct Node *next;
        // 通过void*用户可以指定任意的数据类型，可以是基本数据类型，int，float或者特殊结构体，AVPacket，AVFrame等等
        void* data;
    };
private:
    // 队列当前的数据量大小
    int size;
    // 队列的容量
    int Capacity;
    // 队头指针，用于表示整个队列
    Node *head;
    // 最新入队的数据
    Node *curr;
    // 指向最后一个位置的节点
    Node *tail;

    pthread_mutex_t Mut;
    pthread_cond_t Cond;
};

int main(){
    Queue q;
    for(int i = 0; i < 100 ; i++){
        int *data1 = (int*)malloc(sizeof(int));
        *data1 = i;
        q.Push(data1);
    }
    for(int i = 0; i < 100 ; i++){
        printf("%d  Size: %d\n",*(int*)q.Front(),q.GetSize());
        q.Pop();
    }
    
    
    
    printf("\n");
}
