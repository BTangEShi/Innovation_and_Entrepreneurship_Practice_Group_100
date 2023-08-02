# 工作原理
## 阐释
Actually, it is not possible to uniquely recover the public key from an ECDSA signature (r,s). This remains true even if we also assume you know the curve, the hash function used, and you also have the message that was signed.
However, with the signature and the message that was signed, and the knowledge of the curve, it is possible to generate two public keys; one of which will be the public key corresponding to the private key used.
## 具体流程
First, you find the two points R, R′ which have the value r as the x-coordinate r.  
You also compute r−1, which is the multiplicative inverse of the value r from the signature (modulo the order of the generator of the curve).  
Then, you compute z which is the lowest n bits of the hash of the message (where n is the bit size of the curve).  
Then, the two public keys are r−1(sR−zG)and r−1(sR′−zG).  
It is easy to verify that if you plug either of these values in the ECDSA signature routines as the public keys, the signature validates.  
图示如下：

# 实例
## 具体的以太坊交易
在这种情况下，我们将创建一个随机私钥，然后派生公钥。接下来，我们将为给定的数据值生成一个ECDSA签名，然后使用两种方法（SigToPub和Ecrecover）恢复公钥。

以下代码用于从数据创建SHA-3哈希，然后使用私钥进行签名：

然后，密钥的恢复只需要通过以下方式实现：

## 代码实现
>package main
>
>// Taken from example here: https://stackoverflow.com/questions/51111605/how-do-i-recover-ecdsa-public-key-correctly-from-hashed-message-and-signature-in
>import (
> "bytes"
>	"crypto/rand"
>	"encoding/hex"
>	"fmt"
>	"os"
>
>	"github.com/ethereum/go-ethereum/crypto"
>)
>
>func randomHex(n int) (string, error) {
>	bytes := make([]byte, n)
>	if _, err := rand.Read(bytes); err != nil {
>		return "", err
>	}
>	return hex.EncodeToString(bytes), nil
>}
>
>func main() {
>
>	argCount := len(os.Args[1:])
>
>	msg := "hello"
>	if argCount > 0 {
>		msg = os.Args[1]
>	}
>
>	data := []byte(msg)
>
>	getAddr, _ := randomHex(32)
>
>	privateKey, _ := crypto.HexToECDSA(getAddr)
>	fmt.Printf("Private key: %s\n", getAddr)
>	fmt.Printf("Message to sign: %s\n", msg)
>
>	publicKey := privateKey.PublicKey
>
>	publicKeyBytes := crypto.FromECDSAPub(&publicKey)
>
>	hash := crypto.Keccak256Hash(data)
>	fmt.Printf("Hash: %x\n", hash.Bytes())
>
>	fmt.Printf("\n=== Now using Ecrecover ===\n")
>	signature, _ := crypto.Sign(hash.Bytes(), privateKey)
>
>	fmt.Printf("ECDSA Signature: %x\n", signature)
>	fmt.Printf("  R: %x\n", signature[0:32]) // 32 bytes
>	fmt.Printf("  S: %x\n", signature[32:64]) // 32 bytes
>	fmt.Printf("  V: %x\n", signature[64:])
>
>	sigPublicKey, _ := crypto.Ecrecover(hash.Bytes(), signature)
>
>	fmt.Printf("\nOriginal public key: %x\n", publicKeyBytes)
>fmt.Printf("Recovered public key: %x\n", sigPublicKey)
>
>	rtn := bytes.Equal(sigPublicKey, publicKeyBytes)
>
>	if rtn {
>		fmt.Printf("Public keys match\n\n")
>	}
>
>	fmt.Printf("\n=== Now using FromECDSAPub ===\n")
>	sigPublicKeyECDSA, _ := crypto.SigToPub(hash.Bytes(), signature)
>
>	sigPublicKeyBytes := crypto.FromECDSAPub(sigPublicKeyECDSA)
>	rtn = bytes.Equal(sigPublicKeyBytes, publicKeyBytes)
>
>	fmt.Printf("Original public key: %x\n", publicKeyBytes)
>	fmt.Printf("Recovered public key: %x\n", sigPublicKeyBytes)
>
>	if rtn {
>		fmt.Printf("Public keys match\n\n")
>	}
>
>	signatureNoRecoverID := signature[:len(signature)-1]
>	verified := crypto.VerifySignature(publicKeyBytes, hash.Bytes(), signatureNoRecoverID)
>	fmt.Println(verified)
>}
## 结果展示
