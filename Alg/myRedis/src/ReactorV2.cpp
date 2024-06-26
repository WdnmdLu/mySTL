#include "ReactorV2.h"
#include <string>
#include <string.h>
int SubThreadNum = 0;
int *EventArr;
int Index = 0;

sem_t Full;
sem_t Empty;

void handle_accept(void *arg){
    int lfd = *((int*)arg);
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 接受连接
    int client_fd = accept(lfd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd == -1) {
        perror("accept");
        return;
    }
    
    printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    printf("ClientFd: %d\n",client_fd);
    uint64_t value = client_fd;
    printf("Value: %ld\n",value);
    // printf("Index: %d   EventArr[Index]=%d\n",Index,EventArr[Index]);
    sem_wait(&Full);
    write(EventArr[Index],&value,value);
    sem_post(&Empty);
    Index = (Index + 1) % SubThreadNum;
}

int Init_Server(std::string Ip, int Port) {
    sem_init(&Full, 0, 1);
    sem_init(&Empty, 0, 0);
    struct sockaddr_in server_addr;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(Ip.c_str()); // Convert std::string IP to const char* and then to in_addr_t
    server_addr.sin_port = htons(Port); // Use the passed-in Port parameter

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("listen error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return server_fd;
}


// 返回mainReactor的Epoll_Fd
int Epoll_lfd(int lfd) {
    // 创建 epoll 实例
    int epoll_fd = epoll_create(1);

    // 绑定连接建立时的回调函数
    struct epoll_event event;
    event.data.ptr = malloc(sizeof(struct event_data));
    ((struct event_data*)event.data.ptr)->fd = lfd;
    ((struct event_data*)event.data.ptr)->callback = handle_accept;
    event.events = EPOLLIN; // 监听读事件
    
    // 将连接事件添加到epoll红黑树实例中
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, lfd, &event) == -1) {
        perror("Epoll_lfd epoll_ctl");
        exit(EXIT_FAILURE);
    }
    return epoll_fd; // 返回 epoll 实例的文件描述符
}
// 启动mainReactor
void Run(int epoll_fd){
    pthread_t threads[SubThreadNum];
    for(int i=0;i<SubThreadNum;i++){
        pthread_create(&threads[i],NULL,ThreadFunc,(void*)(EventArr+i));
        pthread_detach(threads[i]);
    }

    struct epoll_event events[MAX_EVENTS];
    while(1){
        int ready_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (ready_count == -1) {
            perror("epoll_wait");
        }
        for (int i = 0; i < ready_count; ++i) {
            struct event_data *data = (struct event_data*)events[i].data.ptr;
            data->callback((void*)(&(data->fd)));
        }
    }
}
// 数据接收，所有的数据全都通过这个函数进行接收并处理
void onMessage(void *arg){
    struct Sub_data *data = (struct Sub_data *)arg;
    int cfd = data->eventfd;
    char buffer[1024]={0};
    int len = read(cfd,buffer,1024);
    int epoll_fd = data->epoll_fd;
    // 如果客户端关闭连接或读数据出现错误，需要使用epoll_fd从上面删除对应的client_fd
    if(len == 0 ){
        close(cfd);
        // 从epoll_fd上将对应的cfd删除
        epoll_ctl(epoll_fd,EPOLL_CTL_DEL,cfd,NULL);
        return;
    }
    if(len < 0){
        perror("write");
        close(cfd);
        epoll_ctl(epoll_fd,EPOLL_CTL_DEL,cfd,NULL);
        return;
    }
    std::string str(buffer);
    std::cout<<"Msg: "<<str<<std::endl;
    const char* Res = myRedis::GetInstance().Parse(str);
    printf("Res: %s\n",Res);
    write(cfd,Res,strlen(Res));
}

void onConnect(void *arg){
    printf("OnConnect!!!\n");
    struct Sub_data *data = (struct Sub_data *)arg;
    int eventFd = data->eventfd;
    int epoll_fd = data->epoll_fd;
    uint64_t value;
    sem_wait(&Empty);
    read(eventFd,&value,sizeof(value));
    sem_post(&Full);
    printf("EventFd: %d   Epoll_fd: %d    Client_fd: %ld\n",eventFd,epoll_fd,value);


    // 添加到epoll中
    struct epoll_event event;
    event.data.ptr = malloc(sizeof(struct Sub_data));
    ((struct Sub_data*)event.data.ptr)->eventfd = (int)value;
    ((struct Sub_data*)event.data.ptr)->epoll_fd = epoll_fd;
    ((struct Sub_data*)event.data.ptr)->callback = onMessage;
    event.events = EPOLLIN; // 监听读事件
    
    // 将连接事件添加到epoll红黑树实例中
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, value, &event) == -1) {
        perror("onConnect epoll_ctl");
        exit(EXIT_FAILURE);
    }
}

int Epoll_sfd(int efd){
    // 创建 epoll 实例
    int epoll_fd = epoll_create(1);

    // 绑定连接建立时的回调函数
    struct epoll_event event;
    event.data.ptr = malloc(sizeof(struct Sub_data));
    ((struct Sub_data*)event.data.ptr)->epoll_fd = epoll_fd;
    ((struct Sub_data*)event.data.ptr)->eventfd = efd;
    ((struct Sub_data*)event.data.ptr)->callback = onConnect;// eventfd对应的回调函数
    event.events = EPOLLIN; // 监听读事件
    // 将连接事件添加到epoll红黑树实例中
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, efd, &event) == -1) {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }
    // printf("EventFd: %d  Add Success\n",efd);
    return epoll_fd; // 返回 epoll 实例的文件描述符
}

void SubRun(int epoll_fd){
    struct epoll_event events[MAX_EVENTS];
    while(1){
        int ready_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (ready_count == -1) {
            perror("epoll_wait");
        }
        for (int i = 0; i < ready_count; ++i) {
            struct Sub_data *data = (struct Sub_data*)events[i].data.ptr;
            data->callback(events[i].data.ptr);
        }
    }
}

void *ThreadFunc(void *arg){
    int EventFd = *(int*)arg;
    printf("ThreadFunc:  %d\n",EventFd);
    int efd = Epoll_sfd(EventFd);
    SubRun(efd);
    return NULL;
}

void SetThreadNum(int Num){
    SubThreadNum = Num;
    EventArr = (int*)malloc(sizeof(int) * SubThreadNum);
    if (EventArr == NULL) {
        // Handle allocation failure
        perror("Failed to allocate memory for EventArr");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < SubThreadNum; j++) {     
        int evtfd = eventfd(0, 0); // Create eventfd with initial value 0
        if (evtfd == -1) {
            // Handle error
            perror("Failed to create eventfd");
            exit(EXIT_FAILURE);
        }
        EventArr[j] = evtfd;
        //printf("Index: %d   EventArr[j] %d\n", j, EventArr[j]);
    }
}

