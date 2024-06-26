#include "ReactorV2.h"

int main() {
    

    int lfd = Init_Server();
    int epoll_fd = Epoll_lfd(lfd);
    SetThreadNum(3);

    //启动整个服务  包括线程创建  主Reactor的启动和SubReactor的启动
    Run(epoll_fd);
    return 0;
}