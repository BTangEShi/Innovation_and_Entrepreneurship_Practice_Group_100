> ## 原理阐释
> 高级加密标准（英语：Advanced Encryption Standard，缩写：AES），在密码学中又称 Rijndael 加密法，是美国联邦政府采用的一种区块加密标准。这个标准用来替代原先的 DES，已经被多方分析且广为全世界所使用。经过五年的甄选流程，高级加密标准由美国国家标准与技术研究院（NIST）于 2001 年 11 月 26 日发布于 FIPS PUB 197，并在 2002 年 5 月 26 日成为有效的标准。2006 年，高级加密标准已然成为对称密钥加密中最流行的算法之一 AES 具有 128 比特的分组长度，三种可选的密钥长，即 128 比特、192 比特和 256 比特。AES 是一个迭代型密码；轮数 Nr 依赖于密钥长度。如果密钥长度为 128 比特，则 Nr =10；如果密钥长度为 192比特，则 Nr =12；如果密钥长度为 256 比特，则 Nr =14。AES 加密过程是在一个 4×4 的字节矩阵上运作，这个矩阵又称为“状态（state）”，其初值就是一个明文区块（矩阵中一个元素大小就是明文区块中的一个 Byte）。加密时，各轮 AES 加密循环（除最后一轮外）均包含 4 个步骤。
>##
> ## 代码说明
> 我们已经使用c++代码完成了SM3的实现。但是，考虑到攻击的方便性，我们本次实验使用python的gmssl库完成SM3的生日碰撞攻击的实现。并且，通过引入python的hashlib库完成sha256的生日碰撞攻击地实现来进行相应的对照。具体代码细节实现如下：
> 
>    ```python
>     def collision_SHA256(num):
        for item in permutations(ts,5):
            item=''.join(item)
            item=item.encode()
            hash_object = hashlib.sha256(item)
            hex_digest = hash_object.hexdigest()
            value=hex_digest[0:num]
            if(value not in st):
                st[value]=(item,1)
            else:
                print(st[value][0])
                print(item)
                print(SHA256(st[value][0].decode()))
                print(SHA256(item.decode()))
                break
> 
>```python
>    def collision_SHA256(num):
        for item in permutations(ts,5):
            item=''.join(item)
            item=item.encode()
            hash_object = hashlib.sha256(item)
            hex_digest = hash_object.hexdigest()
            value=hex_digest[0:num]
            if(value not in st):
                st[value]=(item,1)
            else:
                print(st[value][0])
                print(item)
                print(value)
                break

>
>
>观察上述代码可知，我们构造了一个由数字和字符组成的字符串，然后通过该字符串生成固定长度为5的字符串。通过遍历固定长度为5的字符串，一定程度上简化了程序的复杂性，而不丧失其正确性。我们通过建立哈希表来存储已经进行计算过的字符串，并通过not in 来检查是否发生了reduced 哈希碰撞。这样虽然使得时间复杂度由pow(2,n)降至pow(2,n/2),但是也将空间复杂度由常数变成了pow(2,n).由此来看，生日攻击属于一种空间换取时间的算法。


>## 结果展示
>8bits
>
>
>![8bits](8bits.png)
>
>
>16bits
>
>
>![16bits](16bits.png)
>
>
>24bits
>
>
>![24bits](24bits.png)
>
>
>32bits
>
>
>![32bits](32bits.png)
>
>
>40bits
>
>
>![40bits](40bits.png)
>
>
>![40bits](40bit.png)
>
>
>44bits
>
>
>![44bits](44bits.png)
>
>
>![44bits](44bit.png)
>
>
>48bits
>
>
>![48bits](48bits.png)
>
>
>52bits
>
>
>![52bits](52bits.png)
>
>



>|        | 8bits  | 16bits | 24bits | 32bits | 40bits |44bits |48bits |52bits |
>|--------|--------|--------|--------|--------|--------|-------|-------|-------|
>| SM3    | 0.036s | 0.154s | 1.307s | 11.736s|782.692s|1850.594s|       |       |
>| SHA256 | 0.026s | 0.024s | 0.026s | 0.127s | 3.806s |3.877s |51.939s|1504.711s|
>
>
>![折线图](Figure_1.png)



