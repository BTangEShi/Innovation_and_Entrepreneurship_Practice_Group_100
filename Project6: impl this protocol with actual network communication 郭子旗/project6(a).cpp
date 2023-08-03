#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024

std::string sm3(const std::string& message) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    OpenSSL_add_all_digests();
    md = EVP_get_digestbyname("sm3");

    if (!md) {
        std::cerr << "Error: SM3 not supported!" << std::endl;
        return "";
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, message.c_str(), message.length());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    char result_hex[2 * EVP_MAX_MD_SIZE + 1];
    for (unsigned int i = 0; i < md_len; i++) {
        sprintf(&result_hex[i * 2], "%02x", (unsigned int)md_value[i]);
    }

    return std::string(result_hex);
}


std::string sm3_n_times(const std::string& message, int n) {
    if (n <= 0) {
        std::cerr << "Error: Invalid value of n. n should be greater than 0." << std::endl;
        return "";
    }

    std::string hash_value = message;
    for (int i = 0; i < n; i++) {
        hash_value = sm3(hash_value);
    }

    return hash_value;
}

std::string generate_random_string() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);

    std::stringstream ss;
    for (int i = 0; i < 2; i++) {
        uint64_t random_value = dis(gen);
        ss << std::setfill('0') << std::setw(16) << std::hex << random_value;
    }

    return ss.str();
}

std::string init_two_string(int n) {
    std::string seed = generate_random_string();
    std::cout << "seed: " << seed << std::endl;
    std::string signature = sm3_n_times(seed, n);
    std::cout << "signature: " << signature << std::endl;
    return seed + signature;
}

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
    int nihao;
    std::cout << "Please enter a number.\n";
    std::cin >> nihao;
    std::string number = std::to_string(nihao);
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
    std::string message = "";
    if (sm3_n_times(hexNumber1, nihao) == hexNumber2)  message = "Pass!";
    else message = "Fail!";

    // 发送验证结果消息给B
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














