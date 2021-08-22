```
从字符串里恢复数组等结构
l = eval('[1,2,3]')
但是eval不会对输入进行检查  eval('1_1') -> 11

最好使用以下：
import ast
ast.literal_eval('struct')
遇到不合法的结构会报错

```



```
判断两个map是否相等
map_a == map_b

获得 b中与a不相同的key
[key for key in map_a.keys()&map_b.keys() if map_a[key]!=map_b[key]]
```



```
选择元素创建list
[ i for i in range(5) if i ==2 ]  -> [2]
[ i if i==2 else 5 for i in range(5)] -> [5, 5, 2, 5, 5]
```

```
eval用法
a =  "{'dcn_num':1, 'fc_num':1, 'fcall_size':128, 'dcn_type':'stack'}"
x = eval(a)
type(x) #dict
```



```
* 与 **

单星号（*）：*agrs
将所以参数以元组(tuple)的形式导入：
>>> def foo(param1, *param2):
        print param1
        print param2
>>> foo(1,2,3,4,5)
1
(2, 3, 4, 5)


双星号（**）：**kwargs
将参数以字典的形式导入
>>> def bar(param1, **param2):
        print param1
        print param2
>>> bar(1,a=2,b=3)
1
{'a': 2, 'b': 3}

单星号拆解参数列表：
>>> def foo(bar, lee):
        print bar, lee
>>> l = [1, 2]
>>> foo(*l)
1 2

双星号拆解参数列表：
def tdu(*a,**b):
    print(a)
    print(b)
e=(1,2,3)
ff = {'one':1,'two':2,'three':3}
tdu(**f)
result: (1,2,3)
        {'one':1,'two':2,'three':3}
```



```
字符串格式化
f"/list_tfdata/{COUNTRY}/{args.datedir}/data.tfd.*"
"{} {}".format("hello", "world") 
```

