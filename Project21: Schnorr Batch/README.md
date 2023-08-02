## Schnorr
In cryptography, a Schnorr signature is a digital signature produced by the Schnorr signature algorithm that was described by Claus Schnorr. It is a digital signature scheme known for its simplicity, among the first whose security is based on the intractability of certain discrete logarithm problems. It is efficient and generates short signatures.[1] It was covered by U.S. Patent 4,995,082 which expired in February 2008.
### sign
#### 实现流程
![enter image description here](11.png)

#### 对应代码实现
![enter image description here](12.png)

### verify
#### 实现流程
![enter image description here](21.png)

#### 对应代码实现
![enter image description here](22.png)

### batch verification
#### 实现流程
![enter image description here](31.png)

#### 对应代码实现
![enter image description here](32.png)

#### 速度展示
![enter image description here](1.png) 

![enter image description here](2.png)

![enter image description here](chart.png)












