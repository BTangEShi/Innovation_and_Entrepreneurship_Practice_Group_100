#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize winsock." << std::endl;
        return 1;
    }

    std::string serverIP = "127.0.0.1";
    int serverPort = 12345;

    SOCKET sockfd = INVALID_SOCKET;
    while (sockfd == INVALID_SOCKET) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == INVALID_SOCKET) {
            std::cerr << "Socket creation failed. Retrying..." << std::endl;
        }
    }

    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP.c_str(), &(servaddr.sin_addr));

    while (true) {
        if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != SOCKET_ERROR) {
            break;
        }

        std::cerr << "Connection failed. Retrying..." << std::endl;
    }

    std::cout << "Connected to B." << std::endl;

    // 发送要求验证的数字
    std::string number = "123";
    int sentBytes = send(sockfd, number.c_str(), number.size(), 0);
    if (sentBytes == SOCKET_ERROR) {
        std::cerr << "Sending failed." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // 从B处接收两个数字，一个是hash的中间结果，一个是最终结果
    char buffer[BUFFER_SIZE];
    int receivedBytes1 = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (receivedBytes1 == SOCKET_ERROR) {
        std::cerr << "Receiving failed." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    buffer[receivedBytes1] = '\0';
    std::string hexNumber1(buffer);

    int receivedBytes2 = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (receivedBytes2 == SOCKET_ERROR) {
        std::cerr << "Receiving failed." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    buffer[receivedBytes2] = '\0';
    std::string hexNumber2(buffer);

    std::cout << "Received numbers from B: " << hexNumber1 << ", " << hexNumber2 << std::endl;

    // 发送验证结果消息给B
    std::string message = "Hello from A!";
    int sentBytes2 = send(sockfd, message.c_str(), message.size(), 0);
    if (sentBytes2 == SOCKET_ERROR) {
        std::cerr << "Sending failed." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    std::cout << "Sent message to B." << std::endl;

    closesocket(sockfd);
    WSACleanup();

    return 0;
}
