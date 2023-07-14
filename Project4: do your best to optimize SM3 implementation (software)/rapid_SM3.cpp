#include<iostream>
#include <iomanip>
#include <chrono>
#include <immintrin.h>
using namespace std;
uint32_t W[68];
uint32_t W_[64];
uint32_t IV[] = { 0x7380166f ,0x4914b2b9 ,0x172442d7 ,0xda8a0600 ,0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e };
uint32_t result[8];
char fake_input[100];
uint32_t temp[8];
uint32_t paddedResult[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000,0x00000000, 0x00000000 };
uint32_t IV1[] = { 0x6c781f1a,0x541010aa,0xa20d9999,0xb963be0a,0xd34bcbdc,0xafa43bc0,0x9ec49c19,0x9f0e45e7 };
uint32_t T[64] = { 0x79cc4519,0x79cc4519,0x79cc4519,0x79cc4519,0x79cc4519,0x79cc4519,0x79cc4519,0x79cc4519,
0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519,0x79cc4519, 0x79cc4519, 0x79cc4519 ,0x79cc4519,
0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,
0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,
0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,
0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,
0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,
0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a,0x7a879d8a ,0x7a879d8a ,0x7a879d8a ,0x7a879d8a };
void Log(uint32_t* ts, int num)
{
	for (int i = 0;i < num;i++)
	{
		cout << "0x" << setfill('0') << setw(8) << hex << ts[i] << ",";
	}
	cout << endl;
}
uint32_t Rotate_left(uint32_t value, int shift)
{
	if ((shift &= sizeof(value) * 8 - 1) == 0)
		return value;
	return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}
uint32_t P1(uint32_t temp)
{
	return temp ^ Rotate_left(temp, 15) ^ Rotate_left(temp, 23);
}
void ExpandMessage(uint32_t* paddedResult, uint32_t* W, uint32_t* W_)
{
	__m512i a = _mm512_load_epi32(paddedResult);
	_mm512_store_epi32(W, a);

	for (int i = 16;i < 68;i += 2)
	{
		uint32_t temp1 = W[i - 16] ^ W[i - 9] ^ (Rotate_left(W[i - 3], 15));
		uint32_t temp2 = W[i - 15] ^ W[i - 8] ^ (Rotate_left(W[i - 2], 15));
		uint32_t fake1 = Rotate_left(W[i - 13], 7);
		uint32_t fake2 = Rotate_left(W[i - 12], 7);
		W[i] = P1(temp1) ^ (fake1) ^ W[i - 6];
		W[i + 1] = P1(temp2) ^ (fake2) ^ W[i - 5];
	}
	for (int i = 0;i < 64;i += 4)
	{
		W_[i] = (W[i] ^ W[i + 4]);
		W_[i + 1] = (W[i + 1] ^ W[i + 5]);
		W_[i + 2] = (W[i + 2] ^ W[i + 6]);
		W_[i + 3] = (W[i + 3] ^ W[i + 7]);
	}
}
uint32_t P0(uint32_t X)
{
	return X ^ Rotate_left(X, 9) ^ Rotate_left(X, 17);
}
uint32_t FF1(uint32_t X, uint32_t Y, uint32_t Z)
{
	return (X ^ Y ^ Z);
}
uint32_t FF2(uint32_t X, uint32_t Y, uint32_t Z)
{
	return (X & Y) | (X & Z) | (Y & Z);
}
uint32_t GG1(uint32_t X, uint32_t Y, uint32_t Z)
{
	return (X ^ Y ^ Z);
}
uint32_t GG2(uint32_t X, uint32_t Y, uint32_t Z)
{
	return (X & Y) | ((~X) & Z);
}
uint32_t FF(int j, uint32_t X, uint32_t Y, uint32_t Z)
{
	if (j >= 0 && j <= 15)
	{
		return FF1(X, Y, Z);
	}
	else if (j >= 16 && j <= 63)
	{
		return FF2(X, Y, Z);
	}
	else
	{
		cout << "FF is ERROR!" << endl;
	}
}
uint32_t GG(int j, uint32_t X, uint32_t Y, uint32_t Z)
{
	if (j >= 0 && j <= 15)
	{
		return GG1(X, Y, Z);
	}
	else if (j >= 16 && j <= 63)
	{
		return GG2(X, Y, Z);
	}
	else
	{
		cout << "GG is ERROR!" << endl;
	}
}
uint32_t* Compress(uint32_t* IV, uint32_t* W, uint32_t* W_, uint32_t* result)
{
	uint32_t A = IV[0];
	uint32_t B = IV[1];
	uint32_t C = IV[2];
	uint32_t D = IV[3];
	uint32_t E = IV[4];
	uint32_t F = IV[5];
	uint32_t G = IV[6];
	uint32_t H = IV[7];
	for (int j = 0;j < 64;j++)
	{
		uint32_t SS1 = Rotate_left(Rotate_left(A, 12) + E + Rotate_left(T[j], j), 7);
		uint32_t SS2 = SS1 ^ Rotate_left(A, 12);
		uint32_t TT1 = (FF(j, A, B, C) + D + SS2 + W_[j]);//%int((pow(2,32)));//这一步出现差错
		uint32_t TT2 = (GG(j, E, F, G) + H + SS1 + W[j]);//%int(pow(2,32));
		D = C;
		C = Rotate_left(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = Rotate_left(F, 19);
		F = E;
		E = P0(TT2);
		//cout << A << " " << B << " " << C << " " << D << " " << E << " " << F << " " << G << " " << H << " " << endl;
	}
	//先按照一轮来

	result[0] = A ^ IV[0];
	result[1] = B ^ IV[1];
	result[2] = C ^ IV[2];
	result[3] = D ^ IV[3];
	result[4] = E ^ IV[4];
	result[5] = F ^ IV[5];
	result[6] = G ^ IV[6];
	result[7] = H ^ IV[7];

	return result;
}
std::pair<int, uint32_t*> SM3(char* input, uint32_t* IV, uint32_t* result)
{
	int length = strlen(input);//why length
	int block_size;
	int padding_size;
	if ((length + 5) % 64 == 0)
	{
		block_size = (length + 5) / 64;
		padding_size = 0;
	}
	else
	{
		block_size = (length + 5) / 64 + 1;
		padding_size = 64 - (length + 5) % 64;
	}
	cout << "输入长度是：" << length << "字节。" << endl;
	cout << "块数目为：" << block_size << endl;
	cout << "填充0x00数目为：" << padding_size << endl;
	char* padding = new char[block_size * 64 + 1];//天才般的想法！！！
	for (int i = 0;i < length;i++)
	{
		padding[i] = input[i];
	}
	padding[length] = 0x80;
	for (int i = length + 1;i < (block_size * 64 - 4);i++)
	{
		padding[i] = 0x00;
	}
	int length_ = 8 * length;
	padding[block_size * 64 - 4] = length_ >> 24;
	padding[block_size * 64 - 3] = (length_ & 0x00ff0000) >> 16;
	padding[block_size * 64 - 2] = (length_ & 0x0000ff00) >> 8;
	padding[block_size * 64 - 1] = (length_ & 0x000000ff);
	//uint32_t* paddedResult = new uint32_t[block_size * 16];
	uint32_t** paddedResult = new uint32_t * [block_size];
	for (int i = 0;i < block_size;i++)
	{
		paddedResult[i] = new uint32_t[16];
	}
	for (int i = 0;i < block_size;i++)
	{
		for (int j = 0;j < 16;j++)
		{
			paddedResult[i][j] = (((uint8_t)padding[64 * i + 4 * j]) << 24) | (((uint8_t)padding[64 * i + 4 * j + 1]) << 16) | (((uint8_t)padding[64 * i + 4 * j + 2]) << 8) | (((uint8_t)padding[64 * i + 4 * j + 3]));
		}
	}
	cout << "填充后的消息：" << endl;
	for (int i = 0;i < block_size;i++)
	{
		Log(paddedResult[i], 16);
		cout << endl;
	}

	for (int i = 0;i < 8;i++)
	{
		temp[i] = IV[i];
	}
	uint32_t* temp_ = temp;

	for (int i = 0;i < block_size;i++)
	{
		//ExpandMessage(paddedResult[i], W, W_);
		//cout << "扩展后的消息：" << endl;
		//Log(W, 68);
		//Log(W_, 64);
		temp_ = Compress(temp_, W, W_, result);//可修改的左值
	}
	Log(result, 8);
	uint32_t* fake_result = new uint32_t[8];
	for (int i = 0;i < 8;i += 4)
	{
		temp[i] = IV[i];
		temp[i + 1] = IV[i + 1];
		temp[i + 2] = IV[i + 2];
		temp[i + 3] = IV[i + 3];
	}
	delete[] padding;
	for (int i = 0; i < block_size; ++i) {
		delete[] paddedResult[i];
	}
	delete[]paddedResult;
	return make_pair(length, fake_result);
}


int main()
{
	cout << "这是快速SM3的代码实现。" << endl;
	char input[] = "abc";
	auto start = std::chrono::high_resolution_clock::now();

	SM3(input, IV, result);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "耗时: " << duration.count() << " 秒" << std::endl;
	//std::cout << "Hash speed:" << (length/duration.count())/1000000<< "MB/s." << endl;
	cin.get();

}
