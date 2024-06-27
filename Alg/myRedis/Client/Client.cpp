#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024


int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // 将IP地址从文本转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server at %s:%d\n", SERVER_IP, SERVER_PORT);

    while (true) {
        std::string input;
        
        // 提示用户输入
        std::cout << SERVER_IP<<":"<<SERVER_PORT<<">";
        
        // 读取一行输入
        std::getline(std::cin, input);
        
        // 检查是否输入exit，如果是则退出循环
        write(sockfd,input.c_str(),input.size());
        int len = read(sockfd,buffer,BUFFER_SIZE);
        if(strcmp(buffer,"OUT") == 0){
            break;
        }
        printf("%s\n",buffer);
        memset(buffer,0,len);
    }
    close(sockfd);
    return 0;
}