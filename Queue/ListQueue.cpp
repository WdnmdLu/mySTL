#include <iostream>
#include <pthread.h>
#include <unistd.h>
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
                tail = newNode;
            }
        }
        pthread_mutex_init(&Mut,NULL);
    }
    ~Queue(){ 
        Node *pMove = head->next;
        Node *temp;
        while(pMove != NULL){
            temp = pMove;
            pMove = pMove->next;
            if(temp->data != NULL){
                free(temp->data);
            }
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
        // 释放节点数据
        Node *temp = head->next;
        if(temp == curr){
            curr = head;
        }
        head->next = temp->next;
        temp->next = NULL;
        free(temp->data);
        temp->data = NULL;
        // 将节点插入到队尾从新进行利用
        tail->next = temp;
        tail = temp;
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
        printf("Expand Queue\n");
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
    // 指向最后一个位置的节点，用于进行扩容操作
    Node *tail;

    pthread_mutex_t Mut;
};
static int flag = 1;
void* ThreadFunction(void *arg){
    Queue *q = (Queue*)arg;

    while(flag == 1){
        if(q->GetSize() == 0){
            usleep(10);
            continue;
        }
        std::cout<<"Data: "<<*(int*)q->Front()<<std::endl;
        q->Pop();
    }

    return NULL;
}

void test01(){
    Queue q;
    pthread_t tid;
    pthread_create(&tid,NULL,ThreadFunction,&q);
    int i;
    for(i = 0 ; i < 100 ; i++){
        int *data = (int*)malloc(sizeof(int));
        *data = i;
        while (q.GetSize() > 5)
        {
            usleep(10);
        }
        q.Push(data);
    }
    while(q.GetSize() > 0){
        usleep(10);
    }
    flag = 0;
    pthread_join(tid,NULL);
}

void test02(){
    Queue q;
    int i;
    for(i = 0; i < 100 ; i++){
        int *data = (int*)malloc(sizeof(int));
        *data = i;
        q.Push(data);
    }
    int j = 0;
    printf("QueueSize: %d\n",q.GetSize());
    int Size = q.GetSize();
    for(i = 0 ; i < Size ; i++){
        printf("%d ",*(int*)q.Front());
        q.Pop();
        j++;
        if(j == 5){
            j = 0;
            printf("\n");
        }
    }
}

int main(){
    test01();

    return 0;
}
