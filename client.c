#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "::1"  // 服务器IPv6地址
#define PORT "8080"      // 服务器端口号


int main(void) {
    struct sockaddr_in6 server_addr;
    int sock1;
    char *message = "Hello";

    // 创建IPv6套接字
    if ((sock1 = socket(AF_INET6, SOCK_DGRAM, 0)) == -1) {
        printf("failed to create a socket\n");
        exit(1);
    }

    // 初始化服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(atoi(PORT));
    inet_pton(AF_INET6, SERVER_IP, &server_addr.sin6_addr);
    while(1){
        // 发送消息到服务器
        if (sendto(sock1, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            printf("failed to send\n");
            exit(1);
        }
        sleep(1);
    }

    printf("Message sent to server: %s\n", message);

    close(sock1);
    return 0;
}

