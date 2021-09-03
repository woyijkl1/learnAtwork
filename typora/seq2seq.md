### pointer-network

https://zhuanlan.zhihu.com/p/73590690

<img src="/Users/rongdi.yin/Library/Application Support/typora-user-images/image-20210901185145510.png" alt="image-20210901185145510" style="zoom:67%;" />

```
pointer network 实际上就是输出与输入序列等长的label vec，用这个label vec里面概率最大的一个当做当前步骤的指针--pointer。

```

![image-20210901185345068](/Users/rongdi.yin/Library/Application Support/typora-user-images/image-20210901185345068.png)

```
copynet 相当于把输入的seq的词加入了整体的词表，获得了直接复制输入单词的功能，缓解了oov问题
```

