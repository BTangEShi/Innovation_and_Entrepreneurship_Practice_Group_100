#include<iostream>
#include <iomanip>
#include <chrono>
using namespace std;
uint32_t W[68];
uint32_t W_[64];
uint32_t IV[] = { 0x7380166f ,0x4914b2b9 ,0x172442d7 ,0xda8a0600 ,0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e };
uint32_t result[8];
uint32_t T[64];
char fake_input[100];
uint32_t temp[8];
uint32_t paddedResult[] = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,0x00000000, 0x00000000 };
uint32_t IV1[] = { 0x6c781f1a,0x541010aa,0xa20d9999,0xb963be0a,0xd34bcbdc,0xafa43bc0,0x9ec49c19,0x9f0e45e7 };
void Log(uint32_t* ts, int num)
{
    for (int i = 0;i < num;i++)
    {
        cout <<"0x"<< setfill('0') << setw(8) << hex << ts[i] << ",";
    }
    cout << endl;
}
uint32_t buildIntWithKOnes(uint32_t k)
{
    uint32_t result = 0;

    for (int i = 0; i < (32 - k); i++) {
        result |= (1 << i);
    }
    return ~result;
}

uint32_t Rotate_left(uint32_t W, uint32_t number)//传值
{
    uint32_t temp = buildIntWithKOnes(number % 32);
    uint32_t temp_ = ~temp;
    //获得前k比特
    uint32_t temp1 = temp & W;
    uint32_t temp1_ = temp1 >> (32 - number % 32);
    //获得后面比特
    uint32_t temp2 = temp_ & W;
    uint32_t temp2_ = temp2 << number % 32;

    uint32_t result = temp1_ | temp2_;
    return result;
}
uint32_t P1(uint32_t temp)
{
    return temp ^ Rotate_left(temp, 15) ^ Rotate_left(temp, 23);
}
void ExpandMessage(uint32_t* paddedResult, uint32_t* W, uint32_t* W_)
{
    for (int i = 0;i < 16;i++)
    {
        W[i] = paddedResult[i];
    }
    for (int i = 16;i < 68;i++)
    {
        uint32_t temp = W[i - 16] ^ W[i - 9] ^ (Rotate_left(W[i - 3], 15));
        //if (i == 16)cout << hex << temp <<endl;
        uint32_t fake = Rotate_left(W[i - 13], 7);
        //if (i == 16)cout << hex << fake << endl;
        //if (i == 16)cout << hex << P1(temp);
        W[i] = P1(temp) ^ (fake) ^ W[i - 6];
        //if (i == 16)cout <<hex<< W[i];
    }
    for (int i = 0;i < 64;i++)
    {
        W_[i] = (W[i] ^ W[i + 4]);
    }
}
void transform(char* input, char* fake_input, uint32_t* paddedResult)//这个函数问题最大！！！
{
    int i = 0;
    while (input[i] != '\0')
    {
        fake_input[i] = input[i];
        i++;
    }
    fake_input[i] = 0x80;
    int length = 8 * i;
    for (int j = i + 1;j < 60;j++)
    {
        fake_input[j] = 0x00;
    }
    fake_input[60] = length >> 24;
    fake_input[61] = (length & 0x00ff0000) >> 16;
    fake_input[62] = (length & 0x0000ff00) >> 8;
    fake_input[63] = (length & 0x000000ff);
    for (int j = 0;j < 16;j++)
    {
		//消息填充都有bug
        paddedResult[j] = ((uint32_t)fake_input[4 * j] << 24) | ((uint32_t)fake_input[4 * j + 1] << 16) | ((uint32_t)fake_input[4 * j + 2] << 8) | ((uint32_t)fake_input[4 * j + 3]);
    }
}
void ExpandT(uint32_t* T)
{
	for (int i = 0;i < 16;i++)
	{
		T[i] = 0x79cc4519;
	}
	for (int i = 16;i < 64;i++)
	{
		T[i] = 0x7a879d8a;
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
std::pair<int,uint32_t*> SM3(char*input,uint32_t*IV,uint32_t*result)
{
	ExpandT(T);
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
	//cout << "填充后的消息：" << endl;
	/*
	for (int i = 0;i < block_size;i++)
	{
		Log(paddedResult[i], 16);
		cout << endl;
	}*/

	//uint32_t* temp = IV;
	//uint32_t temp[8]{ 0 };//ERROR
	/*
	for (int i = 0;i < 8;i++)
	{
		temp[i] = IV[i];
	}*/
	//uint32_t temp[] = { 0x7380166f ,0x4914b2b9 ,0x172442d7 ,0xda8a0600 ,0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e };
	//uint32_t temp[8];
	for (int i = 0;i < 8;i++)
	{
		temp[i] = IV[i];
	}
	uint32_t* temp_ = temp;

	for (int i = 0;i < block_size;i++)
	{
		ExpandMessage(paddedResult[i], W, W_);
		//cout << "扩展后的消息：" << endl;
		//Log(W, 68);
		//Log(W_, 64);
		temp_ = Compress(temp_, W, W_, result);//可修改的左值
	}
	Log(result, 8);
	uint32_t* fake_result = new uint32_t[8];
	for (int i = 0;i < 8;i++)
	{
		fake_result[i] = result[i];
	}
	delete[] padding;
	for (int i = 0; i < block_size; ++i) {
		delete[] paddedResult[i];
	}
	delete[]paddedResult;
	return make_pair(length, fake_result);
}
/*
void length_expand_attack()
{
	ExpandT(T);
	uint32_t paddxing[2][8] = { { 0x32303231,0x30303436,0x30313230,0x80000000,0x00000000,0x00000000,0x00000000,0x00000060 },
		{0x61626380,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000218} };
	for (int i = 0;i < 8;i++)
	{
		temp[i] = IV[i];
	}
	uint32_t* temp_ = temp;

	for (int i = 0;i < 2;i++)
	{
		ExpandMessage(paddxing[i], W, W_);
		//cout << "扩展后的消息：" << endl;
		//Log(W, 68);
		//Log(W_, 64);
		temp_ = Compress(temp_, W, W_, result);//可修改的左值
	}
	Log(result, 8);
}*/
/*
int main()
{
	
	//length_expand_attack();
	char s3[100] = "202100460120";
	uint32_t *jkl=SM3(s3, IV,result).second;//再执行一次SM3，jkl会变的
	char s4[100] = "abc";
	SM3(s4, IV,result);
	SM3(s4, jkl,result);
	ExpandT(T);
	uint32_t paddxing[2][16] = { { 0x32303231,0x30303436,0x30313230,0x80000000,0x00000000,0x00000000,
		0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000060 },
		{0x61626380,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
		0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000018} };
	uint32_t temp1[8];
	for (int i = 0;i < 8;i++)
	{
		temp1[i] = IV[i];
	}
	uint32_t* temp_ = temp1;

	for (int i = 0;i < 2;i++)
	{
		ExpandMessage(paddxing[i], W, W_);
		temp_ = Compress(temp_, W, W_, result);//可修改的左值
		
	}
	cout << "构造的信息对应的哈希值是：";
	Log(result, 8);
	cin.get();

	
}*/

int main()
{
	char input[] = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdvabcdabcdabcdabcdabcd";
	auto start = std::chrono::high_resolution_clock::now();
	SM3(input,IV,result);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "耗时: " << duration.count() << " 秒" << std::endl;
	//std::cout << "Hash speed:" << (length/duration.count())/1000000<< "MB/s." << endl;
	cin.get();
	
}
