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
    //输入自己拥有的数字，生成一个签名
    int Havenumber;
    std::cin >> Havenumber;
    std::string proof=init_two_string(Havenumber);

    //开始网络连接
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize winsock." << std::endl;
        return 1;
    }

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(12345);

    if (bind(listenSock, (const sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        std::cerr << "Binding failed." << std::endl;
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    std::cout << "Waiting for connection from A..." << std::endl;

    SOCKET connSock = INVALID_SOCKET;
    while (connSock == INVALID_SOCKET) {
        connSock = accept(listenSock, nullptr, nullptr);
        if (connSock == INVALID_SOCKET) {
            std::cerr << "Accept failed. Retrying..." << std::endl;
        }
    }

    std::cout << "Connection established with A." << std::endl;

    // 从A接收要验证的数字
    char buffer[BUFFER_SIZE];
    int receivedBytes = recv(connSock, buffer, BUFFER_SIZE, 0);
    if (receivedBytes == SOCKET_ERROR) {
        std::cerr << "Receiving failed." << std::endl;
        closesocket(connSock);
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }
    buffer[receivedBytes] = '\0';
    std::string number(buffer);
    int verifynumber = std::stoi(number);
    std::cout << "Received number from A: " << number << std::endl;

    //将两个数字发给A
    std::string hexNumber1 = proof.substr(0, 32);
    hexNumber1=sm3_n_times(hexNumber1, Havenumber - verifynumber);
    std::string hexNumber2 = proof.substr(proof.length() - 64, 64);

    int sentBytes1 = send(connSock, hexNumber1.c_str(), hexNumber1.size(), 0);
    if (sentBytes1 == SOCKET_ERROR) {
        std::cerr << "Sending failed." << std::endl;
        closesocket(connSock);
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    int sentBytes2 = send(connSock, hexNumber2.c_str(), hexNumber2.size(), 0);
    if (sentBytes2 == SOCKET_ERROR) {
        std::cerr << "Sending failed." << std::endl;
        closesocket(connSock);
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    std::cout << "Sent two numbers to A." << std::endl;

    // 从A处接收是否成功的消息
    int receivedBytes2 = recv(connSock, buffer, BUFFER_SIZE, 0);
    if (receivedBytes2 == SOCKET_ERROR) {
        std::cerr << "Receiving failed." << std::endl;
        closesocket(connSock);
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }
    buffer[receivedBytes2] = '\0';
    std::string message(buffer);

    std::cout << "Received message from A: " << message << std::endl;

    closesocket(connSock);
    closesocket(listenSock);
    WSACleanup();

    return 0;
}












