#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#define BUFFER_SIZE 1024

// 函数：十六进制大整数加法
std::string addHexBigIntegers(const std::string& hexNum1, const std::string& hexNum2) {
    std::string result;

    int carry = 0;
    int i = hexNum1.size() - 1;
    int j = hexNum2.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? hexNum1[i] : '0';
        int digit2 = (j >= 0) ? hexNum2[j] : '0';

        int sum = carry;

        if (isdigit(digit1)) sum += digit1 - '0';
        else sum += 10 + (tolower(digit1) - 'a');

        if (isdigit(digit2)) sum += digit2 - '0';
        else sum += 10 + (tolower(digit2) - 'a');

        carry = sum / 16;
        int remainder = sum % 16;

        if (remainder < 10) result.push_back(remainder + '0');
        else result.push_back('a' + (remainder - 10));

        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    std::reverse(result.begin(), result.end()); // 反转结果字符串，得到正确的顺序

    return result;
}


//SM3算法
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

//对一个数据循环运算n次SM3
std::string sm3_n_times(const std::string& message, int n) {
    if (n == 0)return message;
    if (n < 0) {
        std::cerr << "Error: Invalid value of n. n should be greater than 0." << std::endl;
        return "";
    }

    std::string hash_value = message;
    for (int i = 0; i < n; i++) {
        hash_value = sm3(hash_value);
    }

    return hash_value;
}
//随机生成一个256位的十六进制数
std::string generate_random_string() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);

    std::stringstream ss;
    for (int i = 0; i < 4; i++) {
        uint64_t random_value = dis(gen);
        ss << std::setfill('0') << std::setw(16) << std::hex << random_value;
    }

    return ss.str();
}

//初始化，即生成n个随机数
std::vector<std::string >init_string(int geshu) {
    std::vector<std::string> hello;
    for (int i = 0; i < geshu; i++) {
        hello.push_back(generate_random_string());
    }
    return hello;
}

//用于确定新加入的元素的节点位置的函数
unsigned int Jishu(int number, int length) {
    if (number <= 0) return number;
    int hello = 0;
    for (int middle = length / 2; middle > 0; middle = middle / 2) {
        if ((number & 1) == 1) {
            hello += middle;
        }
        number = number >> 1;
    }
    return hello;
}



// 数据结构大小
const int DATA_SIZE = 64;

// 完全二叉树节点
struct TreeNode {
    std::string data;
    // 构造函数，初始化数据
    TreeNode() : data(std::string(DATA_SIZE, '0')) {}
};

//验证节点是否属于一个二叉树
bool proof(std::vector<std::string> proofarray, std::string value) {
    int sizeproof = proofarray.size();
    std::string middle = value;
    for (int i = 0; i < sizeproof - 1; i++) {
        middle = sm3(addHexBigIntegers(middle, proofarray[i]));
    }
    if (middle == proofarray[sizeproof - 1]) return true;
    else return false;
}
// 完全二叉树类
class SMT {
private:
    int Nodenumber;
    int Paddednumber;
    int depth;
    std::vector<TreeNode> nodes;
public:
    SMT() {
        Nodenumber = 0;
        Paddednumber = 0;
        depth = 0;
    }
    SMT(int depthin, std::string init) {
        // 初始化树节点
        depth = depthin;
        Paddednumber = 0;
        Nodenumber = 1;
        for (int i = 0; i < depth - 1; i++) {
            Nodenumber = Nodenumber * 2;
        }
        nodes.resize(2 * Nodenumber - 1);
        for (int i = 0; i < Nodenumber; i++) {
            nodes[Nodenumber + i - 1].data = init;
        }
        for (int i = Nodenumber - 2; i >= 0; i--) {
            nodes[i].data = sm3(nodes[2 * i + 1].data + nodes[2 * i + 2].data);
        }
    }

    void  init(int depthin, std::string initing) {
        // 初始化树节点
        depth = depthin;
        Paddednumber = 0;
        Nodenumber = 1;
        for (int i = 0; i < depth - 1; i++) {
            Nodenumber = Nodenumber * 2;
        }
        nodes.resize(2 * Nodenumber - 1);
        for (int i = 0; i < Nodenumber; i++) {
            nodes[Nodenumber + i - 1].data = initing;
        }
        for (int i = Nodenumber - 2; i >= 0; i--) {
            nodes[i].data = sm3(nodes[2 * i + 1].data + nodes[2 * i + 2].data);
        }
    }
    // 获取节点数量
    int size() const {
        return nodes.size();
    }

    //获取某一元素的值
    std::string& getData(int position) {
        if (position >= 0 && position < nodes.size()) {
            return nodes[position].data;
        }
        else {
            throw std::out_of_range("Invalid position");
        }
    }

    //加入新元素的函数
    bool add(std::string value) {
        int addnumber = Jishu(Paddednumber, Nodenumber) + Nodenumber - 1;
        Paddednumber += 1;
        if (addnumber >= 0 && addnumber < nodes.size()) {
            nodes[addnumber].data = value;
            for (int i = 0; i < depth - 1; i++) {
                addnumber = (addnumber - 1) / 2;
                //替换为hash函数的加法
                nodes[addnumber].data = sm3(addHexBigIntegers(nodes[2 * addnumber + 1].data, nodes[2 * addnumber + 2].data));
            }
            return true;
        }
        else {
            return false;
        }
    }

    //获得节点证明所需的值列表
    std::vector<std::string> getproof(std::string value) {
        std::vector<std::string> stringsArray;
        int numberhello = 0;
        for (int i = 0; i < Paddednumber; i++) {
            numberhello = Jishu(i, Nodenumber) + Nodenumber - 1;
            if (nodes[numberhello].data == value) break;
        }
        for (int i = 0; i < depth - 1; i++) {
            if ((numberhello & 1) == 1) {
                stringsArray.push_back(nodes[numberhello + 1].data);
            }
            else {
                stringsArray.push_back(nodes[numberhello - 1].data);
            }
            numberhello = (numberhello - 1) / 2;
        }
        stringsArray.push_back(nodes[0].data);
        return stringsArray;
    }

    //打印节点信息
    void printnodes() {
        for (int i = 0; i < nodes.size(); ++i) {
            std::cout << "Node " << i << " Data: " << nodes[i].data << std::endl;
        }
    }

};

//通过MDP算法，获得一个数的证明列表
std::vector<int> MDP(int number, int& weishu) {
    int a = number;
    int wei = 0;
    while (a > 0) {
        a = a / 10;
        wei += 1;
    }
    weishu = wei;
    std::vector<int> fanhui;
    fanhui.push_back(number);
    a = 10;
    int b = number;
    for (int i = 0; i < wei - 1; i++) {
        int c = (b % a) / (a / 10);
        if (c == 9)  continue;
        else {
            b = b - (c + 1) * a / 10;
            fanhui.push_back(b);
        }
        a = a * 10;
    }
    return fanhui;
}

class promise {
private:
    int Havenumber;
    SMT tree;
    std::vector<int> MDPlist;
    std::vector<std::string> seedlist;
    std::vector<std::string> prooflist;
public:
    promise(int number) {
        int weishu = 0;
        MDPlist = MDP(number, weishu);
        seedlist = init_string(weishu + 1);
        int MDPnumber = MDPlist.size();
        int i = 0;
        int y = 1;
        while (y < MDPnumber) {
            y *= 2;
            i++;
        }
        tree.init(i, sm3(seedlist[0]));
        std::string middle1;
        for (int j = 0; j < MDPnumber; j++) {
            int temp = MDPlist[j];
            int beishu = 10;
            std::string middle = "";
            for (int x = 1; x < weishu + 1; x++) {
                int c = (temp % beishu) / (beishu / 10);
                middle += sm3_n_times(seedlist[x], c);
                // std::cout << "sm3ntimes" << " Data: " << sm3_n_times(seedlist[x], c) << '\t' << c << '\t' << j << std::endl;
                beishu = beishu * 10;
            }
            //std::cout <<"MIDDLE: " << middle << '\n';
            tree.add(sm3(middle));
            prooflist.push_back(middle);
        }
    };

    //打印数据
    void printshuju() {
        std::cout << "Havenumber is " << Havenumber << '\n';
        for (int i = 0; i < MDPlist.size(); i++) {
            std::cout << "MDP " << i << " Data: " << MDPlist[i] << std::endl;
        }
        for (int i = 0; i < seedlist.size(); i++) {
            std::cout << "seed " << i << " Data: " << seedlist[i] << std::endl;
        }
        tree.printnodes();
    }

    //在一个promise中获得证明一个数字所需的数据
    bool getproof(std::vector<std::string>& seed, std::vector<std::string>& value, int verify, int& number) {
        int j = 0;
        if (verify > MDPlist[0])return 0;
        if (MDPlist[MDPlist.size() - 1] > verify) {
            j = MDPlist.size();
        }
        else {
            while (MDPlist[j] > verify) {
                j++;
            }
        }
        number = MDPlist[j - 1];
        for (int i = 0; i < seedlist.size() - 1; i++) {
            seed.push_back(seedlist[i + 1]);
        }
        /* for (int i = 0; i < seedlist.size() - 1; i++) {
            std::cout<< prooflist[j-1].substr(i*64,64)<<'\n';
         }*/
        value = tree.getproof(sm3(prooflist[j - 1]));
        return 1;
    }
};

//最终的检验函数
bool verify(std::vector < std::string> seed, std::vector < std::string> valuelist, int& number) {
    std::string middle = "";
    int x = 10;
    for (int i = 0; i < seed.size(); i++) {
        int c = (number % x) / (x / 10);
        middle += sm3_n_times(seed[i], c);
        //std::cout << "ntimes" << " Data: " << sm3_n_times(seed[i], c) << '\t' << c << std::endl;
        x = x * 10;
    }
    //std::cout << "proof"  << " Data: " << middle <<'\t'<<number<< std::endl;
    return  proof(valuelist, sm3(middle));
}
int main() {
    int x;
    //输入A拥有的数字
    std::cout << "Please enter a number that you have:  ";
    std::cin >> x;
    //根据输入的数字生成一个承诺
    promise hello(x);
    // hello.printshuju();
    std::vector < std::string> a;
    std::vector < std::string> b;
    int number = 0;
    int y;
    //输入要证明的数字
    std::cout << "Please enter a number that you want to proof:  ";
    std::cin >> y;
    auto start = std::chrono::high_resolution_clock::now();

    bool abc = hello.getproof(a, b, y, number);
    if (abc) {
        std::cout << verify(a, b, number) << '\n';
    }
    else {
        std::cout << "Your number is small!\n";
    }
    // 获取代码执行后的时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算时间差
    std::chrono::duration<double> elapsed_seconds = end - start;

    // 输出执行时间，以秒为单位
    std::cout << "代码执行时间: " << elapsed_seconds.count() << " 秒" << std::endl;
    std::cout << "MDP列表中证明给数字的数字为：" << number << '\n';
    for (int i = 0; i < a.size(); ++i) {
        std::cout << "seed " << i << " Data: " << a[i] << std::endl;
    }
    for (int i = 0; i < b.size(); ++i) {
        std::cout << "merkle树上的节点" << i << " Data: " << b[i] << std::endl;
    }
    return 0;
}




