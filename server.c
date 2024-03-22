#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT "8080"  // 服务器监听的端口号

int main(void) {
    struct sockaddr_in6 server_addr, client_addr;
    int sock;
    int  recv_len;
    socklen_t addr_len;
    char buffer[1024];
    char addr_of_cli[50];

    // 创建IPv6套接字
    if ((sock = socket(AF_INET6, SOCK_DGRAM, 0)) == -1) {
        printf("failed to create a socket\n");
        exit(1);
    }

    // 初始化服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(atoi(PORT));
    server_addr.sin6_addr = in6addr_any;

    // 将套接字绑定到服务器地址
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("failed to bind\n");
        exit(1);
    }

    printf("Server listening on port %s...\n", PORT);

    while (1) {
        // 接收来自客户端的消息
        addr_len = sizeof(client_addr);
        if ((recv_len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
            printf("failed to receive data\n");
            exit(1);
        }

        buffer[recv_len] = '\0';
        printf("The address of client is %s\n", inet_ntop(AF_INET6, &client_addr.sin6_addr, addr_of_cli, sizeof(addr_of_cli)));
        printf("message:%s\n",buffer);
    }

    close(sock);
    return 0;
}
