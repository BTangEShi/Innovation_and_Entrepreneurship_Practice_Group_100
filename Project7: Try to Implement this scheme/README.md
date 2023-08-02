> # 原理阐述
> ## Generalizing Hashchains
> 在这一步中我们将project6中的方案以某种方式拆分单个链。即原来对某一个数字（记作承诺数）的验证只有一个链，现在转化为该数字的每一位都有一个hash链。
>
> ![enter image description here](1.png)
>
> 但如果只是简单的按照位划分成几个hash链，对于哪些低位比该数字大的、但高位小的数，我们将无法验证。因为我们的低位的hash链只到我们有个承诺数在该位的值，而没有到该进制中每一位的上限。\
> 如在下图中，我们无法只用上述办法证明13997大于1599，因为13997个位上的7小于1599个位上的9.
>
> ![enter image description here](2.png)
>
> ## Minimum Dominating Partitions
> 针对上面的情况，我们需要对承诺数生成多个hash多链。即对一个承诺数，我们生成一个列表，列表内容为它本身以及比其小的中最大的且后面i位均为9的递减数列（i取遍1到承诺数的位数，若有重复，只算其中一个）。\
> 举例如下:
>
> ![enter image description here](3.png)
