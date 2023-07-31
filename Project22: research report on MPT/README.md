# 什么是MPT？
Patricia Merkle Tries combine a radix trie with a Merkle tree to store key-value pairs and verify data integrity, ideal for editing and storing ephemeral data.
## Patricia??
P = Practical  
A = Algorithm  
T = To  
R = Retrieve  
I = Information  
C = Coded  
I = In  
A = Alphanumeric  
为什么需要MPT？
There are typically two different types of data:
Permanent
Once a transaction occurs, that record is sealed forever.
This means that once you locate a transaction in a block’s transaction trie, you can return to the same path over and over to retrieve the same result
Ephemeral
In the case of Ethereum, account states change all the time! (ie. A user receives some ether, interacts with a contract, etc)
nonce, balance, storageRoot, codeHash
It makes sense that permanent data, like mined transactions, and ephemeral data, like Ethereum accounts (balance, nonce, etc), should be stored separately. Merkle trees, again, are perfect for permanent data. PMTs are perfect for ephemeral data, which Ethereum is in plenty supply of.
Unlike transaction history, Ethereum account state needs to be frequently updated. The balance and nonce of accounts is often changed, and what’s more, new accounts are frequently inserted, and keys in storage are frequently inserted and deleted.
# MPT的工作原理原理
## 基本键值映射
>type Trie interface {  
>  // methods as a basic key-value mapping  
>  Get(key []byte) ([]byte, bool) {  
>  Put(key []byte, value []byte)  
>  Del(key []byte, value []byte) bool  
> }
## 验证数据完整性  
> type Trie interface {  
> // compute the merkle root hash for verifying data integrity  
>  Hash() []byte  
>}
## 验证是否包含键值对
> type Proof interface {}  
>  
>type Trie interface {  
> // generate a merkle proof for a key-value pair for verifying the inclusion of the key-value pair  
> Prove(key []byte) (Proof, bool)  
>}  
>// verify the proof for the given key with the given merkle root hash  
>func VerifyProof(rootHash []byte, key []byte, proof Proof) (value []byte, err error)  ># 内部构造
trie有4种类型的节点：EmptyNode，LeafNode，BranchNode和ExtensionNode。每个节点将被编码并作为键值对存储在键值存储中。
# 具体实例
## 关键信息阐述
> 主网区块10593417
> 四笔交易
> 交易根哈希：0xab41f886be23cd786d8a69a72b0f988ea72e0b2e03970d0798f5e03763a442cc
> 键值对存储
>>(80, f8ab81a5852e90edd00083012bc294a3bed4e1c75d00fa6f4e5e6922db7261b5e9acd280b844a9059cbb0000000000000000000000008bda8b9823b8490e8cf220dc7b91d97da1c54e250000000000000000000000000000000000000000000000056bc75e2d6310000026a06c89b57113cf7da8aed7911310e03d49be5e40de0bd73af4c9c54726c478691ba056223f039fab98d47c71f84190cf285ce8fc7d9181d6769387e5efd0a970e2e9)
>>(01, f8ab81a6852e90edd00083012bc294a3bed4e1c75d00fa6f4e5e6922db7261b5e9acd280b844a9059cbb0000000000000000000000008bda8b9823b8490e8cf220dc7b91d97da1c54e250000000000000000000000000000000000000000000000056bc75e2d6310000026a0d77c66153a661ecc986611dffda129e14528435ed3fd244c3afb0d434e9fd1c1a05ab202908bf6cbc9f57c595e6ef3229bce80a15cdf67487873e57cc7f5ad7c8a)
>>(02, f86d8229f185199c82cc008252089488e9a2d38e66057e18545ce03b3ae9ce4fc360538702ce7de1537c008025a096e7a1d9683b205f697b4073a3e2f0d0ad42e708f03e899c61ed6a894a7f916aa05da238fbb96d41a4b5ec0338c86cfcb627d0aa8e556f21528e62f31c32f7e672)
>>(03, f86f826b2585199c82cc0083015f9094e955ede0a3dbf651e2891356ecd0509c1edb8d9c8801051fdc4efdc0008025a02190f26e70a82d7f66354a13cda79b6af1aa808db768a787aeb348d425d7d0b3a06a82bd0518bc9b69dc551e20d772a1b06222edfc5d39b6973e4f4dc46ed8b196)
## 图片展示
### 空
### 添加第一个事务
### 添加第二个事务
### 添加第三个事务
### 添加第四个事务
