Hadoop fs :

-mkdir /XXX/XXX

查看文件大小
hadoop fs -du -h /filepath

检测是否运行成功

```
head -n1000 pg2701.txt | ./mapper.py | sort | ./reducer.py
```

```
hadoop 底层的map reduce 的详细过程：
mapper阶段：
 1.对数据分片
 2.map程序处理
 3.map的输出进行排序，写入缓冲区 （如果缓冲区满了就写入磁盘
 4.reducer 可能用commbiner合并mapper的输入进行网络io获得数据（也可能combine）
 5.reducer 进行操作
 
 https://zhuanlan.zhihu.com/p/61892781
 
```



