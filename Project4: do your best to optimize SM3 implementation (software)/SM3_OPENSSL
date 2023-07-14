#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
#include <stdio.h>
#include <string.h>
#include "sm3hash.h"
#include <chrono>
#include<iostream>
int main(void)
{
	const unsigned char sample1[] = { 'a', 'b', 'c'};
	unsigned int sample1_len = strlen((char*)sample1);
	const unsigned char sample2[] = { 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64 };
	unsigned int sample2_len = sizeof(sample2);
	unsigned char hash_value[64];
	unsigned int i, hash_len;
	auto start = std::chrono::high_resolution_clock::now();
	for(int i=0;i<1;i++)sm3_hash(sample1, sample1_len, hash_value, &hash_len);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "耗时: " << duration.count() << " 秒" << std::endl;
	std::cout << "Hash speed:" << (sample1_len / duration.count()) / 1000000 << "MB/s." << std::endl;
	
	auto start1 = std::chrono::high_resolution_clock::now();
	for(int i=0;i<10000;i++)sm3_hash(sample2, sample2_len, hash_value, &hash_len);
	auto end1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration1 = end1 - start1;
	std::cout << "耗时: " << duration1.count() << " 秒" << std::endl;
	std::cout << "Hash speed:" << (sample2_len / duration1.count()) / 1000000 << "MB/s." << std::endl;
	
	return 0;
}
