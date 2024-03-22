#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void sendUdpPacket(char *ip) {
    int udpSocket;
    struct sockaddr_in6 serverAddr;
    char buffer[] = "Discover";

    // 创建UDP套接字
    if ((udpSocket = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create UDP socket");
        return;
    }

    // 设置服务器地址信息
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin6_family = AF_INET6;
    serverAddr.sin6_port = htons(PORT);
    if (inet_pton(AF_INET6, ip, &serverAddr.sin6_addr) <= 0) {
        perror("Invalid IPv6 address");
        close(udpSocket);
        return;
    }

    // 发送UDP数据包
    if (sendto(udpSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Failed to send UDP packet");
    }

    close(udpSocket);
}

int main() {
    char ipv6Address[] = "::1";  //目标IPv6地址
    sendUdpPacket(ipv6Address);
    return 0;
}
