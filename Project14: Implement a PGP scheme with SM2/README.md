> ## 原理阐释
> 密钥协商技术是在安全通信中用于双方或多方在不安全的通信环境中协商和生成共享密钥的一类算法和协议。这些共享密钥可以用于加密通信数据或验证通信的完整性，从而确保通信的保密性和安全性。密钥协商技术在安全通信中起着至关重要的作用，它可以确保通信双方生成的密钥是安全的，并且在通信过程中不容易被攻击者获取。不同的密钥协商技术适用于不同的场景和需求，选择合适的密钥协商技术对于实现安全通信至关重要。   
>密钥协商技术可以分为以下几类：    
>静态密钥交换（Static Key Exchange）：通信双方使用预先共享的密钥进行通信。这些密钥通常在通信双方之间进行安全交换或由信任的第三方实体分发。  
>拉卡斯-鲍尔密钥交换（Lattice-Based Key Exchange）：基于数学问题的困难性，通信双方在不泄露私钥的情况下生成共享密钥。  
>DH（Diffie-Hellman）密钥交换：双方通过在公开信道上传输公共信息生成共享密钥，而不在公开信道上传输私有信息。  


> SM2密钥交换具体实现原理如图所示：
> 
>![enter image description here](1.png)
>
> PGP（Pretty Good Privacy，中文翻译“优良保密协议”）是一个基于RSA体系、将公开密钥加密与传统密钥加密相结合的用于信息加密、验证的商业应用程序，由菲尔·齐默尔曼 (Philip R. Zimmermann) 于1991年开发完成并发布。自发布以来，PGP凭借其可以运行于多种操作系统平台、其加密算法得到普遍认可、具有广泛的应用场景等特性使得PGP的应用领域迅速扩大，同时使PGP自身也得到了更好的发展。
> PGP技术具体实现原理如下：
>
> ![enter image description here](3.png)
>
> 
> ## 代码说明
> 我们通过构建CS模式来实现真实网络通信中的SM2密钥协商，代码细节实现如下：
> 
> 客户端A
> 
>    ```python
>     while True:
      cv     = Curve.get_curve('secp256k1')
      n=cv.order
      G=cv.generator
      pv_keyA = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,
                              cv)
      pu_keyA=pv_keyA.get_public_key()
      print("A的公钥是:",pu_keyA.W)
      dA=pv_keyA.d
      rA=ecrand.rnd(n-1)
      RA=rA*G
      S.send(serialize_dict({"data":cv.encode_point(RA),"keyx":pu_keyA.W.x,"keyy":pu_keyA.W.y}))
      x1=RA.x
      y1=RA.y
      w=math.ceil(math.ceil(math.log(n,2))/2)-1
      x1_=pow(2,w)+(x1&(pow(2,w)-1))
      tA=(dA+x1_*rA)%n
        
      data=S.recv(1024)
      message=deserialize_dict(data)
      RB=cv.decode_point(message['data'])
      print("RB",RB)
      pu_keyB=Point(message["keyx"],message["keyy"],cv)
      print("B的公钥是:",pu_keyB)
      if(cv.is_on_curve(RB)==False):
              print("RB不满足椭圆方程")
              break
      x2=RB.x
      y2=RB.y
      x2_=pow(2,w)+(x2&(pow(2,w)-1))
    
      U=tA*(pu_keyB+x2_*RB)
    
      print("U",U)
      xU=U.x
      yU=U.y
      encryptor=SM2("BTUPLE")
      KA=encryptor.KDF(bin(xU)[2:]+bin(yU)[2:],128)
      S1=hashlib.sha256((bin(xU)[2:]+bin(yU)[2:]).encode()).hexdigest()
      print("S1",S1)
      data=S.recv(1024)
      message=deserialize_dict(data)
      SB=(message['data'])
      if(S1==SB):
          print("密钥协商成功")
      else:
          print("密钥协商失败")
> 
>服务器端B
> 
>    ```python
>      while True:
        cv     = Curve.get_curve('secp256k1')
        n=cv.order
        G=cv.generator
        pv_keyB = ECPrivateKey(0xeb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,
                              cv)
        pu_keyB=pv_keyB.get_public_key()
        print("B的公钥是:",pu_keyB.W)
        dB=pv_keyB.d
        rB=ecrand.rnd(n-1)
        RB=rB*G
        print("RB",RB)
        conn.send(serialize_dict({"data":cv.encode_point(RB),"keyx":pu_keyB.W.x,"keyy":pu_keyB.W.y}))
        x2=RB.x
        y2=RB.y
        w=math.ceil(math.ceil(math.log(n,2))/2)-1
        x2_=pow(2,w)+(x2&(pow(2,w)-1))
        tB=(dB+x2_*rB)%n
        
        data=conn.recv(1024)
        message=deserialize_dict(data)
        pu_keyA=Point(message["keyx"],message["keyy"],cv)
        print("A的公钥是:",pu_keyA)
        RA=cv.decode_point(message['data'])
        print("RA",RA)
        if(cv.is_on_curve(RA)==False):
            print("RA不满足椭圆方程")
            break
        x1=RA.x
        y1=RA.y
        x1_=pow(2,w)+(x1&(pow(2,w)-1))
    
        V=tB*(pu_keyA+x1_*RA)

        
        print("V",V)
        xV=V.x
        yV=V.y
        encryptor=SM2("BTUPLE")
        KB=encryptor.KDF(bin(xV)[2:]+bin(yV)[2:],128)
        SB=hashlib.sha256((bin(xV)[2:]+bin(yV)[2:]).encode()).hexdigest()
        print("SB",SB)
        conn.send(serialize_dict({"data":SB}))
        break
> 
>观察上述代码可知，我们通过生成随机数rA和rB,将其与A、B方的私钥与公钥结合，最终形成固定长度的会话密钥。整个过程基本类似于DH协议。但观察PPT上的PGP可知，会话密钥是发送者随机生成的。对此，我有点疑惑不解。同时，我还是按照PPT我理解的原意，实现了PGP。当然，也并没有落下SM2密钥协商协议的实现。PGP的代码已经写好放在SM2密钥交换.py文件，不在md文档进行展示。

>## 结果展示
>密钥协商结果展示：
>
>服务器端（用户B）
>
>![](B.png)
>
>
>客户端（用户A）
>
>
>![](A.png)
>
>
>PGP展示
>
>
>![](2.png)
>
>






