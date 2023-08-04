## 原理阐述
>ECDSA签名和验证算法的流程如下图：
 >![enter image description here](1.png)

 >根据一对合法签名仿造一对签名的原理如下。简单来说就是随机选取u和v来生成新的R，斌根据新的R还有原来的签名，模拟出一个合法签名。原理图如下：
> ![enter image description here](2.png)

