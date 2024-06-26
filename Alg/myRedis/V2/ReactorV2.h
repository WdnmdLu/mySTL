#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <semaphore.h>

#define MAX_EVENTS 64
#define PORT 9999
#define MAX_THREADS 4

typedef void (*Callback)(void *arg);

void *ThreadFunc(void *arg);

struct event_data {
    int fd;
    Callback callback;
};

struct Sub_data{
    int epoll_fd;
    int eventfd;
    Callback callback;
};

void handle_accept(void *arg);

// 创建主Reactor的lfd
int Init_Server();
// 返回mainReactor的Epoll_Fd
int Epoll_lfd(int lfd);
// 启动mainReactor
void Run(int epoll_fd);

void onMessage(void *arg);

void onConnect(void *arg);

int Epoll_sfd(int efd);

// 启动SubThread
void SubRun(int epoll_fd);
void *ThreadFunc(void *arg);

// 设置SubThread的数量
void SetThreadNum(int Num);

